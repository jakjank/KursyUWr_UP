### Zadanie 1

W procesorze wzrocowym mamy $P_0 = C_0V^2_0f_0$.
Rozważmy da rdzenie pracujące z dwukrotnie mniejszą częstotliwością:
Wtedy:
$C_1 = 2C_0$,
$f_1 = f_0/2$,
$V_1 = V_0/2$.
A algorytm zostanie wykonany tak samo szybko (dwukrotne przyspieszenie wykonanie zadania na dwukrotnie wolniejszych procesorach). Zużyta moc:
$P_1 = C_1V_1^2f_1 = 2C_0 * (V_0/2)^2 * f_0/2 = 1/4 *C_0V_0^2f_0 = P_0/4$

### Zadanie 2

Sekcja krytyczna to fragment kodu ktory może być wykonywany przez maksymalnie jeden wątek w danym momencie ze 
względy na współdzielony między wątkami zasób.

<!-- Problem sekcji krytycznej to zadanaie synchronizacji dostępu wielu wątków do współdzielonych zasobów, tak aby:
1. żadne dwa wątki nie korzystały z zasobu jednocześnie
2. jeśli wątek chce skorzystać z zasobu i żąden inny z niego nie korzysta, to wątek dostanie do niego dostęp. -->

Przykład ze smokami:
Alice i Bob chcą korzystać z jeziora żeby wykąpać smoki ale jeśli zrobią to jednocześnie to będzie katastrofa.

Tutaj wkładanie i bycie smoka w jeziorze jest sekcją krytyczną.

Poprawienie algorytmu tak aby smok Boba też mógł sie kąpać:
<span style="color:green">modyfikujemy</span> stary algorytm:
Alice | Bob
-|-
podnieś flagę | podnieś flagę
<span style="color:green">jeśli wskaznik -> Alice to 1, inaczej 2 | <span style="color:green">jeśli wskaznik -> Alice to 1, inaczej 2
1 czekaj aż flaga Boba będzie opuszczona | 1 dopóki flaga Alicji jest w górze <br/> opuść flagę <br/> czekaj aż Alice opuści flagę <br/> podnieś flagę
<span style="color:green">2 dopóki flaga Boba jest w górze <br/> opuść flagę <br/> czekaj aż Bob opuści flagę <br/> podnieś flagę | <span style="color:green">2 czekaj aż flaga Alice będzie opuszczona
opuść flagę po kąpieli <span style="color:green">i pociagnij za sznurek | opuść flagę po kąpieli <span style="color:green">i pociagnij za sznurek

### Zadanie 3

Problem producenta i konsumenta to zadanaie synchronizacji dostępu wielu wątków do współdzielonych zasobów, tak aby:
1. żadne dwa wątki nie korzystały z zasobu jednocześnie
2. jesli wątek 'produkuje' to inne będą konsumować
3. konsumenci nie będą korzystać z zasobu jeśli nie mają czego z niego wziąć, a producent nie przepełni zasobu/nie produkuje jeśli poprzednie dane nie byly zkonsumowane.

Przykład:
Alice daje smoki do jeziora jesli jest jedzenie a Bob zapewnia jedzenie. Alice i Bob nie mogą się spotkać przy jeziorze. Alice i Bob nie chcą marnować swojego czasu: Alice nie uwalnia smoków jeśli nie miałyby czego jeść, a Bob nie daje jedzenie jeśli poprzednie nie zostało zjedzone.

Jak poprawić algortm jeśli Bob i Alice nie widzi balkonu Alice:
Bob stąca puszkę A u Alice. Alice strąca puszkę B u Boba
Alice | Bob
------|-----
strąć B gdy chcesz jeść | czekaj aż B bedzie strącone
czekaj aż A spadnie | daj jedzenie
wypuść smoki | postaw B 
gdy smoki wrócą postaw A i strąć B | strąć A

### Zadanie 4
Bezpieczenstwo - nic złego nigdu się nie dzieje
Żywotność - coś dobrego się kiedyś stanie
Bezpieczeństwo | 1 | 4 | 6 | <br/>
---------------|---|---|---|---
Żywotność      | 2 | 3 | 5 | 7

### Zadnie 5

jest K więźniów i jeden dostaje role licznika.
Każdy więzien poza licznikiem włącza przełącznik za pierwszym razem gdy wchodzi do celi i przełącznik jest wyłączony.
Gdy więźeń raz włączy przełącznik to więcej go nie rusza.
Tylko licznik wyłącza przełącznik.
Licznik ogłasza koniec gdy wyłączył przełącznik K-1 razy

### Zadanie 6

Jest K więźniów i jeden z nich jest licznikiem.
Zwykli więźniowie jeśli znajdą licznik włączony i wyłączali go mniej niż dwa razy to wyłączają go.
Licznik włącza przełącznik jeśli jest wyłączony, wpp nie rusza go (zlicza włączenia).
Kiedy licznik naliczy $2K-2$ włączeń tzn. że każdy więzień był w pokoju conajmniej raz

wyłączony na start
max liczba zliczonych włączeń taka że nie wszyscy byli  w celi: $2(K-2)+1 = 2K-3$ 

włączony na start
max liczba zliczonych włączeń taka że nie wszyscy byli  w celi: $2(K-2) = 2K-4$  

### Zadanie 7

Zakleszczenie następuje gdy każdy filozof weźmie swoją lewą lewą pałeczkę. Można to zaobserwować po drobnej modyfikacji kodu (N = 3):
```java
class Philosopher extends Thread {
    ...

    public void run() {
        Random random = new Random();
        while (true) {
            try {
                // sleep(random.nextInt(1000));
                // sleep(100);
                System.out.println("Philosopher " + id + " is hungry");
                left.get();
                System.out.println("Philosopher " + id + " got fork");
                right.get();
                System.out.println("Philosopher " + id + " got knife");
                left.put();
                right.put();
            } catch (InterruptedException ex) {
                return;
            }
        }
    }
}
```
Wypisze:
```
Starting...
Waiting for philosopher 0 to finish
Philosopher 1 is hungry
...
Philosopher 0 is hungry
Philosopher 0 got fork
Philosopher 2 is hungry
Philosopher 2 got fork
Philosopher 1 got fork
```
i się zakleszczy. Rozwiązanie problemu:
```java
System.out.println("Philosopher " + id + " is hungry");
if(id % 2 == 0){
    left.get();
    System.out.println("Philosopher " + id + " got fork");
    right.get();
    System.out.println("Philosopher " + id + " got knife");
}
else{
    right.get();
    System.out.println("Philosopher " + id + " got knife");
    left.get();
    System.out.println("Philosopher " + id + " got fork");
}
```
