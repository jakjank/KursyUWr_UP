# Project

...

# Usage

...

# Thinking (tldr)

The idea is exactly the same as in nonogrmas with one small modification.\
All possibilities of filling the row/column are goinig to be generated along with extra variables standing for which possibility is chosen.\
Small modification is that forbiden arrangements are going to be 'included' in the CNF.
The forbiden arrangements are:\

##   ##   #.   .#\
.#   .#   ##   ##\

.   .#.\
#\
.\

How to write this requirement in CNF?\
For example lets look on\
#.\
##\
plus rotations.\
We can think about it like exactly one out of four cells is blank.\
For each cell x_i_j on board (board after alignment for proper range):\

(x_i_j and x_i_j+1 and x_i+1_j and not x_i+1_j+1) or  (3 other posibilities)\

and we want to add negation of this to our CNF.\
not ((x_i_j and x_i_j+1 and x_i+1_j and not x_i+1_j+1) or...) = \
(not (x_i_j and x_i_j+1 and x_i+1_j and not x_i+1_j+1)) and (not ...) ... = \
(not x_i_j or not x_i_j+1 or not x_i+1_j or x_i+1_j+1) and ...\

and this is nicely in CNF already.\
Similiar thing also  needs to be done with .#. requirement.