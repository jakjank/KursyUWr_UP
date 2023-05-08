import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class Pojazd implements Serializable
{
    // atrybuty w klasach Pojazd Samochod i Tramwaj są publiczne
    // (z lenistwa), żeby nie pisać getterów i setterów do
    // zmiany ich wartości w okienku edycji
    public String model;
    public String rok_produkcji;
    public String wlasciciel;

    public Pojazd(String model, String rok_produkcji, String wlasciciel)
    {
        this.model         = model;
        this.rok_produkcji = rok_produkcji;
        this.wlasciciel    = wlasciciel;
    }

    public String toString()
    {
        return "pojazd: "         + model + 
               "; rok produkcji: " + rok_produkcji +
               "; wlasciciel: "    + wlasciciel;
    }

    public void zapiszDoPliku(String nazwaPliku) 
    {
        try 
        {
            FileOutputStream f = new FileOutputStream(new File(nazwaPliku));
            ObjectOutputStream o = new ObjectOutputStream(f);

            o.writeObject(this);
            o.close();
            f.close();
        } 
        catch (IOException e) 
        {
            System.out.println("Error initializing stream");
        } 
    }

    public static Pojazd odczytajZPliku(String nazwaPliku)
    {
        try 
        {
            FileInputStream fi = new FileInputStream(new File(nazwaPliku));
            ObjectInputStream oi = new ObjectInputStream(fi);

            // Read objects
            Pojazd pojazd = (Pojazd) oi.readObject();

            oi.close();
            fi.close();

            return pojazd;
        } 
        catch (IOException | ClassNotFoundException e) 
        {
            //System.out.println("Error initializing stream");
            return new Pojazd("", "", "");
        }  
    }
}

class PojazdSwing extends JFrame implements ActionListener
{
    JFrame ramka;
    JButton przycisk;
    Pojazd pojazd;

    JTextField model_pojazdu;
    JTextField rok_p_pojazdu;
    JTextField wlasc_pojazdu;
    String nazwa_pliku;

    PojazdSwing(Pojazd poj , String nazwa_pliku)
    {   
        // Tworzenie ramki i rozkladu
        ramka = new JFrame("Edycja pojazdu");
        ramka.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        przycisk = new JButton("Zapisz");
        przycisk.addActionListener(this);

        Container kontener = ramka.getContentPane();
        GridLayout rozklad = new GridLayout(4  , 2);
        kontener.setLayout(rozklad);

        this.pojazd = poj;
        this.nazwa_pliku = nazwa_pliku;
        
        // Tworzenie etykiet i pól wprowadzania danych
        JLabel model_etykieta = new JLabel("Model:");
        model_pojazdu = new JTextField(pojazd.model, 20);
        JLabel rok_p_etykieta = new JLabel("Rok produkcji:");
        rok_p_pojazdu = new JTextField(pojazd.rok_produkcji, 20);
        JLabel wlasc_etykieta = new JLabel("Wlasciciel:");
        wlasc_pojazdu = new JTextField(pojazd.wlasciciel,20);

        // Dodawanie pól do kontenera
        kontener.add(model_etykieta);
        kontener.add(model_pojazdu);
        kontener.add(rok_p_etykieta);
        kontener.add(rok_p_pojazdu);
        kontener.add(wlasc_etykieta);
        kontener.add(wlasc_pojazdu);
        kontener.add(przycisk);

        ramka.pack();
        ramka.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // zamiana atrybutów pojazdu
        pojazd.model         = model_pojazdu.getText();
        pojazd.rok_produkcji = rok_p_pojazdu.getText();
        pojazd.wlasciciel    = wlasc_pojazdu.getText();
        pojazd.zapiszDoPliku(nazwa_pliku);
    }
}