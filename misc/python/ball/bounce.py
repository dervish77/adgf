#
# bouncing ball demo using PyGame
#

import sys
import pygame
pygame.init()

size = width, height = 1000, 800
speed = [2, 2]
black = 0, 0, 0

screen = pygame.display.set_mode(size)

ball = pygame.image.load("ball.bmp")
ballrect = ball.get_rect()

while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()

    ballrect = ballrect.move(speed)
    if ballrect.left < 0 or ballrect.right > width:
        speed[0] = -speed[0]
    if ballrect.top < 0 or ballrect.bottom > height:
        speed[1] = -speed[1]

    pygame.time.delay(3)

    screen.fill(black)
    screen.blit(ball, ballrect)
    pygame.display.flip()
		
