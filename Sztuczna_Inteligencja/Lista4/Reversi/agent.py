from board import *

class Agent:
    def __init__(self, color):
        self.color = color

    def get_opponent(self):
        if self.color == WHITE:
            return BLACK
        return WHITE
    
    def get_me(self):
        return self.color
    
    def make_move(self, board):
        pass