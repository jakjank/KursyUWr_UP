### Zadanie 1

Diagramy na FIFO i komoórkach pamięci.

### Zadanie 2

Sequential Consistency nie ma własności kompozycji.

**przypomninenie**
Własność kompozycji - poprawność X nazywamy kompozycyjną, jeśli z tego, że każdy obiekt spełnia X wynika, że cały system spełnia X.

(ex2.png)

Widzimy, że p i q osobno są SC. Ale jeśli połączymy ścieżki wykonania operacji na obiektach z kolejnością operacji w wątkacch to dostaniemy cykl (bardzo źle).

### Zadanie 3

```java
public class WaitFreeQueue {
    int head = 0, tail = 0;
    items = (T[]) new Object[capacity];

    public void enq(Item x) {
        if (tail-head == capacity) throw
            new FullException();
        items[tail % capacity] = x; tail++;
    }

    public Item deq() {
        if (tail == head) throw
            new EmptyException();
        Item item = items[head % capacity]; head++;
        return item;
    }
}
```
a)
Specyfikcaja:

metoda | stan przed | zwracana wartość | stan po
-------|------------|------------------|------------
deq    |  pusta     | empty exc.       | bz.
 <br/> |  pełna     | pierwszy el.     | zwiekszony head
 <br/> |  niepusta  | pierwszy el.     | zwiekszony head
enq    |  pusta     | void             | dodany el, zwiekszony tail 
 <br/> |  pełna     | full exc.        | bz.
 <br/> |  niepusta  | void             | dodany el, zwiekszony tail

Obiekt jest poprawny, jeśli działanie metod jest zgodne ze specyfikacją, gdy są one uporządkowane sekwencyjnie wg. pewnych punktów linearyzacji.  

Musimy ustalić punkty linearyzowania:
dla `enq` niech to będzie `tail++;`
dla `deq` to będzie `head++;`.

Rozwazamy wykonania enq i deq (a co z pojedynczymi enq i deq?):

1. enq pierwsze
1.1 kolejka pusta
enq -> wstawia el, tail++ (OK)
deq -> ściąga ten el, head++ (OK)
1.2 kolejka pełna
enq -> próbuje wstawić el, -> full exception (OK)
deq -> ściąga pierwszy el, head++ (OK)
1.3 kolejka nie z 1.1 i 1.2
enq -> wstawia (OK)
deq -> sciaga (OK)
2. deq pierwsze
2.1 kolejka pusta
deq -> próbuje ściągnąć el -> empty exception (OK)
enq -> wstawia el, tail++ (OK)
2.2 kolejka pełna
deq -> ściąga pierwszy el, head++ (OK)
enq -> tail-head != capacity, wstawia el tail++ (OK)
2.3 kolejka nie z 2.1 i 2.2
deq -> sciaga (OK)
enq -> wstawia (OK)

b)
Skoro obiekt jest linearyzwoalny to jest też sekwancyjnie spójny (?)

### Zadanie 4

```java
public void lock() {
    flag[i] = true;
    victim = i;
    while (flag[j] && victim == i) {};
}

public void unlock() {
    flag[i] = false;
}
```

Dowód wzajemngo wykluczenia w alg. Petersona.

Zał. że A i B weszły do CS. Niech A ostatni zapisał pole vicitm.
$write_B(victim = B)$ -> $write_A(victim = A)$
Skora A wszedł do CS to musiał widzieć, że `flag[B] == false`
$write_A(victim = A)$ -> $read_A(flag[B] = false)$
Czyli mamy ciąg zdarzeń:
$write_B(flag[B] = true)$ -> $write_B(victim = B)$ -> $write_A(victim = A)$ -> $read_A(flag[B] = false)$ 
Ale nikt nie pisał po pierwszej operacji do `flag[B]` więc sprzeczność.

Teraz jeśli dopuszczamy słabszy model pamięci (np. inny wątek nie musi od razu widzieć efektu `store`), to dowód się załamuje.

Przykład:
1. A wykonuje flag[A] = true — zapis nie jest jeszcze widoczny globalnie.
2. B wykonuje flag[B] = true — zapis nie jest jeszcze widoczny globalnie.
3. A wykonuje victim = A — ten zapis jest widoczny globalnie.
4. B wykonuje victim = B — ten zapis jest widoczny globalnie. 
(victim == B)
5. A wykonuje read flag[B] — ponieważ zapis jest opóźniony, A widzi flag[B] == false.
6. B wykonuje read flag[A] — analogicznie widzi flag[A] == false.

Oba wątki widzą, że warunek flag[j] && victim==i jest fałszywy (pierwszemu czynnikowi = flag[j] = false), więc oba wychodzą z pętli i wchodzą do CS.

### Zadanie 5

```java
class BakeryOpt implements Lock {
    boolean flag[];
    int label[];
    int counter;

    public Bakery(int n) {
        flag = new boolean[n];
        label = new Label[n];
        counter = 0;
        for (int i = 0; i < n; i++) {
            flag[i] = false;
            label[i] = 0;
    }

    public void lock () {
        flag[i] = true; // i – numer bieżącego wątku
        label[i] = max(label[i], counter++) //zamiast counter++;
        // load tmp1 counter
        // load tmp2 label[i]
        // addi tmp1 1
        // store counter tmp1
        // ...
        while (∃k flag[k] && (label[i], i) > (label[k], k)) {};
    }

    public void unlock () {
        flag[i] = false;
        }
    }
}
```

Rozwazmy przypadek (pierwotnie wszystko zainicjalizowane na 0):
1. A read(counter = 0)
2. B read(counter = 0)
3. A store(counter = 1)
(A kończy CS)
4. C read(counter = 1)
5. C store(counter = 2)
(C widzi ze B ma podniesiona flage i mniejszy label)
6. D read(counter = 2)
7. D store(counter = 3)
(D widzi ze B i C maja podniesione flagi i mniejsze label)
8. B store(counter = 1) !
(B konczy CS)
(C konczy CS)
(D wchodzi do CS)
9. E read(counter = 1)
9. E store(counter = 2)
E widzi flage D = true i label[D] = 2 (< 1)
więc E wchodzi do CS

**wzajemne wykluczenie**
powyższy przykłąd pokazuje że nie ma tej włąsności (jak max(label, counter) mialo pomoc?)

**dead-lock**
zawsze ktos ma najmniejszy (label, i) więc zawsze ktos wejdze

**starvation-free**
jeśli mamy skończoną ilość wątków to tak. (jesi watek A mialby czekać z dużym label a kilka wątków by robiło powyzszy przykład, to i tak w koncu dojdą do label[A]) (tutaj max pomógł w porównaniu do zad5 listy 3)

### Zadanie 8

**niezależność** - od innych wątków i systemu.
**nieblokowanie** - opóźnienie tu nie wpływa na proges tam.

**wait-freeness** - metoda jest nieczekająca, jeśli gwarantuje że wykona się w skończonej liczbie kroków. Nazywa się tę własność nieblokującą, bo opóźnienie jednego wątku niekonecznie blokuje progres innych wątków. Jest to niezależne od tego w jaki sposób będą działać inne wątki.

**lock-freeness** - gwarantuje, że zawsze jakaś metoda wykona się w skończoną ilość kroków (postęp systemu/pojedynczy wątek może głodować). Jest to niezależne i nieblokujące bo postęp **systemu** nie zależy od tego, czy jakiś wątek został wstrzymany.

**niezakleszczenie** - blokujące, bo jeśli nastąpi opóźnienie wątku który już przygotował się do wejści (podniósł flage itp.) to inny wątek jest opóźniany. Zależne od zachowania innych wątków.

**niezagłodzenie** - zależne od systemu (jeśli scheduler nie przełączy wątku to własność się nie spełni). Może wymagać aby inne wątki ustąpiły więc jest blokujące.

**weird** jest nieczekająca bo gwarantuje wykonanie w skończonej liczbie kroków. nie jest nieczekająca z limitem kroków, bo nie ma górnej granicy na ilość kroków jaką ta funkcja może wykonać.