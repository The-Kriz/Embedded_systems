from machine import Pin, I2C, UART
from imu import MPU6050
import time

# Initialize the I2C bus with a frequency of 400kHz
i2c = I2C(0, sda=Pin(20), scl=Pin(21), freq=400000)

# Initialize the MPU6050 sensor on the I2C bus
imu = MPU6050(i2c)

# Disable the default UART0 on pins 1 and 2
uart = machine.UART(0, baudrate=38400)
uart.deinit()

# Enable UART0 on pins 17 and 16
uart = machine.UART(0, baudrate=38400)
uart.init(tx=Pin(16), rx=Pin(17))


# Store the previous acceleration values
prev_acc_x = 0
prev_acc_y = 0
prev_acc_z = 0
prev_vel_x = 0
prev_vel_y = 0
prev_vel_z = 0
prev_time = time.time()


while True:
    # Check for incoming data
    if uart.any():
        # Read the incoming data as a command
        command = uart.readline()
        # Decode the command and remove the trailing newline character
        print(command.decode().rstrip())
        
    # Read the sensor data for the X, Y, and Z acceleration values
    acc_x = round(imu.accel.x, 2)
    acc_y = round(imu.accel.y, 2)
    acc_z = round(imu.accel.z, 2)
    
    # Print the acceleration values
    print(str(acc_x) + " " + str(acc_y) +  " " + str(acc_z) + " ")
    
    # Read the current time
    current_time = time.time()
    # Print the current time
    print(str(current_time)+ " dt")
    
    # Calculate the time elapsed since the last iteration
    dt = current_time - prev_time
    # Print the elapsed time
    print(str(dt)+ " dt")
    
    # Integrate the acceleration values to find the velocity
    vel_x = prev_vel_x + (prev_acc_x + acc_x) * dt / 2
    vel_y = prev_vel_y + (prev_acc_y + acc_y) * dt / 2
    vel_z = prev_vel_z + (prev_acc_z + acc_z) * dt / 2
    
    
    if vel_x != 0 and vel_y != 0 and vel_z != 0:
        
        vel_x = abs(vel_x)
        vel_y = abs(vel_y)
        vel_z = abs(vel_z)
    
        # Send the calculated velocity values over UART
        uart.write(str(vel_x) + '\n')
        uart.write(str(vel_y) + '\n')
        uart.write(str(vel_z) + '\n')
        # Print the sent velocity values
        print(str(vel_x) + ' val in x')
        print(str(vel_y) + ' val in y')
        print(str(vel_z) + ' val in z')
        
    #Store the current acceleration and time for the next iteration
        
    prev_acc_x = acc_x
    prev_acc_y = acc_y
    prev_acc_z = acc_z
    prev_time = current_time
    
    time.sleep(0.5)
 
    
    
    
    