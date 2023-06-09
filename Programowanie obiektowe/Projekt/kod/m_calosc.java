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

class M_calosc extends Mieszkanie
{
   List<Lokator> lokatorzy;
   String kaucja;
   // koszty koszty
   boolean czy_zaplacone; // ?
   String ile_placi;
   String okres_wynajmu;
   String opis_pokoju;

   public M_calosc(String nazwa)
   {
        super(nazwa);
   }

   @Override
   public void wyswietl_okno()
   {
        new M_calosc_Swing(this);
   }
}

class Dodaj_m_calosc_Swing extends JFrame implements ActionListener
{
   JFrame okno;
   JLabel nazwa_tekst;
   JTextField nazwa;
   JButton zapisz_przycisk;
   Spis_Mieszkan spis_mieszkan;

   Dodaj_m_calosc_Swing(Spis_Mieszkan s_m)
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
      spis_mieszkan.dodaj_mieszkanie_c(nazwa.getText());
      try
      {
         spis_mieszkan.zapisz_do_pliku("dane.txt");
      }
      catch(IOException e1)
      {
         System.out.println("nie udalo sie zapisac spisu mieszkan");
      }
      okno.dispose();
   }  
}

// ile placi i okres wynajmu do klasy lokator
class M_calosc_Swing extends JFrame implements ActionListener
{
   M_calosc mieszkanie;
   JFrame okno;
   JButton przycisk_zapisz;
   JLabel kaucja_tekst;
   JTextField kaucja;
   JLabel koszty_tekst;
   JButton koszty; // "wiecej" rozwija okno z kosztami
   JLabel zaplacone_tekst;
   JCheckBox zaplacone; 
   JLabel opis_tekst;
   JButton opis;   // "wiecej" rozwija okno tylko z tekstem do zapisywania informacji
   JLabel lokatorzy_tekst;
   JButton lokatorzy; // rozwija okno z informacjami o lokatorach

   M_calosc_Swing(M_calosc m)
   {
      okno = new JFrame("Mieszkanie/pokoj");
      okno.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE); //zamiast samego dispose to save i dispose

      this.mieszkanie = m;

      Container kontener = okno.getContentPane();
      GridLayout rozklad = new GridLayout(6  , 2);
      kontener.setLayout(rozklad);

      kaucja_tekst = new JLabel("kaucja:");
      kaucja = new JTextField(mieszkanie.kaucja, 20);
      koszty_tekst = new JLabel("koszty:");
      koszty = new JButton("wiecej");
      koszty.addActionListener(this);
      zaplacone_tekst = new JLabel("czy zaplacone?");
      zaplacone = new JCheckBox();
      opis_tekst = new JLabel("opis:");
      opis = new JButton("wiecej");
      lokatorzy_tekst = new JLabel("lokatorzy:");
      lokatorzy = new JButton("wiecej");
      lokatorzy.addActionListener(this);
      przycisk_zapisz = new JButton("zapisz");
      przycisk_zapisz.addActionListener(this);

      kontener.add(opis_tekst);
      kontener.add(opis);
      kontener.add(koszty_tekst);
      kontener.add(koszty);
      kontener.add(kaucja_tekst);
      kontener.add(kaucja);
      kontener.add(zaplacone_tekst);
      kontener.add(zaplacone);
      kontener.add(lokatorzy_tekst);
      kontener.add(lokatorzy);
      kontener.add(przycisk_zapisz);

      okno.pack();
      okno.setVisible(true);
   }

   @Override
   public void actionPerformed(ActionEvent e) {
      Object ktory_przycisk = e.getSource();

      if(ktory_przycisk == opis)
      {

      }
      if(ktory_przycisk == koszty)
      {

      }
      if(ktory_przycisk == lokatorzy)
      {

      }
   }

   

}