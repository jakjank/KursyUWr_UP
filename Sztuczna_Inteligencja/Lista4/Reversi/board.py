import copy

BOARD_SIZE = 8
EMPTY = 0
WHITE = 1
BLACK = 2
CORNER_POSITIONS = [(0, 0), (0, 7), (7, 0), (7, 7)]

WHITE_BG = "\033[47m  \033[0m"
BLACK_BG = "\033[40m  \033[0m"
EMPTY_BG = "\033[42m  \033[0m"

directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1),(1, -1), (1, 0), (1, 1)]

class Board:
    def __init__(self):
        self.board = [[EMPTY for _ in range(BOARD_SIZE)] for _ in range(BOARD_SIZE)]
        mid = BOARD_SIZE // 2
        self.board[mid - 1][mid - 1] = WHITE
        self.board[mid][mid] = WHITE
        self.board[mid - 1][mid] = BLACK
        self.board[mid][mid - 1] = BLACK
    
    def in_bounds(self, x,y):
        return 0 <= x < BOARD_SIZE and 0 <= y < BOARD_SIZE
    
    def is_opponent_next(self, x, y, opponents_color):
        for dir in directions:
            i, j = x + dir[0], y + dir[1]
            if self.in_bounds(i,j) and self.board[j][i] == opponents_color:
                return True
        return False

    def move(self, x, y, my_color):
        if my_color == WHITE:
            opps_color = BLACK
        else:
            opps_color = WHITE
        if not self.is_opponent_next(x, y, opps_color) or not self.are_flips(x, y, my_color, opps_color):
            return
        self.board[y][x] = my_color
        self.flip(x, y, my_color, opps_color)
        # if is_print:
        #     self.print()
    
    def are_flips(self, x, y, my_color, opps_color):
        #print("\n______",x,y)
        for dir in directions:
            #print(dir, "->", end="")
            i,j = x+dir[0], y+dir[1]
            were_opps = False
            while self.in_bounds(i,j):
                #print("(", i, ", ",j, ")", end="")
                if self.board[j][i] == 0:
                    break
                if self.board[j][i] == opps_color:
                    were_opps = True
                if self.board[j][i] == my_color:
                    if were_opps:
                        return True
                    else:
                        break
                i += dir[0]
                j += dir[1]
            #print()
        return False

    def flip(self, x, y, my_color, opps_color):
        for dir in directions:
            i,j = x+dir[0], y+dir[1]
            were_opps = False
            while self.in_bounds(i,j):
                if self.board[j][i] == 0:
                    were_opps = False
                    break
                if self.board[j][i] == opps_color:
                    were_opps = True
                if self.board[j][i] == my_color:
                    break
                i += dir[0]
                j += dir[1]

            if were_opps and self.in_bounds(i,j):
                i,j = x+dir[0], y+dir[1]
                while self.in_bounds(i,j) and self.board[j][i] == opps_color:
                    self.board[j][i] = my_color
                    i += dir[0]
                    j += dir[1]

    def get_possible_moves(self, my_color):
        if my_color == WHITE:
            opps_color = BLACK
        else:
            opps_color = WHITE
        #my_color = player.get_me()
        positions = []
        for y in range(BOARD_SIZE):
            for x in range(BOARD_SIZE):
                if self.board[y][x] != EMPTY:
                    continue
                if self.is_opponent_next(x,y,opps_color) and self.are_flips(x,y,my_color,opps_color):
                    positions.append((x,y))
        #print(positions)
        return positions
        

    def end(self):
        return not self.get_possible_moves(WHITE) and not self.get_possible_moves(BLACK)

    def print(self):
        for y in range(BOARD_SIZE):
            for x in range(BOARD_SIZE):
                match self.board[y][x]:
                    case 1:
                        print(WHITE_BG,end="")
                    case 2:
                        print(BLACK_BG,end="")
                    case 0:
                        print(EMPTY_BG,end="")
            print()
        print()
    
    # returns #whites pieces, #blacks pieces 
    def stats(self):
        whites, blacks = 0, 0
        for y in range(BOARD_SIZE):
            for x in range(BOARD_SIZE):
                match self.board[y][x]:
                    case 1:
                        whites += 1
                    case 2:
                        blacks += 1
        return whites, blacks
    
    def clone(self):
        return copy.deepcopy(self)
    
    def empty_fields(self):
        return sum(1 for row in self.board for el in row if el==EMPTY)