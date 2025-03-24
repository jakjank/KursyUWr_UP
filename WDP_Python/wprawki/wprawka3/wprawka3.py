slowa = set(open( 'wprawki\wprawka3\popularne_slowa.txt' , encoding='utf8' ).read().split())
lalka = open('wprawki\wprawka3\lalka.txt' , encoding='utf8').read().split()


d  = {}
t = ''
for i in range(5,11):
    for j in range(len(lalka)-i):
        for z in range(i):
            t = t + (lalka[j+z][0])
        
        if t in slowa:
            print(t)
            for z in range(i):
                print(lalka[j+z] , end=" ")
            print() 
            if t not in d:
                d[t] = 1
            else:
                d[t] += 1
        t=''

smax = sorted(d.keys() , key=d.get , reverse=True)[0]
print(smax) 

for j in range(len(lalka)-len(smax)):
    for z in range(len(smax)):
        t = t + (lalka[j+z][0])
    
    if t == smax:
        for z in range(len(smax)):
            print(lalka[j+z] , end = " ")
        print()
    t = ''

        