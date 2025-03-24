from collections import defaultdict as dd
from itertools import permutations
#popularne_slowa = set(open('lista 12\popularne_slowa.txt' , encoding='utf8').read().split())
popularne_slowa = set(open('lista 12\slowa (1).txt' , encoding='utf8').read().split("\n"))


alfabet = 'aąbcćdeęfghijklłmnńoóprsśtuwyzźż'
znaki = ['!' , '.' , '?' , ',' , ':' , ";" , " "]

rzeczy_do_rozszyfrowania = []
tmp = open('lista 12\szyfrogramy.txt' , encoding='utf8').readlines()
for e in tmp:
    rzeczy_do_rozszyfrowania.append(e.strip('\n'))

def perm_post1(s):
    dobre_wart = []
    for litera in s:
        slownik[litera] = 0
    wartosciowania = permutations(alfabet, len(slownik))
    
    for e in wartosciowania:
        slownik = dd(int)
        for l1,l2 in zip(slownik,e):
            slownik[l1]=l2
    
        wynik = ''
        for litera in s:
            wynik = wynik + f'{slownik[litera]}'
        if wynik in popularne_slowa:
            dobre_wart.append(slownik)
    print(s,dobre_wart , len(slownik))
    return dobre_wart

def zloz_slowniki(dobre_wart):
    slownik = dd(str)
    for slowniczek in dobre_wart:
        for litera in slowniczek:
            if litera not in slownik:
                slownik[litera] = slowniczek[litera]
    return slownik

def rozszyfruj(s):
    rozbij = [x for x in s.split() if x not in znaki]
    dobre_wart = []
    print(rozbij)
    for i in range(len(rozbij)):
        dobre_wart.append(perm_post1(rozbij[i]))

    slownik = zloz_slowniki(dobre_wart)

    for e in rozbij:
        for litera in e:
            print(slownik[litera])
        print(' ' , end ='')

rozszyfruj(rzeczy_do_rozszyfrowania[0])