alfabet = 'aąbcćdeęfghijklłmnńoóprsśtuwyzźż'
#slowo = input('Podaj slowo: ')
#klucz = int(input('Podaj klucz: '))

def ceasar(s , k):
    wynik = ''
    for e in s:
        pozycja = 0
        for litera in alfabet:
            if e != litera:
                pozycja += 1
            else:
                break
            
        tmp = (pozycja + k) % len(alfabet)
        wynik = wynik + alfabet[tmp]

    return wynik

for i in range(32):
    print(f'{i} - {ceasar("kuba" , i)}')
