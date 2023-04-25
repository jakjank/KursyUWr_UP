napis = input("podaj napis: ")
slowa = []
slowo = ''
for i in range(len(napis)):
    if napis[i] != ' ' :
        slowo = slowo + napis[i]
    if napis[i] == ' ' and slowo != '' :
        slowa.append(slowo)
        slowo = ''
if slowo != '' :
    slowa.append(slowo)

print(slowa)

