// program implemenuje listę uporządkowaną na kartach
// z użyciem interfejsu Comparable

// karty w kolejności rosnącej: jopek, dama, król, as.

public class Main 
{
    public static void main(String[] args)
    {
        OrderedList talia = new OrderedList();

        talia.add_element(new as());
        talia.add_element(new dama());
        talia.add_element(new jopek());
        talia.add_element(new krol());
        talia.add_element(new dama());
        
        System.out.println("talia wyglada tak: " + talia.to_String());

        System.out.println("pierwszy element w talii to: " + talia.get_first());

        System.out.println("i teraz talia wyglada tak: " + talia.to_String());
    }
}
