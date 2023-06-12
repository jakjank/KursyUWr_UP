import java.util.List;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import javax.swing.*;
import javax.swing.event.AncestorListener;
import java.util.ArrayList;
import java.util.List;
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
import java.lang.Math;

class Koszty implements Serializable
{
    Mieszkanie mieszkanie;
    String spoldzielnia;
    String podatek;
    String prad;
    String woda;
    String gaz;
    String suma;

    public Koszty(Mieszkanie m)
    {
        mieszkanie = m;
        spoldzielnia = "0";
        podatek = "0";
        prad = "0";
        woda = "0";
        gaz = "0";
        suma = "0";
    }
}

class Koszty_Swing extends JFrame implements ActionListener
{
    Koszty koszty;
    JFrame okno;
    JButton przycisk_zapisz;
    JLabel spoldzielnia_tekst;
    JLabel podatek_tekst;
    JLabel prad_tekst;
    JLabel woda_tekst;
    JLabel gaz_teks;
    JLabel suma_tekst;
    JTextField spoldzilnia_p;
    JTextField podatek_p;
    JTextField prad_p;
    JTextField woda_p;
    JTextField gaz_p;
    JLabel suma_wynik;

    public static double round(double value, int places) 
    {
        if (places < 0) throw new IllegalArgumentException();

        long factor = (long) Math.pow(10, places);
        value = value * factor;
        long tmp = Math.round(value);
        return (double) tmp / factor;
    }

    public Koszty_Swing(Koszty k)
    {
        koszty = k;

        okno = new JFrame("koszty " + koszty.mieszkanie.nazwa);
        okno.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        przycisk_zapisz = new JButton("zapisz");
        przycisk_zapisz.addActionListener(this);
        spoldzielnia_tekst = new JLabel("spoldzielnia");
        podatek_tekst = new JLabel("podatek");
        prad_tekst = new JLabel("prad");
        woda_tekst = new JLabel("woda");
        gaz_teks = new JLabel("gaz");
        suma_tekst = new JLabel("suma");

        spoldzilnia_p = new JTextField(koszty.spoldzielnia, 20);
        podatek_p = new JTextField(koszty.podatek); // podatek podaje się samemu
        prad_p = new JTextField(koszty.prad);
        woda_p = new JTextField(koszty.woda);
        gaz_p = new JTextField(koszty.gaz);

        try{
        suma_wynik = new JLabel(String.valueOf(round(Double.parseDouble(koszty.spoldzielnia) +
                                               Double.parseDouble(koszty.podatek) +
                                               Double.parseDouble(koszty.prad) +
                                               Double.parseDouble(koszty.woda) +
                                               Double.parseDouble(koszty.gaz), 2)));
        }
        catch(Throwable o)
        {
            System.out.println("nie udalo sie dodac");
        }

        Container kontener = okno.getContentPane();
        GridLayout rozklad = new GridLayout(7  , 2);
        kontener.setLayout(rozklad);

        kontener.add(spoldzielnia_tekst);
        kontener.add(spoldzilnia_p);
        kontener.add(podatek_tekst);
        kontener.add(podatek_p);
        kontener.add(prad_tekst);
        kontener.add(prad_p);
        kontener.add(woda_tekst);
        kontener.add(woda_p);
        kontener.add(gaz_teks);
        kontener.add(gaz_p);
        kontener.add(suma_tekst);
        kontener.add(suma_wynik);
        kontener.add(przycisk_zapisz);

        okno.pack();
        okno.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        koszty.spoldzielnia = spoldzilnia_p.getText();
        koszty.podatek = podatek_p.getText();
        koszty.prad = prad_p.getText();
        koszty.woda = woda_p.getText();
        koszty.gaz = gaz_p.getText();
        okno.dispose();
        new Koszty_Swing(koszty);
    }
}