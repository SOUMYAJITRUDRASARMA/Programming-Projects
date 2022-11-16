import pygame


# GAME CONSTANTS
SCREEN_WIDTH = 800
SCREEN_HEIGHT = int(SCREEN_WIDTH * 0.8)

# Driver Code
pygame.init()  # Start the game engine ...

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Shooter')




# GAME Variables
# Player Variables
x = y = 200
scale = 3
img = pygame.image.load('img/player/idle/0.png')
img = pygame.transform.scale(img, (img.get_width() * scale, img.get_height() * scale))
rect = img.get_rect()
rect.center = (x, y)




# Game Loop
run = True
while run:

    screen.blit(img, rect)
    pygame.display.update()

    for event in pygame.event.get():

        if event.type == pygame.QUIT:
            run = False




pygame.quit()