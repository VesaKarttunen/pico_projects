import matplotlib.pyplot    as plt
import matplotlib.animation as anim
import socket
import struct
import threading
import time
import queue
import numpy as np

queue_feedback = queue.Queue()

ip_address_pico  = "192.168.101.173"
port_socket_pico = 1234

# Connect TCP socket with configured settings
socket_pico = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_pico.connect((ip_address_pico, port_socket_pico))

def ReceiveFeedbackFromSocket():
    while True:
        count_recv_bytes = 68
        data_raw = socket_pico.recv(count_recv_bytes)
        data_converted = struct.unpack("<17f", data_raw)
        queue_feedback.put(data_converted)

# Create and start the thread
thread_receive_feedback = threading.Thread(target=ReceiveFeedbackFromSocket, daemon=True)
thread_receive_feedback.start()

# Plot feedback data received from Pico
number_of_signals = 16
number_of_subplots = 4
number_of_signals_per_subplot = 4

# Desired time interval of the latest plot data samples kept in figure
plot_window_interval_s = 30.0
sample_time_s = 1e-3
plot_window_sample_count = int(plot_window_interval_s/sample_time_s)

fig, axes = plt.subplots(number_of_subplots, 1, sharex=True, squeeze=False)
fig.set_tight_layout(True)

# List to hold line objects for all the signals.
# Note that every signal needs own line object.
line_objects = []

for n in range(number_of_subplots):
    subplot_axis = axes[n][0]
    subplot_axis.grid()

    for k in range(number_of_signals_per_subplot):
        line_object = subplot_axis.plot([], [])
        line_objects.append(line_object)

plt.xlabel("Time [s]")
plot_data = []

# Update function for animation
def UpdateAnimation(frame_number):
    global plot_data

    while (not queue_feedback.empty()):
        data_frame = queue_feedback.get()
        plot_data.append(data_frame)

    # Limit the data to desired interval of the latest samples
    plot_data = plot_data[-plot_window_sample_count:]

    if len(plot_data) >= 2:
        plot_data_np = np.array(plot_data)
        time_data    = plot_data_np[:, 0]

        for n in range(number_of_signals):
            signal_data = plot_data_np[:, n + 1]
            line_objects[n][0].set_data(time_data, signal_data)

        for k in range(number_of_subplots):
            subplot_axis = axes[k][0]
            subplot_axis.relim()
            subplot_axis.autoscale_view()
            subplot_axis.set_xlim(time_data[0], time_data[-1])

    return line_objects

plot_animation = anim.FuncAnimation(fig      = fig,
                                    func     = UpdateAnimation,
                                    interval = 100,
                                    blit     = False,
                                    cache_frame_data = False)

plt.show()
socket_pico.close()
