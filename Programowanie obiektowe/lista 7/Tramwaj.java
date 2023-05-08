import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Tramwaj extends Pojazd
{
    // W Samchodzie i tramwaju dodatkowe atrybuty sa typu string
    // w celu łatwiejszej implementacji klasy *Swing do nich
    public String ilosc_miejsc;

    public Tramwaj(String model, String rok_produkcji, String wlasciciel, String ilosc)
    {
        super(model, rok_produkcji, wlasciciel);
        ilosc_miejsc = ilosc;
    }

    public String toString()
    {
        return "pojazd: "          + model + 
               "; rok produkcji: " + rok_produkcji +
               "; wlasciciel: "    + wlasciciel +
               "; ilosc miejsc: "  + ilosc_miejsc;
    }

    // Musimy (w Samochodzie też) zasłonić odczytaj z pliku pojazdu (niestety) 
    public static Tramwaj odczytajZPliku(String nazwaPliku)
    {
        try 
        {
            FileInputStream fi = new FileInputStream(new File(nazwaPliku));
            ObjectInputStream oi = new ObjectInputStream(fi);

            // Read objects
            Tramwaj pojazd = (Tramwaj) oi.readObject();

            oi.close();
            fi.close();

            return pojazd;
        } // Jeśl nie ma danego pliku lub jest pusty to zwracamy 
          // pustą klasę tramwaj do wypełnienia (Samochód analogicznia)
        catch (IOException | ClassNotFoundException e) 
        {
            //System.out.println("Error initializing stream");
            return new Tramwaj("", "", "","");
        }  
    }
 }


 class TramwajSwing extends JFrame implements ActionListener
 {
     JFrame ramka;
     JButton przycisk;
     Tramwaj tramwaj;
 
     JTextField model_pojazdu;
     JTextField rok_p_pojazdu;
     JTextField wlasc_pojazdu;
     JTextField ilosc_pojazdu;
     String nazwa_pliku;
 
     TramwajSwing(Tramwaj tramwaj, String nazwa_pliku)
     {   
         // Tworzenie ramki
         ramka = new JFrame("Edycja pojazdu");
         ramka.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         przycisk = new JButton("Zapisz");
         przycisk.addActionListener(this);
 
         Container kontener = ramka.getContentPane();
         GridLayout rozklad = new GridLayout(5  , 2);
         kontener.setLayout(rozklad);
 
         this.tramwaj = tramwaj;
         this.nazwa_pliku = nazwa_pliku;
 
         // Tworzenie etykiet i pól wprowadzania danych
         JLabel model_etykieta = new JLabel("Model:");
         model_pojazdu = new JTextField(tramwaj.model, 20);
         JLabel rok_p_etykieta = new JLabel("Rok produkcji:");
         rok_p_pojazdu = new JTextField(tramwaj.rok_produkcji, 20);
         JLabel wlasc_etykieta = new JLabel("Wlasciciel:");
         wlasc_pojazdu = new JTextField(tramwaj.wlasciciel,20);
         JLabel ilosc_etykieta = new JLabel("Ilosc miejsc:");
         ilosc_pojazdu = new JTextField(tramwaj.ilosc_miejsc,20);

         // Dodawanie pól do kontenera
         kontener.add(model_etykieta);
         kontener.add(model_pojazdu);
         kontener.add(rok_p_etykieta);
         kontener.add(rok_p_pojazdu);
         kontener.add(wlasc_etykieta);
         kontener.add(wlasc_pojazdu);
         kontener.add(ilosc_etykieta);
         kontener.add(ilosc_pojazdu);
         kontener.add(przycisk);
 
         ramka.pack();
         ramka.setVisible(true);
     }
 
     @Override
     public void actionPerformed(ActionEvent e) {
         // zamiana atrybutów pojazdu
         tramwaj.model         = model_pojazdu.getText();
         tramwaj.rok_produkcji = rok_p_pojazdu.getText();
         tramwaj.wlasciciel    = wlasc_pojazdu.getText();
         tramwaj.ilosc_miejsc  = ilosc_pojazdu.getText();
         // o tu tu sie przydaje,             ^^^^^^^^^^
         // że ilość miejsc jest stringiem
         tramwaj.zapiszDoPliku(nazwa_pliku);
     }
 }