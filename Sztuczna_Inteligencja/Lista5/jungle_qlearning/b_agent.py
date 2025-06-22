from board import *
import random


class BAgent:

    def __init__(self, me):
        self.me = me

    def distance(self, posA, posB):
        return abs(posA[0] - posB[0]) + abs(posA[1] - posB[1])

    def get_move(self, board:Board):
        moves = board.get_possible_moves(self.me)
        if len(moves) == 0:
            return (-1,-1,-1,-1)

        closer = []
        for move in moves:
            if (self.distance((move[0],move[1]), board.my_goto_hole(self.me)) < 
                self.distance((move[2],move[3]), board.my_goto_hole(self.me))):
                closer.append(move)
        
        if len(closer) == 0:
            return random.choice(moves)
        
        if random.random() < 0.5:
            return random.choice(closer)
        return random.choice(moves)

    
