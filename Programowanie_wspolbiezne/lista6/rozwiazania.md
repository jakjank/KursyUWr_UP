### Zadanie 1

**bezpieczny** - spodziewane działanie jeśli read i write nie nachodzą na siebie. Jakas wartość (możliwa) wpp.

**regularny** - Jest tylko jeden wątek piszący(?). read zwraca ostania zapisaną wartość jeśli nie koliduje z write-em, wpp. zwraca starą lub nową.

**atomowy** - linearyzowalny do sekwencyjnie bezpiecznego.

Rejestry **MRMW** są bezpieczne regularne i atomowe.
sumylowany rejestr 64 bitowy składa się z 32'b A i B

#### Czy symukowane rejestry sa bezpieczne
Tak. Jeśli read i write nie nachodzą na siebie to wszytko ok. Wpp reader może odczytać wartość A która akurat jest zapisywana i starą wartość B ale to jest "dozwolona" wartość.

#### Czy symulowane rejsetry są regularne.
Nie. Załóżmy że w {A,B} jest stara wartość. Zaczyna się read i write. write zapisuje A. read czyta A i B. Odczytana wartość nie jest (z reguły) ani starą ani nową.

#### Czy symuloane rejestry są atomowe

Nie. Możliwa jest historia która nie jest linearyzowalna do sekwenyjnie bezpiecznej:
(ex1.png)

### Zadanie 2

```java
public void lock() {
    flag[i] = true;
    victim = i;
    while (flag[j] && victim == i) {};
}
```

Co jeśli zastąpimy `flag` rejestrami regularnymi.

**wzajemne wykluczenie**
Wątek B wchodzący jako drugi musiałby w jakis sposób zobaczyć flag[A] = false.
Jeśli `flag` są regularne to B czyta flag[A] = false tylko jeśli w while-u trwa jeszcze write_A(flag[A] = true). Skoro tak, to A ustawi victim na A i nie wejdzie do CS.

**niezagłodzenie**
regularność `flag` nic nie zmienia.

### Zadanie 3

Chcemy dostać M-wartościowy SRSW, taki aby reader mógł odczytać dobrą wartość jeśli reader akurat pisze (raz). Kodowanie one-hot tutaj nie przejdzie bo nie możemy mieć O(M) bitów.

Musimy kodować w takim razie `value` w zapisie binarnym.

Ale skoro pojedynczy writer ma nie psuć `value` to możemy mieć dwie tablice bitów i jeden bit pokazujący readerowi/writerwi którą czytać/zapisywać.

```java
class 1RegMWSR 
{
    boolean sel = 0;
    boolean data[2][k]; 

    void write(int v) {
        int other = 1 - sel.read();
        for (int i = 0; i < k; i++) 
            data[other][i].write( (v >> i) & 1 );
        sel.write(other);
    }

    int read() {
        int s = sel.read();
        int v = 0;
        for (int b = 0; b < k; b++)
            v = v | (data[s][b].read() << b);
        return v % M;
    }
}
```

**Przypadki**
1) read nie jest współbiżny z żadnym writem - reader odczyta aktywną kopię (ostatnia zapisana wartość)
2) read współn. z dokładnie 1 writem
   a) jeśli write jest w trakcie zapisywania to read odczta starą wartość wg `sel`
   b) jeśli write już odwrócił `swl` to read zwróci nową wartość
3) read współb. z wieloma write-ami - wszystko może się zdażyć :)

### Zadanie 4

**regularny** - Jest tylko jeden wątek piszący(?). read zwraca ostania zapisaną wartość jeśli nie koliduje z write-em, wpp. zwraca starą lub nową.

**=>**
Zał. że rejestr jest regularny. Pokażemy, że *własności* zachodą.
1) Gdyby istniało takie $R^i$, $R^i$ -> $W^i$, to przeczyłoby to temu, że rejestr jest **dobry** (wartość rejestru nie bierze się z powietrza)
2) Gdyby istniały i,j takie, że $W^i$ -> $W^j$ -> $R^i$, to przeczyłoby to definicji **regularności** (odczyt musi zwrócić ostatnią zapisaną wartośc)

**<=**
Zał. że rejestr ma *własności*. Pokażemy, że jest regularny.
Weźmy dowolny odczyt $R$. Niech $W^i$ to ostani zapis przed $R$. Z faktu, że rejestr jest *dobry* musi istnieć $W^x$ takie że zapisuje wartość zwróconą przez $R$.
1. Gdyby $R$ -> $W^x$ to przeczyłoby to *własności* 2.
2. Gdyby $W^x$ -> $W^i$ to przeczyłoby to *własności* 1.

Zatem x = i, czyli R zwraca ostatnią zapisaną wartość, wieć rejestr jest regularny.

### Zadanie 5 TODO

**atomowy** - linearyzowalny do sekwencyjnie bezpiecznego.

Rejestr *atomowy* różni się od *regularnego* tym, że jeśli $R^a$ -> $R^b$ i $R^a$ $R^b$ i $W$ na siebie nachodzą. To w *regularnym* $R^a$ i $R^b$ były od siebie niezależne a  w *atomowym* $R^b$ zależy od $R^a$.

**=>**
Zał. że rejestr jest atomowy. Pokażemy, że *własności* zachodą.
1) Gdyby istniało takie $R^i$, $R^i$ -> $W^i$, to przeczyłoby to temu, że rejestr jest **dobry** (wartość rejestru nie bierze się z powietrza)
2) Gdyby istniały i,j takie, że $W^i$ -> $W^j$ -> $R^i$, to przeczyłoby to definicji **regularności** i tym samym **atomowości** (odczyt musi zwrócić ostatnią zapisaną wartośc)
3) Gdyby istniały takie i,j że $R^i$ -> $R^j$ i i > j

**<=**
Zał. że rejestr ma *własności*. Pokażemy, że jest regularny.
Weźmy dowolny odczyt $R$. Niech $W^i$ to ostani zapis przed $R$. Z faktu, że rejestr jest *dobry* musi istnieć $W^x$ takie że zapisuje wartość zwróconą przez $R$.
1. Gdyby $R$ -> $W^x$ to przeczyłoby to *własności* 2.
2. Gdyby $W^x$ -> $W^i$ to przeczyłoby to *własności* 1.

Zatem x = i, czyli R zwraca ostatnią zapisaną wartość, wieć rejestr jest regularny.

### Zadanie 6

regularny M-wartościowy rejestr MRSW używający regularnych rejestrów Boolowskich MRSW:
```java
public class RegMRSWRegister implements Register<Byte> {
    private static int RANGE = Byte.MAX_VALUE - Byte.MIN_VALUE + 1;
    boolean[] r_bit = new boolean[RANGE]; // regular boolean MRSW

    public RegMRSWRegister(int capacity) {
        for (int i = 1; i < r_bit.length; i++)
            r_bit[i] = false;
        r_bit[0] = true;
    }

    public void write(Byte x) {
        r_bit[x] = true;
        for (int i = x - 1; i >= 0; i--)
            r_bit[i] = false;
    }

    public Byte read() {
        for (int i = 0; i < RANGE; i++)
            if (r_bit[i]) {
                return i;
        }
        return -1; // impossible
    }
}
```

1. `read` nie zwraca wartości "z przyszłości".
    bo rejestry są ustawane pierwotnie na `false` i każdy `write(x)` ustawia bity "mniejsze" od *x* na `false`.
2. `read` nie zwraca wartości zapisanych sprzed ostatnim nienachodzącym `write-em`
    bo `read` zwraca pierwszy bit ustaawiony na `true`, więc mamy dwie opcje:
    A) stary bit jest "większy" niż nowy. Wtedy write do niego nie dotrze, bo pierwszy jaki odczyta to ten nowy.
    B) stary bit "jest: młodszy niż nowy. Wtedy skoro `write` zapisujący nowy bit nie nachodzi się z `read-em` to znaczy, że już poustawiał niższe bity (w tym ten stary) na `false`, więc `read` nie może go zwrócić.

Na mocy *zadania 4* powyższa konstrukcja jest poprawna.


### Zadanie 7

```java
public class AtomicMRSWRegister<T> implements Register<T> {
    ThreadLocal<Long> lastStamp;
    private StampedValue<T>[][] a_table; // each entry is SRSW atomic

    public AtomicMRSWRegister(T init, int readers) {
        lastStamp = new ThreadLocal<Long>() {
            protected Long initialValue() { return 0; };
        };
        a_table = (StampedValue<T>[][]) new StampedValue[readers][readers];
        StampedValue<T> value = new StampedValue<T>(init);
        for (int i = 0; i < readers; i++) {
            for (int j = 0; j < readers; j++) {
                a_table[i][j] = value;
            }
        }
    }

    public T read() {
        int me = ThreadID.get();
        StampedValue<T> value = a_table[me][me];
        
        for (int i = 0; i < a_table.length; i++) {
            value = StampedValue.max(value, a_table[i][me]);
        }

        for (int i = 0; i < a_table.length; i++) {
            a_table[me][i] = value;
        }

        return value;
    }

    public void write(T v) {
        long stamp = lastStamp.get() + 1;
        lastStamp.set(stamp);
        StampedValue<T> value = new StampedValue<T>(stamp, v);
        for (int i = 0; i < a_table.length; i++) {
            a_table[i][i] = value;
        }
    }
}
```

1. Żaden `read` nie zwraca wartości "z przyszłości"
2. `write` zawsze zwiększa timestamp, zatem timestamp w każdej kolumnie i wierszu w `a_table` też się zwiększa. Jeśli **A** zapisze *v* z timestampem *t*, to każdy **późniejszy** (nienachodzący) `read` przeczyta wartość z timestampem >= t. Zatem `read` nie zwraca **starych** (zapisanych przez `write` taki że między nim a `read-em` był jeszcze jeden nienachodzący `write`) wartości.
3. Jeśli `A read()` ->  `B read()`, to wtedy A zapisuje wartość z timestampem *t* w kolumnie B, zatem B wybiera wartość z timestampem >= *t*. Czyli wcześniejszy `read` nie zwróci wartości późniejszej niż ta zwracana przez późniejszego `read-a`.

Na mocy *zadania 6* to jest poprawna konstrukcja atomowego MRSW.