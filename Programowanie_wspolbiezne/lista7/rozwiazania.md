### Zadanie 1

```java
public class SimpleSnapshot<T> implements Snapshot<T> {

    private StampedValue<T>[] a_table; // array of atomic MRSW registers

    public SimpleSnapshot(int capacity, T init) {
        a_table = (StampedValue<T>[]) new StampedValue[capacity];
        for (int i = 0; i < capacity; i++) {
            a_table[i] = new StampedValue<T>(init);
        }
    }

    public void update(T value) {
        int me = ThreadID.get();
        StampedValue<T> oldValue = a_table[me];
        StampedValue<T> newValue =
        new StampedValue<T>((oldValue.stamp)+1, value);
            a_table[me] = newValue;
    }

    private StampedValue<T>[] collect() {
        StampedValue<T>[] copy = (StampedValue<T>[])
        new StampedValue[a_table.length];
        for (int j = 0; j < a_table.length; j++)
            copy[j] = a_table[j];
        return copy;
    }

    public T[] scan() {
        StampedValue<T>[] oldCopy, newCopy;
        oldCopy = collect();
        collect: while (true) {
            newCopy = collect();
            if (! Arrays.equals(oldCopy, newCopy)) {
                oldCopy = newCopy;
            continue collect;
            }
            T[] result = (T[]) new Object[a_table.length];
            for (int j = 0; j < a_table.length; j++)
                result[j] = newCopy[j].value;
            return result;
        }
    }
}
```

Metoda `update` zapisuje wartości ze zwiększonymi znacznikami czasowymi.

Metoda `scan` polega na wywoływaniu `collect` dopóki zwrócone przez dwa kolejne `collect` wartości z a_table nie będą takie same. W takiej sytuacji wiemy, że nie został wywołany w czasie pomiędzy dwoma `collectami` żaden update i zwrócona przez wartość jest **dobrym** snapshotem.
Od razu widać że `update` jest wait-free ale za to `scan` moze sie wykonywać nieskonczenie dlugo. Jeśli jednak będzie wykonywał się w izolacji to w końcu się skończy.

### Zadanie 2

```java
public class StampedSnap<T> {
    public long stamp;
    public T value;
    public T[] snap;
    
    public StampedSnap(T value) {
        stamp = 0;
        value = value;
        snap = null;
    }

    public StampedSnap(long label, T value, T[] snap) {
        label = label;
        value = value;
        snap = snap;
    }
}
```

```java
public class WFSnapshot<T> implements Snapshot<T> {
    private StampedSnap<T>[] a_table; // array of atomic MRSW registers

    public WFSnapshot(int capacity, T init) {
        a_table = (StampedSnap<T>[]) new StampedSnap[capacity];
        for (int i = 0; i < a_table.length; i++) {
            a_table[i] = new StampedSnap<T>(init);
        }
    }

    private StampedSnap<T>[] collect() {
        StampedSnap<T>[] copy = (StampedSnap<T>[])
            new StampedSnap[a_table.length];
        for (int j = 0; j < a_table.length; j++)
            copy[j] = a_table[j];
        return copy;
    }   

    public void update(T value) {
        int me = ThreadID.get();
        T[] snap = scan();
        StampedSnap<T> oldValue = a_table[me];
        StampedSnap<T> newValue =
            new StampedSnap<T>(oldValue.stamp+1, value, snap);
        a_table[me] = newValue;
    }
    public T[] scan() {
        StampedSnap<T>[] oldCopy;
        StampedSnap<T>[] newCopy;
        boolean[] moved = new boolean[a_table.length];
        oldCopy = collect();

        collect: while (true) {
            newCopy = collect();
            for (int j = 0; j < a_table.length; j++) {
                if (oldCopy[j].stamp != newCopy[j].stamp) {
                    if (moved[j]) {
                        return oldCopy[j].snap;;
                    } else {
                        moved[j] = true;
                        oldCopy = newCopy;
                        continue collect;
                    }
                }
            }
            T[] result = (T[]) new Object[a_table.length];
            for (int j = 0; j < a_table.length; j++)
                result[j] = newCopy[j].value;
            return result;
        }
    }
}
```

*dobry* snapshot to taki który zwracca stan rejestrów który faktycznie wystąpił w jakimś momencie podczas trwania metody `scan`.

Idea działania dla niewtajemniczonych:
Snapshot robimy zapisujac po sobie dwie kopie stany, jeśli się nie zmieniły to jest to *dobry* snapshot.
Snapshot się w oczywisty sposób nie uda jeśli w trakcie `scan` inny wątek zrobi `update` (conajmniej 2 razy).
Pomysł jest taki aby przed każdym `update` robić snapshot i wtedy "ratować" faktyczne wywołanie `scan` tym zapisanym snapshotem. Ale to jest niewystarczające, bo:

(ex2.png)

Rozwiązaniem tego problemu jest zauważenie, że jeśli inny wątek wykonał `update` dwukrotnie w czasie naszego `scan` to snapshot który on pamięta jest dla nas też dobry.

Chcemy pokazać, że powyższy `WFSnapshot` zwraca (1) dobry snapshot i (2) w skończonej liczbie kroków.

**(1)**
prosty przypadek: jeśli nie było kolizji to `scan` zwraca wynik drugiego `collect` i git.
Jeśli A robi `scan` i podczas kolejnego przeczytania przez A rejestru B jest tam inna wartość, to przynajmniej jeden write B wydarzył się pomiędzy tymi dwoma odczytami komórki przez A. B pisze do rejestru na koniec `update`, więc jakiś `update` wykonany przez B skończył się po pierwszym read-zie A w `scan` i kolejny skończył się pomiędzy ostatnią parą read-ów A. Zatem jeśli wynik zwrócony przez `scan` A zwrócił wartość z rejestru B `if (moved[B])` to wynik ten został uzyskany przez `scan` B podczas trwania `scan` wywołanego przez A. Wynik `scan` B został również otrzymany przez *clean double collect* lub przez jeszcze wewnętrzyny `scan` wg tego samego mechanizmy przez wątek C. I tak mogło być w głębiej i głębiej ale że mamy n wątków, to któryś `scan` musiał zostać uzyskany przez *clen double collect* wykonany pdczas `scan` A.

(ex2.2.png)

**(2)**
Dla dangeo `scan`,  skoro jest n-1 innych wątków, to po n+1 *double collect-ach* albo ostatni jest dobry albo któryś z wątków zmienił wartość swojego rejestru dukrotnie i wtedy zwrócimy wynik jego skanu.
