def szachownica(n , k):
    licznik = 0

    for i in range(2*n):
        for z in range(k):
            for j in range(2*n):
                if(licznik % 2 == 0):
                    print(k*" " , end="")
                if(licznik % 2 == 1):
                    print(k*"#" , end="")
                licznik = licznik + 1
            print()
        licznik = licznik + 1


n = int(input("Podaj n: "))
k = int(input("Podaj k: "))
szachownica(n , k)