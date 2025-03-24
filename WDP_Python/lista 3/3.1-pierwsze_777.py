def pierwsza(n):
    if n%2 == 0:
        return False
    i = 3
    while i*i <= n:
        if n % i == 0:
            return False
        i = i + 2
    return True

licznik = 0

for i in range(1 , 100000) :
    if pierwsza(i):
        if "777" in str(i):
            licznik = licznik + 1
            print(i)
            


print("jest " , licznik , " takich liczb")
