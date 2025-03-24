class ulamek:    #wszystkie operacje tylko z innymi ulamkami
    def __init__(self , licznik , mianownik):
        self.licznik = licznik
        self.mianownik = mianownik

    def __str__(self):
        return f'{self.licznik}/{self.mianownik}'

    def __add__(self , other):
        return ulamek(self.licznik * other.mianownik + other.licznik * self.mianownik , self.mianownik * other.mianownik )

    def __mul__(self , other):
        return ulamek(self.licznik * other.licznik , self.mianownik * other.mianownik)
    
    def __truediv__(self , other):
        return ulamek(self.licznik * other.mianownik , self.mianownik * other.licznik)

    def __sub__(self , other):
        return ulamek(self.licznik * other.mianownik - other.licznik * self.mianownik , self.mianownik * other.mianownik )

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

a = ulamek(3,4)
b = ulamek(2,5)
print(a+b , a*b , a-b , a/b)


        
