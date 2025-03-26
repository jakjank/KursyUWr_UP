#import zad4
import random
import copy
import time
from functools import reduce

GO_RANDOM = 10

def opt_dist3(seq : list[int], blocks : list[int], depth=0):
    n = len(seq)
    res =  n
    
    if len(blocks) == 0:
        return seq.count(1)
    
    for i in range(n - max(reduce(lambda acc,x: acc+x+1, blocks, 0)-2, 0)):
        cur_res = seq[0 : i].count(1)
        cur_res += seq[i : i+blocks[0]].count(0)
        if i+blocks[0] < n:
            cur_res += seq[i+blocks[0]] # we need one zero between blocks
        cur_res += opt_dist3(seq[i+blocks[0]+1:], blocks[1:], depth+1)
        
        res = min(res, cur_res)

    return res

def check_result(result, lines): 
    index = 0
    for row in result:
        if opt_dist3(row, lines[index]) != 0:
            return False
        index += 1

    for col in zip(*result):
        if opt_dist3(col, lines[index]) != 0:
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
            print("->", opt_dist3(result[k],lines[0][k]))
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
        if opt_dist3(result[i],lines[i]) != 0:
            bad_rows.append(i)
    return bad_rows

def get_bad_cols(result, lines): #check
    bad_cols = []
    for i in range(len(result[0])):
        if opt_dist3([result[j][i] for j in range(len(result))], lines[len(result) + i]):
            bad_cols.append(i)
    return bad_cols

def get_best_index(result, lines, row_id, row_desc):
    best_change = 0
    best_id = 0
    row_dist = opt_dist3(result[row_id], row_desc)
    for i in range(len(result[0])):
        dist_before = opt_dist3([result[j][i] for j in range(len(result))], lines[i])
        result[row_id][i] = (result[row_id][i] + 1) % 2
        dist_after = opt_dist3([result[j][i] for j in range(len(result))], lines[i])
        dist_after += opt_dist3(result[row_id], row_desc)
        result[row_id][i] = (result[row_id][i] + 1) % 2
        if dist_before + row_dist - dist_after > best_change:
            best_change = dist_before - dist_after
            best_id = i
    return best_id

def change_pos(result,x,y):
    result[x][y] = (result[x][y] + 1) % 2

def solve(dimX, dimY, lines):
    #result = [[random.choice([0,1]) for i in range(dimY)] for j in range(dimX)]
    result = [[0] * dimY for j in range(dimX)]
    iteration = 0
    while not check_result(result,lines):
        if(iteration % 1000 == 0):
            print_result(result,iteration,lines)
        iteration += 1
        if random.randint(1,100) >= GO_RANDOM:
            if random.choice([0,1]):
                bad_rows = get_bad_rows(result,lines)
                if len(bad_rows) == 0:
                    continue
                row_index = random.choice(bad_rows)
                id = get_best_index(result, lines[len(result):], row_index, lines[row_index])
                change_pos(result, row_index, id)
            else:
                bad_cols = get_bad_cols(result,lines)
                if len(bad_cols) == 0:
                    continue
                col_index = random.choice(bad_cols)
                id = get_best_index([list(row) for row in zip(*result)], lines[0:len(result)], col_index, lines[len(result) + col_index - 1])
                change_pos(result, id, col_index)
        else:
            row = random.randint(0,len(result)-1)
            col = random.randint(0,len(result[0])-1)
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

def test_opt_dist3():
    cases = [
        ([1,1,1,1,1], [2,2], 1),
        ([0,0,0,1,1,1], [4], 1),
        ([0,0,0,0,0,0], [1,2,1], 4),
        ([1,1,1,1,1,1], [1,2,1], 2),
        ([1,1,1,0,1,1], [3,2], 0),
        ([1,1,1,0,1,1], [2,3], 2),
        ([0,1,1,0,0,1,1,1,1,0], [4,5], 3),
        ([0,1,1,1,0,0,1,1,1,0], [3,3], 0),
        ([0,1,1,1,1,1,1,1,1,0], [3,3], 2),
        ([1,1,1,1,0,1,1,1,1,0], [3,3], 2),
        ([0,0,1,1,1,1,0,1,0,0], [10], 5)
    ]
    for el in cases:
        print(opt_dist3(el[0],el[1]), opt_dist3(el[0],el[1])==el[2])

if __name__ == "__main__":
    read("zad_input.txt", "zad_output.txt")
    # test_opt_dist3()
    pass