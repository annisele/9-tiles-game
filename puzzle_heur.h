#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H


class PuzzleHeuristic
{
 public:
  virtual int compute(int *tiles, int size) = 0;
  
};
class ManhattanHeuristic: public PuzzleHeuristic
{
 public:
  int compute(int *tiles, int size) ;
  
};
class OutOfPlaceHeuristic: public PuzzleHeuristic
{
 public:
  int compute(int *tiles, int size);
  
};
// Define actual Heuristic Classes here

#endif
