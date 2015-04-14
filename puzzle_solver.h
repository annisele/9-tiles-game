#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H
#include <queue>
#include <vector>
#include <deque>
#include <set>
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "mylist.h"

/**
puzzle solver class which takes a opy of the current board and computes 
a list of best moves by finding and going through all potential moves and
assigning a number to each move based on efficiency and stored it in a 
closed list.
*/
class PuzzleSolver
{
 public:
  typedef std::set<Board *, BoardLessThan> BoardSet;

  // Constructor (makes a copy of the Board and stores it in _b
  PuzzleSolver(const Board &b);

  // Destructor
  ~PuzzleSolver();

  // Run the A* search returning -1 if no solution exists or
  //  the number of moves in the solution
  int run(PuzzleHeuristic *ph);

 
Board b_;
  // Return how many expansions were performed in the search
  int getNumExpansions();
  mylist<int>* getlist();
mylist<int>sollist;
 private:
  int expansions_;
  
  };

#endif
