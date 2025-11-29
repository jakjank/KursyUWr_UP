### Zadanie 1
Zał. że istnieje taka implementacja.
Puśćmy protokuł aż dojdziemy do krytycznego stanu *S*.
Załóżmy, że jeśli ze stanu *S* ruszy się A to wyniki to będzie 1 i (BSO C możemy nazwać B i odwrotnie) 0 po ruchu B.

Jakie metody mogły zawołać A i B?
1. czytanie rejestrów.
    To już przerabialiśmy. Ten sam stan a inne wyniki. Sprzeczność
2. A pisze do XA, B pisze do XB
    W pierwszym scenariuszu A pisze do XA (przehodzimy do stanu 1-walentnego) B pisze do XB. W drugim B najpierw pisze do XB a potem A do XA (stan 0-walentny). wiec sprzeczność bo skończyliśmy w takim samym stanie a ma być jednocześni 0 i 1 walentny.
3. A pisze do XA, B robi CAS na RAB lub RBC
    jak wyżej. wykounją swoje metody w odwrotnych kolejnościach. kończą w takim samym stanie który jednocześnie ma być 1 i 0 walentny.
4. A robi CAS na XAC, B cokolwiek
    W pierwszym scenariuszu A wykonuje CAS na XAC i potem B runs solo i konczymy z wynikiem 1. W drugim B runs solo i kończymy z wynikiem 0. Ale skoro zawartość XAC nie ma wpływu na B to sprzeczność.
5. A robi CAS na XAB, B CAS XAB
    W pierwszym scenariuszu A CAS na XAB potem C runs solo i wynik mamy 1. W drugim B CAS XAB, C runs solo i wynik 0. Ale zawartość XAB nie ma wpływu na stan jaki widzi C więc sprzeczność.
6. A CAS XAB, B CAS XAC
    A i B wykonują w odwrotnej kolejności te metody i kończymy w tym samym stanie z róznymi walencjami.
7. A CAS XAB, B psize do XB
    jak w 6.

str. 115

### zad 2

Da się. konstrukcja:

```java
class CASConsensus extends ConsensusProtocol {
    private final int FIRST = -1;
    Object[] DX = new Object[3]; //RMW shared registers

    public Object decide(Object value) {
        int i = ThreadID.get();
        int v = double_CAS(DX[i], DX[(i+1)%3], FIRST, value);

        if(value == v)
            return value;
        else
            return v;
    }
}
```

Jako że `double_CAS()` jest atomowy to dokladnie jeden wątek będzie w stanie zapisac swoje oba rejestry, bo kazdy wątek z każdym mają wspólne. Wszystkie wykonywane operacje są wait-free więc `decide()` też.

### zad 3

```java
class CASConsensus extends ConsensusProtocol {
    private final int FIRST = -1;
    private AtomicInteger r = new AtomicInteger(FIRST);

    public Object decide(Object value) {
        propose(value);
        int i = ThreadID.get();
        if (r.CAS(FIRST, value))
            return proposed[i];
        else
            return proposed[r.get()];
    }
}
```

### zad 4

Uzyjemy komorek z CAS do nabywania własnosci nad własciwymi komorkami tablicy 

```java
class write23
{
    Object[] V = Object[3];
    RMW[] x = new RMW[3]; // zainicjalizowane z ⊥

    void write(Object v1, Object v2)
    {
        i = ThreadID.get(); // 0  or 1
        if(x[i].CAS(⊥, i)){
            V[i] = v1;
        }
        if(x[i+1].CAS(⊥, i)){
            V[i+1] = v2;
        }
    }
}
```

Każdy wątek najpierw zgłasza wolę zapisania swojej komórki, wykonując CAS z wartości ⊥ (puste) na swoją etykietę (np. A lub B).

Jeśli CAS:
* powiedzie się → ten wątek jest „właścicielem” komórki
* nie powiedzie się → ktoś inny już wygrał i nie należy zapisywac

Następnie każdy wątek zapisuje do właściwych T[i] swoją wartość, ale tylko wtedy, gdy jest właścicielem.


Każdy wątek wykonuje stałą liczbę operacji:
2× CAS
2× write
Każda operacja CAS zwraca natychmiast (sukces/porażka).
Żadnego czekania na inne wątki → wait-free.


Właściciel komórki jako jedyny zapisuje jej wartość
