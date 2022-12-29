from smbus import SMBus
addr = 0x8
bus = SMBus(1)
numb = 1

print ("Enter a characters \n enter 1 to exit")
while numb == 1:

	a = input(">>>>   ")

	if a == "1":
		num = 0

	else : 
		bus.write_byte(addr, a)
        