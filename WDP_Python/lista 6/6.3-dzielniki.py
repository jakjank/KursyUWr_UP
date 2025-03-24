def pierwsza(n):
    if n%2 == 0:
        return False
    i = 3
    while i*i <= n:
        if n % i == 0:
            return False
        i = i + 2
    return True

wynik = set()
n = int(input("Podaj n: "))

for i in  range(2 , n):
    if n%i ==0:
        if pierwsza(i):
            if n%2==0:
                wynik.add(2)
            wynik.add(i)

print(wynik)