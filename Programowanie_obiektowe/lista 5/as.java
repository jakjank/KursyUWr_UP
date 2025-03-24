public class as implements karty
{
    @Override
    public int wartosc()
    {
        return 14;
    }

    @Override
    public int compareTo(karty karta)
    {
        return Integer.compare(this.wartosc(), karta.wartosc());
    }
}
