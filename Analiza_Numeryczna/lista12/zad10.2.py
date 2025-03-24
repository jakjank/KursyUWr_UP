from math import sin, pi

def T0(f, k, a, b):
    res = []
    for i in range(k):
        #cur = (b-a)/2**k
        sum = f(a)/2
        for j in range(1,2**i):
            sum += f(a + j*(b-a)/2**i)
        sum += f(b)/2
        sum *= (b-a)/2**i
        res.append(sum)
    return res


def Romberg(f, k, m, a, b):
    t = []
    t.append(T0(f, k, a, b))
    #print(t)
    for i in range(1,m+1):
        cur = []
        for j in range(k-i):
            #print(i,j)
            cur.append(((4**i)*t[i-1][j+1]-t[i-1][j])/(4**i-1))
        t.append(cur)
        #print(t)
    return t


def print_rom(t):
    for e in t:
        for el in e:
            print(round(el,3),end=", ")
        print()

def f1(x):
    return 2024*x**8 - 1977*x**4 - 1981

def f2(x):
    return 1/(1+x**2)

def f3(x):
    return sin(5*x - pi/3)


print_rom(Romberg(f1,6,6,-3,2))
#print_rom(Romberg(f2,10,10,-3,3))
# print_rom(Romberg(f3,10,10,-3*pi, pi/6))