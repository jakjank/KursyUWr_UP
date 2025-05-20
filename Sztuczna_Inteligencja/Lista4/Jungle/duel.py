from mc_agent import *
from random_agent import *
from board import *
import time

NO_GAMES = 10

a1_won = 0
a2_won = 0
draws = 0

for i in range(NO_GAMES):
    board = Board()
    a1 = mc_agent(BIG)
    a2 = random_agent(SMALL)
    player = SMALL
    length = 0

    while(not board.win()[0]):
        if player == SMALL:
            move = a2.get_move(board)
            if move != (-1,-1,-1,-1):
                old_pos = (move[0],move[1])
                new_pos = (move[2],move[3])
                board.move(old_pos, new_pos, player)
            player = BIG
        else:
            move = a1.get_move(board)
            if move != (-1,-1,-1,-1):
                old_pos = (move[0],move[1])
                new_pos = (move[2],move[3])
                board.move(old_pos, new_pos, player)
            player = SMALL
        board.print_board()
        print(board.BIGS)
        print(board.SMALLS)
                
        length += 1

    print("LENGTH =", length)
    if board.win()[1] == BIG:
        print("BIG")
    if board.win()[1] == SMALL:
        print("SMALL")
    if board.win()[1] == -1:
        print("smh went wrong")

