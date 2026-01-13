### Zadanie 1

samo CAS nie wystarcza bo nie pozwala odroznic logicznie usunietych wezlow od aktywnych:

(ex1.png)

Jak pomaga *marked*
*marked* w węźle rozróżnia logiczne i fizyczne jego usuniecie. Dzieki *marked* inne watki widza ze element juz nie jest w zbiorze nawet jesli fizycznie jest na liscie, co sprawia ze nie dochodzi do sytacji odzywania usunietych węzłach lub udanego CAS-a na wezlektóry nie powinien byc juz uzywany.

Dzieki `AtomicMarkableReference<T>` mozemy atomowo sprawdzic i zmienic `next` i `marked`.
To daje nam, że mamy informacje czy `pred.next` nadal wskazuje na `curr` i czy `curr` nie ma `marked` = True. 

### Zadanie 4

Uzasadnij, że metody add() i remove() klasy LockFreeList są niewstrzymywane (ang. lock-free), a metoda contains() jest nieczekająca (ang. wait-free).

Powtórzenie:
* lock-free - gwarantuje, że zawsze jakaś metoda wykona się w skończoną ilość kroków (postęp systemu/pojedynczy wątek może głodować). Jest to niezależne i nieblokujące bo postęp systemu nie zależy od tego, czy jakiś wątek został wstrzymany.
* wait-free - metoda jest nieczekająca, jeśli gwarantuje że wykona się w skończonej liczbie kroków. Nazywa się tę własność nieblokującą, bo opóźnienie jednego wątku niekoniecznie blokuje progres innych wątków. Jest to niezależne od tego w jaki sposób będą działać inne wątki.

```java
class Window {
    public Node pred, curr;
    Window(Node myPred, Node myCurr) {
        pred = myPred; curr = myCurr;
    }
}

public Window find(Node head, int key) {
    Node pred = null, curr = null, succ = null;
    boolean[] marked = {false};
    boolean snip;
    retry: while (true) {
        pred = head;
        curr = pred.next.getReference();
        while (true) {
            succ = curr.next.get(marked);
            while (marked[0]) {
                snip = pred.next.compareAndSet(curr, succ, false, false);
                if (!snip) continue retry;
                    curr = succ;
                    succ = curr.next.get(marked);
            }
            if (curr.key >= key)
                return new Window(pred, curr);
            pred = curr;
            curr = succ;
        }
    }
}

public boolean add(T item) {
    int key = item.hashCode();
    while (true) { //(*)
        Window window = find(head, key);
        Node pred = window.pred, curr = window.curr;
        if (curr.key == key) {
            return false;
        } else {
            Node node = new Node(item);
            node.next = new AtomicMarkableReference(curr, false);
            if (pred.next.compareAndSet(curr, node, false, false)) {
                return true;
            }
        }
    }
}
```

W metodzie `add()` synchronizacja odbywa się wyłącznie przez operacje atomowe compareAndSet (CAS) (brak lock-ów więc nie dojdzie do deadlocka). Pętla `(*)` może się powtarzać tylko wtedy, gdy inny wątek zmodyfikował listę szybciej (CAS się nie powiódł), czyli ktoś inny właśnie zrobił postęp.

Finalnie niemożliwe jest aby wszystkie wątki kręciły się w pętli bez postępu (czyli że wszystkim nie powodzą się CAS-y), bo każda porażka CAS implikuje sukces CAS w innym wątku, więc `add()` jest lock-free.

```java

public boolean remove(T item) {
    int key = item.hashCode();
    boolean snip;
    while (true) { //(**)
        Window window = find(head, key);
        Node pred = window.pred, curr = window.curr;
        if (curr.key != key) {
            return false;
        } else {
            Node succ = curr.next.getReference();
            snip = curr.next.attemptMark(succ, true);
            if (!snip)
                continue;
            pred.next.compareAndSet(curr, succ, false, false);
            return true;
        }
    }
}
```

Metoda `remove()` tak jak `add()` używa wyłącznie operacji atomowych. Pętla `(**)` powtarzać się będzie tylko w przypadku niepowodzenia oznaczenia `curr` na logicznie usunięte z listy. Stanie się tak tylko w przypadku gdy inny wątek zmodyfikował listę szybciej (oznaczył już `curr` jako usunięty lub zmienił `next`).

Metoda remove() jest lock-free, ponieważ każda porażka attemptMark oznacza postęp innego wątku.

```java
public boolean contains(T item) {
    boolean[] marked = false{};
    int key = item.hashCode();
    Node curr = head;
    while (curr.key < key) {
        curr = curr.next;
        Node succ = curr.next.get(marked);
    }
    return (curr.key == key && !marked[0])
}
```

Metoda `contains()` jest wait-free, ponieważ pętla nie zawiera żadnych retry, nie ma CAS, compareAndSet ani attemptMark czyli nic nie może zmusić wątku do powtarzania tego samego kroku. `curr` natomiast zawsze przesuwa się do przodu.

### Zadanie 5

Uzasadnij, że metody add(), remove() oraz contains() klasy LazyList są linearyzowalne. Czy dla każdej z tych metod jesteś w stanie wskazać konkretny punkt linearyzacji w jej kodzie?

```java
private boolean validate(Node pred, Node curr) {
    return !pred.marked && !curr.marked && pred.next == curr;
}

public boolean add(T item) {
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
                    if (curr.key == key) {
                        return false; // punkt linearyzacji
                    } else {
                        Node node = new Node(item);
                        node.next = curr;
                        pred.next = node; // punkt linearyzacji
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
                    if (curr.key != key) { // punkt linearyzacji
                        return false;
                    } else {
                        curr.marked = true; // punkt linearyzacji
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

public boolean contains(T item) {
    int key = item.hashCode();
    Node curr = head;
    while (curr.key < key)
        curr = curr.next;
        return curr.key == key && !curr.marked;
}
```

Punkt linearyzacji `add()`:
Jeśli fail to nic się w liście nie zmienia więc ok.
Jeśli success to w tym momencie nowy węzeł staje się osiągalny z `head` i wszystkie kolejne operacje widzą dodany element.

Punkt linearyzacji `remove()`:
Jeśli fail po validate to metoda nic się w liście nie zmienia więc ok.
Jeśli success to w momencie ustawienia `marked = true` węzeł staje się logicznie usunięty wszystkie kolejne operacje to będą widziały.


Punkt linearyzacji `contains()` jest bardziej skomplikowany:
Jeśli success to linearyzujemy w momencie znalezienia niezonaczonego węzła i pasującym kluczu.
(ex5.png)
Nieudane wywołanie `contains()` linearyzujemy we wcześniejszym z momentów:
* moment gdy znaleziono usunięty pasujący węzeł lub węzeł z kluczem większym niż szukany
* moment zaraz przed dodaniem do listy nowego pasującego węzła
Momenty te nie są możliwe do zaznaczenia w kodzie ale uzasadniają je scenariusze na obrazku.

### Zadanie 6

```
Strona 179
"A condition is associated with a lock, and is created by calling that lock’s newCondition() method.
If the thread holding that lock calls the associated condition’s await() method,
it releases that lock and suspends itself, giving another thread the opportunity to acquire the lock.
When the calling thread awakens, it reacquires the lock, perhaps competing with other threads."
```

Przypomnij, jak działa współbieżna kolejka ograniczonego rozmiaru BoundedQueue. W szczególności, w jaki sposób działają i jak są wykorzystywane zmienne warunkowe notEmptyCondition i notFullCondition. Czy istnieje taka sekwencja wykonań metod enq() i deq(), że zmienna size staje się ujemna?

```java
public class BoundedQueue<T> {
    ReentrantLock enqLock, deqLock;
    Condition notEmptyCondition, notFullCondition;
    AtomicInteger size;
    Node head, tail;
    int capacity;
    
    public BoundedQueue(int _capacity) {
        capacity = _capacity;
        head = new Node(null);
        tail = head;
        size = new AtomicInteger(0);
        enqLock = new ReentrantLock();
        notFullCondition = enqLock.newCondition();
        deqLock = new ReentrantLock();
        notEmptyCondition = deqLock.newCondition();
    }

    public void enq(T x) {
        boolean mustWakeDequeuers = false;
        enqLock.lock();
        try {
            while (size.get() == capacity) // (*)
                notFullCondition.await();
            Node e = new Node(x);
            tail.next = tail = e;
            if (size.getAndIncrement() == 0)
                mustWakeDequeuers = true;
        } finally {
            enqLock.unlock();
        }
        if (mustWakeDequeuers) {
            deqLock.lock();
            try {
                notEmptyCondition.signalAll();
            } finally {
                deqLock.unlock();
            }
        }
    }

    public T deq() {
        T result;
        boolean mustWakeEnqueuers = true;
        deqLock.lock();
        try {
            while (size.get() == 0)
                notEmptyCondition.await();
            result = head.next.value;
            head = head.next;
            if (size.getAndDecrement() == capacity) {
                mustWakeEnqueuers = true;
            }
        } finally {
            deqLock.unlock();
        }
        if (mustWakeEnqueuers) {
            enqLock.lock();
            try {
                notFullCondition.signalAll();
            } finally {
                enqLock.unlock();
            }
        }
        return result;
    }
}
```
Skoro kolejka ma ograniczoną ilość miejsc to musimy pamiętać ilość wolnych miejsc. Za ten aspekt odpowiada atomowe pole `size` powiększane przez enqueuer–ów i zmniejszane przez dequeuer-ów.

`enqLock` jest powiązany z warunkiem `notFullCondition`, który informuje oczekująych enqueuer-ów o tym, że kolejka już nie jest pełna.
Analogicznie `deqLock` jest powiązany z `notEmptyCondition` informującym dequeuer-ów o tym, że jest co wyciągać z kolejki.

Użycie `notFullCondition`:
Po zdobyciu `enqLock` w `enq()` wątek sprawdza, czy kolejka ma jeszcze wolne miejsca. Jesli nie, to czeka aż któys z dequeuer-ów zasygnalizuje gotowość `notFullCondition` (bo skoro było `deq()`, to jest szansa, że są już wolne miejsca, ale ważne jest ponowne sprawdzenie `size.get() == capacity` (*)).

Użycie `notEmptyCondition`:
Symetrycznie do powyższej sytuacji. Jeśli kolejka była pusta to dequeuer czeka aż jakiś enqueuer zasygnalizuje, że coś włożył do kolejki. 

Czy `size` moze stać się ujemne?
Jedynym miejscem, w którym size może zostać zmniejszone, jest `deq()`, i to dopiero po przejściu warunku:

```java
while (size.get() == 0)
    notEmptyCondition.await();
```

Zatem `getAndDecrement()` nigdy nie jest wykonane, gdy size == 0