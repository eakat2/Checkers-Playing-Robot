import pygame
from collections import OrderedDict 
from .constants import RED, WHITE, BLACK, ROWS, COLS, SQUARE_SIZE, FORCE_MOVE
from .piece import Piece

class Board:
    def __init__(self):
        self.board = []
        self.red_left = self.white_left = 12
        self.red_kings = self.white_kings = 0
        self.create_board()

    def draw_squares(self, win):
        win.fill(BLACK)
        for row in range(ROWS):
            for col in range(row % 2, COLS, 2):
                pygame.draw.rect(win, RED, (row*SQUARE_SIZE, col*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))

    def evaluate(self):
        return self.white_left - self.red_left + (self.white_kings * 0.5 - self.red_kings * 0.5)

    def get_all_pieces(self, colour):
        pieces = []
        for row in self.board:
            for piece in row:
                if piece != 0 and piece.colour == colour:
                    pieces.append(piece)
        return pieces

    def move(self, piece, row, col):
        self.board[piece.row][piece.col], self.board[row][col] = self.board[row][col], self.board[piece.row][piece.col]
        piece.move(row, col)

        if row == ROWS - 1 or row == 0:
            piece.make_king()
            if piece.colour == WHITE:
                self.white_kings += 1
            else:
                self.red_kings += 1

    def get_piece(self, row, col):
        return self.board[row][col]

    def create_board(self):
        for row in range(ROWS):
            self.board.append([])
            for col in range(COLS):
                if col % 2 == ((row + 1) % 2):
                    if row < 3:
                        self.board[row].append(Piece(row, col, WHITE))
                    elif row > 4:
                        self.board[row].append(Piece(row, col, RED))
                    else:
                        self.board[row].append(0)
                else:
                    self.board[row].append(0)

    def draw(self, win):
        self.draw_squares(win)
        for row in range(ROWS):
            for col in range(COLS):
                piece = self.board[row][col]
                if piece != 0:
                    piece.draw(win)

    def remove(self, coords):
        for coord in coords:
            piece = self.get_piece(coord[0],coord[1])
            self.board[piece.row][piece.col] = 0
            if piece != 0 and not piece.king:
                if piece.colour == RED:
                    self.red_left -= 1
                else:
                    self.white_left -= 1
    
    def winner(self):
        if self.red_left <= 0:
            return WHITE
        elif self.white_left <= 0:
            return RED
        else:
            red_valid, white_valid = False, False

            for row in range(ROWS):
                for col in range(COLS):
                    piece = self.get_piece(row, col)
                    if piece != 0 and piece.colour == RED:
                        if self.get_valid_moves(piece):
                            red_valid = True
                    elif piece != 0 and piece.colour == WHITE:
                        if self.get_valid_moves(piece):
                            white_valid = True

            if not red_valid:
                return WHITE
            elif not white_valid:
                return RED
            else:
                return None

    def can_jump_from_to(self, piece, old_row, old_col, new_row, new_col, step_size) -> bool:
        '''evaluates to True if boundaries are right and if current piece between start/end location is of different color'''
        if not (piece.king or new_row == old_row + piece.direction * step_size):
            # invalid direction
            return False
        if not (0 <= new_row < ROWS and 0 <= new_col < COLS):
            # outside of board
            return False
        new_loc = self.get_piece(new_row, new_col)
        if new_loc != 0:
            # jump location not empty
            return False
        # all base obstacles have been overcome
        if step_size == 2:
            middle_row = (old_row + new_row) // 2
            middle_col = (old_col + new_col) // 2
            middle_piece = self.get_piece(middle_row, middle_col)
            if middle_piece == 0 or middle_piece.colour == piece.colour:
                return False
        
        return True

    def _get_valid_moves(self, piece, row, col, jump_path, step_size):
        ''' this method takes in a row and col of where the piece is currently during the jump. It also takes a jump_path so a king
        does not jump back to where it came from and to prevent jumping over the same piece twice.
        Finally a step_size is provided: if it's 1 only short jumps are considered, if 2 then jump chains are considered
        '''
        up, down, left, right = [x + y * step_size for x in [row, col] for y in [-1, +1]]

        moves = {}

        for new_col in [left, right]:
            for new_row in [up, down]:
                if not self.can_jump_from_to(piece, row, col, new_row, new_col, step_size):
                    continue
                
                if step_size == 1:
                    moves[new_row, new_col] = []
                else:
                    middle_row = (new_row + row) // 2
                    middle_col = (new_col + col) // 2
                    if (middle_row, middle_col) in jump_path:
                        continue
                    new_jump_path = jump_path.copy()
                    new_jump_path.append((middle_row, middle_col))
                    moves[(new_row, new_col)] = new_jump_path
                    # recursive call
                    moves.update(self._get_valid_moves(piece, new_row, new_col, new_jump_path, step_size))
        return moves

    def get_valid_moves(self, piece):
        moves = OrderedDict()

        moves.update(self._get_valid_moves(piece, piece.row, piece.col, [], 1))
        moves.update(self._get_valid_moves(piece, piece.row, piece.col, [], 2))

        if FORCE_MOVE:
            skipped = False

            for move in moves:
                if len(moves[move]): 
                    skipped = True
                    break

            if skipped:
                move_list = {}

                for move, jumps in moves.items():
                    valid = True

                    if len(jumps)  == 0:
                        continue

                    for check, skips in moves.items():
                        if move == check:
                            continue

                        if jumps[len(jumps)-1] in skips:
                            valid = False
                            break

                    if valid:
                        move_list.update({move: jumps})
                    
                return move_list

        return moves

    """ def get_valid_moves(self, piece, longest_move = 0):
        moves = OrderedDict()
        left = piece.col - 1
        right = piece.col + 1
        row = piece.row

        if piece.colour == RED or piece.king:
            moves.update(self._traverse_left(row - 1, max(row - 3, -1), -1, piece.colour, left, piece.king))
            moves.update(self._traverse_right(row - 1, max(row - 3, -1), -1, piece.colour, right, piece.king))
        if piece.colour == WHITE or piece.king:
            moves.update(self._traverse_left(row + 1, min(row + 3, ROWS), 1, piece.colour, left, piece.king))
            moves.update(self._traverse_right(row + 1, min(row + 3, ROWS), 1, piece.colour, right, piece.king))

        
        if FORCE_MOVE:
            for move in moves:
                if len(moves[moves]):
                    skipped == True
                    break
            
            if skipped:
                pass



            max_move = 0
            move_list = {} 

            for move in moves:
                if max_move == len(moves[move]):
                    move_list[move] = moves[move]
                elif max_move < len(moves[move]):
                    max_move = len(moves[move])
                    move_list = {move: moves[move]}

            if move_list != {}:
                if len(list(move_list.values())[0]) >= longest_move:
                    return move_list
                else:
                    return {}

        return moves """
