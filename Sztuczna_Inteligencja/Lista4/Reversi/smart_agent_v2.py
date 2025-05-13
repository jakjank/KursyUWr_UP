import random
import math
from board import *
from agent import *

CORNER_POSITIONS = [(0, 0), (0, 7), (7, 0), (7, 7)]

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

class ReversiAgent2(Agent):
    def __init__(self, color):
        self.color = color
        self.opponent = WHITE if color == BLACK else BLACK

    def make_move(self, board):
        legal_moves = board.get_possible_moves(self.get_me())
        if not legal_moves:
            return None

        for move in legal_moves:
            if move in CORNER_POSITIONS:
                return move
            
        empty = board.empty_fields()
        
        if empty > 8:
            return self.one_step_eval(board)

        else:
            return self.minimax_decision(board, depth=empty)
        # return self.one_step_eval(board)

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

    def minimax_decision(self, board, depth):
        # print('-----------', depth)
        best_score = -math.inf
        best_move = None
        for move in board.get_possible_moves(self.color):
            new_board = board.clone()
            new_board.move(move[0], move[1], self)
            score = self.minimax(new_board, depth - 1, False)
            if score > best_score:
                best_score = score
                best_move = move
        return best_move

    def minimax(self, board, depth, maximizing_player):
        # print("minimax", depth)
        # print('color:', self.color if maximizing_player else self.opponent)
        # print("pos moves: ",board.get_possible_moves(self.color if maximizing_player else self.opponent)) 
        if depth == 0 or board.get_possible_moves(self.color if maximizing_player else self.opponent) == []:
            return self.evaluate(board)
        
        player = self.get_me() if maximizing_player else self.get_opponent()
        
        moves = board.get_possible_moves(player)
        if not moves:
            return self.evaluate(board)

        if maximizing_player:
            max_eval = -math.inf
            for move in moves:
                new_board = board.clone()
                new_board.move(move[0], move[1], player)
                eval = self.minimax(new_board, depth - 1, False)
                max_eval = max(max_eval, eval)
            return max_eval
        else:
            min_eval = math.inf
            for move in moves:
                new_board = board.clone()
                new_board.move(move[0], move[1], player)
                eval = self.minimax(new_board, depth - 1, True)
                min_eval = min(min_eval, eval)
            return min_eval

    def evaluate(self, board):
        score = 0
        for y in range(8):
            for x in range(8):
                if board.board[y][x] == self.get_me():
                    score += WEIGHTS[y][x]
                elif board.board[y][x] == self.get_opponent():
                    score -= WEIGHTS[y][x]
        return score
    
    def evaluate2(self, board):
        score = 0
        for y in range(8):
            for x in range(8):
                if board.board[y][x] == self.get_me():
                    score += WEIGHTS[y][x]
        return score