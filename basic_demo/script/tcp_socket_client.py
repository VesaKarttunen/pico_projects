import matplotlib.pyplot    as plt
import matplotlib.animation as anim
import socket
import struct
import threading
import time
import queue

queue_command  = queue.Queue()
queue_feedback = queue.Queue()

supported_str_args = {"FALSE"   : 0.0,
                      "TRUE"    : 1.0,
                      "OFF"     : 0.0,
                      "ON"      : 1.0,
                      "BLINKING": 2.0}

def GetUserCommandToSend():
    while True:
        command = input("Type command...\n")

        command_tokens = command.replace(" ", "").split(";")
        count_tokens_in_valid_command = 2

        if len(command_tokens) == count_tokens_in_valid_command:
            command_name = command_tokens[0]
            argument_str = command_tokens[1]

            if command_name.isidentifier():
                if argument_str in supported_str_args:
                    argument_float = supported_str_args[argument_str]
                    command_parsed = (command_name, argument_float)
                elif argument_str.replace(".", "", 1).isdigit():
                    argument_float = float(argument_str)
                    command_parsed = (command_name, argument_float)
                else:
                    print("Invalid command!")
            else:
                print("Invalid command!")
        else:
            print("Invalid command!")

        if command_parsed:
            queue_command.put(command_parsed)

# Create and start the thread
thread_get_user_command = threading.Thread(target=GetUserCommandToSend, daemon=True)
thread_get_user_command.start()

ip_address_pico  = "192.168.101.197"
port_socket_pico = 1234

# Connect TCP socket with configured settings
socket_pico = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_pico.connect((ip_address_pico, port_socket_pico))

def ReceiveFeedbackFromSocket():
    while True:
        count_recv_bytes = 8
        data_raw = socket_pico.recv(count_recv_bytes)
        data_converted = struct.unpack("<2f", data_raw)
        queue_feedback.put(data_converted)

# Create and start the thread
thread_receive_feedback = threading.Thread(target=ReceiveFeedbackFromSocket, daemon=True)
thread_receive_feedback.start()

def SendCommandToSocket():
    while True:
        if (not queue_command.empty()):
            command_name, argument = queue_command.get()
            data_raw = struct.pack("<64s1f", command_name.encode(), argument)
            socket_pico.sendall(data_raw)
        else:
            time.sleep(0.1)

thread_send_command = threading.Thread(target=SendCommandToSocket, daemon=True)
thread_send_command.start()

# Plot feedback data received from Pico
fig, axis = plt.subplots(1, 1)
fig.set_tight_layout(True)
line_object = axis.plot([], [])
axis.grid()

plt.title("Feedback data received from Pico")
plt.xlabel("Time [s]")
plt.ylabel("Temperature [C]")

x_axis_data = []
y_axis_data = []

# Update function for animation
def UpdateAnimation(frame_number):
    while (not queue_feedback.empty()):
        time_s, temperature_C = queue_feedback.get()
        x_axis_data.append(time_s)
        y_axis_data.append(temperature_C)

    if len(x_axis_data) >= 2:
        axis.relim()
        axis.autoscale_view()
        axis.set_xlim(x_axis_data[0], x_axis_data[-1])
        line_object[0].set_data(x_axis_data, y_axis_data)

    return line_object

plot_animation = anim.FuncAnimation(fig      = fig,
                                    func     = UpdateAnimation,
                                    interval = 1000,
                                    blit     = False,
                                    cache_frame_data = False)

plt.show()
socket_pico.close()
