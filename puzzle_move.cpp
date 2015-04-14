#include "puzzle_move.h"


PuzzleMove::PuzzleMove(Board& b) {
        tilemove_ = -1;
        b_ = &b;
        g_ = 0;         // distance from the start board
        h_ = 0;         // heuristic distance to the goal
        prev_ = NULL;  // Pointer to parent PuzzleMove
}


PuzzleMove::PuzzleMove(int tile, Board* b, PuzzleMove* parent) {
        tilemove_ = tile;
        b_ = b;
        g_ = 0;
        h_ = 0;
        prev_ = parent;
}

/** Destructor
 * Destroy some allocated objects */
PuzzleMove::~PuzzleMove() {
        delete b_;
        delete prev_;
}


bool PuzzleMove::operator<(const PuzzleMove& p) const {
        if((g_ + h_) < (p.g_ + p.h_)){
                return true;
        }
        else if((g_ + h_ == p.g_ + p.h_) && (g_ > p.g_)){
                return true;
        }
        else {
                return false;
        }
}


bool PuzzleMove::operator>(const PuzzleMove& p) const {
        if((g_ + h_) > (p.g_ + p.h_)){
                return true;
        }
        else if((g_ + h_ == p.g_ + p.h_) && (g_ < p.g_)){
                return true;
        }
        else {
                return false;
        }
}

bool PuzzleMove::operator==(const PuzzleMove& p) const {
        if(tilemove_ == p.tilemove_ && b_ == p.b_ && g_ == p.g_ && h_ == p.h_ && prev_ == p.prev_) {
                return true;
        }
        
        else {
                return false;
        }
}
