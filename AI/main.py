import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import pygame
import pickle
from Checkers.constants import COMPUTER, WIDTH, HEIGHT, SQUARE_SIZE, RED, WHITE, DIFFICULTY, ROWS, COLS, HOR_MARG, VERT_MARG
from Checkers.game import Game
from Minimax.algorithm import minimax
import UI.save_load
import time

FPS = 60

WIN = pygame.display.set_mode((WIDTH + HOR_MARG*2, HEIGHT + VERT_MARG*2), pygame.NOFRAME)
WIN.fill(WHITE)
GAME_WIN = pygame.Surface((WIDTH, HEIGHT))
pygame.display.set_caption('Checkers')

def get_row_col_from_mouse(pos):
    x, y = pos[0] - HOR_MARG, pos[1] - VERT_MARG
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
    game = Game(GAME_WIN)

    while run:
        clock.tick(FPS)

        if game.turn == WHITE and COMPUTER:
            new_board = minimax(game.get_board(), DIFFICULTY, float('-inf'), float('inf'), WHITE, game)[1]
            board_change(game.board, new_board, WHITE)
            game.ai_move(new_board)

        """if game.winner() != None:
            game.update()
            print("Game Over")
            if game.winner() == WHITE:
                  print("The winner is: White")
            else:
                 print("The winner is: RED")
            time.sleep(3)
            run = False"""
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                print("Game Quit")
                run = False

            if event.type == pygame.MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()

                if pos[0] > HOR_MARG and pos[0] < HOR_MARG + WIDTH and pos[1] > VERT_MARG and pos[1] < HEIGHT + VERT_MARG:
                    if game.turn == RED or not COMPUTER:
                        pos = pygame.mouse.get_pos()
                        row, col = get_row_col_from_mouse(pos)
                        game.select(row, col)
            
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_s:
                    save_name = time.strftime("%H_%M_%S", time.localtime())
                    save_name = os.getcwd() + "/Save Games/" + save_name + ".pickle"
                    print(save_name)
                    path = open(save_name,'wb')
                    pickle.dump(game.board, path)
                    path.close()
                    print("Game Saved")
                if event.key == pygame.K_l:
                    game.board = pickle.load(open('save','rb'))
                    print("Game Loaded")
                if event.key == pygame.K_q:
                    print("Game Quit")
                    run = False
        
        WIN.blit(GAME_WIN, (HOR_MARG, VERT_MARG))
        game.update()

    pygame.quit()

main()
exit()