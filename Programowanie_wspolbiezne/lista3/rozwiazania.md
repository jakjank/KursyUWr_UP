### Zadanie 1

**r-Bounded Waiting** - mamy wątki A i B. Jeśli A wejdzie do Doorway Section zamka przed wejściem B do tej sekcji, to B nie wykona swojej sekcji krytycznej więcej niż **r** razy zanim A w końcu wejdzie do swojej.

W algorytmie Petersona:

```java
public void lock() {
    // Doorway section
    flag[i] = true;
    victim = i;
    // end of doorway section (finit #steps)

    // Waiting section 
    while (flag[j] && victim == i) {};
    // end of waiting section (unbounded #steps)
}
```
**Czy Peterson jest FIFO?**
Zał. że A czeka (na while-u), a B wszedł do CS dwa razy z rzędu.
Gdy B po raz drugi wchodził do skecji krytycznej to ustawił `victim` = B. A nie zmienił `victim`. Zatem B nie mógł wejść drugi raz bo spełniał while-a

### Zadanie 2

**Bakery algorithm** - Mamy n wątków. Kiedy wątek chcec wejść do CS to ustaiwa swoją flagę na true oraz bierze numerek (większy od wszystkich jakie **widział** u innych). Następnie wątek czeka aż jego numere jest najmniejszy. Możliwe sąkolizje numerków, które wygrywa wątek o mniejszym ID.

Pobrane etykiety nie muszą być unikatowe. Wątki mogły zacząć szukać maxa razem i wyliczyć sobie takie same etykiet.

```java
public void lock() {
    flag[i] = true;
    label[i] = max(label[0], …,label[n-1])+1;
    while (∃k flag[k]
    && (label[i],i) > (label[k],k));
    }
```

**wzajemne wykluczenie**
Załóżmy że nie spełnia. Niech A i B to wątki które weszły razem do CS. A i B musiały ustawić swoje flagi i wziąć numerki przed wejściem do CS. Zał. że `(label[A], A) < (label[B], B)`. Kiedy B wchodził do CS to musiał widzieć `flag[A] == false` lub `(label[A], A) > (label[B], B)`. Zgodnie z zał. B musiał widzieć `flag[A] == false`.
Zarem musiało być:
`readB(flag[A]) -> writeA(flag[A])`
Ale B musiał pobrać numerek przed czytaniem flag w Waiting Section:
`(B bierze numerek) -> readB(flag[A]) -> writeA(flag[A])`
Natomiast A pobiera numerek dopiero po ustawieniu swojej flagi:
`(B bierze numerek) -> readB(flag[A]) -> writeA(flag[A]) -> (A bierze numerek)`

co jest sprzeczne z założeniem `(label[A], A) < (label[B], B)`.

**niezakleszczenie**
Jakiś wątek musi mieć najmniejszą parę `(label, id)`.

**niezagłodzenie**
Jeśli A wykonał Doorway section przed B, to B nie wejdzie do CS przed A, czyli mamy FIFO. 
FIFO + niezakeleszczenie = niezagłodzenie.

### Zadanie 3

```java
class OneBit implements Lock {
    private boolean[] flag;

    public OneBit (int n) {
        flag = new boolean[n]; // all initially false
    }
    
    public void lock() {
        int i = ThreadID.get(); // ThreadID.get() returns 0,1,..,n-1
        do {
            flag[i] = true; // Im interested
            for (int j = 0; j < i; j++) {
                if (flag[j] == true) { // wait for anyone 'before' me
                    flag[i] = false; //give up for now allowing smaller ids to execute
                    while (flag[j] == true) {} // wait until flag[j] == false
                    break;
                }
            }
        } while (flag[i] == false);
        for (int j = i+1; j < n; j++) {
            while (flag[j] == true) {} // wait until flag[j] == false
        }
    }

    public void unlock() {
        flag[ThreadID.get()] = false;
 }
}
```

**wzajemne wykluczenie**
Załóżmy, że A i B są razem w CS. BSO zał. że A < B (A.id < B.id).
Skoro oba są w CS to mają flagi == true. Ale A nie mógł wejść do CS po B, bo sprawdzał:
```java
for (int j = i+1; j < n; j++) {
    while (flag[j] == true) {} // wait until flag[j] == false
}
```
Czyli było:
`A_CS -> writeB(flag[B] = true)`
Ale A ustawia `flag[A] = true` przed wejsciem do CS a B po ustawieniu swojej flagi sprawdza flagi nizszych id, w tym A. 

**niezakleszczenie**
Zainteresowany wątek o najmniejszym id będzie przepuszczany przez inne.

**niezagłodzenie**
Nie. Wątki o najwyższych id będą przepuszczać mniejsze, więc może dojść do ich zagłodzenia.

### Zadanie 4


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
        label[i] = counter++; //zamiast max(labels) + 1
        // load label[i] counter
        // addi label[i] 1
        // store counter label[i]
        while (∃k flag[k] && (label[i], i) > (label[k], k)) {};
    }

    public void unlock () {
        flag[i] = false;
        }
    }
}
```

Rozwazmy przyklad:
```
1. readA(labelA = counter) //0
2. readB(labelB = counter) //0
3. writeA(counter = 1)
4. readC(labelC = counter) //1
5. writeC(counter = 2)
6. writeB(counter = 1) !
```
pokazuje on, że counter może zmniejszyć swoja wartość (o dowolnie dużą wielkość?)

**wzajemne wykluczenie**
Nie. Watek A moze ustawic labelA na counter. Innym moze zaktualizowac counter na mniejszy. Wątek A wchodzi sobie do CS. Wątek B ustawia label na counter (labelB < labelA). Wątek B wchodzi so CS bo ma najmniejszy label. 

**niezakleszczenie**
Tak jak w zwkłym Bakery zawsze isnieje wątek o najmniejszym `(label, id)` który przejdzie przez while-a.

**niezagłodzenie**
Nie. Wątek A możę wziąć "duży" counter. counter zostanie ustawiony na mniejszy. Jakieś wątki zaczną "kręcić" counter-em tak, żę już nigdy nie dojedzie do dużek wartości i A nie wejdzie do CS.

### Zadanie 6 / 7

```java
class MergeSort implements Runnable {
    private final int[] array;
    private final int[] temp; //zamiast kopiowania arr do kazdego watku
    private final int leftIndex;
    private final int rightIndex;

    public MergeSort(int[] array, int[] temp, int leftIndex, int rightIndex) {
        this.array = array;
        this.temp = temp;
        this.leftIndex = leftIndex;
        this.rightIndex = rightIndex;
    }

    // niepotrzebne synchronized
    // wątki działają na rozłącznych elementach tablicy
    private void merge(int[] array, int[] temp, int left, int middle, int right) {
        int i = left;
        int j = middle + 1;
        int k = left;

        // scalanie do tymczasowej tablicy
        while (i <= middle && j <= right) {
            if (array[i] <= array[j]) {
                temp[k++] = array[i++];
            } else {
                temp[k++] = array[j++];
            }
        }

        // pozostałe elementy
        while (i <= middle) temp[k++] = array[i++];
        while (j <= right) temp[k++] = array[j++];

        // z powrotem do tablicy głównej
        for (i = left; i <= right; i++) {
            array[i] = temp[i];
        }
    }

    private void sequentialMergeSort(int[] array, int[] temp, int left, int right) {
        if (left < right) {
            int middle = (left + right) / 2;
            sequentialMergeSort(array, temp, left, middle);
            sequentialMergeSort(array, temp, middle + 1, right);
            merge(array, temp, left, middle, right);
        }
    }

    @Override
    public void run() {
        if (leftIndex < rightIndex) {
            int size = rightIndex - leftIndex + 1;

            if (size <= 4) {
                sequentialMergeSort(array, temp, leftIndex, rightIndex);
                return;
            }
            int middle = (leftIndex + rightIndex) / 2;
            
            // nie ma potrzeby dwoch nowych watkow.
            // Aktualny watek moze pracowac zamiast jedneg z nowych
            MergeSort leftTask = new MergeSort(array, temp, leftIndex, middle);
            MergeSort rightTask = new MergeSort(array, temp, middle + 1, rightIndex);

            Thread leftThread = new Thread(leftTask);
            // Thread rightThread = new Thread(rightTask);
            rightTask.run();

            leftThread.start();
            // rightThread.start();

            try {
                leftThread.join();
                // rightThread.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }

            merge(array, temp, leftIndex, middle, rightIndex);
        }
    }
}


public class RookieMergeSort {

    public static void main(String[] args) {
        int arr[] = {4, 3, 2, 1, 5, 3, 43, 8, 9, 57};
        int[] temp = new int[arr.length];

        MergeSort job = new MergeSort(arr, temp, 0, arr.length - 1);
        job.run();
        // Thread t = new Thread(w);

        // t.start();
        // try {
        //     t.join();
        // } catch (InterruptedException e) {
        //     e.printStackTrace();
        // }

        for (int i = 0; i < arr.length; i++)
            System.out.printf("%d ", arr[i]);
        System.out.println();
    }
}
```

