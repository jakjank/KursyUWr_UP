# Project

The objective of this project was to "translate" storm puzzle to CNF and then to use SAT solvers to solve the initial puzzle.

# Usage

We need to have some storm puzzle to solve. The input should be of the following format.
In the first line there are two integers defining the grid dimensions.
Next lines have single integers standng for how many storm cells are in the first row, second row ... first column ...\
Example:\
##...\
##.##\
##.##\
such storm is coded as:\
3 5\
2\
4\
4\
3\
3\
0\
2\
2

When we have our storm, let say in storm.txt file, we run
> \$ python3 StormToCnf.py storm.txt storm.cnf

and then we should get CNF coding of our storm in storm.cnf.

Next we use SAT-solver of our choice.

Examples:

To run minisat:
> \$ minisat storm.cnf soulution.txt

Since CaDiCal and Kissat print progress info we need to modify output a bit before saving the solution:
> \$ cadical storm.cnf | grep '^v ' | sed 's/^v //' > solution.txt
> \$ kissat storm.cnf | grep '^v ' | sed 's/^v //' > solution.txt

then to print the solution we just need to call 
> \$ python3 PrintSolution.py cells_def.txt solution.txt

Where cells_def.txt is a file produced by StormToCnf.py.

There are example test storms in test_storms/ folder.\
Max size of the storm I could transform was 13x13. For bigger storms program crashed due to lack of memory. 

# Thinking (tldr)

The idea is exactly the same as in nonogrmas with one small modification.\
All possibilities of filling the row/column are goinig to be generated along with extra variables standing for which possibility is chosen.\
Small modification is that forbiden arrangements are going to be 'included' in the CNF.
The forbiden arrangements are:
|          |             |          |          |
|----------|-------------|----------|----------|
| ##<br>.# | ##<br>#.    | .#<br>## | #.<br>## |
| .#.      | .<br>#<br>. | .#<br>#. | #.<br>.# |

How to write this requirement in CNF?\
For example lets look on

\#.\
\##

plus rotations.

We can think about it like exactly one out of four cells is blank.\
For each cell x_i_j on board (board after alignment for proper range):\

(x_i_j and x_i_j+1 and x_i+1_j and not x_i+1_j+1) or  (3 other posibilities)\

and we want to add negation of this to our CNF.\
not ((x_i_j and x_i_j+1 and x_i+1_j and not x_i+1_j+1) or...) = \
(not (x_i_j and x_i_j+1 and x_i+1_j and not x_i+1_j+1)) and (not ...) ... = \
(not x_i_j or not x_i_j+1 or not x_i+1_j or x_i+1_j+1) and ...

and this is nicely in CNF already.\
Similiar thing also  needs to be done with other requirements.