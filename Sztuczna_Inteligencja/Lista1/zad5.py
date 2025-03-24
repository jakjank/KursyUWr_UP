import zad4
import random

GO_RANDOM = 5 # %

def check_result(result, lines):
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

def get_column(result,lines):
    columns = []
    for i in range(len(result[0])):
        #print(f"{i}) {[result[j][i] for j in range(len(result))]}, {lines[len(result[0])+i]}")
        if zad4.opt_dist2([result[j][i] for j in range(len(result))], lines[len(result[0])+i]) > 0:
            #print(f"column {i}; dist {zad4.opt_dist2([result[j][i] for j in range(len(result))], lines[len(result[0])+i])}")
            columns.append(i)
    print(f"bad columns {columns}")
    if len(columns) > 0:
        return random.choice(columns)
    return False

def get_row(result,lines):
    rows = []
    for i in range(len(result)):
        if zad4.opt_dist2(result[i],lines[i]) > 0:
            rows.append(i)
    print(f"bad rows {rows}")
    if len(rows) > 0:
        return random.choice(rows)
    return False

# def get_worst_row(result, lines):
#     index = 0
#     worst_row = -1
#     max_dist = -1
#     for i in range(len(result)):
#         cur_dist = zad4.opt_dist2(result[i],lines[index])
#         print(f"row: {i} : {cur_dist}")
#         if cur_dist > max_dist:
#             worst_row = i
#             max_dist = cur_dist
#         index += 1
#     return worst_row

def get_worst_index_from_column(worst_column, result, lines):
    worst_index = -1
    max_diff = -1

    MIN_AFTER = 1000

    for i in range(len(result)):
        tmp = [[i for i in line] for line in result]
        tmp[i][worst_column] = (tmp[i][worst_column]+1) % 2

        cur_dist = zad4.opt_dist2(result[i], lines[i])
        dist_after_change = zad4.opt_dist2(tmp[i], lines[i])
        # if cur_dist - dist_after_change >  max_diff:
        #     max_diff = cur_dist - dist_after_change
        #     worst_index = i
        if dist_after_change < MIN_AFTER:
            MIN_AFTER = dist_after_change
            worst_index = i
    return i

def get_worst_index_from_row(worst_row, result, lines):
    worst_index = -1
    max_diff = -1 # sum of opt_dist for row and column
    
    MIN_AFTER = 1000

    for i in range(len(result[0])):
        tmp = [[i for i in line] for line in result]
        tmp[worst_row][i] = (tmp[worst_row][i]+1) % 2

        cur_dist = zad4.opt_dist2([result[j][i] for j in range(len(result))], lines[len(result) + i])
        dist_after_change = zad4.opt_dist2([tmp[j][i] for j in range(len(result))], lines[len(result) + i])
        
        # if cur_dist - dist_after_change >  max_diff:
        #     max_diff = cur_dist - dist_after_change
        #     worst_index = i
        if dist_after_change < MIN_AFTER:
            MIN_AFTER = dist_after_change
            worst_index = i
    return i

def print_result(result, lines):
    k = 0
    for line in result:
        for num in line:
            if num == 1:
                print('#',end="")
            else:
                print('.',end="")
        print(f" {zad4.opt_dist2(line, lines[k])}")
        k += 1
    index = len(result[0])
    for col in zip(*result):
        print(zad4.opt_dist2(col, lines[index]),end="")
    print()

def change_pos(result,x,y,lines):
    print("BEFORE CHANGE")
    print_result(result, lines)

    if random.randint(1,100) >= GO_RANDOM:
        result[x][y] = (result[x][y] + 1) % 2
        print(f"changed: [{x},{y}]")
        print_result(result, lines)
    else:
        row = random.randint(0,len(result)-1)
        col = random.randint(0,len(result[0])-1)
        result[row][col] =(result[row][col] + 1) % 2
        print(f"changed: [{row},{col}]")
        print_result(result, lines)
        

def solve(dimX, dimY, lines):
    result = [[random.choice([0,1]) for i in range(dimX)] for j in range(dimY)]

    while(not check_result(result, lines)):
        if random.choice([True,False]):
            print("doing row")
            worst_row = get_row(result, lines)
            if worst_row == False:
                continue
            worst_index = get_worst_index_from_row(worst_row, result, lines)
            change_pos(result,worst_row,worst_index,lines)
        else:
            print("doing column")
            worst_column = get_column(result, lines)
            if worst_column == False:
                continue
            worst_index = get_worst_index_from_column(worst_column, result, lines)
            change_pos(result,worst_index,worst_column,lines)

    return result

    

def read(input, output):
    lines = []
    with open(input,'r',encoding="utf-8") as f:
        Xdim, Ydim = f.readline().split()
        Xdim, Ydim = int(Xdim), int(Ydim)
        lines = [int(el.strip()) for el in f.readlines()]

    # result = [[0 for i in range(Xdim)] for j in range(Ydim)]
    # print(result)
    # print(lines)
    result = solve(Xdim, Ydim, lines)

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