# Importing Library
from machine import Pin, UART
import time

uart = machine.UART(0, baudrate=38400)

# Store the previous acceleration values
prev_acc_x = 0
prev_acc_y = 0
prev_acc_z = 0

prev_time = time.time()

while True:
    # Store the previous time
    
    # Read data from UART
    data = uart.readline().decode().strip()

    # Split data into individual values
    acc_x = ser.readline().decode().strip()
    acc_y = ser.readline().decode().strip()
    acc_z = ser.readline().decode().strip()
    gyr_x = ser.readline().decode().strip()
    gyr_y = ser.readline().decode().strip()
    gyr_z = ser.readline().decode().strip()

    print("accelerometer X:", acc_x)
    print("accelerometer Y:", acc_y)
    print("accelerometer Z:", acc_z)
    print("gyro X:", gyr_x)
    print("gyro Y:", gyr_y)
    print("gyro Z:", gyr_z)

    # Read the current time
    current_time = time.time()
    
    # Calculate the time elapsed since the last iteration
    dt = current_time - prev_time
    
    # Integrate the acceleration values to find the velocity
    vel_x = prev_vel_x + (prev_acc_x + acc_x) * dt / 2
    vel_y = prev_vel_y + (prev_acc_y + acc_y) * dt / 2
    vel_z = prev_vel_z + (prev_acc_z + acc_z) * dt / 2
    
    print(vel_x)
    print(vel_y)
    print(vel_z)
    
    # Store the current acceleration and time for the next iteration
    prev_acc_x = acc_x
    prev_acc_y = acc_y
    prev_acc_z = acc_z
    prev_time = current_time
    
    
    
    
    


