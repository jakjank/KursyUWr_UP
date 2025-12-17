### Zadanie 1

```java
public class CoarseList<T> {
    private Node head;
    private Lock lock = new ReentrantLock();
    
    public CoarseList() {
        head = new Node(Integer.MIN_VALUE);
        head.next = new Node(Integer.MAX_VALUE);
    }

    public boolean add(T item) {
        Node pred, curr;
        int key = item.hashCode();
        lock.lock();
        try {
            pred = head;
            curr = pred.next;
            while (curr.key < key) {
                pred = curr;
                curr = curr.next;
            }
            if (key == curr.key) {
                return false;
            } else {
                Node node = new Node(item);
                node.next = curr;
                pred.next = node;
                return true;
            }
        } finally {
            lock.unlock();
        }
    }

    public boolean remove(T item) {
        Node pred, curr;
        int key = item.hashCode();
        lock.lock();
        try {
            pred = head;
            curr = pred.next;
            while (curr.key < key) {
                pred = curr;
                curr = curr.next;
            }
            if (key == curr.key) {
                pred.next = curr.next;
                return true;
            } else {
                return false;
            }
        } finally {
            lock.unlock();
        }
    }

    public boolean contains(T item) {
        int key = item.hashCode();
        Node curr = head;
        while (curr.key < key) {
            curr = curr.next;
        }
        return curr.key == key && !curr.marked;
    }
}
```

1) **Niezmiennik reprezentacji** to własność dotycząca danego obiektu kiedy jest tworzony i taka że żaden proces nie jest w stanie wykonać ruchu który by usunął tę własność. W `CoarseList` niezmiennikiem jest to, że dla każdego kluzcza w liście występuje conajwyżej jeden `Node` z nim.

**Mapa abstrakcji** to definicja tego jak mamy rozumieć dany biekt. W `CoarseList` mapa abstrakcji jest taka, że obiekt jest w zbiorze przez nią reprezentowaną jeśli jeśli Node z takim kluczem jest osiągalny z `head`. 

2) W `add` i `remove` dobrym punktem linearyzacji jes zawołanie `unlock()`.

3) Gdyby metody były linearyzowane w momencie zajęcia zamka, to mapa "element należy do zbioru  iff węzeł na liście, w którym znajduje się ten element jest osiągalny z węzła head" nie byłaby poprawna. Zał. że `7` jest w naszej mapie. **A** woła `remove(7)` i zajmuje lock-a. Od ego momentu nie powinniśmy znaleźć `7` w zbiorze ale cały czas można do niego dojść z *head* i gdyby **B** zawołał `contains(7)` to mógłby wciąż dostać *true*.

4) element należy do zbioru  iff węzeł na liście, w którym znajduje się ten element jest osiągalny z węzła *head* i lock nie jest zajety przez metode `remove`.

### Zadanie 2

Ideą `FineList` jest aby nie mieć jednego zamka na całą listę ale blokować dostęp do pojedynczych node-ów. 

```java
public boolean add(T item) {
    int key = item.hashCode();
    head.lock();
    Node pred = head;
    try {
        Node curr = pred.next;
        curr.lock();
            try {
                while (curr.key < key) {
                pred.unlock();
                pred = curr;
                curr = curr.next;
                curr.lock();
            }
            if (curr.key == key) {
                return false;
            }
            Node newNode = new Node(item);
            newNode.next = curr;
            pred.next = newNode;
            return true;
        } finally {
            curr.unlock();
        }
    } finally {
        pred.unlock();
    }
}

public boolean remove(T item) {
    Node pred = null, curr = null;
    int key = item.hashCode();
    head.lock();
    try {
        pred = head;
        curr = pred.next;
        curr.lock();
        try {
            while (curr.key < key) {
                pred.unlock();
                pred = curr;
                curr = curr.next;
                curr.lock();
            }
            if (curr.key == key) {
                pred.next = curr.next;
                return true;
            }
            return false;
        } finally {
            curr.unlock();
        }
    } finally {
        pred.unlock();
    }
}
```

Punkt linearyzacji `add` i `remove` to moment zdobycia locka na node-a z większym lub równym kluczem (klucz jest to success, nie ma to fail). 
`add`: od tego momentu inne wywołania `add` czy `remove` nie będą w stanie zdobyć tego node-a anie jego *pred* przed jegoz zwolnieniem przez aktualne wywołanie. Po zdobyciu locka będą już widziały dodany node w liście dlatego jest to linearyzacja.
`remove`: analogicznie do `add`

### Zadanie 3

Element jest w zbiorze iff node z taką wartością jest osiągalny z head-a (uwzgledniajac .

```java
public boolean bad_contains(T item) {
    int key = item.hashCode();
    Node curr = head.next;

    while (curr.key < key) {
        curr = curr.next;
    }
    return (curr.key == key);
}
```

`bad_contains` zwraca odpowiedź poprawną dla jakiegoś stanu listy, który istniał w trakcie jej wykonania.

Ale nie jest to poprawnosc wspołbieżna jakiej oczekujemy.
My chcemy aby metoda miała punkt linearyzacji.
`bad_contains` nie ma punktu linearyzacji bo w momencie ostatniego `curr.key < key` stan widzianej listy (node jest lub nie) może już być nieaktualny.

```java
public boolean contains(T item) {
    int key = item.hashCode();
    head.lock();
    Node pred = head;
    try {
        Node curr = pred.next; //(*)
        curr.lock();
        try {
            while (curr.key < key) {
                pred.unlock();
                pred = curr;
                curr = curr.next;  // (**)
                curr.lock();
            }
            return (curr.key == key);
        } finally {
            curr.unlock();
        }
    } finally {
        pred.unlock();
    }

}
```

punktem linearyzacji jest (\*) lub ostatnie wykonanie (\*\*). W tych momentach proces ma lock-a na poprzednika zajmowanego node-a i żaden inny wątek nie jest w stanie dodać/usunąć node-a z szukanym kluczem więc odpowiedź będzie zgodna z aktualnym stanem.

### Zadanie 4

```java
public boolean remove(T item) {
    int key = item.hashCode();
    while (true) {
        Node pred = head;
        Node curr = pred.next;
        while (curr.key < key) {
            pred = curr; curr = curr.next;
        }
        pred.lock(); curr.lock();
        try {
            if (validate(pred, curr)) {
                if (curr.key == key) {
                    pred.next = curr.next;
                    return true;
                } else {
                    return false;
                }
            }
        } finally {
            pred.unlock(); curr.unlock();
        }
    }
}
```

*OptimisticList* najpierw iteruje się po liście w add i remove bez patrzenia na lock-i. Po znalezieniu intersujących nas *pred* i *cur* zakładamy na nich lock-i. Potem sprawdzay czy struktura listy w trakcie naszej iteracji nie zmieniła się tak że nasze *pred* lub *cur* już nie są osiągalne. Jeśli dalej są to możemy działać (mielśmy lock-i więc w trakcie walidacji się nie zepsuło), jeśli nie, to szukamy ponownie nowej pary *pred* i *cur*.

Zagłodzenie musi nastąpic na `while(true)`. 
Kolejny obrót tej pętli nastąpi wtw. jeśli `validate` zwróci false.
`validate` zwróci false jeśli nie znajdzie danych *pred* i *curr*.
Przykład ciągłego failowania `validate`:
mamy a -> b -> c
wątek A chce usunąć c,
znalazł b i c,
W tym czasie wątek B dodał woknał `add(b1)` t. że mamy
a -> b -> b1 -> c
więc validate w `remove` z-failuje bo `b.next` != c.
potem A znajdzie b1 i c, B doda b2 itd.

### Zadanie 5

```java
public class TimestampOptimisticList<T> {
    // nodes as before
    // some ctor

    private long timestamp = 0;
    private tsLock = Lock();

    private long getTimestamp() {
        tsLock.lock();
        try {
            return timestamp;
        } finally {
            tsLock.unlock();
        }
    }incrementTimestamp

    private void incrementTimestamp() {
        tsLock.lock();
        try {
            timestamp++;
        } finally {
            tsLock.unlock();
        }
    }

    public boolean contains(T item) {
        int key = item.hashCode();
        
        while (true) {
            long tsSnapshot = getTimestamp();

            Node curr = head;
            while (curr.key < key)
                curr = curr.next;

            // Check result
            boolean result = (curr.key == key);

            // Check that no modifications occurred during this traversal
            long tsNow = getTimestamp();
            if (tsSnapshot == tsNow)
                return result;

            // otherwise retry
        }
    }

    public boolean add(T item) {
        int key = item.hashCode();

        while (true) {
            long tsSnapshot = getTimestamp();

            Node pred = head;
            Node curr = pred.next;
            while (curr.key < key) {
                pred = curr;
                curr = curr.next;
            }

            pred.lock.lock();
            try {
                curr.lock.lock();
                try {
                    // Was the list unchanged?
                    if (tsSnapshot == getTimestamp()) {
                        if (curr.key == key) {
                            return false;
                        }
                        Node newNode = new Node(item);
                        newNode.next = curr;
                        pred.next = newNode;
                        incrementTimestamp();
                        return true;
                    }
                } finally {
                    curr.lock.unlock();
                }
            } finally {
                pred.lock.unlock();
            }
            // otherwise retry
        }
    }

    public boolean remove(T item) {
        int key = item.hashCode();

        while (true) {
            long tsSnapshot = getTimestamp();

            Node pred = head;
            Node curr = pred.next;
            while (curr.key < key) {
                pred = curr;
                curr = curr.next;
            }

            pred.lock.lock();
            try {
                curr.lock.lock();
                try {
                    // Was the list unchanged since traversal?
                    if (tsSnapshot == getTimestamp()) {
                        if (curr.key != key) {
                            return false;
                        }
                        pred.next = curr.next;
                        incrementTimestamp();
                        return true;
                    }
                } finally {
                    curr.lock.unlock();
                }
            } finally {
                pred.lock.unlock();
            }
            // otherwise retry
        }
    }
}
```

### Zadanie 6

LazyList zamiast reiterować po liście jak OptimisticList używa dodatkowych znaczników `marked` w swoich node-ach.
Jesli node jest usunięty to ustawia się `marked` na True i jeśli znaleźliśmy intersującego node-a to nie ma potrzeby reiterować się aby sprawdzić czy dalej jest osiągalny tylko od razu mamy te informację z `marked`.

oryginalny remove:
```java
private boolean validate(Node pred, Node curr) {
    return !pred.marked && !curr.marked && pred.next == curr;
}

public boolean remove(T item) {
    int key = item.hashCode();
    while (true) {
        Node pred = head;
        Node curr = head.next;
        while (curr.key < key) {
            pred = curr; curr = curr.next;
        }
        pred.lock();
        try {
            curr.lock();
            try {
                if (validate(pred, curr)) {
                    if (curr.key != key) {
                        return false;
                    } else {
                        curr.marked = true;
                        pred.next = curr.next;
                        return true;
                    }
                }
            } finally {
                curr.unlock();
            }
        } finally {
            pred.unlock();
        }
    }
}
```

Nie da się używać tylko jednego locka.
Bez zablokowania obu węzłów nie da się atomowo chronić relacji pred → curr, która jest kluczowa dla poprawnego usunięcia elementu w Lazy List.

### Zadanie 7

1. Stan początkowy
`head → A → C`
Szukamy B.

Wątki:
T1: contains(B) (bez locków)
T2: add(B)

Przebieg
T1 czyta A.next = C
T2 wstawia B:
`head → A → B → C`
T1 widzi curr = C
C.key > B.key → T1 zwraca false

2. Stan początkowy
`head → A → B → C`

Wątki
T1: contains(B)
T2: remove(B)

Przebieg
T2:
`B.marked = true;   // punkt liniaryzacji remove`
T1:
dochodzi do B
B.key == key
nie sprawdza marked
zwraca true
T2:
A.next = C;