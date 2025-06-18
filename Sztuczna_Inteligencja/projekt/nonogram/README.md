# Project

...


# Usage

## Nonogram format

First we need to have some nonogram which we would like to solve.
The description of such nonogram is number of rows and columns in first row followed by description of blocks in each row and then in each column.
Example:
3 3
1 1
1 1
1
2
0
3
describes 3x3 nonogram with:
two blocks of length 1 in first row,
same in second row,
one block of length 1 in third row,
one block of length 2 in first column,
no blocks in 2nd column,
one block of length 3 in 3rd column.

It is satisfied by following nonogram:
#.#
#.#
..#

## Using

1. Nonogram to solve described in format explained above should be saved in nonogram.txt.
2. NonogramToCnf.py should be run 'python3 NonogramToCnf.py'
3. nonogram.cnf and cells_def.txt (used for prinitng the nonogram) files are created.
4. SAT solver is used to solve CNF described in nonogram.cnf. For example using minisat and saving the soluion in solution.txt 'minisat nonogram.cnf solution.txt'.
5. solution.txt contains the valuation of logical variables used in nonogram.cnf.
6. Obtained solution can be printed by PrintNonogram.py 'python3 PrintNonogram.py'.

## Using short

Save description in nonogram.txt, then:
$ python3 NonogramToCnf.py
$ minisat nonogram.cnf solution.txt
$ python3 PrintNonogram.py

# Thinking (tldr)

how to do nonogram => CNF?

lets think how we check if solution of nonogram is valind:
(row1 is valid) AND (row2 is valid) AND ... AND (columnM is valid)
so i guess it would be our CNF.

Now how to check if row/column is valid (using OR)?

lets have a row of length 3 and 1 block of length 1 for simplicity.
(1,2,3 are cells)
so to chck validity we should have

(1 and -2 and -3) or (-1 and 2 and -3) or (-1 and -2 and 3)
=
(1 or 2 or 3) and (-1 or -2) and (-1 or -3) and (-2 or -3)
(Exactly 1 variable is true) 

and this stands for "is row valid".

what if we have more complicated row
lat say one described with [2 3] of length 8

a bit complicated to code it in DNF and convert to CNF like before.

lets generate all possible sequences of 0s and 1s which are possible in this row.
lets add variables for sequences (s1, s2, ...)
we have to add (s1 or s2 or ...) so one of sequences is fulfilled
(and we want only one sequence to be true (needed?))
if 1 is black in s1 we need to add (1 or -s1)
if 1 is white in s1 we need to add (-1 or -s1)