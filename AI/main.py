import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import pygame
from Checkers.constants import WIDTH, HEIGHT, SQUARE_SIZE, RED, WHITE, DIFFICULTY, ROWS, COLS
from Checkers.game import Game
from Minimax.algorithm import minimax
import time

FPS = 60

WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Checkers')

def get_row_col_from_mouse(pos):
    x, y = pos
    row = y // SQUARE_SIZE
    col = x // SQUARE_SIZE
    return row, col

def board_change(old, new, turn):
    moved = []
    skipped = []
    for row in range(ROWS):
        for col in range (COLS):
            if not (old.board[row][col] == 0 and new.board[row][col] == 0):
                if old.board[row][col] == 0:
                    moved.append([row, col, new.board[row][col].king])
                if new.board[row][col] == 0:
                    if old.board[row][col].colour == turn:
                        moved.insert(0, [row, col, old.board[row][col].king])
                    else:
                        skipped.append([row, col, old.board[row][col].king])               
    
    print(moved)
    print(skipped)
    return None

def main():
    run = True
    clock = pygame.time.Clock()
    game = Game(WIN)

    while run:
        clock.tick(FPS)

        if game.turn == WHITE:
            value, new_board = minimax(game.get_board(), DIFFICULTY, float('-inf'), float('inf'), WHITE, game)
            board_change(game.board, new_board, WHITE)
            game.ai_move(new_boa rd)

        if game.winner() != None:
            game.update()
            print("Game Over")
            print("The winner is: " + str(game.winner()))
            time.sleep(3)
            run = False
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                print("Game Quit")
                run = False

            if event.type == pygame.MOUSEBUTTONDOWN and game.turn == RED:
                pos = pygame.mouse.get_pos()
                row, col = get_row_col_from_mouse(pos)
                game.select(row, col)

        game.update()

    pygame.quit()

main()
exit()