from board import *
from agent import *
from random_agent import *
from smart_agent_v1 import *
from smart_agent_v2 import *

NO_GAMES = 100

a1_won = 0
a2_won = 0
draws = 0

for i in range(NO_GAMES):
    b = Board()

    # Alternate agent roles
    if i % 2 == 0:
        a1 = RandomAgent(WHITE)
        a2 = ReversiAgent2(BLACK)
        print("smart is BLACK")
    else:
        a1 = RandomAgent(BLACK)
        a2 = ReversiAgent2(WHITE)
        print("smart is WHITE")

    turn = (i+1)%2
    stop1 = False
    stop2 = False

    while not b.end():
        if turn == 0:
            pos = a1.make_move(b)
            if pos:
                #print(pos)
                b.move(pos[0], pos[1], a1.color)
        else:
            pos = a2.make_move(b)
            if pos:
                #print(pos)
                b.move(pos[0], pos[1], a2.color)
        turn = (turn + 1) % 2
        # b.print()

    w, bl = b.stats()
    
    if w > bl:
        winner = WHITE
    elif bl > w:
        winner = BLACK
    else:
        winner = None

    if winner == a1.color:
        a1_won += 1
    elif winner == a2.color:
        a2_won += 1
    else:
        draws += 1

    print(f"Game {i+1} finished. Score: White={w}, Black={bl}")

print("\nResults after", NO_GAMES, "games:")
print("Agent a1 wins:", a1_won)
print("Agent a2 wins:", a2_won)
print("Draws:", draws)