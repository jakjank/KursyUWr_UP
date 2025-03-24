slowa = set(open("lista 7\popularne_slowa.txt" , encoding='utf8').read().split())

def odwroc(slowo):
    tmp = ''
    for e in slowo:
        tmp = e + tmp
    return tmp

def odwrotne():
    bylo = set()
    for slowo in slowa:
        if slowo not in bylo:
            slowo = odwroc(slowo)
            if slowo in slowa:
                print(odwroc(slowo) , "  " , slowo)
        bylo | {slowo}

odwrotne()