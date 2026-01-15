### Zadanie 1

Rozważmy punkty linearyzacji metod enq() i deq() w kolejce LockFreeQueue.
1. Czy jako punkt linearyzacji metody deq(), w przypadku gdy odnosi ona sukces, można wybrać instrukcję która odczytuje zwracaną wartość z węzła?

```java
public T deq() throws EmptyException {
    while (true) {
        Node first = head.get();
        Node last = tail.get();
        Node next = first.next.get();
        if (first == head.get()) {
            if (first == last) {
                if (next == null) {
                    throw new EmptyException();
                }
                tail.compareAndSet(last, next);
            } else {
                T value = next.value; // tutaj bysmy chcieli zlinearyzować
                if (head.compareAndSet(first, next))
                    return value;
            }
        }
    }
}
```

Nie można. Punkt linearyzacji ma byc pojedynczym momentem w którym efekt wywołania metody staje się widoczny dla wszystkich innych wątków. 
W zaznaczonym momencie next dalej *abstrakcyjnie* należy do kolejki i inny wątek mógłby wykonać na niem `deq()` co nie mogłoby się zdarzyć gdyby był to poprawny punkt linearyzzcji.

2. Czy jako punkt linearyzacji metody enq() można wybrać instrukcję (być może wykonywaną przez inny wątek), która z sukcesem aktualizuje pole tail?

Punkt linearyzacji nie może być na takiej instrukcji, bo dodawany node nie zaczyna w tym momencie należeć do kolejki. Operacja `tail.compareAndSet(last, next);` jedynie aktualizuje pomocniczy wskaźnik `tail`, a element faktycznie trafia do kolejki (kolejne będą dodawane za nim i może być usunięty (choć nie wydarzy się to zanim ustawiony zostanie tail bo mamy helping)) w momencie `last.next.compareAndSet(next, node)`.    

```java
public void enq(T value) {
    Node node = new Node(value);
    while (true) {
        Node last = tail.get();
        Node next = last.next.get();
        if (last == tail.get()) {
            if (next == null) {
                if (last.next.compareAndSet(next, node)) {
                    tail.compareAndSet(last, node);
                    return;
                }
            } else {
                tail.compareAndSet(last, next);
            }
        }
    }
}
```

### Zadanie 2

Zdefiniuj problem ABA i pokaż, w jaki sposób objawia się on w algorytmach wykorzystujących instrukcję compareAndSet()? Jak można mu zapobiegać?

Problem ABA występuje w algorytmach współbieżnych opartych na instrukcji
compareAndSet(), gdy wątek X sprawdza, że zmienna ma wartość A, w międzyczasie inny wątek(i) zmienia ją z A na B i ponownie B na A, a następnie pierwszy wątek wykonuje compareAndSet(A, C) i uznaje, że zmienna nie była modyfikowana.

Przykład: (ex2.png)

Prostym rozwiązaniem tego problemu jest dodanie timestamp-ów do referencji. W ten sposób nawet jeśli po kilku zmaianach wartość obiektu wróci do początkowej, to timestamp zapewni nam prawidłowe rozpoznanie faktu, że to nie jest ten sam obiekt, wobec czego CAS sie nie powiedzie.

### Zadanie 3

Na przykładzie SynchronousQueue wyjaśnij, czym są synchroniczne struktury danych i do czego mogą służyć? Czym jest spotkanie (ang. rendezvous)?

```java
public class SynchronousQueue<T> {
    T item = null;
    boolean enqueuing;
    Lock lock;
    Condition condition;
    ...
    public void enq(T value) {
        lock.lock();
        try {
            while (enqueuing)
                condition.await();
            enqueuing = true;
            item = value;
            condition.signalAll();
            while (item != null)
                condition.await();
            enqueuing = false;
            condition.signalAll();
        } finally {
            lock.unlock();
        }
    }
    
    public T deq() {
        lock.lock();
        try {
            while (item == null)
                condition.await();
            T t = item;
            item = null;
            condition.signalAll();
            return t;
        } finally {
            lock.unlock();
        }
    }
}
```
Synchroniczna struktura danych to taka w której operacje kończą się dopiero gdy inne się zaczną. W przypadku SynchronousQueue `enq()` nie zakończy się dopóki jakieś `enq()` nie wykona `item = null; condition.signalAll();`.
Takie struktury mogą służyć do przekazywania danych między wątkami i synchronizacji ich tempa. Np wysyłanie sygnałów tak aby ich nie zgubić.

Rendezvous to forma synchronizacji, w której wywołanie jednej operacji blokuje się, dopóki nie pojawi się oczekiwane wywołanie innej operacji. Operacja kończy się dopiero po spotkaniu.

### Zadanie 4

Jakie uzasadnienie stoi za pomysłem synchronicznych dualnych struktur danych? Omów implementację kolejki SynchronousDualQueue. 
Dla każdego wywołania metody compareAndSet() w kodzie enq() i deq() wymień wszystkie powody, dla których może ono zawieść. Dla wszystkich wywołań tej metody, których wartość zwracana nie jest sprawdzana wyjaśnij, dlaczego tak jest.

```java
private enum NodeType {ITEM, RESERVATION};
private class Node {
    volatile NodeType type;
    volatile AtomicReference<T> item;
    volatile AtomicReference<Node> next;
    Node(T myItem, NodeType myType) {
        item = new AtomicReference<T>(myItem);
        next = new AtomicReference<Node>(null);
        type = myType;
    }
}

public SynchronousDualQueue() {
    Node sentinel = new Node(null, NodeType.ITEM);
    head = new AtomicReference<Node>(sentinel);
    tail = new AtomicReference<Node>(sentinel);
    }

public void enq(T e) {
    Node offer = new Node(e, NodeType.ITEM);
    while (true) {
        Node t = tail.get(), h = head.get();
        if (h == t || t.type == NodeType.ITEM) {
            Node n = t.next.get();
            if (t == tail.get()) {
                if (n != null) {
                    tail.compareAndSet(t, n); // 1
                } else if (t.next.compareAndSet(n, offer)) { // 2
                    tail.compareAndSet(t, offer); // 3
                    while (offer.item.get() == e);
                        h = head.get();
                    if (offer == h.next.get())
                        head.compareAndSet(h, offer); // 4
                    return;
                }
            }
        } else {
            Node n = h.next.get();
            if (t != tail.get() || h != head.get() || n == null) {
                continue;
            }
            boolean success = n.item.compareAndSet(null, e); // 5
            head.compareAndSet(h, n); // 6
            if (success)
                return;
        }
    }
}

public T deq() {
    Node request = new Node(null, NodeType.RESERVATION);
    while (true) {
        Node h = head.get();
        Node t = tail.get();

        if (h == t || t.type == NodeType.RESERVATION) {
            // brak ITEM-ów — trzeba czekać
            Node n = t.next.get();
            if (t == tail.get()) {
                if (n != null) {
                    tail.compareAndSet(t, n); // 1
                } else if (t.next.compareAndSet(n, request)) { // 2
                    tail.compareAndSet(t, request); // 3
                    // czekanie na rendezvous
                    while (request.item.get() == null);
                    h = head.get();
                    if (request == h.next.get())
                        head.compareAndSet(h, request); // 4
                    return request.item.get();
                }
            }
        } else {
            // są ITEM-y — rendezvous natychmiast
            Node n = h.next.get();
            if (t != tail.get() || h != head.get() || n == null)
                continue;

            T value = n.item.get();
            boolean success = n.item.compareAndSet(value, null); // 5
            head.compareAndSet(h, n); // 6
            if (success)
                return value;
        }
    }
}
```

Synchroniczne struktury danych na przykładzie `SynchronousDualQueue` i `SynchronousQueue` są efektywniejsze bo wątki spinują na zmiennych lokalnych które są efektywnia cache-owane. Drugiim argumentem e strukturami dualnymi jest to że rezerwacje są faktycznie FIFO, bo nie muszą walczyć (losowo) o zdobycie zamka. 

Omówienei CAS-ów w `enq()`:
1. Pomoc innemu wątkowi w aktaulizacji `tail` po dodaniu nowego węzła na koniec kolejki. Może zawieść jeśli inny wątek już to zrobił. Wartość nie jest zwracana bo to jest tylko pomocnicza operacja a my już i tak będziemy próbować od nowa.
2. Próba wstawienia naszego node-a na koniec kolejki. Może zawieść jeśli ktoś inny już wstawił swojego node-a.
3. Próba zaktualizowania `tail` na świeżo dodanego przez nas node-a. Może się nie udać jeśli ktoś nam już pomógł i zrobił to za nas. Czyli nie potrzebujemy infromacji zwrotenaj bo albo nam się udało a jeśli nie, to daltego, że ktoś zrobił to co właśnie chcialisśmy zrobić.
4. Aktualizacja `head` po naszym rendezvous. Może się nie udać jeśli inny wątek już posprzątał za nas. jw.
5. Przekazanie naszej wartości czekającemu dequeuer-owi. Mogło się nie udać jeśli inny enqueuer przekazał swoją wartość przed nami.
6. Aktualizacja `head`. Pomoc innemu wątkowi lub posprzątanie po nas. Nie uda się jeśli ktoś wykonał tę samą operację przed nami dlatego nie interesuje nas czy się udało.

CAS-y w `deq()`:
1. Jak w `enq()` próba pomocy w aktualizacji `tail`. Wyjasnienie jak (1) w enq.
2. Próba wstawnienia naszego requestu na zdjęcie node-a do kolejki. Może się nie powieść jeśli ktoś na ubiegł i wstawił swojego.
3. Próba zaktualizowania `tail` na świeżo dodanego przez nas node-a. Wyjaśnienie jak (3) w enq.
4. Aktualizacja `head` po naszym rendezvous. Może się nie udać jeśli inny wątek już posprzątał za nas. Nie udało się jeśli inny wątek wykonał tę samą operację.
5. Próba 'wyciągnięcia` elementu z kolejki. Nie uda się jeśli inny dequeuer był szybszy.
6. Aktualizacja `head`. Pomoc innemu wątkowi lub posprzątanie po nas. Wyjasnienie jak (6) w enq.

### Zadanie 5

Głównym problemem stosu Boba jest to, że nie działa jak stos.
Wątki chcące zrobić `pop()` spinują się na określonych przez początkową wartość `top` i nie sprawdzają który node był dodany najpóźniej.
Przykładowo. 
A.pop() -> spinuje na i==0
B.push() -> wkłada na i==0
C.push() -> wkłada na i==1
A zwraca wartość z stack[0], mimo że byłą wcześniej niż ta na 1.

Drugim problemem jest to, że `top` może mieć wartości większe niż `capacity` i mniejsze niż `0` i nie reprezentuje faktycznego rozmiaru stosu.

Nie potrafię tego przepisać przez dodanie jakichś flag lub dodatkowych sprawdzeń (np aktualizowanie pozycji spinowania w `pop()` wcale nie pomaga przed tym, ze sciągniemy odpowiedni element) aby dobrze działało. 