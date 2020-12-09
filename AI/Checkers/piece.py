import pygame
from .constants import RED, WHITE, GREY, GOLD, SQUARE_SIZE

class Piece:
    RADIUS = SQUARE_SIZE // 3
    BORDER = SQUARE_SIZE // 20

    def __init__(self, row, col, colour):
        self.row = row
        self.col = col
        self.colour = colour
        self.king = False
        self.x = 0
        self.y = 0
        self.direction = 0
        self.calc_pos()
        

    def calc_pos(self):
        self.x = SQUARE_SIZE * self.col + SQUARE_SIZE // 2
        self.y = SQUARE_SIZE * self.row + SQUARE_SIZE // 2
        if self.colour == WHITE:
            self.direction = 1
        else:
            self.direction = -1

    def make_king(self):
        self.king = True

    def draw(self, win):
        pygame.draw.circle(win, GREY, (self.x, self.y), self.RADIUS + self.BORDER)
        pygame.draw.circle(win, self.colour, (self.x, self.y), self.RADIUS)
        if self.king:
            pygame.draw.circle(win, GOLD, (self.x, self.y), self.RADIUS // 2)

    def move(self, row, col):
        self.row = row
        self.col = col
        self.calc_pos()

    def __repr__(self):
        return str(self.colour)