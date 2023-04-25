
def erastostenes(b):
    t = []

    for i in range(b+1):
        t.append(i)

    for i in range(b+1):
        if t[i] != 1 and t[i] != 0:
            tmp = 2
            while tmp * t[i] <= b:
                t[tmp * t[i]] = 0
                tmp = tmp + 1
    return(t)

def palindromy(a , b):
    t = erastostenes(b)
    wynik = []

    for i in range (b+1):
        if t[i] != 0 and t[i] >=a:
            tmp1 = str(t[i])
            tmp2 = tmp1[::-1]
            if tmp1 == tmp2:
                wynik.append(t[i])
    return(wynik)

a = int(input('Podaj a: '))
b = int(input('Podaj b: '))

print(palindromy(a , b))





    
