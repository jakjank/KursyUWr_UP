def silnia(n):
    if n <= 0:
        return 1
    res = 1
    for i in range(1,n+1):
        res = res*i
    return res

def dwumian(n,k):
    if k>n or k<0:
        return 0
    return int(silnia(n)/(silnia(n-k)*silnia(k)))

def kolory_z_worka(liczby, n):
    if n == 1:
        return 1

    return (kolory_z_worka(liczby,n-1)*dwumian(liczby[n-1]-1,liczby[n-1]-liczby[n-2]-1)) % 1_000_000_007


kolory = int(input())
liczby = []
liczby.append(int(input()))
for i in range(1,kolory):
    x = liczby[i-1]
    liczby.append(int(input())+x)

print(kolory_z_worka(liczby, kolory) % 1_000_000_007) 