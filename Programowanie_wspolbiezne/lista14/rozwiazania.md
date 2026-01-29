### Zadanie 1

Licznik współdzielony

Licznik współdzielony to struktura danych, do której jednocześnie odwołuje się wiele wątków, a jego zadaniem jest zwracanie kolejnych, unikalnych wartości bez konieczności pełnej serializacji dostępu.

Sieć zliczająca (counting network)

Zamiast jednego licznika stosuje się wiele mini-liczników, z których każdy odpowiada za wartości o innym reszcie modulo ich liczby. Sieć zliczająca, złożona z balancerów, kieruje wątki do odpowiednich mini-liczników, umożliwiając równoległe wykonywanie operacji.

Własność krokowa (step property)

Własność krokowa wymaga, aby po opuszczeniu sieci przez wszystkie wątki wartości mini-liczników różniły się co najwyżej o jeden. Zapewnia to brak luk i duplikatów w sekwencji zwracanych wartości.

Operacja getAndIncrement

Wątek przechodzi przez sieć zliczającą, trafia do mini-licznika y o wartosci i, zwraca i*x+y,a następnie zwiększa wartość tego mini-licznika.

### Zadanie 3

```java
public class Balancer {
    AtomicInteger x = new AtomicInteger(0);
    public int traverse() {
        return x.getAndIncrement() % 2;
    }
}
```