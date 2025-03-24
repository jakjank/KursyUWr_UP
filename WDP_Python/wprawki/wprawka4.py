import random

arabia = ('Arabia_Saudyjska', 2, 3, 0.3, 0.3)
argentyna = ('Argentyna', 4, 6, 0.5, 0.8)
meksyk = ('Meksyk', 3, 4, 0.6, 0.5) 
polska = ('Polska', 2, 3, 0.9, 0.8)

grupa = [arabia, argentyna, meksyk, polska]

def mecz(A , B):
    golA=0
    golB=0
    A_FD = A[1] + random.randint(1 , 6)         #sila obrony
    B_FD = B[1] + random.randint(1 , 6)

    A_FA = A[2] + random.randint(1 , 6)         #sila ataku
    B_FA = B[2] + random.randint(1 , 6)
    A_okazja = 0
    B_okazja = 0
    if A_FA - A_FD > 0:             
        A_okazja = A_FA - B_FD
    if B_FA - B_FD > 0:             
        B_okazja = B_FA - A_FD

    for i in range(A_okazja):
        sila_bramkarza = random.random()
        while sila_bramkarza > B[3]:
            sila_bramkarza = random.random()

        bramkost = random.random()
        while bramkost > A[4]:
            bramkost = random.random()

        if bramkost>sila_bramkarza:
            golA = golA+1

    for i in range(B_okazja):
        sila_bramkarza = random.random()
        while sila_bramkarza > A[3]:
            sila_bramkarza = random.random()

        bramkost = random.random()
        while bramkost > B[4]:
            bramkost = random.random()

        if bramkost>sila_bramkarza:
            golB = golB+1

    return (golA , golB)

def rozgrywki_grupowe(grupa , czy_wyniki):
    for i in range(len(grupa)):
        for j in range(i , len(grupa)):
            if i!=j:
                wynik = mecz(grupa[i] , grupa[j])
                if czy_wyniki == True:
                    print(grupa[i][0] , grupa[j][0])
                    print(wynik)
                
                golA = wynik[0]
                golB = wynik[1]

                if golA>golB:
                    tabela[grupa[i][0]][0] += 3
                if golA<golB:
                    tabela[grupa[j][0]][0] += 3
                if golA == golB:
                    tabela[grupa[i][0]][0] += 1
                    tabela[grupa[j][0]][0] += 1
                
                tabela[grupa[i][0]][1] += golA-golB
                tabela[grupa[j][0]][1] += golB-golA

    print(tabela)
    

                
tabela = {}
for i in range(len(grupa)):
        for j in range(i , len(grupa)):
            if i!=j:
                if grupa[i] not in tabela:
                    tabela[grupa[i][0]] = [0,0]
                if grupa[j] not in tabela:
                    tabela[grupa[j][0]] = [0,0] 

rozgrywki_grupowe(grupa,True)

'''
ile_wygr = 0                          prawdopodobienstwo polska w. argentyna
for i in range(100_000):
    k = mecz(grupa[3] , grupa[1])
    A = k[0]
    B = k[1]
    #print (A , B)
    if A>B:
       ile_wygr = ile_wygr+1
pr = ile_wygr/100_000
print(pr)
'''

