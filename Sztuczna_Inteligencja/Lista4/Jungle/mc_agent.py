from board import *
import copy
from random_game import *

NO_RANDOM_GAMES = 1
NO_MOVES_PER_CHOICE = 2_000

class mc_agent:
    
    def __init__(self, me):
        self.me = me
        self.simulated_moves = 0
        self.counter= 50

    def get_move(self, board:Board):
        print(self.simulated_moves)
        moves = board.get_possible_moves(self.me)
        if len(moves) == 0:
            return (-1,-1,-1,-1)
        # if self.counter > 0:
        #     self.counter -= 1
        #     return random.choice(moves)
        
        best_move = moves[0]
        best_win_simulated_ratio = 0

        for move in moves:
            # print(move)
            max_simulated_moves= NO_MOVES_PER_CHOICE / len(moves)
            my_board = copy.deepcopy(board)
            old_pos = (move[0],move[1])
            new_pos = (move[2],move[3])
            my_board.move(old_pos, new_pos, self.me)
            played_games = 0
            won_games = 0
            while max_simulated_moves > 0 and played_games < 20:

                if self.me == BIG:
                    not_me = SMALL
                else:
                    not_me = BIG

                my_board2 = copy.deepcopy(my_board)
                who_won, NO_moves = random_game(my_board2, not_me)
                played_games += 1
                self.simulated_moves += NO_moves
                max_simulated_moves -= NO_moves
                if who_won == self.me:
                    won_games += 1
                
            #print(stats)
            if won_games/played_games > best_win_simulated_ratio:
                best_move = move
                best_win_simulated_ratio = won_games/played_games

        return best_move
        
