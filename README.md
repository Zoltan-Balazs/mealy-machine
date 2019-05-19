# mealy-machine
A C++ program which solves a mealy machine, with a given state table and inputs

The program is quite simple, it requires two files to be given by the user. The files must be .txt files, one containing the state table and the other containing the given inputs the user wants to go through. The user is also required to enter a filename which they want to save the solution to. All files must be in the same directory as the program.
(Note: the states must be only from A to Z, this is a possible improvement possibility, as it shouldn't be that hard to change it to multiple letters, or even numbers. Also, the state file must contain a '-' at the top left as its starting "state")

Each line in the input file is considered one clock cycle.

Example state table file:
> -	00	01	11	10
> A	-	  A/0	D/1	B/-
> B	-	  -	  C/0	 -
> C	A/1	B/0	C/-	D/1
> D	B/1	C/0	D/-	A/1

Example input file:
> 01 11 01 00
> 01	11 01
> 11 10	11	11
> 00 11	10 00
(Note: the input file accepts both spaces and tabulators as separting different inputs)

The output which the program gives to these files:
> Solution: 
> 01 11 01 00          A/1
> 01 11 01          C/0
> 11 10 11 11          D/-
> 00 11 10 00          B/1 
(Note: the program prints this solution to the screen and to the given file, it also prints each line, so the user is aware which line might contribute to it going into a neutral state)
