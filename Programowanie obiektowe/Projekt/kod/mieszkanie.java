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

    public Mieszkanie(String nazwa)
    {
        this.nazwa = nazwa;
    }

    public String daj_nazwe()
    {
        return  nazwa;
    }
}
