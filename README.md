# rikudo_solver
Solver methods for Rikudo puzzles

Methods for solving rikudo puzzles. 

Command line: rikudo_solver[.exe] <filename> [<method> [<method parameters>]]

<filename> - input file 
<method> 
  - M1 (no parameters) [default]
  - Mpb [<start_value>] [default start_value = 1]

Syntax of input file:

whole line comments starts with # (optionally preceded with white space characters space, tab)
(other comment types at the end of line are not supported (yet))

[Shape]
--
[Forced directions]
--
[Non fillable elements]
--
[Forced values]
--
[max_element_value]



[Shape] is specified as series of triples <num> LRA LRA (one per line), where num in number of tiles in a row
and the first LRA is a connection type of the next row (L - as UL, R - as UR, A - there is no upper row)
and the second LRA is a connection type of the previous row (L - as DL, R - as DR, A - there is no previous row).

[Forced directions] is specified as series of (x, y) <list_of_directions>. Coordinates are indexed from 0.
(0,0) is the bottom left element. <list_of_directions> is a white space(space or tab) separated list of directions:
allowed directions are: UR - upper right, R - right, DR - down right, DL - down left, L - left and UL - upper left.

[Non fillable elements] is a comma separated list of coordinates (x,y). 

[Forced values] is a series of triples (x,y) => v (one per line), which represents that at position (x,y) is 
the forced value v.

[max_element_value] is a number, which represents last value filled in the rikudo puzzle.

