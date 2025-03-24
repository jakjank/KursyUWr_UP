class Function
    def initialize(wzor)
        @wzor = wzor
    end

    def value(x)
        @wzor.call(x)
    end

    def zero(a,b,e)
        wynik = []
        # zakładam, że funkcja jest ciągła,
        while a < b
            # sprawdzamy czy wartości końców przedzialiku [a,a+e]
            # są różnych znaków (bądź któwryś jest równy 0), 
            # jeśli tak to znaczy, że gdzieś w nim
            # jest miejsce zerowe, 
            # więc dodajemy środek przedzialiku do wyniku
            if self.value(a) * self.value(a + e) <= 0
                wynik << (2*a + e)/2
            end
            a = a + e
        end
        # jeśli znaleźliśmy jakieś miejsce/a zerowe to je zwracamy,
        # a jak nie to zwracamy nil
        if wynik.length > 0
            return wynik
        end
        return nil
    end

    def field(a,b)
        skok = 0.0001
        pole = 0
        while a < b
            pole = pole + self.value(a) * skok
            a = a + skok
        end
        return pole.round(3)
    end

    def deriv(x)
        # liczymy pochodna z definicji
        return ((self.value(x+0.00001) - self.value(x))/0.00001).round(3)
    end
end

p1 = Function.new(proc{ |x| x*x-2})
puts "Wartość x^2-2 w 2 to " + (p1.value(2)).to_s
puts "a miejsca zerowe to " + p1.zero(-2,3,0.001).to_s
puts ""
p2 = Function.new(proc{|x| x+1})
puts "Pole x+1 na przedziale 0 10 to " + p2.field(0,10).to_s
puts "Pochodna x+1 w 5 i 50 odpowiednio " + p2.deriv(5).to_s+", " +p2.deriv(50).to_s