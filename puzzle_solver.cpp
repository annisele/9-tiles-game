#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "puzzle_solver.h"
#include "pmminlist.h"

using namespace std;

/**
puzzle solver class which takes 
@param a copy of the current board
*/
PuzzleSolver::PuzzleSolver(const Board &b) {
        b_ = b;
        expansions_ = 0;
}

/** Destructor */
PuzzleSolver::~PuzzleSolver() {}

/** runs puzzle solver
@param type of puzzle heuristic to use
*/
int PuzzleSolver::run(PuzzleHeuristic *ph) {
        PMMinList openList;
        BoardSet closedList;
        vector<PuzzleMove*> garbage;
        
        //Creates an initial board for openList
        PuzzleMove* temp = new PuzzleMove(b_);
        temp->h_ = ph->compute(b_.getTiles(), b_.getSize());
        openList.push(temp);    //Adds temp to the openList
        
        while(!openList.empty()) {
                PuzzleMove* move = openList.top();
                openList.pop();
                
                closedList.insert(move->b_);
                garbage.push_back(move);
                
                if(move->b_->solved()) {
                        //Iterates to build the list of moves in reverse
                        mylist<int>* movelist = new mylist<int>;
                        while(move->prev_ != NULL) {
                                movelist->push_back(move->tilemove_);
                                move = move->prev_;
                        }
                        
                        //Puts the list in order.
                        for(int cnt = movelist->listsize() - 1; cnt >= 0; cnt--) {
                                sollist.push_back(movelist->at(cnt));
                        }
                        delete movelist;
                        return sollist.listsize();
                }
                
                //Generate expansions (potential moves)
                mylist<PuzzleMove*> expansions;
                int dim = sqrt(move->b_->getSize());
                int* moveTiles = move->b_->getTiles();
                
                //Find the empty space
                int empty = 0;
                for(int cnt = 0; cnt < move->b_->getSize(); cnt++) {
                        if(move->b_->getTiles()[cnt] == 0) {
                                empty = cnt;
                                break;
                        }
                }
                
                //Up
                if(empty - dim >= 0) {
                        Board* eb = new Board(*(move->b_));
                        eb->move(moveTiles[empty - dim]);
                        PuzzleMove* tempMove = new PuzzleMove(moveTiles[empty - dim], eb, move);
                        expansions.push_back(tempMove);
                }
                
                //Down
                if(empty + dim < move->b_->getSize()) {
                        Board* eb = new Board(*(move->b_));
                        eb->move(moveTiles[empty + dim]);
                        PuzzleMove* tempMove = new PuzzleMove(moveTiles[empty + dim], eb, move);
                        expansions.push_back(tempMove);
                }
                
                //Right
                if(empty + 1 < move->b_->getSize() && empty % dim != (dim - 1)) {
                        Board* eb = new Board(*(move->b_));
                        eb->move(moveTiles[empty + 1]);
                        PuzzleMove* tempMove = new PuzzleMove(moveTiles[empty + 1], eb, move);
                        expansions.push_back(tempMove);
                }
                
                //Left
                if(empty - 1 >= 0 && empty % dim != 0) {
                        Board* eb = new Board(*(move->b_));
                        eb->move(moveTiles[empty - 1]);
                        PuzzleMove* tempMove = new PuzzleMove(moveTiles[empty - 1], eb, move);
                        expansions.push_back(tempMove);
                }
        
        //Check expansions and heuristic scores, then add the expansions to the lists.
        for(int cnt = 0; cnt < expansions.listsize(); cnt++) {
                if(closedList.find(expansions[cnt]->b_) == closedList.end()) {
                      
                        expansions[cnt]->h_ = ph->compute(expansions[cnt]->b_->getTiles(), expansions[cnt]->b_->getSize());
                        
                        PuzzleMove* prev = expansions[cnt];
                        while(prev->prev_ != NULL) {
                                expansions[cnt]->g_ += 1;
                                prev = prev->prev_;
                        }
                        closedList.insert(expansions[cnt]->b_); //Adds board to closedList
                        openList.push(expansions[cnt]); //Adds expansions to openList
                        expansions_++;  //Increments expansions
                        }
                }
        }
        return -1; 
}
//return list of cheat moves
mylist<int>* PuzzleSolver::getlist() {
        return &sollist;
}
// get potential moves to explore
int PuzzleSolver::getNumExpansions() {
        return expansions_;
}

