s1 = input("Podaj slowo: ")
s2 = input("Podaj slowo ktore chcesz sprawdzic: ")

literki_1 = {}
literki_2 = {}

ok = 0

for e in s1:
    if e not in literki_1:
        literki_1[e] = 0
    literki_1[e] += 1

for e in s2:
    if e not in literki_2:
        literki_2[e] = 0
    literki_2[e] += 1

for e in literki_2:
    if e not in literki_1:
        ok =1
        break
    if literki_2[e] > literki_1[e]:
        ok =1
        break

if ok == 1:
    print("slowo nie jest ukladalne")
else:
    print("slowo jest ukladalne")