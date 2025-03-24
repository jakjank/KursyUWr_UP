class Collection
    def initialize()
        @value = nil
        @previous = nil
        @next = nil
        @position = nil
    end

    def set_previous(col)
        @previous = col
    end

    def get_previous()
        return @previous
    end

    def set_next(col)
        @next = col
    end

    def get_next()
        return @next
    end

    def set_value(value)
        @value = value
    end

    def get_value()
        return @value
    end

    def set_position(i)
        @position = i
    end

    def get_position()
        return @position
    end

    def add1()
        @position = @position + 1
        if @next != nil
            @next.add1()
        end
    end

    def add(value)
        if @value == nil
            @value = value
            @position = 0
        else
            if value > @value
                if @next == nil
                    @next = Collection.new()
                    @next.set_previous(self)
                    @next.set_value(value)
                    @next.set_position(@position + 1)
                elsif value < @next.get_value()
                    tmp = @next
                    tmp.add1()
                    @next = Collection.new()
                    @next.set_previous(self)
                    @next.set_value(value)
                    @next.set_next(tmp)
                    @next.set_position(@position + 1)
                else
                    @next.add(value)
                end
            else 
                if @previous == nil
                    @previous = Collection.new()
                    @previous.set_next(self)
                    @previous.set_value(value)
                    @previous.set_position(@position)
                    self.add1()
                elsif value > @previous.get_value()
                    tmp = @previous
                    self.add1()
                    @previous = Collection.new()
                    @previous.set_previous(tmp)
                    @previous.set_value(value)
                    @previous.set_position(@position - 1)
                    @previous.set_next(self)
                else
                    @previous.add(value)
                end
            end
        end
    end

    def get(i)
        if i == @position
            return @value
        elsif (i > @position && @next == nil) || (i < @position && @previous == nil)
            return "Index out of range"
        elsif i < @position
            @previous.get(i)
        else
            @next.get(i)
        end
    end
    
    def length()
        if @value == nil
            return 0
        elsif @next == nil
            return @position + 1
        else
            @next.length()
        end
    end
end

class Search
    # sprawdza po kolei w górę lub w dół
    def search1(collection, value)
        # pierwszy warunek sprawdza czy kolekcja nie pusta
        if collection.get_value() == nil
            return "There is no " + value.to_s() +  " in collection"
        end
        if value > collection.get_value()
            if collection.get_next() == nil
                return "There is no " + value.to_s() +  " in collection"
            else
                return search1(collection.get_next, value)
            end
        elsif value < collection.get_value()
            if collection.get_previous() == nil
                return "There is no " + value.to_s() +  " in collection"
            else
                return search1(collection.get_previous, value)
            end
        else
            return value.to_s() + " is on position " + collection.get_position().to_s()
        end
    end

    #Wyszukiwanie binarne
    def search2(collection, value)
        def it(collection, value, l, r)
            if value == collection.get((l+r)/2)
                return value.to_s() + " is on position " + ((l+r)/2).to_s()
            elsif l == r
                return "There is no " + value.to_s() +  " in collection"
            elsif value < collection.get((l+r)/2)
                it(collection, value, l, (l+r)/2-1)
            else
                it(collection, value, (l+r)/2+1, r)

            end
        end
        return it(collection, value, 0, collection.length()-1)
    end
end

puts "Tworzymy nową kolekcję i dodajmey 0,-1,1 i kolekcj wygląda tak:"
p = Collection.new()
p.add(0)
p.add(-1)
p.add(1)

puts p.get_previous().get_value()
puts p.get_value()
puts p.get_next().get_value()

puts
puts "Sprobjemy wyszukać kolejno -3,3,1 i -1 w naszej kolekcji:"
puts Search.new().search1(p,-3)
puts Search.new().search1(p,3)
puts Search.new().search1(p,1)
puts Search.new().search1(p,-1)

puts
puts "Dodamy jeszcze 5, -5 oraz 4 do kolekcji"
p.add(5)
p.add(-5)
p.add(4)

puts "i kolekcja wyglada tak:"
puts "-5 -1 0 1 4 5"
puts "I sprobujemy wyszukać -5,4,0 i 7"
puts Search.new().search2(p,-5)
puts Search.new().search2(p,4)
puts Search.new().search2(p,0)
puts Search.new().search2(p,7)


