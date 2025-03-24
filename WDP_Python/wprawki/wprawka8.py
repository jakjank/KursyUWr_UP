import random

plansza = [[2,2,2,2,2,2,2,2],[2,2,2,2,2,2,2,2],[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1]]

pionki1 = [(a,b) for a in range(6,8) for b in range(8) ]
pionki2 = [(a,b) for a in range(0,2)  for b in range(8) ]

def wypisz_plansze():
    for i in range(8):
        for j in range(8):
            print(plansza[i][j],end=' ')
        print('')

def ruch_do_przodu(pionek , pozycja):
    if plansza[pionek[0]][pionek[1]] == 1:
        if plansza[pozycja[0]][pozycja[1]] == 0:
            return True
    if plansza[pionek[0]][pionek[1]] == 2:
        if plansza[pozycja[0]][pozycja[1]] == 0:
            return True
    return False

def ruch_na_boki(pionek , pozycja):
    if plansza[pionek[0]][pionek[1]] == 1:
        if plansza[pozycja[0]][pozycja[1]] == 0 or plansza[pozycja[0]][pozycja[1]] == 2:
            return True        
    if plansza[pionek[0]][pionek[1]] == 2:
        if plansza[pozycja[0]][pozycja[1]] == 0 or plansza[pozycja[0]][pozycja[1]] == 1:
            return True 
    return False

def czy_koniec():
    if any(plansza[0][a] == 1 for a in range(0,8)):
        return False
    if any(plansza[7][a] == 2 for a in range(0,8)):
        return False
    return True

def gra():
    licznik = 1
    while czy_koniec():
        if licznik%2 == 1:
            ok = True
            while ok:
                pionek = random.choice(pionki1)
                pozycja = (pionek[0]-1, pionek[1]+random.randint(-1,1))
                #print(pozycja)
                if pozycja[1]>=0 and pozycja[1]<=7 and pozycja[0]>=0 and pozycja[0]<=7:
                    if pozycja[1] == pionek[1]:
                        if ruch_do_przodu(pionek , pozycja):
                            ok =False
                    if pozycja[1] == pionek[1]+1 or pozycja[1] == pionek[1]-1:
                        if ruch_na_boki(pionek , pozycja):
                            ok =False
                #print(ok)
            plansza[pionek[0]][pionek[1]] = 0
            plansza[pozycja[0]][pozycja[1]] = 1
            if pozycja in pionki2:
                pionki2.remove(pozycja)
            pionki1.append(pozycja)
            pionki1.remove(pionek)
            wypisz_plansze()      
            print('')         
        if licznik%2 ==0:
            ok = True
            while ok:
                pionek = random.choice(pionki2)
                pozycja = (pionek[0]+1, pionek[1]+random.randint(-1,1))
                #print(pozycja)
                if pozycja[1]>=0 and pozycja[1]<=7 and pozycja[0]>=0 and pozycja[0]<=7:
                    if pozycja[1] == pionek[1]:
                        if ruch_do_przodu(pionek , pozycja):
                            ok =False
                    if pozycja[1] == pionek[1]+1 or pozycja[1] == pionek[1]-1:
                        if ruch_na_boki(pionek , pozycja):
                            ok =False
                print(ok)
            plansza[pionek[0]][pionek[1]] = 0
            plansza[pozycja[0]][pozycja[1]] = 2
            if pozycja in pionki1:
                pionki1.remove(pozycja)
            pionki2.append(pozycja)
            pionki2.remove(pionek)
            wypisz_plansze()      
            print('') 
        licznik += 1

gra()

'''
def czy_1_wygraly

def gra_z_agentem():
    licznik = 1
    while czy_koniec():
        if licznik%2 == 1:
            ok = True
            while ok:
                pionek = min(pionki1)
                pozycja = (pionek[0]-1, pionek[1]+random.randint(-1,1))
                print(pionek)
                #print(pozycja)
                if pozycja[1]>=0 and pozycja[1]<=7 and pozycja[0]>=0 and pozycja[0]<=7:
                    if pozycja[1] == pionek[1]:
                        if ruch_do_przodu(pionek , pozycja):
                            ok =False
                    if pozycja[1] == pionek[1]+1 or pozycja[1] == pionek[1]-1:
                        if ruch_na_boki(pionek , pozycja):
                            ok =False
                #print(ok)
            plansza[pionek[0]][pionek[1]] = 0
            plansza[pozycja[0]][pozycja[1]] = 1
            if pozycja in pionki2:
                pionki2.remove(pozycja)
            pionki1.append(pozycja)
            pionki1.remove(pionek)
            wypisz_plansze()      
            print('')         
        if licznik%2 ==0:
            ok = True
            while ok:
                pionek = random.choice(pionki2)
                pozycja = (pionek[0]+1, pionek[1]+random.randint(-1,1))
                #print(pozycja)
                if pozycja[1]>=0 and pozycja[1]<=7 and pozycja[0]>=0 and pozycja[0]<=7:
                    if pozycja[1] == pionek[1]:
                        if ruch_do_przodu(pionek , pozycja):
                            ok =False
                    if pozycja[1] == pionek[1]+1 or pozycja[1] == pionek[1]-1:
                        if ruch_na_boki(pionek , pozycja):
                            ok =False
                print(ok)
            plansza[pionek[0]][pionek[1]] = 0
            plansza[pozycja[0]][pozycja[1]] = 2
            if pozycja in pionki1:
                pionki1.remove(pozycja)
            pionki2.append(pozycja)
            pionki2.remove(pionek)
            wypisz_plansze()      
            print('') 
        licznik += 1
    if czy_1_wygraly():
        return 1

gra_z_agentem()
'''