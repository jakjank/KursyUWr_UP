from board import *
import copy
from random_game import *

NO_RANDOM_GAMES = 1
NO_MOVES_PER_CHOICE = 20_000

class mc_agent:
    
    def __init__(self, me):
        self.me = me
        self.simulated_moves = 0

    def get_move(self, board:Board):
        print(self.simulated_moves)
        moves = board.get_possible_moves(self.me)
        if len(moves) == 0:
            return (-1,-1,-1,-1)
        
        best_move = moves[0]
        best_stats = 0
        stats = 0

        for move in moves:
            max_simulated_moves= NO_MOVES_PER_CHOICE / len(moves)
            my_board = copy.deepcopy(board)
            old_pos = (move[0],move[1])
            new_pos = (move[2],move[3])
            my_board.move(old_pos, new_pos, self.me)
            stats = 0
            while max_simulated_moves > 0:
                if self.me == BIG:
                    not_me = SMALL
                else:
                    not_me = BIG
                my_board2 = copy.deepcopy(board)
                who_won, NO_moves = random_game(my_board2, not_me)
                self.simulated_moves += NO_moves
                max_simulated_moves -= NO_moves
                if who_won == self.me:
                    stats += 1
                else:
                    stats -= 1
            #print(stats)
            if stats > best_stats:
                best_move = move
                best_stats = stats
        return best_move
        
