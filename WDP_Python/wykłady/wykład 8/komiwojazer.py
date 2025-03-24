import random

L = input().split(" ")

def perm(L):
    if L == []:
        return [[]]
    ps = perm(L[1:])
    h = L[0]
    return [p[:i]+[h]+p[i:] for p in ps for i in range(0, len(p)+1)]

print(perm(L))