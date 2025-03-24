from kolo import kolo



n = int(input("Podaj wielkosc najmniejszego kola: "))
a = int(input("Ile kol ma zostac wypisanych: "))
b = int(input("O ile ma rosnac promien kolejnych kol: "))

for i in range(a):
    kolo(n+i*2*b , a*b-i*b)