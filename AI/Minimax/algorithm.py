import pygame
from copy import deepcopy
from random import randint

RED = (255, 0, 0)
WHITE = (255, 255, 255)

def minimax(position, depth, a, b, max_player, game):
    if depth == 0 or position.winner() != None:
        return position.evaluate(), position

    if max_player:
        maxEval = float('-inf')
        best_move = None
        options = []
        for move in get_all_moves(position, WHITE, game):
            evaluation = minimax(move, depth - 1, a, b, False, game)[0]
            if evaluation > maxEval:
                options = [(evaluation, move)]
                maxEval = evaluation
            elif evaluation == maxEval:
                options.append((evaluation, move))
            
            a = max(a, maxEval)
            if a >= b:
                break

        choice = options[randint(0, len(options) - 1)]

        return choice[0], choice[1]

    else:
        minEval = float('inf')
        best_move = None
        for move in get_all_moves(position, RED, game):
            evaluation = minimax(move, depth - 1, a, b, True, game)[0]
            if evaluation < minEval:
                options = [(evaluation, move)]
                minEval = evaluation
            elif evaluation == minEval:
                options.append((evaluation, move))
        
            b = min(b, minEval)
            if b <= a:
                break

        choice = options[randint(0, len(options) - 1)]

        return choice[0], choice[1]

def simulate_move(piece, move, board, game, skip):
    board.move(piece, move[0], move[1])
    if skip:
        board.remove(skip)
    
    return board

def get_all_moves(board, colour, game):
    moves = []
    longest_move = board.get_longest_move(colour)
    for piece in board.get_all_pieces(colour):
        valid_moves = board.get_valid_moves(piece, longest_move)
        for move, skip in valid_moves.items():
            temp_board = deepcopy(board)
            temp_piece = temp_board.get_piece(piece.row, piece.col)
            new_board = simulate_move(temp_piece, move, temp_board, game, skip)
            moves.append(new_board)
    
    return moves