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

class Spis_Mieszkan implements Serializable
{
    ArrayList<Mieszkanie> lista_mieszkan;
    //int podatek_calosc;

    public Spis_Mieszkan()
    {
        lista_mieszkan = new ArrayList<Mieszkanie>(0);
        try
        {
            odczytaj_z_pliku("dane.txt");
        }
        catch(IOException ex)
        {
            System.out.println("deserializacja nieudana1");
        }
        catch(ClassNotFoundException ex)
        {
            System.out.println("deserializacja nieudana2");
        }
    }
    public void dodaj_mieszkanie_c(String nazwa_nowego_mieszkania)
    {
        lista_mieszkan.add(new M_calosc(nazwa_nowego_mieszkania, this));
    }
    
    public void dodaj_mieszkanie_p(String nazwa_nowego_mieszkania)
    {
        lista_mieszkan.add(new M_na_pokoje(nazwa_nowego_mieszkania, this));
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

class Spis_Mieszkan_Swing extends JFrame implements ActionListener
{   
    Spis_Mieszkan spis_mieszkan;
    JFrame okno;
    JButton dodaj_mieszkanie;
    JButton dodaj_mieszkanie_na_pokoje;
    JButton usun_mieszkanie;
    ArrayList<Para_p_m> lista_mieszkan;
    
    public Spis_Mieszkan_Swing(Spis_Mieszkan spis_m)
    {
        lista_mieszkan = new ArrayList<Para_p_m>();
        dodaj_mieszkanie = new JButton("dodaj mieszkanie");
        dodaj_mieszkanie.addActionListener(this);
        dodaj_mieszkanie_na_pokoje = new JButton("dodaj mieszknaie na pokoje");
        dodaj_mieszkanie_na_pokoje.addActionListener(this);
        usun_mieszkanie = new JButton("usun mieszkanie");
        usun_mieszkanie.addActionListener(this);

        spis_mieszkan = spis_m;
        okno = new JFrame("Mieszkania");
        okno.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        for(Mieszkanie mieszkanie : spis_mieszkan.daj_liste_mieszkan())
        {
            lista_mieszkan.add(new Para_p_m(new JButton(mieszkanie.daj_nazwe()), mieszkanie));
            lista_mieszkan.get(lista_mieszkan.size() - 1).daj_p().addActionListener(this);
            lista_mieszkan.get(lista_mieszkan.size() - 1).daj_m().sprawdz_stan();
            if(lista_mieszkan.get(lista_mieszkan.size() - 1).daj_m().czy_opoznione == true)
            {
                //lista_mieszkan.get(lista_mieszkan.size() - 1).daj_p().setBackground(Color.RED);
                lista_mieszkan.get(lista_mieszkan.size() - 1).daj_p().setBackground(Color.RED);
            }
            else
            {
                //lista_mieszkan.get(lista_mieszkan.size() - 1).daj_p().setBackground(Color.RED);
                lista_mieszkan.get(lista_mieszkan.size() - 1).daj_p().setBackground(Color.WHITE);
            }
        }

        Container kontener = okno.getContentPane();
        GridLayout rozklad = new GridLayout(lista_mieszkan.size() + 3  , 1);
        kontener.setLayout(rozklad);

        for(Para_p_m para : lista_mieszkan)
        {
            kontener.add(para.daj_p());
        }
        kontener.add(dodaj_mieszkanie);
        kontener.add(dodaj_mieszkanie_na_pokoje);
        kontener.add(usun_mieszkanie);

        okno.pack();
        okno.setSize(300, (lista_mieszkan.size() + 3)*32 + 40);
        okno.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        Object ktory_przycisk = e.getSource();
        
        if(ktory_przycisk == dodaj_mieszkanie)
        {
            new Dodaj_m_calosc_Swing(spis_mieszkan);     
            okno.dispose();
        }
        
        if(ktory_przycisk == dodaj_mieszkanie_na_pokoje)
        {
            new Dodaj_m_na_pokoje_Swing(spis_mieszkan);
            okno.dispose();
        }
        
        if(ktory_przycisk == usun_mieszkanie)
        {
            new Usun_mieszkanie_Swing(spis_mieszkan);
            okno.dispose();
        }
        
        for(Para_p_m para : lista_mieszkan)
        {
            if(ktory_przycisk == para.daj_p())
            {   
                // do wyświetl okno przekazujemy spis mieszkań,
                // aby w razie modyfikacji móc go zapisać.
                // przekazujemy rownież Spis_mieszkan_Swing 
                // aby móc usunąć czerwone podświetlenie
                para.daj_m().wyswietl_okno(spis_mieszkan, this);
            }
        }
        sprawdz_stany();
    }
    
    // funkcja odpowiadająca za czerwone podświetlenie
    // nieopłaconych mieszkań
    public void sprawdz_stany()
    {
        for(Para_p_m para : lista_mieszkan)
        {
            para.daj_m().sprawdz_stan();
            if(para.daj_m().czy_opoznione == true)
            {
                //lista_mieszkan.get(lista_mieszkan.size() - 1).daj_p().setBackground(Color.RED);
                para.daj_p().setBackground(Color.RED);
            }
            else
            {
                para.daj_p().setBackground(Color.WHITE);
            }
        }
    }
}

class Usun_mieszkanie_Swing extends JFrame implements ActionListener
{
    Spis_Mieszkan spis_mieszkan;
    JFrame okno;
    JLabel nazwa_tekst;
    JTextField nazwa;
    JButton przycisk_usun;

    Usun_mieszkanie_Swing(Spis_Mieszkan s_m)
    {
        okno = new JFrame("Usun mieszkanie");
        okno.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        this.spis_mieszkan = s_m;

        nazwa_tekst = new JLabel("Adres usuwanego mieszkania");
        nazwa = new JTextField();
        przycisk_usun = new JButton("usun");   
        przycisk_usun.addActionListener(this);

        Container kontener = okno.getContentPane();
        GridLayout rozklad = new GridLayout(2  , 2);
        kontener.setLayout(rozklad);

        kontener.add(nazwa_tekst);
        kontener.add(nazwa);
        kontener.add(przycisk_usun);

        okno.pack();
        okno.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        for(int i = 0; i < spis_mieszkan.lista_mieszkan.size(); i++)
        {   
            if(spis_mieszkan.lista_mieszkan.get(i).nazwa.equals(nazwa.getText()))
            {
                spis_mieszkan.lista_mieszkan.remove(i);
            }
        }
        try
        {
            spis_mieszkan.zapisz_do_pliku("dane.txt");
        }
        catch(IOException e1)
        {
            System.out.println("nieudany zapis do pliku");
        }
        new Spis_Mieszkan_Swing(spis_mieszkan);
        okno.dispose();
    }
}