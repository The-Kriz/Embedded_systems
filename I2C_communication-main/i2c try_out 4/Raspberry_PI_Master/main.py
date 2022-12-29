import smbus

# Slave Addresses
ARDUINO_ADDRESS = 0x04
I2Cbus = smbus.SMBus(1)

direction = int(input("Enter the 1 to move forward  or 2 to move backward : "))


I2Cbus.write_i2c_block_data(ARDUINO_ADDRESS, 0x00, [direction])



