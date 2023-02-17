import machine
import time
import network
import socket

# Wi-Fi network credentials
WIFI_SSID = "ssid"
WIFI_PASSWORD = "password"

#port number
CAR_PORT_NUMBER = 8080

#Wi-Fi connection
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(WIFI_SSID, WIFI_PASSWORD)

while not wifi.isconnected():
    time.sleep(1)

print("Connected to Wi-Fi:", wifi.ifconfig())

#socket server
server_socket = socket.socket()
server_socket.bind(('',CAR_PORT_NUMBER))
server_socket.listen(5)

#motor pins
motor_1_forward = machine.Pin(2, machine.Pin.OUT)
motor_1_backward = machine.Pin(3, machine.Pin.OUT)
motor_2_forward = machine.Pin(4, machine.Pin.OUT)
motor_2_backward = machine.Pin(5, machine.Pin.OUT)

#car control
def control_car(command):
    if command == "forward":
        motor_1_forward.value(1)
        motor_1_backward.value(0)
        motor_2_forward.value(1)
        motor_2_backward.value(0)
    elif command == "backward":
        motor_1_forward.value(0)
        motor_1_backward.value(1)
        motor_2_forward.value(0)
        motor_2_backward.value(1)
    elif command == "left":
        motor_1_forward.value(0)
        motor_1_backward.value(1)
        motor_2_forward.value(1)
        motor_2_backward.value(0)
    elif command == "right":
        motor_1_forward.value(1)
        motor_1_backward.value(0)
        motor_2_forward.value(0)
        motor_2_backward.value(1)
    elif command == "stop":
        motor_1_forward.value(0)
        motor_1_backward.value(0)
        motor_2_forward.value(0)
        motor_2_backward.value(0)

#Main loop
while True:
    #connecting to client
    print("Waiting for client...")
    client_socket, client_address = server_socket.accept()
    print("Client connected:", client_address)
    
    #Cheching for RX commands
    while True:
        try:
            command = client_socket.recv(1024).decode().strip()
            if not command:
                break
            print("Received command:", command)
            control_car(command)
            client_socket.send("OK".encode())
        except Exception as e:
            print("Error:", e)
            break
    
    #Close client socket
    print("Closing client connection")
    client_socket.close()

