class Collection
    def initialize()
        @next = nil
        @position = 0
        @value = nil
    end

    def change_num_of_pos(i)
        @position = i
    end

    def get_num_of_pos()
        return @position
    end

    def add(elem)
        if(@next == nil)
            @next = Collection.new()
            @next.change_num_of_pos(@position + 1)
            @value = elem
        else
            @next.add(elem)
        end
    end

    def length()
        if @next == nil
            return @position
        else
            return @next.length()
        end
    end

    def get(i)
        if(i >= self.length() || i< 0)
            return "No such adress in collection"
        end
        if(i == @position)
            return @value
        else
            @next.get(i)
        end
    end

    def change(i , value)
        if(i >= self.length() || i< 0)
            retrun "No such adress in collection"
        end
        if(i == @position)
            @value = value
        else
            @next.change(i, value)
        end
    end

    def swap(i,j)
        if(i >= self.length() || j >= self.length() || i < 0 || j < 0)
            return "No such adresses in collection"
        end
        elem_i = get(i)
        elem_j = get(j)
        self.change(i, elem_j)
        self.change(j, elem_i)
    end

    def subcollection(i,j)
        if(i >= self.length() || j >= self.length() || i < 0 || j < 0)
            return "No such adresses in collection"
        end
        if(i > j)
            return "Start of subcollection cannot be bigger than the end"
        end

        subcol = Collection.new()
        k = 0

        while(k <= j)
            if(k >= i)
                subcol.add(self.get(k))
            end
            k = k + 1
        end

        return subcol
    end
end


class Sorter
    # bubble sort O(n^2)
    def sort1(collection)
        n = collection.length()
        i = 0
        while i < n
            j = 0
            while j < n - 1
                if(collection.get(j) > collection.get(j+1))
                    collection.swap(j, j+1)
                end
                j = j + 1
            end
            i = i + 1
        end
    end

    # sortowanie przez szukanie maksimum O(n^2)
    def sort2(collection)
        i = collection.length() - 1
        while i > 0
            j = 0
            max_position = nil
            while j <= i
                if max_position == nil || collection.get(j) >= collection.get(max_position)
                    max_position = j
                end
                j = j + 1
            end
            collection.swap(max_position, i)
            i = i - 1
        end
    end
end


p = Collection.new()
puts "Tworzymy pusta kolekcje, jej dlugosc to:"
puts p.length()

puts "Wkladamy do niej kolejno 1, 2, 3 i teraz wygląda tak: "
p.add(1)
p.add(2)
p.add(3)
puts p.get(0)
puts p.get(1)
puts p.get(2)

puts "A jej dlugosc to teraz:"
puts p.length()

puts "Po zamienieniu zerowego (1) i drugiego (3) elementu wygląda tak:"
p.swap(0,2)
puts p.get(0)
puts p.get(1)
puts p.get(2)

puts "Posortujmy uzywajac sort1 i mamy:"
Sorter.new().sort1(p)
puts p.get(0)
puts p.get(1)
puts p.get(2)

puts "dodajmy teraz 4, 3, 5 do kolekcji i mamy"
p.add(4)
p.add(3)
p.add(5)
puts p.get(0)
puts p.get(1)
puts p.get(2)
puts p.get(3)
puts p.get(4)
puts p.get(5)

puts "To teraz posortujmy uzywajac sort2 i mamy"
Sorter.new().sort2(p)
puts p.get(0)
puts p.get(1)
puts p.get(2)
puts p.get(3)
puts p.get(4)
puts p.get(5)