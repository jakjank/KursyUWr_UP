# zadanie 2 z kolokwium z 2017 krotkologo
from turtle import *

def wykonaj(P): #zakladam ze P jest lista instrukcji
    for x in P:
        eval(x[0])(x[1])

def wykonaj2(P):
    for instrukcja in P:
        if len(instrukcja) == 3:
            for i in range(instrukcja[1]):
                wykonaj2(instrukcja[2])
        else:
            wykonaj([instrukcja])

def piszProgram(P, wciecie):
    for instrukcja in P:
        if len(instrukcja) == 3:
            print(f'{wciecie}for i in range({instrukcja[1]}):')
            piszProgram(instrukcja[2] , wciecie+'   ')
        else:
            print(f'{wciecie}{instrukcja[0]}({instrukcja[1]})')

P =[('repeat',10,[('fd',50),('repeat', 4, [('fd',40), ('rt',90)]),('bk',50),('lt',36)] )]
#wykonaj2(P)
piszProgram(P , '')
input()

