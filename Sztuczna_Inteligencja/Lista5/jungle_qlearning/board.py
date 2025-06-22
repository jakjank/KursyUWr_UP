import copy

# board is 7x9 with superiority 
# r < c < d < w < j < t < l < e
# L.#*#.T 0
# .D.#.C. 1
# R.J.W.E 2
# .~~.~~. 3
# .~~.~~. 4 
# .~~.~~. 5
# e.w.j.r 6
# .c.#.d. 7
# t.#*#.l 8

#players:
BIG = 1
SMALL = 0

#starting positions of animals:
SBIGS =   [(2, 0), (1, 5), (1, 1), (2, 4), (2, 2), (0, 6), (0, 0), (2, 6)]
SSMALLS = [(6, 6), (7, 1), (7, 5), (6, 2), (6, 4), (8, 0), (8, 6), (6, 0)]

WATER = [(3,1),(3,2),(3,4),(3,5),(4,1),(4,2),(4,4),(4,5),(5,1),(5,2),(5,4),(5,5)]
TRAPS = [(0,2),(1,3),(0,4),(7,3),(8,2),(8,4)]

ANIMALS = ['R','C','D','W','J','T','L','E']


class Board:
    def __init__(self, sbigs:list=SBIGS, ssmalls:list=SSMALLS):
        self.BIGS = copy.deepcopy(sbigs)
        self.SMALLS = copy.deepcopy(ssmalls)

    # return a set of tuples where each consist of 
    # 4 numbers: xs ys xd xd  
    def get_possible_moves(self, p):
        return (
            self.rat_moves(p) + 
            self.cat_moves(p) + 
            self.dog_moves(p) + 
            self.wolf_moves(p) + 
            self.panther_moves(p) + 
            self.tiger_moves(p) + 
            self.lion_moves(p) + 
            self.elephant_moves(p)
        )

    def get_position(self, NO_animal, player):
        if player == BIG:
            return  self.BIGS[NO_animal]
        return self.SMALLS[NO_animal]

    def get_valid_neighbors(self, position):
        result = []
        for dir in [(1,0),(0,1),(-1,0),(0,-1)]:
            x, y = position[1] + dir[1], position[0] + dir[0]
            if 0 <= x < 7 and 0 <= y < 9:
                result.append((y,x))
        return result

    def in_water(self, pos):
        return pos in WATER
        
    def in_trap(self, pos):
        return pos in TRAPS

    def in_opp_hole(self, pos, player):
        if player == BIG:
            return pos == (8,3)
        return pos == (0,3)

    def in_my_hole(self, pos, player):
        if player == BIG:
            return pos == (0,3)
        return pos == (8,3)
    
    def my_goto_hole(self, player):
        if player == SMALL:
            return (8,3)
        return (0,3)

    def players_board(self, player):
        if player == BIG:
            return self.BIGS
        return self.SMALLS

    def ops_board(self, player):
        if player == BIG:
            return self.SMALLS
        return self.BIGS

    def can_go_for_tiger_and_lion(self, position):
        result = []
        for dir in [(1,0),(0,1),(-1,0),(0,-1)]:
            x, y = position[1] + dir[1], position[0] + dir[0]
            if 0 <= x < 7 and 0 <= y < 9:
                while (y,x) in WATER:
                    x += dir[1]
                    y += dir[0]
                result.append((y,x))
        return result

    def rat_moves(self, player):
        pos = self.get_position(0,player)
        if pos[0] == -1 and pos[1] == -1: #zbity
            return []
        can_go = self.get_valid_neighbors(pos)

        can_go = [x for x in can_go if not self.in_my_hole(x,player)] # nie w naszej norze
        can_go = [x for x in can_go if x not in self.players_board(player)]# nie wchodzi na naszych
        can_go = [x for x in can_go if (x not in self.ops_board(player)[1:7] or x in TRAPS)]# nie atakuje wiekszych (poza sloniem) chyba ze jest w pulapce
        can_go = [x for x in can_go if not (pos in WATER and x in self.ops_board(player))]# nie atakuje z wody
        return [(pos[0],pos[1],y,x) for y,x in can_go]

    def cat_moves(self, player):
        pos = self.get_position(1,player)
        if pos[0] == -1 and pos[1] == -1: #zbity
            return []
        can_go = self.get_valid_neighbors(pos)
        can_go = [x for x in can_go if not self.in_my_hole(x,player)] # nie w naszej norze
        can_go = [x for x in can_go if x not in self.players_board(player)]# nie wchodzi na naszych
        can_go = [x for x in can_go if (x not in self.ops_board(player)[2:8] or x in TRAPS)]# nie atakuje wiekszych (poza sloniem) chyba ze jest w pulapce
        can_go = [x for x in can_go if x not in WATER]#not in water
        return [(pos[0],pos[1],y,x) for y,x in can_go]

    def dog_moves(self, player):
        pos = self.get_position(2,player)
        if pos[0] == -1 and pos[1] == -1: #zbity
            return []
        can_go = self.get_valid_neighbors(pos)
        can_go = [x for x in can_go if not self.in_my_hole(x,player)] # nie w naszej norze
        can_go = [x for x in can_go if x not in self.players_board(player)]# nie wchodzi na naszych
        can_go = [x for x in can_go if (x not in self.ops_board(player)[3:8] or x in TRAPS)]# nie atakuje wiekszych (poza sloniem) chyba ze jest w pulapce
        can_go = [x for x in can_go if x not in WATER]#not in water
        return [(pos[0],pos[1],y,x) for y,x in can_go]

    def wolf_moves(self, player):
        pos = self.get_position(3,player)
        if pos[0] == -1 and pos[1] == -1: #zbity
            return []
        can_go = self.get_valid_neighbors(pos)
        can_go = [x for x in can_go if not self.in_my_hole(x,player)] # nie w naszej norze
        can_go = [x for x in can_go if x not in self.players_board(player)]# nie wchodzi na naszych
        can_go = [x for x in can_go if (x not in self.ops_board(player)[4:8] or x in TRAPS)]# nie atakuje wiekszych (poza sloniem) chyba ze jest w pulapce
        can_go = [x for x in can_go if x not in WATER]#not in water
        return [(pos[0],pos[1],y,x) for y,x in can_go]

    def panther_moves(self, player):
        pos = self.get_position(4,player)
        if pos[0] == -1 and pos[1] == -1: #zbity
            return []
        can_go = self.get_valid_neighbors(pos)
        can_go = [x for x in can_go if not self.in_my_hole(x,player)] # nie w naszej norze
        can_go = [x for x in can_go if x not in self.players_board(player)]# nie wchodzi na naszych
        can_go = [x for x in can_go if (x not in self.ops_board(player)[5:8] or x in TRAPS)]# nie atakuje wiekszych (poza sloniem) chyba ze jest w pulapce
        can_go = [x for x in can_go if x not in WATER]#not in water
        return [(pos[0],pos[1],y,x) for y,x in can_go]

    def tiger_moves(self, player):
        pos = self.get_position(5,player)
        if pos[0] == -1 and pos[1] == -1: #zbity
            return []
        can_go = self.can_go_for_tiger_and_lion(pos)
        can_go = [x for x in can_go if not self.in_my_hole(x,player)] # nie w naszej norze
        can_go = [x for x in can_go if x not in self.players_board(player)]# nie wchodzi na naszych
        can_go = [x for x in can_go if (x not in self.ops_board(player)[6:8] or x in TRAPS)]# nie atakuje wiekszych (poza sloniem) chyba ze jest w pulapce
        can_go = [x for x in can_go if x not in WATER]#not in water
        can_go = [x for x in can_go if x not in WATER]#not in water
        return [(pos[0],pos[1],y,x) for y,x in can_go]

    def lion_moves(self, player):
        pos = self.get_position(6,player)
        if pos[0] == -1 and pos[1] == -1: #zbity
            return []
        can_go = self.can_go_for_tiger_and_lion(pos)
        can_go = [x for x in can_go if not self.in_my_hole(x,player)] # nie w naszej norze
        can_go = [x for x in can_go if x not in self.players_board(player)]# nie wchodzi na naszych
        can_go = [x for x in can_go if (x not in self.ops_board(player)[7:8] or x in TRAPS)]# nie atakuje wiekszych (poza sloniem) chyba ze jest w pulapce
        can_go = [x for x in can_go if x not in WATER]#not in water
        return [(pos[0],pos[1],y,x) for y,x in can_go]

    def elephant_moves(self, player):
        pos = self.get_position(7,player)
        if pos[0] == -1 and pos[1] == -1: #zbity
            return []
        can_go = self.get_valid_neighbors(pos)
        can_go = [x for x in can_go if not self.in_my_hole(x,player)] # nie w naszej norze
        can_go = [x for x in can_go if x not in self.players_board(player)]# nie wchodzi na naszych
        can_go = [x for x in can_go if (x not in self.ops_board(player)[0:1] or x in TRAPS)]#nie atakuje szczura
        can_go = [x for x in can_go if x not in WATER]#not in water
        return [(pos[0],pos[1],y,x) for y,x in can_go]

    def print_board(self):
        board = [
            list("..#*#.."),
            list("...#..."),
            list("......."),
            list(".~~.~~."),
            list(".~~.~~."),
            list(".~~.~~."),
            list("......."),
            list("...#..."),
            list("..#*#..")
            ]
        i = 0
        for (y,x) in self.BIGS:
            if 0 <= x < 7 and 0 <= y < 9:
                board[y][x] = ANIMALS[i]
            i += 1
        i = 0
        for (y,x) in self.SMALLS:
            if 0 <= x < 7 and 0 <= y < 9:
                board[y][x] = ANIMALS[i].lower()
            i += 1
        for row in board:
            for el in row:
                print(el,end="")
            print()
        print()

    # partialy checks validity
    def valid_move(self,old_pos,new_pos,player):
        if 0 <= new_pos[1] < 7 and 0 <= new_pos[0] < 9 and old_pos in self.players_board(player):
            if new_pos not in self.ops_board(player):
                return True
            if new_pos in TRAPS:
                return True
            old_index = self.players_board(player).index(old_pos)
            new_index = self.ops_board(player).index(new_pos)
            if old_index == 7: # elephant cant kill mice
                if 1 <= new_index:
                    return True
                else:
                    return False
            elif old_index == 0: # mice can kill other mice and elephant
                if 7 == new_index or 0 == new_index:
                    return True
                else:
                    return False
            else:
                if new_index <= old_index:
                    return True
            return False
        print("first if fail")
        return False

    def move(self, old_pos, new_pos, player, ask_fag=False):
        if self.valid_move(old_pos,new_pos,player):
            index = self.players_board(player).index(old_pos)
            self.players_board(player)[index] = new_pos
        else:
            print("BIG ERROR")
            self.print_board()
            print(old_pos, "-?>", new_pos)
            input()
        if new_pos in self.ops_board(player):
            # if(ask_fag):
            #     # input(f"bicie {old_pos} na {new_pos}")
            #     print("BICIE!")
            #     print(self.BIGS)
            #     print(self.SMALLS)
            index = self.ops_board(player).index(new_pos)
            self.ops_board(player)[index] = (-1,-1)
            # if(ask_fag):
            #     print("zmienilo sie na:")
            #     print(self.BIGS)
            #     print(self.SMALLS)
            #     # input("wznow")
        return {
            "player" : player,
            "start" : old_pos,
            "end" : new_pos,
            "captured" : index
        }

    def win(self, print_flag=False):
        if(print_flag):
            print("win checking in function")
        if (0,3) in self.BIGS:
            print("wszedlo do siebie")
            return True,-1
        if (0,3) in self.SMALLS:
            return True, SMALL
        if (8,3) in self.SMALLS:
            print("wszedlo do siebie")
            return True,-1
        if (8,3) in self.BIGS:
            return True,BIG
        if all(fig == (-1,-1) for fig in self.BIGS):
            return True,SMALL
        if all(fig == (-1,-1) for fig in self.SMALLS):
            return True,BIG
        return False,-1