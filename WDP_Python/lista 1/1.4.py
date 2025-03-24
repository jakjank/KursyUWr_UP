from random import choice

fragmenty = "sia je ta da pra wie nie ce ca be ba bu ko rolo waje wsie fija kura kika fra fiu fu ra ro chry kawa kwa waka tra cny dze rze rzy grzy wsze ja na ma kre dy pu pi bi gra fra dro kila laki juki fika miki fiki we wa wu ku ka ra cza cze czu czte siu by bry bre bru  gi gida gafa fago zy za zi zie zimy cima cia ciu dziu".split()

def losuj_fragment():
     return choice(fragmenty)

def losuj_haslo(n):
    haslo = ""
    fragment = losuj_fragment()
    
    while n - len(haslo) > 5:  
        haslo = haslo + fragment
        fragment = losuj_fragment()
    
    if n - len(haslo) == 5:
        while n - len(fragment) - len(haslo) == 1: # Odrzuca mozliwosc wylosowania '4' , bo wtedy zostanie jedno miejsce
            fragment = losuj_fragment()
        haslo = haslo + fragment

    while n - len(fragment) - len(haslo) != 0:
        fragment = losuj_fragment()

    haslo = haslo + fragment
    
    print(haslo)

for i in range(8,13,2):
    print(f'10 hasel losowanych dla n = {i}')
    for j in range (10):
        losuj_haslo(i)

