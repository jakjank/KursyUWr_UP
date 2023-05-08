public class dama implements karty
{
    @Override
    public int wartosc()
    {
        return 12;
    }

    @Override
    public int compareTo(karty karta)
    {
        return Integer.compare(this.wartosc(), karta.wartosc());
    }
}
