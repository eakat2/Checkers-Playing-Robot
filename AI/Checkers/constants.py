import pygame

WIDTH, HEIGHT = 600, 600
ROWS, COLS = 8, 8
SQUARE_SIZE = WIDTH//COLS

# rgb
RED = (255, 0, 0)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
GREY = (128, 128, 128)
GOLD = (255, 223, 0)

# Difficulty Levels
Novice = 1
Beginner = 2
Intermediate = 3
Hard = 4

# Settings
FORCE_TAKE = True
KING_MOVE = False
KING_TAKE = True
FIRST = RED
DIFFICULTY = Intermediate
COMPUTER = False
