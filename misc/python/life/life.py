# life.py - a game of life
#
#

import sys, pygame

pygame.init()

# screen and grid stuff
size = width, height = 800, 800

gridsize = 40

gridx = width // gridsize
gridy = height // gridsize

# some colors
black = 0, 0, 0
gridcolor = pygame.Color("green")
wincolor = pygame.Color("white")

# game states
state_idle   = 0
state_title  = 1
state_play   = 2
state_winner = 3
game_state = state_title


def draw_centered_image(image_name):
    # load the image
    img = pygame.image.load(image_name)
    imgrect = img.get_rect()

    # compute centering position
    topleft = [width/2 - img.get_width()/2, height/2 - img.get_height()/2]
    imgrect = imgrect.move(topleft)

    # draw the image
    screen.blit(img, imgrect)


def draw_grid_lines():
    # draw horizontal grid lines
    y_incr = 0
    for y in range (0, gridy):
        y_incr = y_incr + gridsize
        start = [0, y_incr]
        end = [width, y_incr]
        pygame.draw.line(screen, gridcolor, start, end, 1)

	# draw vertical grid lines
    x_incr = 0
    for x in range (0, gridx):
        x_incr = x_incr + gridsize
        start = [x_incr, 0]
        end = [x_incr, height]
        pygame.draw.line(screen, gridcolor, start, end, 1)


def draw_filled_grid_cell(position):
	gx = position[0] // gridsize
	gy = position[1] // gridsize
	gridrect = pygame.Rect(gx * gridsize, gy * gridsize, gridsize, gridsize)
	pygame.draw.rect(screen, gridcolor, gridrect, 0)


screen = pygame.display.set_mode(size)

not_done = 1

mouse_down = 0

while not_done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: not_done = 0
        if event.type == pygame.MOUSEBUTTONDOWN: mouse_down = 1

    if game_state == state_idle:
        pygame.time.delay(10)
        game_state = state_title

    elif game_state == state_title:
        screen.fill(black)
        draw_centered_image("title.bmp")
        pygame.display.flip()

        pygame.time.delay(1000)
        game_state = state_play
        screen.fill(black)
        draw_grid_lines()
        pygame.display.flip()

    elif game_state == state_play:
        if mouse_down == 1:
            draw_filled_grid_cell(event.pos)
            pygame.display.flip()

    elif game_state == state_winner:
        screen.fill(black)
        start = [0, 0]
        end = [width, height]
        pygame.draw.line(screen, wincolor, start, end, 1)
        pygame.display.flip()

    mouse_down = 0

sys.exit()
