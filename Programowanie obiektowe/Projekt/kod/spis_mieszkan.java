import java.io.Console;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.List;

class Spis_Mieszkan implements Serializable
{
    ArrayList<Mieszkanie> lista_mieszkan;
    int podatek_calosc;
    // ? podsumowanie

    public Spis_Mieszkan()
    {
        lista_mieszkan = new ArrayList<Mieszkanie>(0);
        try
        {
            odczytaj_z_pliku("dane.txt");
        }
        catch(IOException ex)
        {
            System.out.println("deserializacja nieudana");
        }
        catch(ClassNotFoundException ex)
        {
            System.out.println("deserializacja nieudana");
        }
    }
    public void dodaj_mieszkanie(String nazwa_nowego_mieszkania)
    {
        lista_mieszkan.add(new Mieszkanie(nazwa_nowego_mieszkania));
    }

    public void odczytaj_z_pliku(String nazwa_pliku) throws ClassNotFoundException, IOException
    {
        
        FileInputStream fis = new FileInputStream(nazwa_pliku);
        ObjectInputStream obj = new ObjectInputStream(fis);
        while (fis.available() != -1) 
        {
            Mieszkanie acc = (Mieszkanie) obj.readObject();
            lista_mieszkan.add(acc);
        }
        obj.close();
        fis.close();
    }

    public void zapisz_do_pliku(String nazwa_pliku) throws FileNotFoundException, IOException
    {
        FileOutputStream fos = new FileOutputStream(nazwa_pliku);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        for (Object mieszkanie : lista_mieszkan) 
        {

            oos.writeObject(mieszkanie);
            oos.reset();
        }
        oos.close();
        fos.close();
    }

    public ArrayList<Mieszkanie> daj_liste_mieszkan()
    {
        return lista_mieszkan;
    }
}


class Spis_Mieszkan_Swing extends JFrame implements ActionListener
{   
    class Para_p_m
    {
        JButton przycisk;
        Mieszkanie mieszkanie;

        public Para_p_m(JButton p, Mieszkanie m)
        {
            przycisk = p;
            mieszkanie = m;
        }
        public JButton daj_p()
        {
            return przycisk;
        }
        public Mieszkanie daj_m()
        {
            return mieszkanie;
        }
        public void ustaw_p(JButton p)
        {
            przycisk = p;
        }
        public void ustaw_m(Mieszkanie m)
        {
            mieszkanie = m;
        }
    }
    Spis_Mieszkan spis_mieszkan;
    JFrame okno;
    JButton dodaj_mieszkanie;
    ArrayList<Para_p_m> lista_mieszkan;
    
    public Spis_Mieszkan_Swing(Spis_Mieszkan spis_m)
    {
        lista_mieszkan = new ArrayList<Para_p_m>();
        dodaj_mieszkanie = new JButton("dodaj mieszkanie");
        dodaj_mieszkanie.addActionListener(this);

        spis_mieszkan = spis_m;
        okno = new JFrame("Mieszkania");
        okno.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        for(Mieszkanie mieszkanie : spis_mieszkan.daj_liste_mieszkan())
        {
            lista_mieszkan.add(new Para_p_m(new JButton(mieszkanie.daj_nazwe()), mieszkanie));
            lista_mieszkan.get(lista_mieszkan.size() - 1).daj_p().addActionListener(this); //?
        }

        Container kontener = okno.getContentPane();
        GridLayout rozklad = new GridLayout(lista_mieszkan.size() + 1  , 1);
        kontener.setLayout(rozklad);

        for(Para_p_m para : lista_mieszkan)
        {
            kontener.add(para.daj_p());
        }
        kontener.add(dodaj_mieszkanie);

        okno.pack();
        okno.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        Object ktory_przycisk = e.getSource();
        
        if(ktory_przycisk == dodaj_mieszkanie)
        {
            System.out.println("to byl dodaj");
        }
        else
        {
            System.out.println("to nie byl dodaj");
        }
    }

}