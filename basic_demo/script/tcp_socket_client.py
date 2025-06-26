import socket
import struct
import threading
import time
import queue

queue_send_message = queue.Queue()

def GetUserMessageToSend():
    while True:
        message_to_send = input("Type message...\n")
        queue_send_message.put(message_to_send)

# Create and start the thread
wait_keyboard_thread = threading.Thread(target=GetUserMessageToSend, daemon=True)
wait_keyboard_thread.start()

ip_address_pico  = "192.168.101.173"
port_socket_pico = 1234

# Connect TCP socket with configured settings
socket_pico = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_pico.connect((ip_address_pico, port_socket_pico))

def ReceiveDataFromTcpSocket():
    while True:
        size_recv_message_bytes = 11
        data_received_raw = socket_pico.recv(size_recv_message_bytes)

        # Convert received raw bits to actual message
        message = struct.unpack("<11s", data_received_raw)


# Create and start the thread
receive_feedback_thread = threading.Thread(target=ReceiveDataFromTcpSocket, daemon=True)
receive_feedback_thread.start()

def SendDataToTcpSocket():
    while True:
        if (not queue_send_message.empty()):
            message = queue_send_message.get()
            data_send = struct.pack("<64s", message.encode())
            socket_pico.sendall(data_send)
        else:
            time.sleep(5.0)

send_command_thread = threading.Thread(target=SendDataToTcpSocket, daemon=True)
send_command_thread.start()

while True:
    pass
