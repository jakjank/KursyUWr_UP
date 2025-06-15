import random
import copy

BOARD = [[0 for _ in range(70)] for _ in range(70)]
BEST = []
LOWEST_EMPTY = 10_000
SQUARES = ".ABCDEFGHIJKLMNOPQRSTUVWX"
INCLUDED = []
NUMS = [i for i in range(24,0,-1)]
NO_TRIES = 1000

def find_first_possible(square):
    for i in range(70):
        for j in range(70):
            if BOARD[i][j] == 0 and i+square < 70 and j+square<70:
                can_fit = True
                for dx in range(square):
                    for dy in range(square):
                        if BOARD[i + dx][j + dy] != 0:
                            can_fit = False
                            break
                # can be better ^^^
                if can_fit:
                    return i,j
    return -1,-1

def fill_board(square, x, y):
    for dx in range(square):
        for dy in range(square):
            BOARD[x + dx][y + dy] = square


def add_square(square):
    # if x not in board already
    x,y = find_first_possible(square)
    if x != -1:
        fill_board(square, x, y)
        INCLUDED.append(square)

def solve():
    global BEST, BOARD, LOWEST_EMPTY, NUMS
    for n in range(NO_TRIES):
        BOARD = [[0 for _ in range(70)] for _ in range(70)]
        for i in NUMS:
            add_square(i)
        if get_empty() < LOWEST_EMPTY:
            LOWEST_EMPTY = get_empty()
            BEST = copy.deepcopy(BOARD)
        random.shuffle(NUMS)

    
def print_board(b=BOARD):
    for row in b:
        for el in row:
            print(SQUARES[el],end="")
            #print(el, end="")
        print()

def get_empty(b=BOARD):
    sum = 0
    for row in b:
        for el in row:
            if el == 0:
                sum += 1
    return sum

def print_stats(b=BOARD):
    print("pustych pol:",get_empty(b))
    #print("zmieszczono kwadraty:",INCLUDED)

solve()
print_board(BEST)
print_stats(BEST)