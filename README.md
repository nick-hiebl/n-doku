# n-doku
A solver for n-doku's or (m,n)-doku's.

# What is an n-doku?
An n-doku as an sudoku of size n by n. Traditional sudokus are 9-dokus.
All cells in the n by n grid are filled with integers 1 to n, where no
two cells in the same row or column can have be the same value.
Additionally the n by n grid is split into subsections of size square
root n by square root n, and no two cells within the same of these
subsections can have the same value.

This definition is somewhat limited as the subsection rule means that
n-doku's can only be made for square numbers n, which restricts our
options.

# What is a (m,n)-doku?
This idea may be unfamiliar to most, even those who have reasonable
experience solving sudokus or some variants. An (m,n)-doku is a sudoku
with different internal box sizes.

Overall the grid is of size *mn* by *mn*. The values in each cell range
from 1 to *mn*.
