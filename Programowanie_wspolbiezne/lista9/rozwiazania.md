### Zadanie 1

**Zasada lokalności odwołań** mówi o tym, że aby efektywnie implementować *spin lock-i* wątki powinny odczytwać wartości zmiennych pamiętane w cache-ach aby nie produkować zbędnego ruchu na bus-ie.

**protokoły spójności** są potrzebne aby programy współb. wykonywały się w oczekiwany sposób. Jak np. działałby algorytm Petersona (poza tym że i tak nie działa w naszym modelu pamięci :) ) gdyby oba procesy miały z-cache-owanego vicitma?

**protokół MESI** - każda linia w cache-u jest oznaczona jednym z nast. tagów:
* *Modified* - żaden inny procesor nie ma tej linii w swoim cache-u. Linia była zmodyfikowana i musi być wpisana ponownie do pamięci.
* *Exclusive* - żaden inny procesor nie ma tej lini w swoim cache-u i linia nie była modyfikowana.
* *Shared* - linia nie była zmodyfikowana i inne procesory mogą ją też mieć w swoich cache-ach.
* *Invalid* - linia nie zawiera nic użytecznego

Kiedy procesor wykonuje load lub store na pamięci to wysyła *request* na tę operację na bus-ie. Inne procesory słuchają bus-a i odpowiednio aktualizują tagi.

* Jeśli procesor requestuje *load* na danej linii w trybie *exclusive* (zamierza ją modyfikować), inne procesore ustawiaja tagi na tę linię na *invalid*.
* Kiedy procesor requestuje *load* w trybie *shared*, to jeśli jakiś procesor ma tę linię w trybie exclusive to musi zmienić tag na *shared*. Każdy procesor który ma tę linie *modified* musi wykonać *write* z powrotem do pamięci zanim requestowany *load* będzię mógł być wykonany.
* Jeśli cache się zapełni i trzeba usunąć linię, to jeśli jest ona *modified* to trzeba zrobić na niej wpierw *write*.

### Zadanie 2
```java
public class TASLock implements Lock {
AtomicBoolean state = new AtomicBoolean(false);
public void lock() {
while (state.getAndSet(true)) {}
}
public void unlock() {
state.set(false);
}
}
```

```java
public class TTASLock implements Lock {
AtomicBoolean state = new AtomicBoolean(false);
public void lock() {
while (true) {
while (state.get()) {};
if (!state.getAndSet(true))
return;
}
}
public void unlock() {
state.set(false);
}
}
```
Wydajność implementacji zamków mierzy się czasem potrzebnego na uzyskanie przez jakiś proces dostępu do sekcji krytycznej względem ilości procesów próbujących ten dostęp uzyskać.

Różnice wydajności TAS i TTAS sprowadzają się do ilości *cache miss-ów*. Jeśli procesor chce odczytać wartość jakiegoś adresu to najpierw sprawdza swój lokalny (bardzo szybki w porównaniu do pamęci) cache. Jeśli adres tam jest to mamy *cache hit*. Jeśli nie to procesor wysyła request o wartość tego adresu na bus-ie (czas) i czeka na odpowiedź od innych procesorów lub pamięci (czas).

W TAS każdy czekający procesor wysyła request na bus-ie więc muszą czekać aż będzie wolny. Dodatko skoro getAndSet() 'zmienia' wartość `state` to pozostałe czekające procesy muszą na nowo odczytać niezmienioną wartość `state` z pamięci (*cache miss* prawie zawsze). Ostatecznie gdy proces wychodząćy z sekcji krytycznej chce zwolnić zamek, to też musi czekać aż bus będzie wolny.

W TTAS skoro wartość `state` nie jest 'zmieniana' przez czekające procesy to czytają one ze swoich cache-y i bus jest wolny. Z kolei kiedy lock jest zwalniany to znowu wszytskie procesy inwalidują swoje linie i wysyłają requesty na bus-ie. Pierwszy który wykona getAndSet wchodzi do CS ale pozostałe znowu mają inwalidacje i znowu robią burzę na bus-ie. (Ale to już jest w czasie kiedy i tak by czekały na CS więc nas już aż tak nie boli?)

### Zadanie 3

```java
public class ALock implements Lock {
    ThreadLocal<Integer> mySlotIndex = new ThreadLocal<Integer> (){
        protected Integer initialValue() {
            return 0;
        }
    };

    AtomicInteger tail;
    boolean[] flag;
    int size;

    public ALock(int capacity) {
        size = capacity;
        tail = new AtomicInteger(0);
        flag = new boolean[capacity];
        flag[0] = true;
    }

    public void lock() {
        int slot = tail.getAndIncrement() % size;
        mySlotIndex.set(slot);
        while (! flag[slot]) {};
    }

    public void unlock() {
        int slot = mySlotIndex.get();
        flag[slot] = false;
        flag[(slot + 1) % size] = true;
    }
}
```

Zasada działania jak widać (możne przepisac początek 7.5.1). Warto zwrócić uwagę, że modyfikacja *lokalneg* `mySlotIndex` nie generuje ruchu na bus-ie.

Przewaga nad *Exponential Backoff*, *TAS* i *TTAS*:
* w powyższych algorytmach zdobycie zamka zależało od czytania/modyfikowania jednej wspólnej zmiennej. Jeśli nastąpiła jej modyfikacja, to wszystkie procesy musiały ją na nowo odczytać z pamięci (lub od innych procesów) generując duży ruch na bus-ie.
* W algorytmie *BackoffLock* procesy mogą czekać na dostęp dłużej niż to potrzebne. Procesy czekałyby na dostęp do CS pomimo tegeo, że nikt w niej nie jest.
W *ALock* te problemy są rozwązane. Każðy proces *spinnuje* się na innej zmiennek i wchodzi do CS gdy jego poprzednik ją zwolni.

**False shering** to zjawisko gdy sąsiednie w pamięci elementy (np. komórki listy) są cache-owane w tej samej linii. Write do jednej zmiennej inwaliduje cała linie zmuszając procesy do aktualizowania lini pomimo tego, że interesująca ich zmienna się nie zmieniła.
Można ten problem na liście w *ALock* rozwiązać używając *paddingu* pomiędzy elementami listy. Polega to na zwiększeniu rozmiaru elementów listy tak aby każdy "wpadł" do innej linii cache-a.

(ex3.png)

### Zadanie 4

W sposobie **1** problemem jest, że każda operacja na liczniku lub na zamku powoduje invalidację linii cache u wszystkich pozostałych procesorów.
Ponieważ wszystkie wątki wirują na tej samej zmiennej, w systemie z pojedynczą szyną prowadzi to do dużej liczby globalnych odczytów tej samej linii.
Dodatkowo intensywne *spinning* opóźnia zwalnianie zamka.
Protokół ten bardzo słabo skalują się dla dużego n.

W sposobie **2** każdy wątek wiruje na własnej zmiennej, więc zmiana jednej komórki tablicy powoduje invalidację tylko na tym rdzeniu, który jej potrzebuje, a nie na wszystkich jednocześnie.
Zakładając brak *false sharingu*, odczyty linii są lokalne, a liczba invalidacji jest proporcjonalna do n, a nie do $n^2$.
Dzięki temu protokół jest bardziej skalowalny, a pojedyncza szyna nie staje się aż tak dużym wąskim gardłem.

### Zadanie 5

```java
public class CLHLock implements Lock {
    AtomicReference<QNode> tail = new AtomicReference<QNode>(new QNode());
    ThreadLocal<QNode> myPred;
    ThreadLocal<QNode> myNode;
    
    public CLHLock() {
        tail = new AtomicReference<QNode>(new QNode());
        myNode = new ThreadLocal<QNode>() {
            protected QNode initialValue() {
                return new QNode();
            }
        };
        myPred = new ThreadLocal<QNode>() {
            protected QNode initialValue() {
                return null;
            }
        };
    }

    public void lock() {
        QNode qnode = myNode.get();
        qnode.locked = true;
        QNode pred = tail.getAndSet(qnode);
        myPred.set(pred);
        while (pred.locked) {}
    }
    
    public void unlock() {
        QNode qnode = myNode.get();
        qnode.locked = false;
        myNode.set(myPred.get());
    }
}
```

Każdy proces bierze ostatniego qNode-a z globalnego tail-a dzielonego między wszystkie wątki i jednocześnie (atomowy getAndSet) ustawia swojego node-a na jako tail-a.
Następnie czeka aż poprzednik skończy CS. W `unlock` proces oświadcza, że skończył pracę i recyklinguje qNoda swojego poprzednika na swój kolejny node.

W sytuacji gdy proces robi `unlock()` i żaden kolejny nie czeka w kolejce, to jego myNode (tail również został wczesniej ustawiony na myNode) nie ma już żadnej referencji i zostanie usunięty, a kolejny proces wołąjący `lock()` będzie musiał utworzyć nowego qNoda w `tail.getAndSet(qnode)`.

Aby pozbyć się problemu potencjalnego tworzenia  i sprzątania (GC) nieskonczonej liczby qNode-ów możemy w każdym CLHLocku używać zawsze tych samych dwóch qNodów:

```java
public class CLHLock implements Lock {
    AtomicReference<QNode> tail = new AtomicReference<QNode>(new QNode());
    ThreadLocal<QNode> myPred;
    ThreadLocal<QNode> myNode;
    
    public CLHLock() {
        tail = new AtomicReference<QNode>(new QNode());
        myNode = new ThreadLocal<QNode>() {
            protected QNode initialValue() {
                return new QNode();
            }
        };
        myPred = new ThreadLocal<QNode>() {
            protected QNode initialValue() {
                return null;
            }
        };
    }

    public void lock() {
        QNode qnode = myNode.get();
        qnode.locked = true;
        QNode pred = tail.getAndSet(qnode);
        myPred.set(pred);
        while (pred.locked) {}
    }
    
    // public void unlock() {
    //     QNode qnode = myNode.get();
    //     qnode.locked = false;
    //     myNode.set(myPred.get());
    // }

    public void unlock() {
        QNode node = myNode.get();
        node.locked = false;

        // Zamiana ról: stary node staje się pred, a pred staje się node do następnej iteracji
        QNode temp = myNode.get(); 
        myNode.set(myPred.get());
        myPred.set(temp);
    }
}
```

### Zadanie 6

```java
public class BadCLHLock implements Lock { 
    AtomicReference<Qnode> tail = new AtomicReference<QNode>(new QNode()); 
    ThreadLocal<Qnode> myNode = new ThreadLocal<QNode> { 
        protected QNode initialValue() { 
            return new QNode(); 
        } 
    }; 
    public void lock() { 
        Qnode qnode = myNode.get(); 
        qnode.locked = true; // I’m not done 
        // Make me the new tail, and find my predecessor 
        Qnode pred = tail.getAndSet(qnode); 
        while (pred.locked) {} 
    } 
    public void unlock() { 
        // reuse my node next time 
        myNode.get().locked = false; 
    } 
    static class Qnode { // Queue node inner class 
        volatile boolean locked = false; 
    } 
}
```

W tej wersji może dojść do zakleszczenia. Wątek A zaczyna.
1. A ustawia `locked` = true i wchodzi do CS
2. B ustawia `tail` na swojego node z `locked` = true
3. B czeka w while-u
4. A wychodzi z CS, robi `locked` = false i od razu woła `lock` i ustawia `Anode.locked` = true
5. B nie zdążył odczytać, że A wyszedł i wciąż ma `Bnode.locked` == true
6. A czeka na B i B czeka na A

### Zadanie 7

```java
public class TOLock implements Lock{

    // jesli proces zobaczy ten node, znaczy że może wejsc do CS
    static QNode AVAILABLE = new QNode();
    AtomicReference<QNode> tail;
    ThreadLocal<QNode> myNode;

    public TOLock() {
        tail = new AtomicReference<QNode>(null);
        myNode = new ThreadLocal<QNode>() {
            protected QNode initialValue() {
                return new QNode();
            }
        };
    }

    public boolean tryLock(long time, TimeUnit unit)
            throws InterruptedException {
        // zacznij mierzyć czas
        long startTime = System.currentTimeMillis();
        long patience = TimeUnit.MILLISECONDS.convert(time, unit);
        
        // stwórz i ustaw swojego Node-a
        QNode qnode = new QNode();
        myNode.set(qnode);
        qnode.pred = null;

        // ustaw swojego Pred na tail-a i tail-a na swojego node-a
        QNode myPred = tail.getAndSet(qnode);

        // jeśli nie było poprzednika lub poprzednik ustawił
        // swojeg pred na AVAILABLE (zrobił unlock) to zdobyłeś lock-a
        if (myPred == null || myPred.pred == AVAILABLE) {
            return true;
        }

        // poczekaj chwile
        while (System.currentTimeMillis() - startTime < patience) {

            // weź pred swojego pred
            QNode predPred = myPred.pred;

            // jeśli pred zrobił unlock to można wejść
            if (predPred == AVAILABLE) {
                return true;
            }
            // jesli pred opóścił kolejkę to ustawił swojego pred z null na 
            // swojego node-a. Wtedy zaczynamy na nim czekac.
            else if (predPred != null) {
                myPred = predPred;
            }
        }

        // poddajemy sie.
        // sprawdzamy czy tail to nasz qnode,
        // jeśli tak to ustawiamy naszego pred na koniec kolejki.
        if (!tail.compareAndSet(qnode, myPred))
            // jesli nie, to naszego pred zmianiemy z null na na poprzediego noda z kolejki
            qnode.pred = myPred;
        return false;
    }
    
    public void unlock() {
        QNode qnode = myNode.get();
        // jesli bylismy ostatni w kolejce to ustaw tail na null
        if (!tail.compareAndSet(qnode, null))
            // jesli nie to daj kolejnemu znać, że skończylismy
            qnode.pred = AVAILABLE;
    }
    
    static class QNode {
        public QNode pred = null;
    }
}
```

### Zadanie 8

W MCSLock po wywołaniu `lock()` proces appenduje swojego node-a na koniec kolejki.
Jeśli kolejka była pusta to wchodzi do CS. Wpp. ustawia pole `next` w poprzednim w kolejce node-zie na swojego node-a i pole `locked` u siebie na true.
Następnie czeka aż poprzednik ustawi jego pole `locked` na folse podczes `unlock()`.
`unlock` jest trochę bardziej skomplikowany, bo musi rozważyć czy po nas ktoś jest w kolejce (sprawdzając pole `next` w swoim node-zie) i potencjalnie ustawić temu komuś `locked` na false.
Także w `unlock` proces bierze swój `next`, jeśli jest równe null to sprawdza czy `tail` faktycznie jest ustawiony na nim (nikt inny się nie zdążył dołaczyć). Jeśli tak to ustawia `tail` na null. Wpp. czeka aż kolejny proces ustawi pole `next` na swojego node-a i od razu mu je false-ujemy.

```java
public class MCSLock implements Lock {
    AtomicReference<QNode> tail;
    ThreadLocal<QNode> myNode;

    public MCSLock() {
        queue = new AtomicReference<QNode>(null);
        myNode = new ThreadLocal<QNode>() {
            protected QNode initialValue() {
                return new QNode();
            }
        };
    }

    public void lock() {
        QNode qnode = myNode.get();
        QNode pred = tail.getAndSet(qnode);
        if (pred != null) {
            qnode.locked = true;
            pred.next = qnode;
            // wait until predecessor gives up the lock
            while (qnode.locked) {}
        }
    }

    public void unlock() {
    QNode qnode = myNode.get();
    if (qnode.next == null) {
        if (tail.compareAndSet(qnode, null))
            return;
        // wait until predecessor fills in its next field
        while (qnode.next == null) {}
        }    
        qnode.next.locked = false;
        qnode.next = null;
    }

    class QNode {
        boolean locked = false;
        QNode next = null;
    }
}
```

Czemu może być lepsze od CLH na systemach z architekturą NUMA?
(W numie każdy proces ma swój (szybki) kawałek pamięci, jeśli chce odczytać z kawałka pamięci innego procesora to jest to wolne)

W CLH i MCS wątki aktywnie operują na strukturach w pamięci, które mogą leżeć:
* w lokalnej pamięci (szybko),
* lub w zdalnej pamięci (wolno).

Na NUMA unikamy odczytywania/zapisywania pamięci, która należy do innego procesora, bo to generuje kosztowne transfery cache-line’ów między węzłami NUMA.

W CLH locku każdy wątek:
czeka na pole locked w węźle swojego poprzednika,
czyli robi spin na pamięci należącej do poprzedniego wątku (wolne).

W MCS locku wątki:
spinują na swoim własnym węźle (myNode),
czekając, aż poprzednik ustawi w ich własnym węźle flagę, że mogą wejść (on zmienia u mnie raz, a nie ja w kółko srawdzam jego).
co skutkuje mniejszą ilością ruchu między pamięciami procesów.

### Zadanie 9

Zwracamy boola który mówi czy w tym momencie lock wykonałby się bez czekania

a)
```java
public class TASLock implements Lock {
    AtomicBoolean state = new AtomicBoolean(false);

    public void lock() {
        while (state.getAndSet(true)) {}
    }
    
    public void unlock() {
        state.set(false);
    }

    public boolean isLocked() {
        // wykonalibyśmy obrót na while-u
        return state.get();
    }
}
```

b)
```java
public class CLHLock implements Lock {
    AtomicReference<QNode> tail = new AtomicReference<QNode>(new QNode());
    ThreadLocal<QNode> myPred;
    ThreadLocal<QNode> myNode;
    
    public CLHLock() {
        tail = new AtomicReference<QNode>(new QNode());
        myNode = new ThreadLocal<QNode>() {
            protected QNode initialValue() {
                return new QNode();
            }
        };
        myPred = new ThreadLocal<QNode>() {
            protected QNode initialValue() {
                return null;
            }
        };
    }

    public void lock() {
        QNode qnode = myNode.get();
        qnode.locked = true;
        QNode pred = tail.getAndSet(qnode);
        myPred.set(pred);
        while (pred.locked) {}
    }
    
    public void unlock() {
        QNode qnode = myNode.get();
        qnode.locked = false;
        myNode.set(myPred.get());
    }

    public boolean isLocked() {
        return tail.get().locked;   
    }
}
```

c)
```java
public class MCSLock implements Lock {
    AtomicReference<QNode> tail;
    ThreadLocal<QNode> myNode;

    public MCSLock() {
        queue = new AtomicReference<QNode>(null);
        myNode = new ThreadLocal<QNode>() {
            protected QNode initialValue() {
                return new QNode();
            }
        };
    }

    public void lock() {
        QNode qnode = myNode.get();
        QNode pred = tail.getAndSet(qnode);
        if (pred != null) {
            qnode.locked = true;
            pred.next = qnode;
            // wait until predecessor gives up the lock
            while (qnode.locked) {}
        }
    }

    public void unlock() {
    QNode qnode = myNode.get();
    if (qnode.next == null) {
        if (tail.compareAndSet(qnode, null))
            return;
        // wait until predecessor fills in its next field
        while (qnode.next == null) {}
        }    
        qnode.next.locked = false;
        qnode.next = null;
    }

    public boolean isLocked() {
        Qnode p = tail.get();
        if (p != null)
            return p.locked;
        return false;
    }

    class QNode {
        boolean locked = false;
        QNode next = null;
    }
}
```

### Zadanie 10

Zamki hierarchiczne mają brać pod uwagę *hierarchiczną* budowę komputerów.
To znaczy, że procesory powinny inaczej częściej zdobywać lock-a jeśli aktualnie lock należy do procesora z którym są w stanie szybciej się komunikować bo wtedy nie ma kosztownego przenoszenia lock-a między clustrami.

```java
public class HBOLock implements Lock {
    private static final int LOCAL_MIN_DELAY = ...;
    private static final int LOCAL_MAX_DELAY = ...;
    private static final int REMOTE_MIN_DELAY = ...;
    private static final int REMOTE_MAX_DELAY = ...;
    private static final int FREE = -1;

    AtomicInteger state;
    
    public HBOLock() {
        state = new AtomicInteger(FREE);
    }

    public void lock() {
        int myCluster = ThreadID.getCluster();
        Backoff localBackoff =
            new Backoff(LOCAL_MIN_DELAY, LOCAL_MAX_DELAY);
        Backoff remoteBackoff =
            new Backoff(REMOTE_MIN_DELAY, REMOTE_MAX_DELAY);
        
        while (true) {
            if (state.compareAndSet(FREE, myCluster)) {
                return;
            }
            int lockState = state.get();
            if (lockState == myCluster) {
                localBackoff.backoff();
            } else {
                remoteBackoff.backoff();
            }
        }
    }

    public void unlock() {
        state.set(FREE);
    }
}
```

W `HBOLock` procesy z tego samego clustra mogą mieć krótszy backoff dzięki czemu prawdopodobnie częściej zdobędą locka i rzadziej trzeba będzie przenosić locka do innego clustra (drogie). 
Wyjasnienie: `state` jest trzymane w jakims cache-u. Jeśli 'dalekiemu' procesowi uda się
`compareAndSet` to wtedy (na architekturze NUMA) trzeba przenieść tę zmienną z cacha jednej grupy procesorów do drugiej.
(1. exclusive ownership 2. invalidate line from all pther caches 3. perform atomic CAS locally)
co zajmuje czasw którym ktoś mógłby wykonywać swoje zadanie w CS.

