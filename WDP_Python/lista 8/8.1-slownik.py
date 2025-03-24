import random
from collections import defaultdict as dd

pol_ang = dd(lambda:[])
popularnosc = {}
brown = open('lista 8\korpus.txt' , encoding='utf8').read().split()

for x in brown:
    if x not in popularnosc:
        popularnosc[x] = 0
    popularnosc[x] += 1

for x in open('lista 8\pol_ang.txt' , encoding='utf8'):
    x = x.strip()
    L = x.split('=')
    if len(L) != 2:
        continue    
    pol, ang = L
    pol_ang[pol].append(ang)
    
def tlumacz(polskie):
    wynik = []
    for s in polskie:
        if s in pol_ang:
            najczestsze = ''
            ile = 0
            for e in pol_ang[s]:
                if e in popularnosc:
                    if popularnosc[e] > ile:
                        najczestsze = e
                        ile = popularnosc[e]
            if najczestsze != '':
                wynik.append(najczestsze)
            else:
                wynik.append(random.choice(pol_ang[s]))
        else:
            wynik.append('[?]')
    return ' '.join(wynik)
    

zdanie = 'chłopiec z bocian i król pójść do myjnia samochód'.split()

print('\n' , tlumacz(zdanie)) 