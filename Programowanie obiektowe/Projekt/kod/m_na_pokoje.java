import java.util.List;
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
import java.util.ArrayList;

class M_na_pokoje extends Mieszkanie
{
    ArrayList<M_calosc> pokoje;

    public M_na_pokoje(String nazwa, Spis_Mieszkan s_m)
    {
        super(nazwa, s_m);
        pokoje = new ArrayList<M_calosc>(0);
    }

    public List<M_calosc> daj_liste_pokoi()
    {
        return pokoje;
    }

    public void dodaj_pokoj(String nazwa)
    {
        pokoje.add(new M_calosc(nazwa, spis_mieszkan));
        this.zapisz();
        System.out.println("mieszkanie ma pokoi: " + pokoje.size());
    }

    @Override
    public void wyswietl_okno(Spis_Mieszkan spis_mieszkan)
    {
        new M_na_pokoje_Swing(this);
    }
}

class Dodaj_m_na_pokoje_Swing extends JFrame implements ActionListener
{
   JFrame okno;
   JLabel nazwa_tekst;
   JTextField nazwa;
   JButton zapisz_przycisk;
   Spis_Mieszkan spis_mieszkan;

   Dodaj_m_na_pokoje_Swing(Spis_Mieszkan s_m)
   {
      okno = new JFrame("Dodaj mieszkania");
      okno.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

      this.spis_mieszkan = s_m;

      zapisz_przycisk = new JButton("zapisz");
      zapisz_przycisk.addActionListener(this);
      nazwa_tekst = new JLabel("nazwa mieszkania");
      nazwa = new JTextField(20);

      Container kontener = okno.getContentPane();
      GridLayout rozklad = new GridLayout(2  , 2);
      kontener.setLayout(rozklad);

      kontener.add(nazwa_tekst);
      kontener.add(nazwa);
      kontener.add(zapisz_przycisk);

      okno.pack();
      okno.setVisible(true);
   }

   @Override
   public void actionPerformed(ActionEvent e) {
      spis_mieszkan.dodaj_mieszkanie_p(nazwa.getText());
      try
      {
         spis_mieszkan.zapisz_do_pliku("dane.txt");
      }
      catch(IOException e1)
      {
         System.out.println("nie udalo sie zapisac spisu mieszkan");
      }
      okno.dispose();
      new Spis_Mieszkan_Swing(spis_mieszkan);
   }  
}

class Dodaj_pokoj_Swing extends JFrame implements ActionListener
{
   JFrame okno;
   JLabel nazwa_tekst;
   JTextField nazwa;
   JButton zapisz_przycisk;
   M_na_pokoje mieszkanie;

   Dodaj_pokoj_Swing(M_na_pokoje m)
   {
      okno = new JFrame("Dodaj mieszkania");
      okno.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

      this.mieszkanie = m;

      zapisz_przycisk = new JButton("zapisz");
      zapisz_przycisk.addActionListener(this);
      nazwa_tekst = new JLabel("ktory pokoj");
      nazwa = new JTextField(20);

      Container kontener = okno.getContentPane();
      GridLayout rozklad = new GridLayout(2  , 2);
      kontener.setLayout(rozklad);

      kontener.add(nazwa_tekst);
      kontener.add(nazwa);
      kontener.add(zapisz_przycisk);

      okno.pack();
      okno.setVisible(true);
   }

   @Override
   public void actionPerformed(ActionEvent e) {
      mieszkanie.dodaj_pokoj(nazwa.getText());
      okno.dispose();
      new M_na_pokoje_Swing(mieszkanie);
   }  
}

class M_na_pokoje_Swing extends JFrame implements ActionListener
{
    M_na_pokoje mieszkanie;
    JFrame okno;
    JButton dodaj_pokoj;
    ArrayList<Para_p_m> lista_pokoi;

    M_na_pokoje_Swing(M_na_pokoje m)
    {
        okno = new JFrame("Mieszkanie na pokoje");
        okno.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        this.mieszkanie = m;

        dodaj_pokoj = new JButton("dodaj pokoj");
        dodaj_pokoj.addActionListener(this);
        
        lista_pokoi = new ArrayList<Para_p_m>(0);
        for(M_calosc m_c : mieszkanie.daj_liste_pokoi())
        {
            lista_pokoi.add(new Para_p_m(new JButton(m_c.daj_nazwe()), m_c));
            lista_pokoi.get(lista_pokoi.size() - 1).daj_p().addActionListener(this); 
        }

        Container kontener = okno.getContentPane();
        GridLayout rozklad = new GridLayout(lista_pokoi.size() + 1  , 1);
        kontener.setLayout(rozklad);

        for(Para_p_m para : lista_pokoi)
        {
            kontener.add(para.daj_p());
        }
        kontener.add(dodaj_pokoj);

        okno.pack();
        okno.setSize(300, (lista_pokoi.size() + 1) * 32 + 40);
        okno.setVisible(true);
    }


    @Override
    public void actionPerformed(ActionEvent e) {
        Object ktory_przycisk = e.getSource();
        
        if(ktory_przycisk == dodaj_pokoj)
        {
            new Dodaj_pokoj_Swing(mieszkanie); 
            okno.dispose();
        }

        for(Para_p_m para : lista_pokoi)
        {
            if(para.daj_p() == ktory_przycisk)
            {
                para.daj_m().wyswietl_okno(para.daj_m().spis_mieszkan);
            }
        }
    }
}