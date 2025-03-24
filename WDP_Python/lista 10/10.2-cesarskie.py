slowa = sorted(set(open("lista 7\popularne_slowa.txt" , encoding="utf8").read().split()))
slowa = set(['a','b','c','cd','će','z'])
alfabet = 'aąbcćdeęfghijklłmnńoóprsśtuwyzźż'

def ceasar(s , k):
    wynik = ''
    for e in s:
        pozycja = 0
        for litera in alfabet:
            if e != litera:
                pozycja += 1
            else:
                break
            if pozycja > 31:
                return "pomin to slowo"

        tmp = (pozycja + k) % len(alfabet)
        wynik = wynik + alfabet[tmp]

    return wynik

def cesarskie():
    dl_m = 0
    for i in range(1 , 32):
        for slowo in slowa:
            if len(slowo) >= dl_m:
                tmp = ceasar(slowo , i)
                if tmp in slowa:
                    if len(slowo) >= dl_m:
                        print(f'{slowo} - {tmp}')
                        dl_m = len(slowo)



cesarskie()