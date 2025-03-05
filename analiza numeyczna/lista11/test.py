def il_skalarny(xs,f,g):
    suma=0
    for x in xs:
        suma += f(x)*g(x)
        print(suma)

#il_skalarny([-9,-6,0,6,9], lambda x : -3 if x==9 or x==-9 else 4 if x==4 or x==-4 else -2 , lambda x : x**2-234/5)
#il_skalarny([-9,-6,0,6,9], lambda x : x, lambda x : 1)
# il_skalarny([-9,-6,0,6,9], lambda x : x**2-234/5 , lambda x : x**2-234/5)
il_skalarny([-9,-6,0,6,9], lambda x : 2*x**2 - 468/5, lambda x : 1)