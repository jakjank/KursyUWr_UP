# How?
# we have lst of 1s and 0s and we want to change least amount of bits 
# to get one block of ones length num
# so for every i from [0, n-num+1] we check how many:
# - 0s are in the [i:i+num] piece of text (we have to change them to 1s)
# - 1s are in the [0:i] and [i+num:n] (we have to change them to 0s)

# speedup by checking what goes inand out of template

def opt_dist(lst, num):
    # print('*',lst,num)
    # block = '1'*num
    n = len(lst)
    # around_block = '0'*(n-num)
    res = n
    no_ones = lst.count('1')
    #print(no_ones)

    for i in range(0,n-num+1):
        current = lst[i:i+num]
        # rest = lst[0:i] + lst[i+num:n]
        no_ones_current = current.count('1')
        # cur_res = 0
        cur_res = num - no_ones_current + (no_ones - no_ones_current)
        # if current and block:
        #     cur_res += bin(int(current,2) ^ int(block,2)).count('1') 
        # if rest and around_block:    
        #     cur_res += bin(int(rest,2) ^ int(around_block,2)).count('1')

        # whats wrong with?
        # if current:
        #     cur_res += bin(int(current,2)).count('0') 
        # if rest:    
        #     cur_res += bin(int(rest,2)).count('1')

        if cur_res < res:
            res = cur_res 

    # print(res)
    return str(res)


def solve(input, output):
    lines = []
    with open(input,'r',encoding="utf-8") as f:
        lines = [el.split() for el in f.readlines()]

    result = []
    for line in lines:
        result.append(opt_dist(line[0],int(line[1])))

    with open(output,'w',encoding="utf-8") as f:
        for line in result:
            f.write(line + '\n')



if __name__ == "__main__":
    solve("zad4_input.txt", "zad4_output.txt")