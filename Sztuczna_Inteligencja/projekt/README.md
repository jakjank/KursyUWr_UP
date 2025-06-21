# Puzzles to CNF

Mini-project for AI course at UWr.\
The objective was to code puzzle as a logical sentences (CNF) and try to solve it with some SAT solver.
Two 'transformators' vere implemented. One for nonogram and one for storms puzzles.
There is more info in READMEs in storms/ and nonogram/ folders.

# Performance

Below are the tables describing time/used memory performance (s/MB) of minisat, CaDiCal and kissat for few tests:

nonogram:
        
| instance | minisat       | CaDiCal      | kissat      |
|----------|---------------|--------------|-------------|
| easy     | 0.003 / 11    | ~0 / 6       | ~0 / 6      |
| medium   | 1.193 / 36    | 0.37 / 48    | 1.46 / 25   |   
| medium2  | 1.661 / 41    | 0.39 / 59    | 0.94 / 30   |
| hard     | 57.855 / 1111 | 12.13 / 2133 | 41.14 / 679 |


storms:
        
| instance | minisat      | CaDiCal      |  kissat     |
|----------|--------------|--------------|-------------|
| easy     | 0.6 / 50     | ~0 / 6       | ~0 / 6      |
| medium   | 0.6 / 50     | 0.11 / 60    | 0.63 / 33   |
| hard     | 65.79 / 1462 | 10.82 / 2661 | 18.70 / 633 |
