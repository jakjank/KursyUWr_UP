public class jopek implements karty
{
    @Override
    public int wartosc()
    {
        return 11;
    }

    @Override
    public int compareTo(karty karta)
    {
        return Integer.compare(this.wartosc(), karta.wartosc());
    }
}
