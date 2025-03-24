from duze_cyfry import daj_cyfre

n = str(input("Podaj liczbe do wypisania: "))

t=[]

for i in range(len(n)):
    if n[i] in ['0','1','2','3','4','5','6','7','8','9']:
        t.append(daj_cyfre(int(n[i])))
    else:
        t.append(daj_cyfre(10))

for i in range(5):
    for j in range(len(n)):
        print(t[j][i] , end=" ")
    print()
