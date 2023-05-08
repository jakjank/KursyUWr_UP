// program implemenuje algorytm sortowania
// na listach elementów posiadających interfejs Comparable

import java.util.List;
import java.util.ArrayList;
import java.util.Arrays; 
class MergeSort<T extends Comparable<T>>
{
    public void sort(List<T> lista)
    {
        if(lista.size() > 1)
        {   
            // wyznaczamy środek listy
            int srodek    = lista.size() / 2;
            // tworzymy dwie nowe listy odpowiadające 
            // dwóm częściom listy wejściowej
            List<T> lewa  = new ArrayList<>(lista.subList(0, srodek));
            List<T> prawa = new ArrayList<>(lista.subList(srodek, lista.size()));
            // rekurencyjnie sortujemy obie części i
            // podmieniamy listę wejściową na posortowaną
            // sumę lewej i prawej listy
            this.sort(lewa);
            this.sort(prawa);
            this.merge(lewa, prawa, lista);
        }
    }
    public void merge(List<T> lewa, List<T> prawa, List<T> lista)
    {
        int wsk_lewy  = 0;
        int wsk_prawy = 0;
        int wskaznik  = 0;

        while(wsk_lewy < lewa.size() && wsk_prawy < prawa.size())
        {
            // sprawdzamy, czy mniejszy jest pierwszy el. z lewej,
            // czy pierwszy element z prawej listy i
            // ustawiamy na odpowiednim miejscu mniejszy element
            if(lewa.get(wsk_lewy).compareTo(prawa.get(wsk_prawy)) < 0)
            {
                lista.set(wskaznik, lewa.get(wsk_lewy));
                wsk_lewy++;
            }
            else
            {
                lista.set(wskaznik, prawa.get(wsk_prawy));
                wsk_prawy++;
            }
            wskaznik++;
            
            // zwiększamy odpowiednio każdy wskaźnik
        }

        // dopełniamy listę odpowiednio ogonem lewej lub prawej listy
        while(wsk_lewy < lewa.size())
        {
            lista.set(wskaznik, lewa.get(wsk_lewy));
            wsk_lewy++;
            wskaznik++;
        }
        while(wsk_prawy < prawa.size())
        {
            lista.set(wskaznik , prawa.get(wsk_prawy));
            wsk_prawy++;
            wskaznik++;
        }
    }
}

class Test
{
    public static void main(String[] args)
    {
        MergeSort<Integer> mergeSortLiczby = new MergeSort<>();
        MergeSort<String> mergeSortSlowa = new MergeSort<>();
        List<Integer> liczby = Arrays.asList(2,1,0,32,7,-3);
        List<String> slowa = Arrays.asList("c","aa","ab","x","b");

        // sortujemy 
        mergeSortLiczby.sort(liczby);
        mergeSortSlowa.sort(slowa);
        
        System.out.println("posortowane liczby: " + liczby);
        System.out.println("posortowane slowa: " + slowa);
    }

}