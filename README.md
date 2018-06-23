# n-doku
A solver for n-doku's or (m,n)-doku's.

# What is an n-doku?
An n-doku as an sudoku of size n by n. Traditional sudokus are 9-doku's.
All cells in the n by n grid are filled with integers 1 to *n*, where no
two cells in the same row or column can have be the same value.
Additionally the n by n grid is split into subsections of size square
root *n* by square root *n*, and no two cells within the same of these
subsections can have the same value.

This definition is somewhat limited as the subsection rule means that
n-doku's can only be made for square numbers *n*, which restricts our
options.

# What is a (m,n)-doku?
This idea may be unfamiliar to most, even those who have reasonable
experience solving sudokus or some sudoku variants. An (m,n)-doku is a
sudoku with different internal box sizes.

Overall the grid is of size *mn* by *mn*. The values in each cell range
from 1 to *mn*. As above no two cells in the same row or column can
contain the same value. However there is a distinction in the way
that subsections are made. Subsections have dimensions *m* by *n*, in
this case meaning *m* cells vertically and *n* cells vertically.
Consequently there are *n* subsections placed above each other, and *m*
subsections placed side by side.

By this definition traditional sudoku puzzles (or 9-doku's) can also be
called (3,3)-doku's, as they consist of 3 by 3 subsections. A more
interesting example of an (m,n)-doku is in traditional 8x8 sudokus or
some common sudokus of other non-square dimensions. A (2,4)-doku is
shown below, such sudokus might be typically called 8x8 sudokus.

![A (2,4)-doku](http://markhuckvale.com/games/sudoku/variants/gp8-s.png)

This definition gives slightly more flexibility in the kinds of puzzles
we can specify. For example consider a 12x12 sudoku. Such a sudoku will
typically consist of 3 by 4 subsections. However, it would also be valid
to make a 12x12 sudoku with 2 by 6 subsections, and as my aim is to
try to implement generic sudoku solving I will use this definition to
allow me to solve a wider range of possible puzzles (and possibly study
the differences in solving a (3,4)-doku versus a (2,6)-doku).
