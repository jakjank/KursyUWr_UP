slowa = set(open("lista 7\popularne_slowa.txt" , encoding='utf8').read().split())

def ukladalne(a ,b):
    literki_1 = {}
    literki_2 = {}

    ok = True

    for e in a:
        if e not in literki_1:
            literki_1[e] = 0
        literki_1[e] += 1

    for e in b:
        if e not in literki_2:
            literki_2[e] = 0
        literki_2[e] += 1

    for e in literki_2:
        if e not in literki_1:
            ok = False
            break
        if literki_2[e] > literki_1[e]:
            ok = False
            break
    return ok

def mozliwe(imie):
    nowe = set()
    for slowo in slowa:
        if ukladalne(imie , slowo):
            nowe.add(slowo)
    return nowe

def przekladanki(litery):
    slowa2 = mozliwe(litery)
    bylo = set()
    for s1 in slowa2:
        for s2 in slowa2:
            if len(s1+s2)<len(litery):
                for s3 in slowa2:
                    if len(s1+s2+s3) == len(litery):
                        if tuple(sorted([s1,s2,s3])) not in bylo:
                            tmp = s1+s2+s3
                            slownik_slow = {}
                            for e in (tmp):
                                if e not in slownik_slow:
                                    slownik_slow[e] = 0
                                slownik_slow[e] += 1
                            
                            if slownik_liter == slownik_slow:
                                print(s1,s2,s3)
                                bylo.add(tuple(sorted([s1,s2,s3])))



litery = input("Podaj litery: ")
slownik_liter = {}
for e in litery:
    if e not in slownik_liter:
        slownik_liter[e]=0
    slownik_liter[e]+=1
przekladanki(litery)