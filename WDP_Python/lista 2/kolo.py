
def kolo(n):
    for i in range(n):
        for j in range(n):

            x = n/2 - (i + 0.5)
            y = n/2 - (j + 0.5)

            if(x*x + y*y  < n/2 * n/2 ):
                print("#" , end="")
            else:
                print(" " , end="")
        print()


n = int(input("podaj n: "))
kolo(n)