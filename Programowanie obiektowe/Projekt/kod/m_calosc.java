import java.util.List;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import javax.swing.*;
import javax.swing.event.AncestorListener;

import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

class M_calosc extends Mieszkanie
{
   String opis;
   ArrayList<Lokator> lista_lokatorow;
   Koszty koszty;
   String kaucja;
   String czynsz;
   String okres_wynajmu;
   boolean czy_zaplacone; // ?
   String platnosc;
   

   public M_calosc(String nazwa, Spis_Mieszkan s_m)
   {
      super(nazwa, s_m);
      opis = "";
      lista_lokatorow = new ArrayList<Lokator>(0);
      kaucja = "";
      czynsz = "";
      okres_wynajmu = "";
      czy_zaplacone = false;
      koszty = new Koszty(this);
      platnosc = "1";
   }

   @Override
   public void wyswietl_okno(Spis_Mieszkan spis_mieszkan)
   {
      new M_calosc_Swing(this, spis_mieszkan);
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
      okno.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

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
      new Spis_Mieszkan_Swing(spis_mieszkan);
   }  
}

// ile placi i okres wynajmu do klasy lokator (kaucja tez do lokatora)
class M_calosc_Swing extends JFrame implements ActionListener
{
   M_calosc mieszkanie;
   JFrame okno;
   JButton przycisk_zapisz;
   JLabel koszty_tekst;
   JButton koszty_p; // "wiecej" rozwija okno z kosztami
   JLabel zaplacone_tekst;
   JCheckBox zaplacone_p; // p jak przycisk lub pole tekstowe (konflikt nazw)
   JLabel kaucja_tekst;
   JTextField kaucja_p;
   JLabel czynsz_tekst;
   JTextField czynsz_p;
   JLabel okres_tekst;
   JTextField okres_p; 
   JLabel opis_tekst;
   JButton opis_p;   // "wiecej" rozwija okno tylko z tekstem do zapisywania informacji
   JLabel lokatorzy_tekst;
   JButton lokatorzy_p; // rozwija okno z informacjami o lokatorach
   JLabel platnos_tekst;
   JTextField platnosc_p; //określa dzień miesiąca do którego mieszkanie lub pokoj powinno być opłacone

   M_calosc_Swing(M_calosc m, Spis_Mieszkan spis_mieszkan)
   {
      okno = new JFrame("Mieszkanie/pokoj " + m.nazwa);
      okno.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE); //zamiast samego dispose to save i dispose

      this.mieszkanie = m;

      Container kontener = okno.getContentPane();
      GridLayout rozklad = new GridLayout(9  , 2);
      kontener.setLayout(rozklad);

      koszty_tekst = new JLabel("koszty:");
      koszty_p = new JButton("wiecej");
      koszty_p.addActionListener(this);
      zaplacone_tekst = new JLabel("czy zaplacone?");
      zaplacone_p = new JCheckBox();
      zaplacone_p.addActionListener(this);
      zaplacone_p.setSelected(mieszkanie.czy_zaplacone);
      opis_tekst = new JLabel("opis:");
      opis_p = new JButton("wiecej");
      opis_p.addActionListener(this);
      lokatorzy_tekst = new JLabel("lokatorzy:");
      lokatorzy_p = new JButton("wiecej");
      lokatorzy_p.addActionListener(this);
      przycisk_zapisz = new JButton("zapisz");
      przycisk_zapisz.addActionListener(this);
      kaucja_tekst = new JLabel("kaucja");
      kaucja_p = new JTextField(mieszkanie.kaucja);
      czynsz_tekst = new JLabel("czynsz");
      czynsz_p = new JTextField(mieszkanie.czynsz);
      okres_tekst = new JLabel("okres_wynajmu");
      okres_p = new JTextField(mieszkanie.okres_wynajmu);
      platnos_tekst = new JLabel("platnosc");
      platnosc_p = new JTextField(mieszkanie.platnosc);

      kontener.add(opis_tekst);
      kontener.add(opis_p);
      kontener.add(lokatorzy_tekst);
      kontener.add(lokatorzy_p);
      kontener.add(koszty_tekst);
      kontener.add(koszty_p);
      kontener.add(okres_tekst);
      kontener.add(okres_p);
      kontener.add(czynsz_tekst);
      kontener.add(czynsz_p);
      kontener.add(kaucja_tekst);
      kontener.add(kaucja_p);
      kontener.add(platnos_tekst);
      kontener.add(platnosc_p);
      kontener.add(zaplacone_tekst);
      kontener.add(zaplacone_p);
      kontener.add(przycisk_zapisz);

      okno.pack();
      okno.setSize(300, 360); //dodac ktorego dnia miesiaca platnosc
      okno.setVisible(true);
   }

   @Override
   public void actionPerformed(ActionEvent e) {
      Object ktory_przycisk = e.getSource();

      if(ktory_przycisk == opis_p)
      {
         new Opis_Swing(mieszkanie);
      }
      if(ktory_przycisk == lokatorzy_p)
      {
         new Lokatorzy_Swing(mieszkanie);
      }
      if(ktory_przycisk == koszty_p)
      {
         new Koszty_Swing(mieszkanie.koszty);
      }
      if(ktory_przycisk == zaplacone_p)
      {
         mieszkanie.czy_zaplacone = zaplacone_p.isSelected();
         System.out.println(mieszkanie.czy_zaplacone);
         mieszkanie.zapisz();
      }
      if(ktory_przycisk == przycisk_zapisz)
      {
         mieszkanie.czynsz = czynsz_p.getText();
         mieszkanie.okres_wynajmu = okres_p.getText();
         mieszkanie.kaucja = kaucja_p.getText();
         mieszkanie.platnosc = platnosc_p.getText();
         mieszkanie.zapisz();
      }
   }
}

class Opis_Swing extends JFrame implements KeyListener
{
   M_calosc mieszkanie;
   JFrame okno;
   JTextArea opis_tekst;

   Opis_Swing(M_calosc m)
   {
      mieszkanie = m;

      okno = new JFrame("opis " + mieszkanie.nazwa);
      okno.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);


      Container kontener = okno.getContentPane();
      GridLayout rozklad = new GridLayout(1  , 1);
      kontener.setLayout(rozklad);

      opis_tekst = new JTextArea(mieszkanie.opis, 30,60);
      opis_tekst.setLineWrap(true);
      opis_tekst.setWrapStyleWord(true);
      opis_tekst.addKeyListener(this);

      kontener.add(opis_tekst);

      okno.pack();
      okno.setVisible(true);
   }

   @Override
   public void keyTyped(KeyEvent e) {}

   @Override
   public void keyPressed(KeyEvent e) {
      if(e.getKeyCode() == KeyEvent.VK_ENTER)
      {
         mieszkanie.opis = opis_tekst.getText();
         mieszkanie.zapisz();
         okno.dispose();
      }
   }

   @Override
   public void keyReleased(KeyEvent e) {}
} 
