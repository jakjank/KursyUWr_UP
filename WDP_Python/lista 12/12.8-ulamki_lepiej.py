def skroc(self):
    while self.licznik%2 == 0 and self.mianownik%2 == 0:
            self.licznik = self.licznik/2
            self.mianownik=self.mianownik/2
    for i in range(3 , int(self.licznik)//2+2 , 2): 
        while self.licznik%i == 0 and self.mianownik%i == 0:
            self.licznik = self.licznik/i
            self.mianownik=self.mianownik/i
    return int(self.licznik) , int(self.mianownik)

class Ulamek:    #wszystkie operacje tylko z innymi ulamkami
    def __init__(self , licznik , mianownik):
        self.licznik = licznik
        self.mianownik = mianownik
        tmp = skroc(self)
        self.licznik = tmp[0]
        self.mianownik = tmp[1]

    def __str__(self):
        tmp = skroc(self)
        return f'{tmp[0]}/{tmp[1]}'

    def __add__(self , other): # +
        tmp = skroc(ulamek(self.licznik * other.mianownik + other.licznik * self.mianownik , self.mianownik * other.mianownik))
        return ulamek(tmp[0],tmp[1])

    def __mul__(self , other): # *
        tmp = skroc(ulamek(self.licznik * other.licznik , self.mianownik * other.mianownik))
        return ulamek(tmp[0],tmp[1])
    
    def __truediv__(self , other): # /
        tmp = skroc(ulamek(self.licznik * other.mianownik , self.mianownik * other.licznik))
        return ulamek(tmp[0],tmp[1])

    def __sub__(self , other): # -
        tmp = skroc(ulamek(self.licznik * other.mianownik - other.licznik * self.mianownik , self.mianownik * other.mianownik))
        return ulamek(tmp[0],tmp[1])

    def __lt__(self , other): # <
        if self.licznik * other.mianownik < other.licznik * self.mianownik:
            return True
        return False
    
    def __le__(self , other): # <=
        if self.licznik * other.mianownik <= other.licznik * self.mianownik:
            return True
        return False

    def __eq__(self , other): # ==
        if self.licznik * other.mianownik - other.licznik * self.mianownik == 0:
            return True
        return False

    def __ne__(self , other): # !=
        return not (self == other)

e = '2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427427466391932003059921817413596629043572900334295260'

#Bardzo na siłe ale coz. jaka anegdota?

for i in range(2 , len(e)-5):
    tmp = int(e[i:i+5])
    if len(str(tmp)) == 5:
        for j in range(2 , tmp//2+1):
            if Ulamek(tmp , j).licznik != tmp:
                break
            if j == tmp//2:
                print(tmp , i)
