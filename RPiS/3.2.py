#1 stycznia 1601 (poniedzialek) – 31 grudnia 2000

dic = {"pon":0,
    "wt":0,
    "sr":0,
    "czw":0,
    "pt":0,
    "sob":0,
    "niedz":0}

dni = ["pon","wt","sr","czw","pt","sob","niedz"]
dzien = 1
miesiac = 1
rok = 1601
i = 0

while dzien != 31 or miesiac != 12 or rok != 2000:
    if dzien == 13:
        dic[dni[i%7]] += 1
    
    i += 1
    if miesiac in [1,3,5,7,8,10,12]:
        if dzien < 31:
            dzien += 1
        else:
            dzien = 1
            miesiac = (miesiac + 1) % 12
            if miesiac == 1:
                rok += 1
        continue

    if miesiac in [4,6,9,11]:
        if dzien < 30:
            dzien += 1
        else:
            dzien = 1
            miesiac += 1
        continue
    
    if miesiac == 2:
        if rok%4 == 0 & (rok%100 != 0 or rok%400 ==0): #przest
            if dzien<29:
                dzien += 1
            else:
                dzien = 1
                miesiac += 1
        else:
            if dzien<28:
                dzien += 1
            else:
                dzien = 1
                miesiac += 1
        continue


print(dic)