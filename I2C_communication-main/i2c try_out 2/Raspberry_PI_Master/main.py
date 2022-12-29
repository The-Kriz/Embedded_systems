import smbus

# Slave Addresses
ARDUINO_1_ADDRESS = 0x04 
ARDUINO_2_ADDRESS = 0x05
ARDUINO_3_ADDRESS = 0x06
 

I2Cbus = smbus.SMBus(1)
 
arduinoSelect = input("Which Arduino (1-3): ")
ledStateSelect = input("Enter 1 or 0 (on/off): ")
 
if arduinoSelect == 1:
	SlaveAddress = ARDUINO_1_ADDRESS
elif arduinoSelect == 2:
	SlaveAddress = ARDUINO_2_ADDRESS
elif arduinoSelect == 3:
	SlaveAddress = ARDUINO_3_ADDRESS
else:
	quit()

if ledStateSelect != "1" or ledStateSelect != "0":
    	quit()

I2Cbus.write_i2c_block_data(SlaveAddress, 0x00, ledStateSelect)
print("Sent " + SlaveAddress + " the " + ledStateSelect + " command.")
 