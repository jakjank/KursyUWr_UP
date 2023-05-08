public interface karty extends Comparable<karty>
{
    int wartosc();

    @Override
    int compareTo(karty karta);
}