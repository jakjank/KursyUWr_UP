silnia=6 #3! to 6, zaczynamy od 4!
dl=0
for i in range(4,101): #??
    silnia=silnia*i
    dl=len(str(silnia))
    kon=dl%10
    if( kon==2 or kon==3 or kon==4):
        if(dl%100!=12 and dl%100!=13 and dl%100!=14):
            print(i,'! ma ',dl,' cyfry')
        else:
            print(i,'! ma ',dl,' cyfr')
    else:
        print(i,'! ma ',dl,' cyfr')

