import random
import math
from board import *
from agent import *

CORNER_POSITIONS = [(0, 0), (0, 7), (7, 0), (7, 7)]
MAX_DEPTH = 3  # For midgame minimax

WEIGHTS = [
    [100, -30, 6,  2,  2, 6, -30, 100],
    [-30, -50, 0, 0, 0, 0, -50,   -30],
    [6,   0,   0, 0, 0, 0,    0,    6],
    [2,   0,   0, 0, 0, 0,    0,    2],
    [2,   0,   0, 0, 0, 0,    0,    2],
    [6,   0,   0, 0, 0, 0,    0,    6],
    [-30, -50, 0, 0, 0, 0, -50,   -30],
    [100, -30, 6,  2,  2, 6, -30, 100]
]

class ReversiAgent(Agent):
    def __init__(self, color):
        self.color = color
        self.opponent = 'W' if color == 'B' else 'B'

    def make_move(self, board):
        legal_moves = board.get_possible_moves(self.get_me())
        if not legal_moves:
            return None

        for move in legal_moves:
            if move in CORNER_POSITIONS:
                return move

        return self.one_step_eval(board)

    def one_step_eval(self,board):
        best_score = -math.inf
        moves = board.get_possible_moves(self.get_me())
        best_move = random.choice(moves)
        #print("OPTIONS ----------")
        for move in moves:
            new_board = board.clone()
            new_board.move(move[0], move[1], self.color)
            #new_board.print()
            score = self.evaluate2(new_board)
            #print(score)
            if score > best_score:
                best_score = score
                best_move = move
        #print("OPTIONS STOP -----")
        #print(best_score, "best score")
        return best_move
    
    
    
    def evaluate2(self, board):
        score = 0
        for y in range(8):
            for x in range(8):
                if board.board[y][x] == self.get_me():
                    score += WEIGHTS[y][x]
        return score