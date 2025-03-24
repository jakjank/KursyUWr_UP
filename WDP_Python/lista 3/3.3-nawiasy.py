s = str(input("podaj tekst: "))
x = []

for i in range(len(s)):
    x.append(s[i])

def usun_w_nawiasach( s ):
    x = list(s)
    for i in range(len(x)):
        if x[i] == '(':
            x[i] = ''
            
            while(x[i] != ')'):
                x[i] = ''
                i = i + 1
            
            x[i] = ''   
    return ''.join(x)

s = usun_w_nawiasach(s)
print(s)


