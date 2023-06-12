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

class Mieszkanie implements Serializable
{
    String nazwa;
    String opis;
    //? dokumenty
    Spis_Mieszkan spis_mieszkan;

    public Mieszkanie(String s, Spis_Mieszkan s_m)
    {
        nazwa = s;
        spis_mieszkan = s_m;
    }

    public void ustaw_nazwe(String nazwa)
    {
        this.nazwa = nazwa;
    }

    public String daj_nazwe()
    {
        return nazwa;
    }
    public void wyswietl_okno(Spis_Mieszkan spis_mieszkan) {}

    public void zapisz()
    {
        try
        {
            this.spis_mieszkan.zapisz_do_pliku("dane.txt");
        }
        catch(IOException e1)
        {
            System.out.println("nie udalo sie zapisac");
        }
    }
}

