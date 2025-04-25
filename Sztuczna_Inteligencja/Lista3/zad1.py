# How?
# simple reasoning is added
# for every row and column if there is a block of 1s
# longer than half of row/column, we mark some field as certain 1s
# for example if we have row of length 5 and block of length 4
# then we know 3 point which are 1s for shure (01110)

import random
import copy
import time
from functools import reduce
from functools import cache
GO_RANDOM = 3
ONES = []
ZEROS = []

@cache
def opt_dist3(seq : list[int], blocks : list[int]):
    n = len(seq)
    res =  n
    
    if len(blocks) == 0:
        return seq.count(1)
    
    last_pos_index = n - sum(blocks) - len(blocks) + 2
    
    for i in range(last_pos_index):
        cur_res = sum(seq[0 : i]) + blocks[0] - sum(seq[i : i+blocks[0]])
        if i+blocks[0] < n:
            cur_res += seq[i+blocks[0]] # we need one zero between blocks
        cur_res += opt_dist3(tuple(seq[i+blocks[0]+1:]), tuple(blocks[1:]))
        res = min(res, cur_res)

    return res

def check_result(result, lines): 
    index = 0
    for row in result:
        if opt_dist3(tuple(row), tuple(lines[index])) != 0:
            return False
        index += 1

    for col in zip(*result):
        if opt_dist3(tuple(col), tuple(lines[index])) != 0:
            return False
        index += 1
    return True

def print_result(result, iteration=-1, *lines):
    # for row in result:
    #     print(row)
    # print("|")
    if lines:
        k=0
        if not iteration == -1:
            print("--------------------", iteration)
        for line in result:
            for num in line:
                if num == 1:
                    print('#',end="")
                else:
                    print('.',end="")
            #print(result[k],lines[0][k],'\n',lines)
            print("->", opt_dist3(tuple(result[k]),tuple(lines[0][k])))
            k+=1
        print()
    else:
        if not iteration == -1:
            print("--------------------", iteration)
        for line in result:
            for num in line:
                if num == 1:
                    print('#',end="")
                else:
                    print('.',end="")
            print()
        print()

def get_bad_rows(result, lines): #check
    bad_rows = []
    for i in range(len(result)):
        if opt_dist3(tuple(result[i]),tuple(lines[i])) != 0:
            bad_rows.append(i)
    return bad_rows

def get_bad_cols(result, lines): #check
    bad_cols = []
    for i in range(len(result[0])):
        if opt_dist3(tuple([result[j][i] for j in range(len(result))]), tuple(lines[len(result) + i])):
            bad_cols.append(i)
    return bad_cols

def get_best_index(result, lines, row_id, row_desc):
    res = []
    best_change = 0
    best_id = 0
    row_dist = opt_dist3(tuple(result[row_id]), tuple(row_desc))
    for i in range(len(result[0])):
        dist_before = opt_dist3(tuple([result[j][i] for j in range(len(result))]), tuple(lines[i]))
        result[row_id][i] = (result[row_id][i] + 1) % 2
        dist_after = opt_dist3(tuple([result[j][i] for j in range(len(result))]), tuple(lines[i]))
        #dist_after += opt_dist3(result[row_id], row_desc)
        result[row_id][i] = (result[row_id][i] + 1) % 2
        if dist_before - dist_after == best_change:
            res.append(i)
        if dist_before - dist_after > best_change: #dist_before + row_dist - dist_after > best_change:
            best_change = dist_before - dist_after
            res = []
            res.append(i)

    return res

def change_pos(result,x,y):
	global ONES
	if((x,y) in ONES):
		#print((x,y))
		pass
	else:
		result[x][y] = (result[x][y] + 1) % 2

def reason(result, lines):
	global ONES
	X = len(result[0])
	Y = len(result)

	for i in range(Y):
		for k in range(len(lines[i])):
			if lines[i][k] > X/2:
				for j in range(X-lines[i][k],lines[i][k]):
					print("row adds", (i,j))
					result[i][j] = 1
					ONES.append((i,j))
		
	for i in range(X):
		for k in range(len(lines[Y+i])):
			if lines[Y+i][k] > Y/2:
				for j in range(Y-lines[Y+i][k],lines[Y+i][k]):
					print("cols adds", (j,i))
					result[j][i] = 1
					ONES.append((j,i))

	print("REASON")
	print_result(result)
	print("ONES:", ONES)
				

def solve(dimX, dimY, lines):
    #result = [[random.choice([0,1]) for i in range(dimY)] for j in range(dimX)]
    result = [[0] * dimY for j in range(dimX)]
    reason(result, lines)
    iteration = 0
    while not check_result(result,lines):
        if(iteration % 1000000 == 0):
            print_result(result,iteration,lines)
        iteration += 1
        if random.randint(1,100) >= GO_RANDOM:
            if random.choice([0,1]):
                bad_rows = get_bad_rows(result,lines)
                if len(bad_rows) == 0:
                    continue
                row_index = random.choice(bad_rows)
                options = get_best_index(result, lines[len(result):], row_index, lines[row_index])
                if len(options) == 0:
                    continue
                id = random.choice(options)
                change_pos(result, row_index, id)
            else:
                bad_cols = get_bad_cols(result,lines)
                if len(bad_cols) == 0:
                    continue
                col_index = random.choice(bad_cols)
                options = get_best_index([list(row) for row in zip(*result)], lines[0:len(result)], col_index, lines[len(result) + col_index - 1])
                if len(options) == 0:
                    continue
                id = random.choice(options)
                change_pos(result, id, col_index)
        else:
            row = random.randint(0,len(result)-1)
            col = random.randint(0,len(result[0])-1)
            while((row,col) in ONES):
                row = random.randint(0,len(result)-1)
                col = random.randint(0,len(result[0])-1)
            # while((row,col) in ONES):
			# 	row = random.randint(0,len(result)-1)
            #     col = random.randint(0,len(result[0])-1)
            result[row][col] =(result[row][col] + 1) % 2
        
    
    return result

def read(input, output):
    lines = []
    with open(input,'r',encoding="utf-8") as f:
        Ydim, Xdim = f.readline().split()
        Ydim, Xdim = int(Xdim), int(Ydim)
        lines = [list(map(int, el.strip().split())) for el in f.readlines()]

    result = solve(Xdim, Ydim, lines)
    print_result(result,-1)

    with open(output,'w',encoding="utf-8") as f:
        for line in result:
            for num in line:
                if num == 1:
                    f.write('#')
                else:
                    f.write('.')
            f.write('\n')

if __name__ == "__main__":
    read("zad_input.txt", "zad_output.txt")
    # test_opt_dist3()
