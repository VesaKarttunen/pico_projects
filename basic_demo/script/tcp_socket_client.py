import matplotlib.pyplot    as plt
import matplotlib.animation as anim
import socket
import struct
import threading
import time
import queue

queue_command = queue.Queue()
queue_plot_data    = queue.Queue()

def GetUserCommandToSend():
    while True:
        command_to_send = input("Type command...\n")
        queue_command.put(command_to_send)

# Create and start the thread
get_user_command_thread = threading.Thread(target=GetUserCommandToSend, daemon=True)
get_user_command_thread.start()

ip_address_pico  = "192.168.101.197"
port_socket_pico = 1234

# Connect TCP socket with configured settings
socket_pico = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_pico.connect((ip_address_pico, port_socket_pico))

def ReceiveDataFromTcpSocket():
    while True:
        count_recv_bytes = 8
        data_raw = socket_pico.recv(count_recv_bytes)

        # Convert received raw bits to actual data types
        data_converted = struct.unpack("<2f", data_raw)
        queue_plot_data.put(data_converted)

# Create and start the thread
receive_feedback_thread = threading.Thread(target=ReceiveDataFromTcpSocket, daemon=True)
receive_feedback_thread.start()

def SendDataToTcpSocket():
    while True:
        if (not queue_command.empty()):
            message = queue_command.get()
            data_send = struct.pack("<64s", message.encode())
            socket_pico.sendall(data_send)
        else:
            time.sleep(0.1)

send_command_thread = threading.Thread(target=SendDataToTcpSocket, daemon=True)
send_command_thread.start()

# Plot feedback data received from Pico
fig, axis = plt.subplots(1, 1)
fig.set_tight_layout(True)
line_object = axis.plot([], [])
axis.grid()

plt.xlabel("Time [s]")
plt.ylabel("Temperature [C]")

x_axis_data = []
y_axis_data = []

# Update function for animation
def UpdateAnimation(frame_number):
    while (not queue_plot_data.empty()):
        time_s, temperature_C = queue_plot_data.get()
        x_axis_data.append(time_s)
        y_axis_data.append(temperature_C)

    if x_axis_data:
        axis.relim()
        axis.autoscale_view()
        axis.set_xlim(x_axis_data[0], (x_axis_data[-1] + 1.0e-3))
        line_object[0].set_data(x_axis_data, y_axis_data)

    return line_object

plot_animation = anim.FuncAnimation(fig      = fig,
                                    func     = UpdateAnimation,
                                    interval = 1000,
                                    blit     = False,
                                    cache_frame_data = False)

plt.show()
socket_pico.close()
