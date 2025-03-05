from itertools import permutations

our_sum = 0
is_0 = False
how_many_even = 0
cases = int(input())
for i in range(cases):
    our_sum = 0
    is_0 = False
    how_many = 0
    number = str(input())
    for x in number:
        el = int(x)
        if el == 0:
            is_0 = True
        if el%2 == 0:
            how_many = how_many+1
        our_sum = our_sum + el
    
    if our_sum%3==0 and is_0 and how_many>=2:
        print("red")
    else:
        print("cyan")
