#zadanie 4 kolokwium 2019
from math import *

def wczytajMape(nazwa):
    t = open(nazwa , encoding='utf8').read().split()
    w = []
    for i in range(len(t)):
        tmp = []
        for e in t[i]:
            tmp.append(e)
        w.append(tmp)
    return w
            
def maksOdleglosc(mapa):
    w = []
    for i in range(len(mapa)):                  #wspolrzedne platform do w
        for j in range(len(mapa[i])):
            if mapa[i][j] == '#':
                w.append((i,j))
    maks = 0
    for a in w:                                 #maks z odleglosci
        for b in w:
            odl = sqrt((a[0]-b[0])**2 + (a[1]-b[1])**2)
            if odl > maks:
                maks = odl
    return maks

def sredniaOdleglosc(mapa):
    w = []
    for i in range(len(mapa)):
        for j in range(len(mapa[i])):
            if mapa[i][j] == '#':
                w.append((i,j))
    odleglosci = []
    for a in w:
        for b in w:
            if a != b:
                odl = sqrt((a[0]-b[0])**2 + (a[1]-b[1])**2)
                odleglosci.append(odl)
    return sum(odleglosci)/len(odleglosci)

def ileStanowiskNaKwadrat(mapa):
    ile = 0
    for i in range(len(mapa)):
        for j in range(len(mapa[i])):
            if mapa[i][j] == '#':
                ile += 1
    return ile / (len(mapa) * len(mapa[0]))

mapa = wczytajMape('lista 13\mapa.txt')
maks = maksOdleglosc(mapa)
srednia = sredniaOdleglosc(mapa)
sredniaIloscPlatform = ileStanowiskNaKwadrat(mapa)
print(sredniaIloscPlatform)
