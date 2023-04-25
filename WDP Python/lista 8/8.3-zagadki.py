slowa = set(open("lista 7\popularne_slowa.txt" , encoding='utf8').read().split())
imie = input("Podaj imie i nazwisko: ")

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

def przestawianka(imie , slownik_imie):
    dobre_slowa = mozliwe(imie)
    bylo = set()

    for s1 in dobre_slowa:
        for s2 in dobre_slowa:
            if (s1 ,s2) not in bylo:
                if len(s1 + s2) == len(imie):
                    
                    slownik_slow = {}
                    tmp = s1+s2
                    for e in (tmp):
                        if e not in slownik_slow:
                            slownik_slow[e] = 0
                        slownik_slow[e] += 1

                    if slownik_slow == slownik_imie:
                        print(s1 , " " , s2)
                        bylo.add((s1 , s2))
                        bylo.add((s2 , s1))


tmp = imie.split(" ")
imie = ""
for e in tmp:
    imie = imie + e

slownik_imie = {}

for e in imie:
    if e not in slownik_imie:
        slownik_imie[e] = 0
    slownik_imie[e] += 1

przestawianka(imie , slownik_imie)