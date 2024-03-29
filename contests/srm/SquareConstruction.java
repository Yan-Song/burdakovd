// BEGIN CUT HERE
// PROBLEM STATEMENT
// There is an NxN square with its cells initially empty. The rows of the square are indexed from top to bottom, and columns from left to right. All indices start from 0.

You wish to fill the cells of the square with consecutive integers, starting from 1, using the following algorithm. At the beginning you stand at the topmost leftmost cell and put 1 in this cell. Each time you want to find the cell for the next number, you use the following method: Move a cells down and b cells right from your current cell (all moves are cyclic, so moving down one row from row N-1 takes you to row 0, and moving right one column from column N-1 takes you to column 0). If the current cell is empty, then you put the next number in this cell. Otherwise, move an additional c cells down and d cells right. If the current cell is empty, then you put the next number in this cell, otherwise the entire algorithm is finished.

Return a String[] describing the final state of the square after the algorithm is finished. The i-th element of the return should be a list of N integers, separated by single spaces and without leading or trailing spaces. The j-th integer in this list should be the integer written in the cell in row i, column j of the square, or -1 if this cell is empty.

DEFINITION
Class:SquareConstruction
Method:construct
Parameters:int, int, int, int, int
Returns:String[]
Method signature:String[] construct(int N, int a, int b, int c, int d)


CONSTRAINTS
-N will be between 1 and 10, inclusive.
-a, b, c and d will each be between 0 and N-1, inclusive.


EXAMPLES

0)
5
0
0
0
0

Returns: {"1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1" }

Here you don't move at all, so the algorithm finishes after putting 1 in the topmost leftmost cell.

1)
5
1
1
2
2

Returns: {"1 -1 -1 -1 -1", "-1 2 -1 -1 -1", "-1 -1 3 -1 -1", "-1 -1 -1 4 -1", "-1 -1 -1 -1 5" }

First you put numbers 1, 2, 3, 4 and 5 in the cells on the main diagonal. Then you analyze the cells at row 0, column 0 and at row 2, column 2. Neither cell is empty, so the algorithm is finished.

2)
5
1
1
1
0

Returns: {"1 22 18 14 10", "6 2 23 19 15", "11 7 3 24 20", "16 12 8 4 25", "21 17 13 9 5" }

In this case you will fill all the cells with numbers.

3)
5
0
1
2
3

Returns: {"1 2 3 4 5", "17 18 19 20 16", "8 9 10 6 7", "24 25 21 22 23", "15 11 12 13 14" }



4)
6
1
2
2
2

Returns: {"1 -1 15 -1 11 -1", "12 -1 2 -1 16 -1", "17 -1 7 -1 3 -1", "4 -1 18 -1 8 -1", "9 -1 5 -1 13 -1", "14 -1 10 -1 6 -1" }



5)
1
0
0
0
0

Returns: {"1" }



// END CUT HERE
import java.util.*;
public class SquareConstruction {
	public String[] construct(int N, int a, int b, int c, int d) {
		
	}
	public static void main(String[] args) {
		SquareConstruction temp = new SquareConstruction();
		System.out.println(temp.construct(int N, int a, int b, int c, int d));
	}
}
