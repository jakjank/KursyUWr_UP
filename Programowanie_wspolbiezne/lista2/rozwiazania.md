### Zadanie 1

Prawo Amdahl-a:
$$speedup = \frac{1}{1 - p + p/n}$$
$p$ - zrównoleglana część programu
$n$ - number of threads
(licznik - czas wykonania na jednym proc., mianownik - czas na n proc.)

#### 1  
$p = 1 - 0.4 = 0.6$, więc speedup -> 1/0.4 = 2.5
#### 2  
Jakie przyspieszenie ma $P'$ dla różnej ilości procesorów:
$speedup = 1/(1-0.7+0.7/n)$

#procesorów | 1 | 2  | 3  | 4  | 32 | inf
------------|---|----|----|----|----|-----
speedup     | 1 |1.54|1.88|2.1 | 3.1| 3.3 

Niech T to czas wykonania $P'$ chcemy obliczyć s tak aby:
$$0.3T +\frac{0.7T}{n}  = 2(\frac{0.3T}{s} + \frac{0.7T}{n}) \\
0.3 + \frac{0.7}{n} = \frac{0.6}{s} + \frac{1.4}{n} \\
0.3 - \frac{0.7}{n} = \frac{0.6}{s} \\
s = \frac{0.6}{0.3 - \frac{0.7}{n}}$$


Musimy miec 0.3 > 0.7/n
n > 0.7/3 > 2
Czyli dla mnej niż 2 procesorów nie osiągniemy oczekiwanego efektu.

Podstawiając do wzoru mamy  tabelkę:

#procesorów | 1 | 2  | 3  | 4  | 32 | inf
------------|---|----|----|----|----|-----
needed s    | x |  x | 9  | 4.8 |2.2| 2 

#### 3
Mamy M przyspieszone trzykrotnie.

Chcemy znalezc takie p, że:
(po podzieleniu przez T)
$$(1-p) + \frac{p}{n} = 2\frac{1-p}{3} + \frac{p}{n} \\
(1-p) + \frac{p}{n} = \frac{2-2p}{3} + \frac{2p}{n} \\
1 - p + \frac{p}{n} - \frac{2-2p}{3} - \frac{2p}{n} = 0 \\ 
1 - p + \frac{p}{n} - \frac{2}{3} + \frac{2p}{3} - \frac{2p}{n} = 0 \\
1 + p(-1 + \frac{1}{n} + \frac{2}{3} - \frac{2}{n}) - \frac{2}{3} = 0 \\
-1/3 = p(-1 + \frac{1}{n} + \frac{2}{3} - \frac{2}{n}) \\
p = -1/(3(-1 + \frac{1}{n} + \frac{2}{3} - \frac{2}{n})) \\
p = \frac{1}{\frac{3}{n} + 1}$$

Musimy mieć: $3/n + 1 >= 1$ (część wspólna nie może być wiśksza od całości) -> $n > 0$

Podstawiamy i mamy tabelkę

#procesorów | 1 | 2  | 3  | 4  | 32 | inf
-----------------|---|----|----|----|----|-----
min parallel part|0.25|0.4| 0.5|0.57|0.91| ~1 



### Zadanie 2

Zmodyfikowany algorytm Petersona:
```java
public void lock() {
    flag[i] = true;
    victim = i;
    while (flag[j] && victim == i) {}; (1)
}

public void unlock() {
    int i = ThreadID.get(); /*returns 0 or 1*/
    flag[i] = false;
    int j = 1 - i;
    while (flag[j] == true) {} (2)
}
```

#### Niezakleszczenie
Wystąpi jeśli A i B oba bedą czekać na (1) lub (2)
Oba na (1)
BSO niech A był ostatnim piszącym do victim. Wtedy B wejdzie.

Oba na (2)
Jeśli oba czekają na dwa to znaczy że oba usawiły swoje flagi na false więc niemożliwe.

BSO A na (1) B na (2)
Jeśli B czeka na (2) to ustawił swoją flagę na false więc A wejdzie.

#### Niezagłodzenia
Zagłodzenie jest możliwe. 
Przykład:
```
1. wątek 0 przechodzi przez CS i woła unlock.
2. write0(flag[0] = false)
3. write0(j = 1)
4. write1(flag[1] = true)
5. read0(flag[1] == true) 0 czeka na while-u w unlock
6. write1(victim = 1)
7. read1(flag[0] == false)
8. 1 przechodzi przez CS
9. write1(flag[1] = false)
10. write1(j = 0)
11. read1(flag[0] == false)
powrót do 4.
```

### Zadanie 3

```java
public void lock() {
    int i = ThreadID.get(); /*returns 0 or 1*/
    int j = 1 - i;
    flag[i] = true;
    local[i] = (turn[j] + i) % 2; (1)
    turn[i] = local[i];
    while (flag[j] == true && local[i] == ((turn[j] + i) % 2));
}
public void unlock() {
    int i = ThreadID.get();
    flag[i] = false;
}
```

Zauważmy, że wykonanie (1) zmienia parzystość local[i]. BSO załóżmy, że pierwotnie local[i/j] == 0 i turn[i/j] == 0.

#### wzajemne wykluczenie

???

### Zadanie 4

```java
lass Foo implements Lock {
    private int turn;
    private boolean busy = false;

    public void lock() {
        int me = ThreadID.get(); /*get id of my thread*/
        do {
            do {
                turn = me;
            } while (busy);
            busy = true;
        } while (turn != me);
    }

    public void unlock() {
        busy = false;
    }
}
```

#### wzajemne wykluczenie
Załóżmy, że 2 wątki weszły do CS.
Wtedy:
z kodu:
write0(turn = 0) -> read0(busy == false) -> write0(busy = true) -> read0(turn == 0)
write1(turn = 1) -> read1(busy == false) -> write1(busy = true) -> read1(turn == 1)

z założenia musiało być:
read0(turn == 0) -> write1(turn = 1)
read1(turn == 1) -> write0(turn = 0)

mamy cykl:
read0(turn == 0) -> write1(turn = 1) -> -> read1(busy == false) -> write1(busy = true) -> read1(turn == 1) -> write0(turn = 0) -> read0(busy == false) -> write0(busy = true) -> read0(turn == 0)
czyli sprzeczność (bo porządek częściowy)

#### warunek niezagłodzenia
Może dojść do zagłodzenia.
```
1. 0 wchodzi do CS
2. 1 czeka na while(busy)
3. 0 busy = false
4. 0 turn = 0
5. 0 busy = true
6. 0 wchodzi do CS
```

#### warunek niezakleszczenia
Może dojść do zakleszczenia. Np.:

write0(turn = 0) -> read0(busy == false) -> write1(turn = 1) -> read1(busy = false) -> write0(busy = true) -> write1(busy = true) -> read0(turn == 1) -> write0(turn = 0) -> read1( turn = 0) ...

## Zadanie 5
#### wzajemne wykluczenie
Sprowadza się do tego że Alg. Petersona działa i każdy poziom odfiltrowuje połowę 'niepoległych' wątków.

#### niezagłodzenie
Alg Petersona dla dwóch wątów nie głodzi wątków.
Załóżmy, że nasz nowy algorytm nie ma tej własności.
Znaczy to, żę istnieje wątek który czeka na pewnym węźle.
Ale przecież węzeł jako Peterson lock nie głodzi więc sprzeczność.

#### Niezakleszczenie
Analogicznie do niezagłodzenia.