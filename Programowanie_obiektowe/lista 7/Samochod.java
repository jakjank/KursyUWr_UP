import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Samochod extends Pojazd
{
    public String moc_silnika;

    public Samochod(String model, String rok_produkcji, String wlasciciel, String moc)
    {
        super(model, rok_produkcji, wlasciciel);
        moc_silnika = moc;
    }

    public String toString()
    {
        return "pojazd: "          + model + 
               "; rok produkcji: " + rok_produkcji +
               "; wlasciciel: "    + wlasciciel +
               "; moc silnika: "   + moc_silnika;
    }

    public static Samochod odczytajZPliku(String nazwaPliku)
    {
        try 
        {
            FileInputStream fi = new FileInputStream(new File(nazwaPliku));
            ObjectInputStream oi = new ObjectInputStream(fi);

            // Read objects
            Samochod pojazd = (Samochod) oi.readObject();

            oi.close();
            fi.close();

            return pojazd;
        } 
        catch (IOException | ClassNotFoundException e) 
        {
            //System.out.println("Error initializing stream");
            return new Samochod("", "", "","");
        }  
    }
 }


 class SamochodSwing extends JFrame implements ActionListener
{
    JFrame ramka;
    JButton przycisk;
    Samochod samochod;

    JTextField model_pojazdu;
    JTextField rok_p_pojazdu;
    JTextField wlasc_pojazdu;
    JTextField moc_pojazdu;
    String nazwa_pliku;

    SamochodSwing(Samochod samochod, String nazwa_pliku)
    {   
        // Tworzenie ramki
        ramka = new JFrame("Edycja samochodu");
        ramka.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        przycisk = new JButton("Zapisz");
        przycisk.addActionListener(this);

        Container kontener = ramka.getContentPane();
        GridLayout rozklad = new GridLayout(5  , 2);
        kontener.setLayout(rozklad);

        this.samochod = samochod;
        this.nazwa_pliku = nazwa_pliku;

        // Tworzenie etykiet i pól wprowadzania danych
        JLabel model_etykieta = new JLabel("Model:");
        model_pojazdu = new JTextField(samochod.model, 20);
        JLabel rok_p_etykieta = new JLabel("Rok produkcji:");
        rok_p_pojazdu = new JTextField(samochod.rok_produkcji, 20);
        JLabel wlasc_etykieta = new JLabel("Wlasciciel:");
        wlasc_pojazdu = new JTextField(samochod.wlasciciel,20);
        JLabel moc_etykieta = new JLabel("Moc silnika:");
        moc_pojazdu = new JTextField(samochod.moc_silnika,20);

        // Dodawanie pól do kontenera
        kontener.add(model_etykieta);
        kontener.add(model_pojazdu);
        kontener.add(rok_p_etykieta);
        kontener.add(rok_p_pojazdu);
        kontener.add(wlasc_etykieta);
        kontener.add(wlasc_pojazdu);
        kontener.add(moc_etykieta);
        kontener.add(moc_pojazdu);
        kontener.add(przycisk);

        ramka.pack();
        ramka.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // zamiana atrybutów pojazdu
        samochod.model         = model_pojazdu.getText();
        samochod.rok_produkcji = rok_p_pojazdu.getText();
        samochod.wlasciciel    = wlasc_pojazdu.getText();
        samochod.moc_silnika   = moc_pojazdu.getText();
        samochod.zapiszDoPliku(nazwa_pliku);
    }
}