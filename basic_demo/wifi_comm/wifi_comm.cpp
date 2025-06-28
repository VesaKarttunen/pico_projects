// Own
#include "wifi_comm.hpp"

// Local-project
#include "app_command/app_command.hpp"
#include "app_feedback/app_feedback.hpp"

// Pico-SDK
#include "pico/cyw43_arch.h"

// lwIP
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwipopts.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

// STD
#include <array>
#include <cstdio>
#include <string_view>

static constexpr uint16_t f_socket_port = 1234u;

// Own separate task is creater for each new connection
static void TaskReceiveComm(void* p)
{
    // Socket descriptor value is just int number that is passed through void pointer
    int socket = *static_cast<int*>(p);

    while (true)
    {
        std::array<char, 64> command_buffer = {};

        int count_bytes_received = lwip_read(socket,
                                             command_buffer.data(),
                                             sizeof(command_buffer));

        if (count_bytes_received <= 0)
        {
            std::printf("Reading from the TCP socket failed. Closing the socket.\n");
            break;
        }
        else
        {
            AppCommand::ProcessCommand(command_buffer.data());
        }
    }

    lwip_close(socket);
    vTaskDelete(nullptr);
}

// Own separate task is creater for each new connection
static void TaskSendComm(void* p)
{
    // Socket descriptor value is just int number that is passed through void pointer
    int socket = *static_cast<int*>(p);

    TickType_t ticks_previous_wake = xTaskGetTickCount();

    while (true)
    {
        xTaskDelayUntil(&ticks_previous_wake, pdMS_TO_TICKS(1000));

        FeedbackFrame feedback_frame = AppFeedback::GetData();

        int count_bytes_sent = lwip_write(socket,
                                          &feedback_frame,
                                          sizeof(feedback_frame));

        if (count_bytes_sent <= 0)
        {
            std::printf("Writing into the TCP socket failed. Closing the socket.\n");
            break;
        }
    }

    lwip_close(socket);
    vTaskDelete(nullptr);
}

static void TaskCreateSocket(void* p)
{
    (void)p;

    int socket_listening = lwip_socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address     = {};
    address.sin_family      = AF_INET;
    address.sin_port        = htons(f_socket_port);
    address.sin_addr.s_addr = INADDR_ANY;

    lwip_bind(socket_listening,
              reinterpret_cast<sockaddr*>(&address),
              sizeof(address));

    lwip_listen(socket_listening, 0);

    while (true)
    {
        int socket_new = lwip_accept(socket_listening, nullptr, nullptr);

        // Successful new socket connection
        if (socket_new >= 0)
        {
            std::printf("New socket connection accepted\n");

            // Create tasks to handle sending and receiving data with the socket
            sys_thread_new("TaskReceiveComm",
                           TaskReceiveComm,
                           &socket_new,
                           DEFAULT_THREAD_STACKSIZE,
                           2);

            sys_thread_new("TaskSendComm",
                           TaskSendComm,
                           &socket_new,
                           DEFAULT_THREAD_STACKSIZE,
                           2);
        }
    }
}

// This init needs to be executed in a RTOS task because of it will also initialize
// lwIP stack which requires it or the init will fail.
void WifiComm::Init()
{
    cyw43_arch_init();
    cyw43_arch_enable_sta_mode();

    std::printf("Connecting to Wi-Fi...\n");

    // Wi-Fi SSID and password are given as command line arguments in cmake configuration step:
    // $ cmake -G "Ninja" -S <source-dir> -D WIFI_SSID=<ssid> -D WIFI_PASSWORD=<password>
    // Never write the password into source code directly!
    int status = cyw43_arch_wifi_connect_timeout_ms(SECRET_WIFI_SSID,
                                                    SECRET_WIFI_PASSWORD,
                                                    CYW43_AUTH_WPA2_AES_PSK,
                                                    30'000u);

    if (status == PICO_OK)
    {
        std::printf("Wi-Fi connected successfully!\n");
    }
    else
    {
        std::printf("Wi-Fi connection failed with error code: %i\n", status);
    }

    std::string_view ip_address = ip4addr_ntoa(netif_ip4_addr(netif_list));
    std::printf("Starting TCP socket server:\n");
    std::printf("IP:   %s\n", ip_address.data());
    std::printf("Port: %u\n", f_socket_port);

    sys_thread_new("TaskCreateSocket",
                   TaskCreateSocket,
                   nullptr,
                   DEFAULT_THREAD_STACKSIZE,
                   2);
}
