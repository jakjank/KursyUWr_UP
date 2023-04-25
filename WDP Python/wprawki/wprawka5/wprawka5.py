dane = open("wprawki\wprawka5\dane.txt" , encoding='utf8').readlines()

def zarobil(linia):
    t = linia.split()
    if t[1] not in osoby:
        osoby[t[1]] = 0
    osoby[t[1]] += int(t[2])

def przelew(linia):
    t = linia.split()
    if t[0] not in osoby:
        osoby[t[0]] = 0
    if t[1] not in osoby:
        osoby[t[1]] = 0
    osoby[t[0]] -= int(t[2])
    osoby[t[1]] += int(t[2])

def wylicz():
    for e in dane:
        if e[0] == '+':
            zarobil(e)
        if e[0] == '#':
            continue
        if e[0] != '#' and e[0] != '+':
            przelew(e)

osoby = {}
wylicz()
print(osoby)
for w in sorted(osoby.keys() , key=osoby.get , reverse=True)[:1]:
    print(w , osoby[w])