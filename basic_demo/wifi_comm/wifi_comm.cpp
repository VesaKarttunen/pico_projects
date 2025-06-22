// Own
#include "wifi_comm.hpp"

// Pico-SDK
#include "pico/cyw43_arch.h"

// lwIP
#include "lwipopts.h"
// Preven clan-format reordering
#include "lwip/sockets.h"
#include "lwip/sys.h"

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
        std::array<char, 64> message = {};

        int count_bytes_received = lwip_read(socket,
                                             message.data(),
                                             sizeof(message));

        if (count_bytes_received <= 0)
        {
            printf("Reading from the TCP socket failed. Closing the socket.\n");
            break;
        }
        else if (static_cast<uint32_t>(count_bytes_received) == sizeof(message))
        {
            printf("Received message: %s\n", message.data());
        }
        else
        {
            printf("Received less bytes than expected from the socket. Discard message.\n");
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
        xTaskDelayUntil(&ticks_previous_wake, pdMS_TO_TICKS(2000));

        std::string_view message = "Hello world";

        int count_bytes_sent = lwip_write(socket,
                                          message.data(),
                                          message.size());

        if (count_bytes_sent <= 0)
        {
            printf("Writing into the TCP socket failed. Closing the socket.\n");
            break;
        }
        else if (static_cast<unsigned>(count_bytes_sent) < message.size())
        {
            printf("Wrote less bytes than expected into the socket\n");
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
    bool is_error        = socket_listening < 0;

    if (is_error)
    {
        printf("Creating listening socket failed\n");
        return;
    }

    sockaddr_in address     = {};
    address.sin_family      = AF_INET;
    address.sin_port        = htons(f_socket_port);
    address.sin_addr.s_addr = INADDR_ANY;

    int status_bind = lwip_bind(socket_listening,
                                reinterpret_cast<sockaddr*>(&address),
                                sizeof(address));

    is_error = status_bind < 0;

    if (is_error)
    {
        printf("Binding socket failed\n");
        return;
    }

    int status_listen = lwip_listen(socket_listening, 0);
    is_error          = status_listen < 0;

    if (is_error)
    {
        printf("Socket failed to start listening incoming connection\n");
        return;
    }

    while (true)
    {
        int socket_new = lwip_accept(socket_listening, nullptr, nullptr);
        is_error       = socket_new < 0;

        // Successful new socket connection
        if (!is_error)
        {
            printf("New socket connection accepted\n");

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
        else
        {
            printf("Socket failed to accept incoming connection\n");
        }
    }
}

// This init needs to be executed in a RTOS task because of it will also initialize
// lwIP stack which requires it or the init will fail.
void WifiComm::Init()
{
    cyw43_arch_init();
    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");

    // Wi-Fi SSID and password are given as command line arguments in cmake configuration step:
    // $ cmake -G "Ninja" -S <source-dir> -D WIFI_SSID=<ssid> -D WIFI_PASSWORD=<password>
    // Never write the password into source code directly!
    int error_code = cyw43_arch_wifi_connect_timeout_ms(SECRET_WIFI_SSID,
                                                        SECRET_WIFI_PASSWORD,
                                                        CYW43_AUTH_WPA2_AES_PSK,
                                                        30'000u);

    bool is_connection_successful = error_code == 0;

    if (is_connection_successful)
    {
        printf("Wi-Fi connected successfully\n");
    }
    else
    {
        printf("Wi-Fi connection failed\n");
    }

    printf("Starting TCP socket server at:\n");
    printf("IP: %s; Port %u\n", ip4addr_ntoa(netif_ip4_addr(netif_list)), f_socket_port);

    sys_thread_new("TaskCreateSocket",
                   TaskCreateSocket,
                   nullptr,
                   DEFAULT_THREAD_STACKSIZE,
                   2);
}
