import time
import pygame
import os
import pickle
from Checkers.constants import RED

def load_game(game, win):
    #saves = os.listdir(os.getcwd() + "/Save Games/")
    #for i in range(len(saves)):
    #    pygame.draw.rect(win, RED, (16, 80+2*(i*40), 180, 40))
    game.board = pickle.load(open('save_name','rb'))
    print("Game Loaded")
    return

def save_game(game):
    save_name = time.strftime("%d_%m_%y %H_%M", time.localtime())
    save_name = os.getcwd() + "/Save Games/" + save_name
    print(save_name)
    path = open('save_name','wb')
    pickle.dump(game.board, path)
    print("Game Saved")
    return