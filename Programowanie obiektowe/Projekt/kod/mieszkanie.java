import java.io.IOException;
import java.io.Serializable;
import java.util.Calendar;

class Mieszkanie implements Serializable
{
    String nazwa;
    String opis;
    //? dokumenty
    boolean czy_opoznione;
    // mieszkanie jest opóznione z zapłata jeśli nie jest opłacone
    // i dzień rozliczenia już minął
    Spis_Mieszkan spis_mieszkan;
    Calendar c = Calendar.getInstance();


    public Mieszkanie(String s, Spis_Mieszkan s_m)
    {
        nazwa = s;
        spis_mieszkan = s_m;
        czy_opoznione = false;
    }

    public void ustaw_nazwe(String nazwa)
    {
        this.nazwa = nazwa;
    }

    public String daj_nazwe()
    {
        return nazwa;
    }
    public void wyswietl_okno(Spis_Mieszkan spis_mieszkan, Spis_Mieszkan_Swing s_m) {}

    public void zapisz()
    {
        try
        {
            this.spis_mieszkan.zapisz_do_pliku("dane.txt");
        }
        catch(IOException e1)
        {
            System.out.println("nie udalo sie zapisac");
        }
    }

    public void sprawdz_stan() {}
}

