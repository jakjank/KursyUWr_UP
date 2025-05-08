from agent import Agent
import random

class RandomAgent(Agent):
    def make_move(self, board):
        possible_moves = board.get_possible_moves(self.get_me())
        if len(possible_moves) == 0:
            return None
        return random.choice(possible_moves)