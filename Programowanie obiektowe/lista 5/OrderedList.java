import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class OrderedList
{
    List<karty> dane;

    OrderedList()
    {
        dane = new ArrayList<karty>();
    }

    void add_element(karty elem)
    {
        dane.add(elem);
        Collections.sort(dane);
    }

    karty get_first()
    {
        if(dane.size() == 0)
        {
            System.out.println("Kolekcja jest pusta");
            return null;
        }
        karty tmp = dane.get(0);
        dane.remove(0);
        return tmp;
    }

    public String to_String()
    {
        String tmp = "";

        for(karty elem : dane)
        {
            tmp += elem + " ";
        }

        return tmp;
    }
}
