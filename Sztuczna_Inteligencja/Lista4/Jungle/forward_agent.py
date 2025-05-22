from board import *
import random

#plays only as SMALL (easyfix)
class forward_agent:
    def __init__(self, me):
        self.counter = 0
        self.me = me
    
    def go_right(self, animal, board:Board):
        #check if can go right
        position = board.get_position(animal, self.me)
        return (position[0], position[1], position[0], position[1]+1)
    
    def go_up(self, animal, board:Board):
        #check if can go up
        position = board.get_position(animal, self.me)
        return (position[0], position[1], position[0]-1, position[1])
    
    def go_left(self, animal, board:Board):
        #check if can go right
        position = board.get_position(animal, self.me)
        return (position[0], position[1], position[0], position[1]-1)
    
    def go_down(self, animal, board:Board):
        #check if can go up
        position = board.get_position(animal, self.me)
        return (position[0], position[1], position[0]+1, position[1])


    def get_move(self, board:Board):
        #get_biggest_animal()
        move = (-1,-1,-1,-1)

        if self.counter == 0:
            self.counter = 1
            if self.me == SMALL:
                return (6,2,7,2)
            return (2,4,1,4)

        if(board.players_board(self.me)[7] == (-1,-1)): # no elephant
            move = random.choice(board.get_possible_moves(self.me))
        else:
            if self.counter < 4:
                if self.me == SMALL:
                    move = self.go_right(7, board)
                else:
                    move = self.go_left(7, board)
            else:
                if self.me == SMALL:
                    move = self.go_up(7,board)
                else:
                    move = self.go_down(7,board)

        self.counter += 1
        return move
    