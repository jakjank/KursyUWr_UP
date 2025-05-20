from board import *
import random

# return winner and #done moves
def random_game(board:Board, who_starts):
    player = who_starts
    NO_moves = 0

    while(not board.win()[0]):
        moves = board.get_possible_moves(player)
        if len(moves) == 0:
            return (player+1)%2,NO_moves
        move = random.choice(moves)
        old_pos = (move[0],move[1])
        new_pos = (move[2],move[3])
        board.move(old_pos,new_pos,player)

        #board.print_board()
        #print()

        player = (player+1) % 2
        NO_moves += 1

    return board.win()[1], NO_moves


