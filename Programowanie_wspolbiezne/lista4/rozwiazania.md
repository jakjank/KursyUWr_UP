### Zadanie 2

1) ex2.1.png

2) ex2.2.png

3) Wywołanie p.deq -> q nie ma oczekiwanego efektu (nie da sie tak rozłożyć punktów linearyzacji).

4) p.deq zwraca y, a enq(x) wydarzyło się pierwsze

### ZAdanie 3
Ułożyć historię H. Przekształcić do G. 

#### 1
**H:**
B r.wite(1)
B r:void
A r.read()
A r:1
C r.wite(2)
C r:void
B r.read()
B r:2
H|r jest zgodne ze specyfikacja komórki pamięci

#### 2
**H:**
B r.write(1)
C r.write(2)
C r:void
B r:void
A r.read()
A r:1
B r.read()
B r:1
H|r jest zgodne ze specyfikacja komórki pamięci

#### 3
**H:**
A p.enq(x)
A p:void // nie możę być inaczej
B p.enq(y)
B p:void // tez nie moze byc inaczej
A p.deq()
A p:y // NIEZGODNE ZE SPECYFIKACJA FIFO !

#### 4
**H:**
A p.enq(x)
A p.void
B q.enq(y)
B q:void
A q.enq(x)
A q.void
B p.enq(y)
B p:void
A p.deq()
A p:y // NIEZGODNE ZE SPECYFIKACJA FIFO !
...

**H|p:**
A p.enq(x)
A p.void
B p.enq(y)
B p:void
A p.deq()
A p:y 

### Zadanie 4

```java
Filter implements Lock {
    int[] level;
    int[] victim;

    public Filter(int n) {
        level = new int[n];
        victim = new int[n]; // use 1..n-1
        for (int i = 0; i < n; i++) {
            level[i] = 0;
        }
    }

    public void lock() {
        int me = ThreadID.get(); // returns 0..n-1
        for (int i = 1; i < n; i++) { // attempt to enter level i
            level[me] = i;
            victim[i] = me;
            // spin while conflicts exist
            while (( ∃ k != me) (level[k] >= i && victim[i] == me)) {};
        }
    }

    public void unlock() {
        int me = ThreadID.get();
        level[me] = 0;
    }
}
```

**fakt**
Na kazdym poziomie i jest max n-i watków (tzn. n-i wątków ma level[self] == i)

Zał. że na poziomie $i-1$ jest maksymalnie $n-i+1$ wątków. Pokażemy, że maksymalnie i wątków "przejdze wyżej". 
Niech A to ostatni wątek który wszedł na ten poziom (ostatni nadpisał victim[i]). Wtedy dla każdego B:
$write_B(victim = B)$ -> $write_A(victim = A)$
Z kodu widzimy, że B ustawił swój poziom przed nadpisaniem victim. Zatem A po nadpisaniu victim będzie już widział poziom B. W takim razie A nie może ukończyć while-a dopóki inne wątki nie wyjdą z CS (A zostanie na poziomie $i-1$). Czyli na poziome i jest maksymalnie n-i wątków. Na mocy ind. matem. teza.

**wzajemne wykluczenie**
Z naszego **faktu** skoro na poziomie 1 znajduje się jednocześnie maks. n - (n-1)
wątków to do CS wejdzie tylko 1 wątek.

### Zadanie 5
**niezagłodzenie**
Załóżmy, że każdy wątek który jest na poziomie i+1 lub wyżej w końcu wejdzie do CS.
dla poziomou `n` oczywiste (zad. 4).
Załóżmy, że A utknął na poziomie `i`. W końcu nie ma wąteków na poziomach > i.
Skoro A jest na poziomie i to nie wchodzą tam nowe wątki (widzą że level[A] jest większy od ich) zatem `victim[i]` przestaje się zmieniać. Jeśli `victim[i] = A` to wszystkie pozostałe wątki przechodzą wyżej i z zał. dochodzą do CS. Wtedy A przechodzi wyżej bo nie ma k : level[k] >= level[A]. Jeśli `victim[i] != A` to A po prostu przechodzi wyżej i z zał. przechodzi do CS.

**niezakleszczenie**
Niezagłodzenie jest silniejsze od niezakleszczenia więc Filter ma własność niezakleszczenia

### Zadanie 6

**Przypomnienie**
r-Bounded Waiting - mamy wątek A. Nie ma gwarancji, że A przejdzie na poziom +1 po tym jak co najwyżej r innych wątków przejdzie na +1.

W filtrze nie da sie określić takiej stałej bo na poziomie i moze być dowolnie wiele wątków (duże n).

Niezagłodzenie mówi o tym, że wątek zostanie **kiedyś** przepuszczony a r-ograniczone czekanie próbuje podać górną granicę tego oczekiwanie (niezależną od n).