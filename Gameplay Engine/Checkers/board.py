import pygame
from collections import OrderedDict 
from .constants import RED, WHITE, BLACK, ROWS, COLS, SQUARE_SIZE, FORCE_TAKE, KING_TAKE, KING_MOVE
from .piece import Piece

class Board:
    # Initialise board characteristics 
    def __init__(self):
        self.board = []
        self.red_left = self.white_left = 12
        self.red_kings = self.white_kings = 0
        self.create_board()

    # Draws the board in the window
    def draw_squares(self, win):
        win.fill(BLACK)
        for row in range(ROWS):
            for col in range(row % 2, COLS, 2):
                pygame.draw.rect(win, RED, (row*SQUARE_SIZE, col*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))

    # Calculates the "score" of the board for the AI
    def evaluate(self):
        return self.white_left - self.red_left + (self.white_kings * 0.5 - self.red_kings * 0.5)

    # Returns all pieces of one colour
    def get_all_pieces(self, colour):
        pieces = []
        for row in self.board:
            for piece in row:
                if piece != 0 and piece.colour == colour:
                    pieces.append(piece)
        return pieces

    # Moves a piece to a new row and col, changes piece to king if needed
    def move(self, piece, row, col):
        self.board[piece.row][piece.col], self.board[row][col] = self.board[row][col], self.board[piece.row][piece.col]
        piece.move(row, col)

        if row == ROWS - 1 or row == 0:
            piece.make_king()
            if piece.colour == WHITE:
                self.white_kings += 1
            else:
                self.red_kings += 1

    # Returns piece in row and col
    def get_piece(self, row, col):
        return self.board[row][col]

    # Populates a board with pieces in their starting positions
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

    # Draws the board and pieces
    def draw(self, win):
        self.draw_squares(win)
        for row in range(ROWS):
            for col in range(COLS):
                piece = self.board[row][col]
                if piece != 0:
                    piece.draw(win)

    # Removes a piece
    def remove(self, coords):
        for coord in coords:
            piece = self.get_piece(coord[0],coord[1])
            self.board[piece.row][piece.col] = 0
            if piece != 0:
                if piece.colour == RED:
                    self.red_left -= 1
                    if piece.king:
                        self.red_kings -= 1
                else:
                    self.white_left -= 1
                    if piece.king:
                        self.white_kings -= 1
    
    # Checks to see if their is a winner
    def winner(self):
        if self.red_left <= 0:
            return WHITE
        elif self.white_left <= 0:
            return RED
        else:
            red_valid, white_valid = False, False

            # Checks if red or white have any valid moves
            for row in range(ROWS):
                for col in range(COLS):
                    piece = self.get_piece(row, col)
                    if piece != 0 and piece.colour == RED:
                        if self.get_moves_list(piece):
                            red_valid = True
                    elif piece != 0 and piece.colour == WHITE:
                        if self.get_moves_list(piece):
                            white_valid = True

            if not red_valid:
                return WHITE
            elif not white_valid:
                return RED
            else:
                return None

    # Checks if a piece can jump from one postion to a new position
    def can_jump_from_to(self, piece, old_row, old_col, new_row, new_col, step_size):
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
        
        # If the KING_MOVE variant rule is active, this checks the alternate move type
        if KING_MOVE and piece.king and step_size != 1 and step_size != 2:
            jumped = 0
            row_step, col_step = 1, 1
            if old_row > new_row:
                row_step = -1
            if old_col > new_col:
                col_step = -1
            rows = list(range(old_row, new_row, row_step))
            cols = list(range(old_col, new_col, col_step))
            values = tuple(zip(rows,cols))
            for row, col in values:
                    if (row, col) == (old_row, old_col):
                        continue
                    if self.get_piece(row, col) != 0:
                        jumped += 1
            
            if jumped > 1:
                return False

        return True

    # Uses the current row, col and jump path to check for valid moves. Step_size 1 = short jump, step_size 2 = jump chain
    def _get_valid_moves(self, piece, old_row, old_col, jump_path, step_size):
        up, down, left, right = [x + y * step_size for x in [old_row, old_col] for y in [-1, +1]]
        moves = {}

        for new_col in [left, right]:
            for new_row in [up, down]:
                if not self.can_jump_from_to(piece, old_row, old_col, new_row, new_col, step_size):
                    continue
                
                if step_size == 1:
                    moves[new_row, new_col] = []
                if step_size == 2 and not piece.king or step_size == 2 and piece.king and not KING_MOVE:
                    middle_row = (new_row + old_row) // 2
                    middle_col = (new_col + old_col) // 2
                    if (middle_row, middle_col) in jump_path:
                        continue
                    new_jump_path = jump_path.copy()
                    new_jump_path.append((middle_row, middle_col))
                    moves[(new_row, new_col)] = new_jump_path
                    # recursive call
                    moves.update(self._get_valid_moves(piece, new_row, new_col, new_jump_path, step_size))

                if KING_MOVE and piece.king and step_size != 1 and step_size != 2:
                    row_step, col_step = 1, 1
                    if old_row > new_row:
                        row_step = -1
                    if old_col > new_col:
                        col_step = -1
                    rows = list(range(old_row, new_row, row_step))
                    cols = list(range(old_col, new_col, col_step))
                    values = tuple(zip(rows,cols))
                    for row, col in values:
                        if (row, col) in jump_path:
                            continue
                        new_jump_path = jump_path.copy()
                        new_jump_path.append((row,col))
                        moves[(new_row, new_col)] = new_jump_path

                        for step_size in range (2,7):
                            moves.update(self._get_valid_moves(piece, new_row, new_col, new_jump_path, step_size))

        return moves

    # Gets a list of all valid moves
    def get_moves_list(self, piece, must_attack = FORCE_TAKE):
        moves = OrderedDict()

        # Adds single jumps and chain jumps to the list
        moves.update(self._get_valid_moves(piece, piece.row, piece.col, [], 1))
        moves.update(self._get_valid_moves(piece, piece.row, piece.col, [], 2))

        # If the KING_MOVE variant rule is active, this checks the alternate move type
        if KING_MOVE and piece.king:
            for step_size in range(3, 7):
                moves.update(self._get_valid_moves(piece, piece.row, piece.col, [], step_size))
        
        if must_attack:
            moves = self._forced_take(moves, piece)

        # If the KING_TAKE variant rule is active this checks what the largest king jump is
        if piece.king and KING_TAKE and must_attack:
            move_list = {}
            longest = 0
            for move, jumps in moves.items():
                if jumps == 0 and longest == 0:
                    move_list.update({move: jumps})
                elif len(jumps) > longest:
                    longest = len(jumps)
                    move_list = {move: jumps}
                elif len(jumps) == longest:
                    move_list.update({move: jumps})
            
            return move_list

        return moves

    # If the FORCE_TAKE variant rule is active, this removes non-viable options
    def _forced_take(self, moves, piece):
        if not self.can_attack(piece.colour):
            return moves

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

    # Checkers to see if any of the players pieces can attack
    def can_attack(self, turn):
        pieces = self.get_all_pieces(turn)
        
        for piece in pieces:
            moves = self.get_moves_list(piece, False)
            for move in moves:
                if len(moves[move]):
                    return True