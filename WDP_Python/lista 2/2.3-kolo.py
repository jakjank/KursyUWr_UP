
def kolo(n):
    for i in range(1 , n+1):
        for j in range(1 , n+1):
            if i<(n+1)/2:
                x = (n+1)/2 - i + 0.5
            else:
                x = i - (n+1)/2 + 0.5

            if j<(n+1)/2:
                y = (n+1)/2 - j + 0.5
            else:
                y = j - (n+1)/2 + 0.5

            if(x*x + y*y  < (n+1)/2 * (n+1)/2 ):
                print("#" , end="")
                #print(x*x+y*y, end="/")
                #print((n+1)/2*(n+1)/2 , end="")
            else:
                print(" " , end="")
                #print(x*x+y*y, end="/")
                #print((n+1)/2*(n+1)/2 , end="")
        print()


n = int(input("podaj n: "))
kolo(n)