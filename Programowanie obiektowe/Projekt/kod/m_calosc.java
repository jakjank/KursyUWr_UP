import java.util.List;

class M_calosc extends Mieszkanie
{
   List<Lokator> lokatorzy;
   int kaucja;
   // koszty koszty
   boolean czy_zaplacone;
   int ile_placi;
   String okres_wynajmu;
   String opis_pokoju;

   public M_calosc(String nazwa)
   {
        super(nazwa);
   }
}
