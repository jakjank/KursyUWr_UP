def wieza(n):
    s = ''
    for i in range(n):
        for j in range(3):
            for z in range(n-i-1):
                s += ' '
            for x in range(2*i+1):
                s += '#'
            s += '\n'
    return s
        
print(wieza(3))

'''
t = list(wieza(3))
for e in t:
    print(e ,end="")
'''

def wieze(a):
    wynik = []
    for e in a:
        wynik.append(wieza(e))
    print (wynik)

#wieze([3,1,2])
