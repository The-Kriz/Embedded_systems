import smbus

# Slave Addresses
ARDUINO_ADDRESS = 0x04
I2Cbus = smbus.SMBus(1)

degree = int(input("Enter the angle: "))


I2Cbus.write_i2c_block_data(ARDUINO_ADDRESS, 0x00, [degree])



