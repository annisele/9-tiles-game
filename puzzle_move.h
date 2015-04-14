#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include <functional>
#include "board.h"
#include "puzzle_heur.h"

/* PuzzleMove Class
 * This class handles the process of determining the best possible moves for the
 * PuzzleSolver class */
class PuzzleMove {
        public:
                PuzzleMove(Board &b);
                PuzzleMove(int tile, Board *b, PuzzleMove *parent);
                ~PuzzleMove();

                bool operator<(const PuzzleMove& p) const;
                bool operator>(const PuzzleMove& p) const;
                bool operator==(const PuzzleMove& p) const;

        public:
                int tilemove_;  // tile moved to reach the Board b
                Board* b_;      // Pointer to a board representing the updated state
                int g_;         // distance from the start board
                int h_;         // heuristic distance to the goal
                PuzzleMove *prev_;  // Pointer to parent PuzzleMove
};

struct PuzzleMoveGreater : public std::binary_function<const PuzzleMove*, const PuzzleMove*,bool> {
                bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const {
                        return *m1 > *m2;
                }
};

#endif
