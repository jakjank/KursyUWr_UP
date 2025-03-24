def koperta(n):
    for i in range(2*n+1):
        for j in range(2*n+1):
            if(i == 0 or i ==2*n):      # pierwsza i ostatnia linijka
                print((2*n+1)*"*")
                break
            else:
                if(j == 0):
                    print("*" , end="")
                else:
                    if(j == i or j==(2*n-i)):
                        print("*" , end="")
                    else:
                        if(j == 2*n):
                            print("*")
                        else:
                            print(" " , end="")

n = int(input("Podaj n: "))
koperta(n)