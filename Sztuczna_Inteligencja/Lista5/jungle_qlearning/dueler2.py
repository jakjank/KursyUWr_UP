from board import *
from random_agent import RandomAgent
from b_agent import BAgent
from qlearner import *
import copy

NO_GAMES = 10

qLearner_won = 0
random_won = 0
draws = 0

qLearner = QLearner(SMALL)
bAgent = BAgent(BIG)

lost_games = []

for i in range(NO_GAMES):
    print(qLearner.weights)
    board = Board()
    player = SMALL
    move_history = []
    length = 0

    while not board.win()[0]:
        # if i > NO_GAMES-4:
        #     board.print_board()
        if player == SMALL:
            move = qLearner.get_move(board)
            # print("qs move:", move)
        else:
            move = bAgent.get_move(board)
            # print("rs move:", move)

        if move == (-1, -1, -1, -1):
            # no valid moves
            break

        old_board = copy.deepcopy(board)
        old_pos = (move[0], move[1])
        new_pos = (move[2], move[3])
        board.move(old_pos, new_pos, player, True)

        if player == SMALL:
            move_history.append((old_board, move, player))

        player = BIG if player == SMALL else SMALL

        
        # board.print_board()
        # print(board.BIGS)
        # print(board.SMALLS)

        length += 1
    
    board.print_board()
    print(f"(game {i})")
    # print("LENGTH =", length)

    win_state, winner = board.win()
    if winner == BIG:
        random_won += 1
        final_reward = -1
        lost_games.append(i)
    elif winner == SMALL:
        qLearner_won += 1
        final_reward = 1
    else:
        final_reward = 0
        print(win_state)
        print("Draw or error")
        board.print_board()

    # Update Q-learner based on outcome
    #for old_board, move, p in reversed(move_history):
    qLearner.update(final_reward, move_history)
    print(qLearner.weights)

print("qlearner won:", qLearner_won, "\nb_agent won:", random_won)
print("lost games:", lost_games)
