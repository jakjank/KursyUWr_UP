from board import *
import random

class random_agent:

    def __init__(self, me):
        self.me = me

    def get_move(self, board:Board):
        moves = board.get_possible_moves(self.me)
        if len(moves) == 0:
            return (-1,-1,-1,-1)
        return random.choice(moves)