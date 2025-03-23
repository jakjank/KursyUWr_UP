import zad4
import random
import copy
import time

GO_RANDOM = 10

def check_result(result, lines): #check
    index = 0
    for row in result:
        if zad4.opt_dist2(row, lines[index]) != 0:
            return False
        index += 1

    for col in zip(*result):
        if zad4.opt_dist2(col, lines[index]) != 0:
            return False
        index += 1
    return True

def print_result(result, lines): #check
    print("--------------------")
    k = 0
    for line in result:
        for num in line:
            if num == 1:
                print('#',end="")
            else:
                print('.',end="")
        print(f" {lines[k]}")
        k += 1
    for i in range(k,len(lines)):
        print(lines[i], end="")
    print()

def get_bad_rows(result, lines): #check
    bad_rows = []
    for i in range(len(result)):
        if zad4.opt_dist2(result[i],lines[i]) != 0:
            bad_rows.append(i)
    return bad_rows

def get_bad_cols(result, lines): #check
    bad_cols = []
    for i in range(len(result[0])):
        if zad4.opt_dist2([result[j][i] for j in range(len(result))], lines[len(result) + i]):
            bad_cols.append(i)
    return bad_cols

def get_best_index(result, lines, row_id):
    best_change = 0
    best_id = 0
    for i in range(len(result[0])):
        dist_before = zad4.opt_dist2([result[j][i] for j in range(len(result))], lines[i])
        result[row_id][i] = (result[row_id][i] + 1) % 2
        dist_after = zad4.opt_dist2([result[j][i] for j in range(len(result))], lines[i])
        result[row_id][i] = (result[row_id][i] + 1) % 2
        if dist_before - dist_after > best_change:
            best_change = dist_before - dist_after
            best_id = i
    return best_id

def change_pos(result,x,y):
    if random.randint(1,100) >= GO_RANDOM:
        result[x][y] = (result[x][y] + 1) % 2
    else:
        row = random.randint(0,len(result)-1)
        col = random.randint(0,len(result[0])-1)
        result[row][col] =(result[row][col] + 1) % 2

def solve(dimX, dimY, lines):
    result = [[random.choice([0,1]) for i in range(dimX)] for j in range(dimY)]
    # result = [[0] * dimX for j in range(dimY)]

    while not check_result(result,lines):
        #print_result(result,lines)
        if random.choice([0,1]):
            # do row
            bad_rows = get_bad_rows(result,lines)
            if len(bad_rows) == 0:
                continue
            #print("bad rows: ", bad_rows)
            row_index = random.choice(bad_rows)
            id = get_best_index(result, lines[len(result)::], row_index)
            change_pos(result, row_index, id)
        else:
            # do column
            bad_cols = get_bad_cols(result,lines)
            if len(bad_cols) == 0:
                continue
            #print("bad cols: ", bad_cols)
            col_index = random.choice(bad_cols)
            id = get_best_index([list(row) for row in zip(*result)], lines[0:len(result)], col_index)
            change_pos(result, id, col_index)
        #time.sleep(15)
        
    
    return result

def read(input, output): #check
    lines = []
    with open(input,'r',encoding="utf-8") as f:
        Xdim, Ydim = f.readline().split()
        Xdim, Ydim = int(Xdim), int(Ydim)
        lines = [int(el.strip()) for el in f.readlines()]

    result = solve(Xdim, Ydim, lines)
    print_result(result,lines)

    with open(output,'w',encoding="utf-8") as f:
        for line in result:
            for num in line:
                if num == 1:
                    f.write('#')
                else:
                    f.write('.')
            f.write('\n')

if __name__ == "__main__":
    read("zad5_input.txt", "zad5_output.txt")
    pass


# print(check_result([[1,1,1,1],
#                     [1,1,1,1],
#                     [1,1,1,1],
#                     [1,1,1,1]],
#                     [4,4,4,4,4,4,4,4]))
# print(check_result([[1]*7, 
#                     [0,1,1,1,1,1,0],
#                     [0,0,1,1,1,0,0],
#                     [0,0,0,1,0,0,0],
#                     [0,0,0,1,0,0,0],
#                     [0,0,0,1,0,0,0],
#                     [0,0,0,1,0,0,0],
#                     ],
#                     [7,5,3,1,1,1,1,1,2,3,7,3,2,1]))
