import smbus

# Slave Addresses
ARDUINO_ADDRESS = 0x04
I2Cbus = smbus.SMBus(1)

direction = int(input("Enter\n1: forward\n2: backward \n3:Turn Left\n4:Turn Right\n>>>"))


I2Cbus.write_i2c_block_data(ARDUINO_ADDRESS, 0x00, [direction])



