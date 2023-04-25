from collections import defaultdict as dd
from itertools import permutations
import random

def utworz_graf(start , ktore_wywolanie): #ale po co tworzyc??
    sytuacja_w_swiecie = dd(list)
    twory = ['wilk' , 'koza' , 'kapusta' , 'lodz']
    brzeg1 = sorted(start)
    brzeg2 = sorted([x for x in twory if x not in brzeg1])
    po_ruchu = []
    if 'lodz' in brzeg1:
        for e in brzeg1:
            po_ruchu.append(tuple(sorted([x for x in brzeg1 if x != 'lodz' and x != e])))
        tmp = (tuple(brzeg1) , tuple(brzeg2))
        sytuacja_w_swiecie[tmp] = tuple(po_ruchu)
    else:
        for e in brzeg2:
            if e != 'lodz':
                po_ruchu.append(tuple(sorted([x for x in brzeg1] + [e] + ['lodz'])))
            else:
                po_ruchu.append(tuple(sorted([x for x in brzeg1] + [e])))
        tmp = (tuple(brzeg1) , tuple(brzeg2))
        sytuacja_w_swiecie[tmp] = tuple(po_ruchu)
    
    print(po_ruchu , sytuacja_w_swiecie)

    return sytuacja_w_swiecie     


def w_głąb():
    twory = ['wilk' , 'koza' , 'kapusta' , 'lodz']
    brzeg1 = set(['wilk' ,'koza' , 'kapusta' , 'lodz'])
    brzeg2 = set([])
    stary_brzeg1 = set()
    stary_brzeg2 = set()
    zle1 = set(['wilk' , 'koza'])
    zle2 = set(['koza' , 'kapusta'])
    bylo = [[brzeg1,brzeg2] , [set(['koza','wilk','kapusta']),set(['lodz'])]] #male? oszustwo

    print('0 ' ,brzeg1, '            ',brzeg2)
    jeszcze_nie = True

    while jeszcze_nie:
        if 'lodz' in brzeg1:
            zle_bo_zle = True
            zle_bo_bylo = True
            licznik = 0
            while zle_bo_zle or zle_bo_bylo:
                licznik += 1
                zle_bo_zle = True
                zle_bo_bylo = True
                zabierz = ['lodz'] + [random.choice([x for x in brzeg1 if x != 'lodz']+['nic'])]
                nowy_brzeg1 = {x for x in brzeg1 if x not in zabierz}
                nowy_brzeg2 = brzeg2 | {x for x in zabierz if x != 'nic'}
                if nowy_brzeg1 != zle1 and nowy_brzeg1 != zle2:
                    zle_bo_zle = False
                    if [nowy_brzeg1 , nowy_brzeg2] not in bylo:
                        zle_bo_bylo = False
                        stary_brzeg1 = brzeg1
                        stary_brzeg2 = brzeg2
                        brzeg1 = nowy_brzeg1
                        brzeg2 = nowy_brzeg2
                        bylo.append([brzeg1,brzeg2])
                        #print(zabierz , end = ' ')
                if licznik == 10 and len(bylo)>=2:
                    bylo = bylo[0:len(bylo)-1]
                    brzeg1 = bylo[-1][0]
                    brzeg2 = bylo[-1][1]
                    licznik = 0
            print('1 ', brzeg1 , '            ' , brzeg2)


        else:
            zle_bo_zle = True
            zle_bo_bylo = True
            licznik = 0
            while zle_bo_zle or zle_bo_bylo:
                licznik +=1
                zle_bo_zle = True
                zle_bo_bylo = True
                zabierz = ['lodz'] + [random.choice([x for x in brzeg2 if x != 'lodz'] + ['nic'])]
                nowy_brzeg2 = {x for x in brzeg2 if x not in zabierz}
                nowy_brzeg1 = brzeg1 | {x for x in zabierz if x != 'nic'}
                if nowy_brzeg2 != zle1 and nowy_brzeg2 != zle2:
                    zle_bo_zle = False
                    if [nowy_brzeg1 , nowy_brzeg2] not in bylo:
                        zle_bo_bylo = False
                        brzeg1 = nowy_brzeg1
                        brzeg2 = nowy_brzeg2
                        bylo.append([brzeg1,brzeg2])
                        #print(zabierz , end = ' ')
                if licznik == 10 and len(bylo)>=2:
                    bylo = bylo[0:len(bylo)-1]
                    brzeg1 = bylo[-1][0]
                    brzeg2 = bylo[-1][1]
                    licznik = 0
            print('2 ' , brzeg1 , '            ' , brzeg2)

        if brzeg1 == set():
            jeszcze_nie = False


def losowo():
    brzeg1 = set(['wilk' ,'koza' , 'kapusta'])
    brzeg2 = set([])
    zle1 = set(['wilk' , 'koza'])
    zle2 = set(['koza' , 'kapusta'])

    licznik = 0 #mowi na ktorej stronie brzegu jestesmy
    co_zabierze1 = ''
    co_zabierze2 = ''

    while True:
        if licznik % 2 == 0:
            zle = True
            while zle:
                co_zabierze1 = random.choice(list(brzeg1 | {'nic'}))
                tmp = {x for x in brzeg1 if x != co_zabierze1}
                if tmp != zle1 and tmp != zle2:
                    zle = False
            if co_zabierze1 != 'nic':
                brzeg1 -= {co_zabierze1}
            print(f'{brzeg1} -- {co_zabierze1} --> {brzeg2}')
            if co_zabierze1 != 'nic':
                brzeg2.add(co_zabierze1)
            licznik += 1
        
        if brzeg2 == {'wilk' , 'koza' , 'kapusta'}:
            break

        if licznik % 2 == 1:
            zle = True
            while zle:
                co_zabierze2 = random.choice(list(brzeg2 | {'nic'}))
                tmp = {x for x in brzeg2 if x != co_zabierze2}
                if tmp != zle1 and tmp != zle2:
                    zle = False
            if co_zabierze2 != 'nic':
                brzeg2 -= {co_zabierze2}
            print(f'{brzeg1} <-- {co_zabierze2} -- {brzeg2}')
            if co_zabierze2 != 'nic':
                brzeg1.add(co_zabierze2)
            licznik += 1
        
        if brzeg2 == {'wilk' , 'koza' , 'kapusta'}:
            break

w_głąb()