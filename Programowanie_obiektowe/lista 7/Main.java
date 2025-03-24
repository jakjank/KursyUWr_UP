// Program kompilujemy poleceniem:
//      javac *.java
// Następnie uruchamiamy poleceniem:
//      java Main nazwa_pliku.txt nazwa_klasy
// Dostępne klasy: Pojazd, Samochod, Tramwaj

// Przykładowo jeśli uruchomimy program poleceniem
//      java Main samochodzik.txt Samochod
// to wyświetli się interfejs edycji 
// ale jako że nie ma takiego pliku to interfejs będzie pusty.
// Po jego uzupełenieniu i zapisaniu, jeśli kolejny raz 
// uruchomimy program poleceniem 
//      java Main samochodzik.txt Samochod
// to w edytorze będą dane poprzednio zapisanego samochodu.
// Świetna sprawa!

public class Main{
    public static void main(String[] args)
    {

        if (args[1].equals("Pojazd"))
        {            
            Pojazd pojazd = Pojazd.odczytajZPliku(args[0]);
            new PojazdSwing(pojazd, args[0]);
        }
        else if (args[1].equals("Samochod")) 
        {
            Samochod pojazd = (Samochod) Samochod.odczytajZPliku(args[0]);
            new SamochodSwing(pojazd, args[0]);
        }
        else if (args[1].equals("Tramwaj")) 
        {
            Tramwaj pojazd = (Tramwaj) Tramwaj.odczytajZPliku(args[0]);
            new TramwajSwing(pojazd, args[0]);
        }
    }
}