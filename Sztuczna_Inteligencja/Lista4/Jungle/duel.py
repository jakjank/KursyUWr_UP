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
        # print("after win check")
        if player == SMALL:
            move = a2.get_move(board)
            if move != (-1,-1,-1,-1):
                old_pos = (move[0],move[1])
                new_pos = (move[2],move[3])
                print(move)
                board.move(old_pos, new_pos, player,True)
            player = BIG
        else:
            move = a1.get_move(board)
            if move != (-1,-1,-1,-1):
                old_pos = (move[0],move[1])
                new_pos = (move[2],move[3])
                print(move)
                board.move(old_pos, new_pos, player,True)
            player = SMALL
        print(f"(game {i})")
        board.print_board()
        print(board.BIGS)
        print(board.SMALLS)
                
        length += 1

    print("LENGTH =", length)
    if board.win()[1] == BIG:
        print("BIG won")
        a1_won += 1
    if board.win()[1] == SMALL:
        print("SMALL won")
        a2_won += 1
    if board.win()[1] == -1:
        print("smh went wrong")

print("big won:",a1_won, "\nsmall won:", a2_won)
# print(board.BIGS,"\n",board.SMALLS)