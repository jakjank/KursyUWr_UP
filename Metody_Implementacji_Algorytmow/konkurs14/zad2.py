n = int(input())

t={}
# t['a'] = 1
# print(t)

for i in range(1,n+1):
    t[i] = []

for i in range(n):
    s = input().split()
    t[int(s[0])].append(int(s[1]))


