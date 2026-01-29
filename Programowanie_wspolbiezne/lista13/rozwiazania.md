### Zadanie 1

Wyjaśnij, jak działa metoda exchange() z klasy LockFreeExchanger.  Dla każdego wywołania metody compareAndSet() wymień wszystkie powody, dla których może ono zawieść i wyjaśnij, jakie akcje podejmuje exchange() w takim przypadku. Dlaczego w pewnych dwóch miejscach w kodzie ustawia się zmienną slot przy pomocy set() a nie compareAndSet()? 

```java
public class LockFreeExchanger<T> {
    static final int EMPTY = ..., WAITING = ..., BUSY = ...;
    AtomicStampedReference<T> slot = new AtomicStampedReference<T>(null, 0);

    public T exchange(T myItem, long timeout, TimeUnit unit) throws TimeoutException {
        long nanos = unit.toNanos(timeout);
        long timeBound = System.nanoTime() + nanos;
        int[] stampHolder = {EMPTY};

        while (true) {
            if (System.nanoTime() > timeBound)
                throw new TimeoutException();
            T yrItem = slot.get(stampHolder);
            int stamp = stampHolder[0];
            switch(stamp) {
                case EMPTY:
                    if (slot.compareAndSet(yrItem, myItem, EMPTY, WAITING)) { // (1)
                        while (System.nanoTime() < timeBound){
                            yrItem = slot.get(stampHolder);
                            if (stampHolder[0] == BUSY) {
                                slot.set(null, EMPTY);
                                return yrItem;
                            }
                        }
                        if (slot.compareAndSet(myItem, null, WAITING, EMPTY)) { // (2)
                            throw new TimeoutException();
                        } else {
                            yrItem = slot.get(stampHolder);
                            slot.set(null, EMPTY);
                            return yrItem;
                        }
                    }
                    break;
                case WAITING:
                    if (slot.compareAndSet(yrItem, myItem, WAITING, BUSY)) // (2)
                        return yrItem;
                    break;
                case BUSY:
                    break;
                default: // impossible
                    ...
            }
        }
    }
}
```

(Opis działania TAOMP 251)

1. Może się  nie powieść jeśli inny wątek slot po naszej modyfikacji (przed swirtch-em). W takim przypadku (jeśli czas się nie skończył) zaczniemy pętlę od nowa (prawdopodobnie wpadając do case-a  WAITING).  
2. To jest zabezpieczenie na wypadek sytuacji gdy skończył się czas i checmy wyjść, a inny wątek w wszedł w miedzyczasie i pobrał wartość. Jeśli tak się zdarzyło, to pobieżemy wartość ze `slotu`, zresetujemy jego state na EMPTY i ostatecznie wymiana się powiedzie.
3. Może się nie powieść jeśli inny wątek nas wyprzedzi, lub jeśli wątek czekający skończy z timeoutem. W takim wypadku zaczynamy od nowa.

czemu w dwóch miejscach jest `set()`
Są to miejsca w któ©ych sprzątamu po naszej udanej wymianie. W trakcie/po udanej wymianie żąden inny wątek poza dwoma kótre brały w niej udział nic nie modyfikuje (lądują w case BUSY). A skoro nic się nie zmieniło to do zresetowania slot-u używamy set.

### Zadanie 2

Omów działanie klasy EliminationBackoffStack. Jaką rolę pełni w niej klasa RangePolicy? Wskaż punkty linearyzacji metod push() i pop().

EliminationBackoffStack jest klasą pochodną LockFreeStack. Ulepsza ją poprzez zaimplementowanie mechanizmu możliwości "cancel-owania" się par operacji push i pop (zamiast czasowego backoff-u) bez modyfikacji stanu "wewnętrznego" LockFreeStack.
EliminationBackoffStack wykonuje tryPush i tryPop (str. 246-247) i w przypadku niepowodzenia odsyła wątki do EliminationArray (lista exchanger-ów) gdzie mają one szanse na rendezvous (jednoczesny push i pop).

Obiekt RangePolicy określa wielkość używanego przez wątki kawałka EliminationArray. Im większy tym mniejsza szansa na rendezvous push-a i pop-a ale powinien się zwiększać proporcjonalnie do liczby aktywnych wątków.

Jeśli push lub pop jest udany poprzez dostęp do wewnętrznego LockFreeStack (tryPush/tryPop), to może być zlinearyzowany w momencie dostępu do LockFreeStack. 
Jeśli push lub pop był udany poprzez rendezvous w EliminationArray z przeciwną operacją, to może być zlinearyzowany w momencie tego zderzenia.
Nieudany pop, czyli został rzucony emptyException, linearyzuje się w momencie sprawdzenia oldTop == null w tryPop (str. 247)
Nie ma nieudanych push-y.

### Zadanie 3

Opisz w sposób wysokopoziomowy (tzn. bez odwoływania się do kodu) algorytm implementowany przez metodę getAndIncrement() klasy CombiningTree.

Metoda getAndIncrement ma za zadanie zwiększyć współdzielny między wątkami counter.
Może to zrobić bezpośrednio (nasze wywołanie doszło do root-a) lub pośrednio (inny wątek dodał naszą wartość za nas)
Składa się z 4 etapów:
1. Wątek wspina się tak wysoko jak może w drzewie. Po drodze oznacza mijane node-y jako odwiedzone i że do nich wróci zebrać ew. wartości o jakie inny wątek chce zwiększyć counter lub, jeśli wszedł do node-a w którym już był inny wątek i zadeklarował, że wróci po wartość, to zatrzymuje się na nim i go odpowiedni oznacza.
2. W fazie drugiej wątek odwiedza wszystkie minięte node-y i zbiera z nich wartości wstawione przez inne wątki lub blokuje je, tak aby inny wątek nie mógł już wsadzić do node-a swojej inkrementacji.
3. Wątek zsumował wartości o jakie ma zwiększyć swój node i jeśli jest w root-cie to go zwiększa a wpp. zwiększa wartość w nodzie, zaczyn czekać aż wątek który go wyprzedził wróci po tę wartość.
4. Jeśli wątek był w root-cie to wraca w dół drzewa i przekazuje czekającym wątkom wartość z root-a. Jeśli nie był w root-cie to sam czeka, aż otrzyma wartość z root-a i potem przekazuje ją wątkom poniżej.

### Zadane 4

(kod str. 264)
Flaga locked w każdym węźle oznacza, czy w tym węźle trwa już aktywna faza combining / operacji, do której nie wolno dołączać nowemu wątkowi.
* locked == false - węzeł może jeszcze zmienic wartosc first/secondValue
* locked == true - węzeł jest zamknięty na modyfikacje wartosci

1. Sens wysokopoziomowy
W fazach:
precombine (rezerwacja drogi w górę)
combine (zbieranie wartości)

wątek:
próbuje dołączyć do aktualnej rundy combining w danym węźle.

Jeśli locked == true, to znaczy:
ten węzeł już bierze udział w innej, wcześniejszej rundzie

ktoś inny:
zebrał już wartości
albo czeka na wynik z góry

inaczej:
W precombine() i combine() wątek czeka, aż locked będzie false, ponieważ nie wolno dołączać do węzła, który bierze udział w innej, nierozliczonej jeszcze rundzie combining; flaga locked chroni przed mieszaniem żądań z różnych rund.

2. W metodach op() i distribute() nie ma oczekiwania na locked == false, ponieważ w tych fazach wątek nie próbuje dołączyć do rundy, lecz wykonuje lub kończy już rozpoczętą rundę, do której dostęp nowych wątków został wcześniej zablokowany.

3. 
A. precombine()
case FIRST:
    locked = true;
    cStatus = SECOND;
    return false;

Znaczenie

Ten wątek:

był pierwszym w tym węźle,

teraz stał się drugim,

i zamyka węzeł dla kolejnych wątków.

Efekt:

Od tej chwili żaden nowy wątek nie może dołączyć do tej rundy w tym węźle.

Wpływ na inne wątki:

każdy nowy wątek:

trafi na while (locked) wait();

poczeka na następną rundę.

B. combine()
while (locked) wait();
locked = true;
firstValue = combined;

Znaczenie

Wątek:

zaczyna fazę zbierania w tym węźle,

zamyka węzeł, aby:

nikt już nie dopisał nowej wartości do tej rundy.

Efekt:

Ten węzeł jest teraz „w trakcie combining”.

Wpływ:

inne wątki:

nie mogą wejść ani do precombine, ani do combine

muszą czekać na zakończenie rundy.

C. op() – przypadek SECOND
secondValue = combined;
locked = false;
notifyAll();
while (cStatus != RESULT) wait();
locked = false;
notifyAll();
cStatus = IDLE;


Tu są dwa bardzo ważne momenty.

1️⃣ locked = false po zapisaniu secondValue

Znaczenie:

wątek nadrzędny może:

pobrać wartość

i kontynuować w górę

Wpływ:

Odblokowuje wątek nadrzędny tej rundy.

2️⃣ locked = false po otrzymaniu wyniku

To jest moment:

Zakończenia rundy w tym węźle.

Wpływ:

wątki czekające w precombine() i combine():

mogą wejść

rozpocząć nową rundę.

D. distribute()
Przypadek FIRST:
cStatus = IDLE;
locked = false;


Znaczenie:

wątek kończy rundę w tym węźle,

węzeł wraca do stanu spoczynkowego.

Wpływ:

Wszyscy czekający w precombine() mogą ruszyć.

Przypadek SECOND:
result = prior + firstValue;
cStatus = RESULT;


Tu nie ma zmiany locked, bo:

ten wątek nie kończy jeszcze rundy

czeka, aż wątek z op() go zwolni.