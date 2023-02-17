import pygame

#IP address of the car
CAR_IP_ADDRESS = "192.168.1.100"

#port number of car's server
CAR_PORT_NUMBER = 8080

#Initializing Pygame
pygame.init()

#joystick
joystick = None
if pygame.joystick.get_count() > 0:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

#Output screen
screen_width = 300
screen_height = 300
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Car Controller")
font = pygame.font.Font(None, 36)

#Main loop
while True:
    #Checking for inputs
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()
    
    #Clear screen
    screen.fill((255, 255, 255))
    
    # Get the joystick axes
    if joystick:
        axis_x = joystick.get_axis(0)
        axis_y = joystick.get_axis(1)
    else:
        axis_x = 0
        axis_y = 0
    
    #Display axes
    text = font.render("Axis X: {:.2f}   Axis Y: {:.2f}".format(axis_x, axis_y), True, (0, 0, 0))
    screen.blit(text, (10, 10))
    
    #TX cmommand
    if abs(axis_x) > abs(axis_y):
        if axis_x > 0:
            command = "right"
        else:
            command = "left"
    else:
        if axis_y > 0:
            command = "forward"
        else:
            command = "backward"
    
    #Sending command to car
    try:
        client_socket = socket.socket()
        client_socket.connect((CAR_IP_ADDRESS, CAR_PORT_NUMBER))
        client_socket.send(command.encode())
        response = client_socket.recv(1024)
        client_socket.close()
    except:
        pass
    
    #Display update 
    pygame.display.flip()
