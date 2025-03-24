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
        cur = [0]*i
        for j in range(i,k-i+1):
            #print(j)
            cur.append((4**i*t[i-1][j-1]-t[i-1][j])/(4**i-1))
        t.append(cur)
        #print(t)
    return t


def print_rom(t):
    pass

def f1(x):
    return 2024*x**8 - 1977*x**4 - 1981

print(Romberg(f1,4,4,-3,2))