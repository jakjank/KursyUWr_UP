import java.util.ArrayList;
import java.io.Serializable;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class Lokator implements Serializable
{
    Mieszkanie mieszkanie;
    String imie;
    String nazwisko;
    String nr_tel;
    String email;
    public Lokator(Mieszkanie m, String i, String n, String t,  String e)
    {
        mieszkanie = m;
        imie = i;
        nazwisko = n;
        nr_tel = t;
        email = e;
    }

    public void zapisz()
    {
        mieszkanie.zapisz();
    }
}

class Dodaj_lokatora_Swing extends JFrame implements ActionListener
{
    M_calosc mieszkanie;
    JFrame okno;
    JLabel imie_tekst;
    JLabel nazwisko_tekst;
    JTextField imie_p;
    JTextField nazwisko_p;
    JLabel nr_tel_tekst;
    JTextField nr_tel_p;
    JLabel email_tekst;
    JTextField email_p;
    JButton przycisk_zapisz;

    public Dodaj_lokatora_Swing(M_calosc m)
    {
        okno = new JFrame("Dodawanie lokatora");
        okno.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        mieszkanie = m;

        // Aby utworzyć nowy obiekt lokator trzeba podać imię i nazwisko
        imie_tekst = new JLabel("imie");
        nazwisko_tekst = new JLabel("nazwisko");
        imie_p = new JTextField();
        nazwisko_p = new JTextField();
        nr_tel_tekst = new JLabel("numer telefonu   ");
        nr_tel_p = new JTextField();
        email_tekst = new JLabel("email              ");
        email_p = new JTextField();
        przycisk_zapisz = new JButton("zapisz");
        przycisk_zapisz.addActionListener(this);

        Container kontener = okno.getContentPane();
        GridLayout rozklad = new GridLayout(3  , 4);
        kontener.setLayout(rozklad);

        kontener.add(imie_tekst);
        kontener.add(nazwisko_tekst);
        kontener.add(nr_tel_tekst);
        kontener.add(email_tekst);
        kontener.add(imie_p);
        kontener.add(nazwisko_p);
        kontener.add(nr_tel_p);
        kontener.add(email_p);
        kontener.add(przycisk_zapisz);
        kontener.add(new JLabel(""));

        okno.pack();
        okno.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        mieszkanie.lista_lokatorow.add(new Lokator(
                                            mieszkanie, 
                                            imie_p.getText(), 
                                            nazwisko_p.getText(), 
                                            nr_tel_p.getText(), 
                                            email_p.getText())
                                        );
        mieszkanie.zapisz();

        okno.dispose();
        new Lokatorzy_Swing(mieszkanie);

        // odswieżanie poprzedniego okna lokatorów
        // w przypadku dodanie nowego lokatora
        // poprzednie_okno.dispose();
        // new Lokatorzy_Swing(mieszkanie);
    }


    //?
    public int close_operation()
    {
        okno.dispose();
        new Lokatorzy_Swing(mieszkanie);
        return 1;
    }
}

class Lokatorzy_Swing extends JFrame implements ActionListener
{
    M_calosc mieszkanie;
    JFrame okno;
    JLabel imie_tekst;
    JLabel nazwisko_tekst;
    JLabel nr_tel_tekst;
    JLabel email_tekst;
    JButton usun_lokatorow;
    JButton dodaj_lokatora;

    public Lokatorzy_Swing(M_calosc m)
    {
        okno = new JFrame("Lokatorzy");
        okno.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        mieszkanie = m;

        imie_tekst = new JLabel("imie");
        nazwisko_tekst = new JLabel("nazwisko");
        nr_tel_tekst = new JLabel("numer telefonu");
        email_tekst = new JLabel("email");
        usun_lokatorow = new JButton("usun lokatorow");
        usun_lokatorow.addActionListener(this);
        dodaj_lokatora = new JButton("dodaj lokatora");
        dodaj_lokatora.addActionListener(this);

        Container kontener = okno.getContentPane();
        GridLayout rozklad = new GridLayout(mieszkanie.lista_lokatorow.size() + 2  , 4);
        kontener.setLayout(rozklad);

        kontener.add(imie_tekst);
        kontener.add(nazwisko_tekst);
        kontener.add(nr_tel_tekst);
        kontener.add(email_tekst);

        for(Lokator lokator : mieszkanie.lista_lokatorow)
        {
            kontener.add(new JLabel(lokator.imie));
            kontener.add(new JLabel(lokator.nazwisko));
            kontener.add(new JLabel(lokator.nr_tel));
            kontener.add(new JLabel(lokator.email));
        }

        kontener.add(new JLabel(""));
        kontener.add(usun_lokatorow);
        kontener.add(dodaj_lokatora);


        okno.pack();
        okno.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        Object ktory_przycisk = e.getSource();

        if(ktory_przycisk == usun_lokatorow)
        {
            mieszkanie.lista_lokatorow = new ArrayList<Lokator>(0);
            mieszkanie.zapisz();
            okno.dispose();
            new Lokatorzy_Swing(mieszkanie);
        }
        if(ktory_przycisk == dodaj_lokatora)
        {
            new Dodaj_lokatora_Swing(mieszkanie);
            okno.dispose();
        }
    }
}