// Program implementuje kolejkę obsługującą środowisko
// wielowątkowe. Klasa ta jest testowana na przykładzie
// producenta-konsumenta (producent wkłada rzecz do bufora, 
// a konsument je zjada)

import java.util.ArrayList;

class Bufor<T>
{
    private ArrayList<T> lista;
    private int wielkosc;
    private int ile;

    // Konstruktor buforu 
    public Bufor(int wielkosc)
    {
        lista = new ArrayList<T>(wielkosc);
        this.wielkosc = wielkosc;
        ile = 0;
    }

    // InterruptedException dodany po sugestji IDE
    public synchronized void push(T elem) throws InterruptedException
    {
        while(ile == wielkosc)
        {
            wait();
        }

        lista.add(elem);
        ile++;
        notify();
        return;
    }

    public synchronized T pop() throws InterruptedException
    {
        while(ile == 0)
        {
            wait();
        }

        ile--;
        notify();
        return lista.remove(0);
    }
}

class Test
{
    public static void main(String[] args)
    {
        Bufor<Character> buf = new Bufor<>(5);
        
        // Wątek producent produkuje kolejne 20 znaków alfabetu
        Thread producent = new Thread(() -> 
        {
            for(int i = 0; i < 20; i++){
                try {
                    System.out.println("producent zrobil: "+((char) (i + 65)));
                    buf.push((char) (i + 65));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.println("Producent skonczyl");
        });

        // Wątek konsument zjada wszystko co jest w buforze
        Thread konsument = new Thread(() -> 
        {
            for(int i = 0; i < 20; i++){
                try {
                    System.out.println("konsument zjadl: "+buf.pop());
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.println("Konsument skonczyl");
        });

        // wątki startują
        producent.start();
        konsument.start();
    }
}