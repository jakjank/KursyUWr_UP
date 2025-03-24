lalka = open("lista\lalka.txt" , encoding="utf8").read().split()
slowa_polskie = set(open("lista 7 (7.3 do oddania)\popularne_slowa.txt" , encoding="utf8").read().split())

polskie = set(['ą' , 'ć' , 'ę' ,'ł' , 'ź' , 'ż' , 'ó' , 'ś' , 'ń'])
znaki = set([',' , '.' , '/' , '?' , '-'])

def czy_brak_pol(slowo):
    for litera in slowo:
        if litera in polskie:
            return False
    return True

def nowe_slowo(slowo):
    nowe = ""
    for litera in slowo:
        if litera not in znaki:
            nowe = nowe + litera
    return nowe

def dl():
    dl_max = 0
    dl_akt = 0
    fr_max = ''
    fr_akt = ''
    for slowo in lalka:
        if czy_brak_pol(slowo) == True and nowe_slowo(slowo) in slowa_polskie:
            dl_akt += len(nowe_slowo(slowo))
            fr_akt = fr_akt + slowo + ' '
        else:
            if dl_akt>dl_max:
                dl_max = dl_akt
                fr_max = fr_akt
                print(fr_max)
                print()
                print()
            dl_akt = 0
            fr_akt = ''
            

    
dl()