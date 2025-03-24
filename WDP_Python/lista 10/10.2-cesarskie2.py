slowa = set(open("lista 7\popularne_slowa.txt" , encoding="utf8").read().split())
#slowa = sorted(set(['a','b','c','cd','će','z' , 'lłm' , 'łmm']))
alfabet = 'aąbcćdeęfghijklłmnńoóprsśtuwyzźż'
zbior_alfabet = set([*alfabet])

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

def czy_litery(s):
    for e in s:
        if e not in zbior_alfabet:
            return False
    return True

def cesarskie():
    dl_max = 0
    licznik = 0
    wynik = []
    bylo = set()
    for slowo in slowa:
        licznik +=1
        if len(slowo) >= dl_max:
            if slowo not in bylo:
                if czy_litery(slowo):
                    for i in range(1 , 32):
                        tmp = ceasar(slowo , i)
                        #print(slowo , tmp)
                        if tmp in slowa:
                            if len(slowo) > dl_max:
                                wynik = []
                                wynik.append(f'{(slowo)} - {tmp}')
                                dl_max = len(slowo)
                            else:
                                wynik.append(f'{(slowo)} - {tmp}')
                            bylo = bylo | {tmp}
        if licznik % 10000 == 0:
            print("------------------" , licznik)
    return wynik

print(cesarskie())