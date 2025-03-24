from collections import defaultdict as dd
from itertools import permutations
popularne_slowa = set(open('lista 12\popularne_slowa.txt' , encoding='utf8').read().split())
alfabet = 'aąbcćdeęfghijklłmnńoóprsśtuwyzźż'
znaki = ['!' , '.' , '?' , ',' , ':' , ";" , " "]

rzeczy_do_rozszyfrowania = []
tmp = open('lista 12\szyfrogramy.txt' , encoding='utf8').readlines()
for e in tmp:
    rzeczy_do_rozszyfrowania.append(e.strip('\n'))

def nowe_slowo(slowo , slownik):
    w = ''
    for litera in slowo:
        w = w + slownik[litera]
    return w

def slownik_wiecej(slowo , slownik):
    for litera in slowo:
        if litera not in slownik:
            slownik[litera] = ''
    return slownik

def uzupelnij_slownik(slownik , wart):
    licznik = 0
    for litera in slownik:
        if slownik[litera] == '':
            slownik[litera] = wart[licznik]
            licznik += 1
    return slownik

def uzupelnij_slownik2(wart , slownik):
    slownik = dd(str)
    for e,w in zip(slownik,wart):
        slownik[e] = w
    return slownik

def rozszyfruj(s):
    slownik = dd(str)
    rozbij = [x for x in s.split() if x not in znaki]
    
    for slowo in rozbij:
        if slowo not in znaki:
            slownik = slownik_wiecej(slowo , slownik)
            litery_dopasowane = [slownik[x] for x in slownik if slownik[x] != '']
            ile_wolnych = sum([1 for x in slownik if slownik[x] == ''])
            nAlfabet = [x for x in alfabet if x not in litery_dopasowane]

            wartosciowania = permutations(nAlfabet , ile_wolnych)

            backup = {x: slownik[x] for x in slownik }
            print(backup)
            for wart in wartosciowania:
                slownik = uzupelnij_slownik(slownik , wart)
                print(slownik)
                print(backup , 'b')
                w = ''
                for litera in slowo:
                    w = w + slownik[litera]
                if w in popularne_slowa:
                    print(w)
                if w not in popularne_slowa:
                    slownik = backup




rozszyfruj(rzeczy_do_rozszyfrowania[0])


