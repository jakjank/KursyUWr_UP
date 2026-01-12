# Generator Liczb Pseudo-losowych Blum-Blum-Shub na FPGA

## Opis projektu

Projekt implementuje kryptograficznie bezpieczny generator liczb pseudo-losowych Blum-Blum-Shub (BBS) na układzie FPGA z wizualizacją procesu generowania na wyświetlaczu.

## Zasada działania algorytmu

Generator BBS opiera się na wzorze:

$$x_{n+1} = x_{n}^{2} \bmod M$$

gdzie:
- $M = p \times q$ jest produktem dwóch **dużych** liczb pierwszych $p$ i $q$
- $x_0$ to ziarno (seed) generatora
- Przy każdej iteracji bity wyjściowe są ekstrahowane jako:
  - Parzystość bitów $x_{n+1}$, lub
  - Jeden lub więcej najmniej znaczących bitów $x_{n+1}$

## Wymagania dla parametrów

### Liczby pierwsze p i q:
- Muszą być **kongruentne do 3 modulo 4**: $p \equiv 3 \pmod{4}$ oraz $q \equiv 3 \pmod{4}$
- Powinny być **bezpiecznymi liczbami pierwszymi**: $p = 2p' + 1$ gdzie $p'$ też jest liczbą pierwszą
- Powinny mieć małe $\gcd(p-1, q-1)$ dla lepszych właściwości kryptograficznych

### Ziarno (seed) $x_0$:
- Musi być względnie pierwsze z $M$ (czyli $\gcd(x_0, M) = 1$)
- Powinno spełniać: $1 < x_0 < M$

## Szczegóły implementacji FPGA

### 1. Moduł mnożenia dużych liczb (Parallel Multiplier)

**Architektura równoległa - metoda Karatsuba lub Array Multiplier:**

```vhdl
-- Dla N-bitowych liczb, mnożenie x_n * x_n
-- Podział na mniejsze bloki dla równoległości
```

**Implementacja:**
- **Array Multiplier** dla liczb do 32-bit
  - Macierz komórek mnożących (AND gates + full adders)
  - Wszystkie częściowe iloczyny generowane równolegle
  - Drzewo sumatora Wallace'a/Dadda dla redukcji
  - Latencja: O(log N) cykli zegara

LUB

- **Karatsuba dla większych liczb** (64-bit+)
  - Rekurencyjny podział: $xy = 2^n \cdot ac + 2^{n/2} \cdot ((a+b)(c+d) - ac - bd) + bd$
  - 3 mnożenia zamiast 4 dla każdego poziomu
  - Pipeline: 4-6 stages
  - Równoległe obliczanie podwyrażeń

**Pipeline stages:**
```
Stage 1: Podział operandów, obliczanie sum a+b, c+d
Stage 2: Start 3 równoległych mnożeń
Stage 3-4: Redukcja częściowych iloczynów
Stage 5: Rekombinacja wyniku (2^n * ac + ...)
Stage 6: Output ready
```

### 2. Moduł redukcji modularnej (Modular Reduction)

**Problem:** Dla wyniku mnożenia $P = x_n^2$ (2N bitów), oblicz $P \bmod M$

**Metoda Barrett Reduction - optymalna dla stałego M:**

```
Preprocessing (wykonywane raz):
  μ = ⌊2^(2N) / M⌋

Reduction Runtime:
  q = ⌊(P * μ) / 2^(2N)⌋  // aproksymacja ilorazu
  r = P - q * M            // reszta
  if r ≥ M: r = r - M      // korekta (max 2 iteracje)
```

**Implementacja równoległa:**

```
Blok 1 (równolegle):  q_approx = (P_high * μ) >> 2N
Blok 2 (równolegle):  prod = q_approx * M
Blok 3:               r = P - prod
Blok 4 (conditional): r = (r >= M) ? r - M : r
Blok 5 (conditional): r = (r >= M) ? r - M : r
```

**Zasoby:**
- 1x mnożenie N×N dla q×M (reużycie multipliera z BBS)
- 2x subtraktor N-bit
- 2x komparator N-bit
- Całkowita latencja: ~10-15 cykli

**Alternatywa - Montgomery Reduction:**
- Lepsza dla wielu operacji modulo z tym samym M
- Transformacja do/z dziedziny Montgomery: $\tilde{x} = xR \bmod M$
- Redukcja bez dzielenia, tylko mnożenia i shifty

### 3. Moduł rdzenia BBS - Pipeline

**Architektura potokowa:**

```
[State Register x_n] 
    ↓
[Stage 1-6: Squaring (Multiplier)]
    ↓
[Stage 7-15: Modular Reduction]
    ↓
[Stage 16: Bit Extraction (LSB)]
    ↓
[Output Register] → x_{n+1}, random_bit
    ↓
[Feedback do State Register]
```

**Throughput:** 1 iteracja co ~16 cykli (przy pełnym pipeline)

**Sterowanie:**
```vhdl
FSM States:
  IDLE      → czeka na START
  COMPUTE   → pipeline aktywny
  EXTRACT   → ekstrakcja bitu
  DISPLAY   → aktualizacja wyświetlacza
  NEXT      → feedback do rejestru stanu
```

### 4. Kontroler sekwencji i timing

```vhdl
entity BBS_Controller is
  generic (
    N : integer := 32  -- szerokość słowa
  );
  port (
    clk          : in  std_logic;
    rst          : in  std_logic;
    start        : in  std_logic;
    pipeline_rdy : in  std_logic;
    
    iteration    : out integer;
    x_current    : out std_logic_vector(N-1 downto 0);
    x_next       : out std_logic_vector(N-1 downto 0);
    random_bit   : out std_logic;
    valid        : out std_logic
  );
end BBS_Controller;
```

### 5. Moduł ekstrakcji bitów

**Opcje ekstrakcji:**
- **Parity bit:** XOR wszystkich bitów x_{n+1}
- **LSB:** Najmłodszy bit
- **k-LSBs:** k najmłodszych bitów (k=1..8)

**Implementacja dla k bitów:**
```vhdl
random_bits <= x_next(k-1 downto 0);
-- Równoległe wyodrębnienie w 1 cyklu
```

### 6. Optymalizacje sprzętowe

**Reużycie zasobów:**
- Ten sam multiplier dla $x_n \times x_n$ i $q \times M$
- Multiplexery dla wyboru operandów
- Tradeoff: latencja vs zasoby (LUTs/DSP blocks)

**DSP48 slices (Xilinx) / DSP blocks (Intel):**
- Wykorzystanie wbudowanych bloków DSP dla mnożeń 18x18 lub 27x27
- Kaskadowanie dla większych liczb

**Block RAM:**
- Opcjonalne: lookup table dla małych wartości M
- Bufor FIFO dla wygenerowanych bitów

### Moduły wsparcia:

**Interfejs wyświetlacza:**
- Konwerter binarny → BCD dla wyświetlacza 7-segmentowego
- Kontroler multipleksowania cyfr
- Częstotliwość odświeżania: 1kHz per cyfra

**Debugging:**
- Wbudowane Logic Analyzer (ILA) do obserwacji pipeline
- Licznik iteracji
- Status flags (overflow, valid, busy)

### Wyświetlane informacje w każdej iteracji:

```
Iteracja: n
x[n]:     [wartość heksadecymalna]
x[n+1]:   [wartość heksadecymalna]
Bit(y):   [wygenerowane bity 0/1]
Suma:     [łączna liczba bitów]
```

## Architektura sprzętowa

### Wejścia:
- `CLK` - zegar systemowy
- `RST` - reset systemu
- `START` - rozpoczęcie generowania
- `SEED[N-1:0]` - wartość ziarna (opcjonalnie programowalna)

### Wyjścia:
- `RANDOM_BIT` - wygenerowany bit losowy
- `VALID` - sygnał gotowości nowego bitu
- Sygnały sterujące wyświetlaczem (7-segment lub LCD/OLED)

### Parametry implementacji:
- Szerokość słowa: 16-64 bity (w zależności od zasobów FPGA)
- Przykładowe wartości:
  - $p = 11$ (lub większe: 499, 6547)
  - $q = 19$ (lub większe: 547, 7219)
  - $M = p \times q$
  - $x_0 = 3$ (lub inna wartość spełniająca wymagania)

## Etapy realizacji projektu

1. **Implementacja arytmetyki modularnej**
   - Mnożenie modulo
   - Optymalizacja dla sprzętu (pipeline, parallel)

2. **Implementacja rdzenia BBS**
   - Inicjalizacja z ziarnem
   - Iteracja $x_{n+1} = x_{n}^{2} \bmod M$

3. **Interfejs użytkownika**
   - Sterownik wyświetlacza 7-segmentowego / LCD
   - Formatowanie i wyświetlanie wartości

4. **Testowanie i weryfikacja**
   - Testbench w VHDL/Verilog
   - Weryfikacja statystyczna wygenerowanych sekwencji
   - Testy sprzętowe na płytce FPGA

## Możliwe rozszerzenia

- Programowalne parametry p, q, seed przez interfejs UART/SPI
- Analiza statystyczna generowanych bitów w czasie rzeczywistym
- Wizualizacja rozkładu bitów na matrycy LED
- Tryb ciągłego generowania z buforowaniem FIFO
- Eksport danych przez interfejs komunikacyjny


# Problemy
Split 256-bit numbers into 64-bit or 32-bit chunks

Compute partial products using DSPs (pipelined)

Reduce modulo M using Barrett reduction (constant modulus)

Pipeline stages so that throughput = 1 result per clock after latency, even if latency is 10–20 cycles

You can do this on Cyclone V, but you cannot do all in one cycle

Simulation of full 256-bit numbers in Icarus Verilog is mostly impossible; use smaller numbers for verification