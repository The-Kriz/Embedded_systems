import pygame
import serial
import time

# Bluetooth COM-8

port = serial.Serial('COM8', 9600, timeout=2)

pygame.init()

pygame.joystick.init()


def val_map(value, istart, istop, ostart, ostop):
    return int(ostart + (ostop - ostart) * ((value - istart) / (istop - istart)))


def main():
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

    old_msg = ''
    done = False

    clock = pygame.time.Clock()
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True

        move_to = round(joystick.get_axis(1), 2)
        turn_to = round(joystick.get_axis(3), 2)

        angle = val_map(turn_to, -1.0, 1.0, -255, 255)
        move = val_map(move_to, 1.0, -1.0, -255, 255)

        move = str(move) if move >= 100 else '0' + str(move)
        angle = str(angle) if angle >= 100 else '0' + str(angle)

        # msg = "/M" + move + "/T" + angle + "#"

        btn0_state = joystick.get_button(0)
        btn1_state = joystick.get_button(1)
        btn2_state = joystick.get_button(2)
        btn3_state = joystick.get_button(3)
        buttons = [str(i) for i in [btn0_state, btn1_state, btn2_state, btn3_state]]
        msg = "/T" + angle + "/M" + move + "/B" + str(''.join(buttons)) + "/"

        # 90904d = (buttons)
        if old_msg != msg:
            print(msg)
            port.write(msg.encode())
            old_msg = msg
        print(msg)

        clock.tick(10)


if __name__ == '__main__':
    main()
