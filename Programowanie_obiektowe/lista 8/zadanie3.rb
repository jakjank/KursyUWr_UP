# Windows Visual Studio Code
# ruby 3.2.2

class WyrazenieONP
    def initialize(tab)
        @wyrazenie = tab
    end

    # metoda oblicz ze słownikiem z wartościami zmiennych
    # domyślnie pusty
    def oblicz(slownik = {})
        stos = []
        @wyrazenie.each do |element|
            # element w tablicy jest albo liczbą 
            if element.is_a?(Numeric)
                stos << element
            # albo zmienną
            elsif slownik.key?(element)
                stos << slownik[element]
            # albo operatorem (+, -, / ,*)
            else
                arg2 = stos.pop
                arg1 = stos.pop
                # takie send - coś wspaniałego, 
                # prawie jak w Rackecie
                wynik = arg1.send(element, arg2)
                stos << wynik
            end
            # wypisujemy aktualny wygląd stosu
            puts "#{stos}"
        end
        stos.first
    end
end

# (1 + 2) * 3 = 9
przyklad1 = WyrazenieONP.new([1, 2, '+', 3, '*'])
puts przyklad1.oblicz()
puts ""

# (2 - 2) * 2 = 0
przyklad2 = WyrazenieONP.new([2, 'x', '-', 2, '*'])
puts przyklad2.oblicz({'x' => 2})
puts ""

# (4 / 2) * 0 - 1 = -1
przyklad3 = WyrazenieONP.new(['x', 'y', '/', 'z', '*', 1, '-'])
puts przyklad3.oblicz({'x' => 4, 'y' => 2, 'z' => 0})

 