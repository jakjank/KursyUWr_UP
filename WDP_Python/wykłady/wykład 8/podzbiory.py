L = input('podaj el: ')
t = []
for e in L:
    t.append(e)

def subset(t):
    if t == []:
        return [set()]
    s2 = subset(t[1:])
    return s2 | [x.add(t[0]) for x in s2]

print(subset(t))
