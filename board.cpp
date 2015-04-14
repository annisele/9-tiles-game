#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include "board.h"

using namespace std;
/**constructor*/
Board::Board() {
        size_ = 4;
        tiles_ = new int[size_];
        
        for(int i=0; i < size_; i++) {
                tiles_[i] = i;
        }
}

/** makes inital board given arguments*/
Board::Board(int size, int numInitMoves, int seed ) {
        size_ = size;
        tiles_ = new int[size_];
        int dim = static_cast<int>(sqrt(size_));
        srand(seed);
        
        for(int i=0; i < size_; i++) {
                tiles_[i] = i;
        }
        
        int blankLoc = 0;
        for(int i=0; i < numInitMoves; i++) {
                int r = rand()%4;
                int randNeighbor = -1;
                if(r == 0){
                        int n = blankLoc - dim;
                        if(n >= 0){
                                randNeighbor = n;
                        }
                }
                else if(r == 1) {
                        int w = blankLoc - 1;
                        if(blankLoc % dim != 0){
                                randNeighbor = w;
                        }
                }
                else if(r == 2) {
                        int s = blankLoc + dim;
                        if(s  < size_) {
                                randNeighbor = s;
                        }
                }
                else {
                        int e = blankLoc + 1;
                        if(blankLoc % dim != dim-1) {
                                randNeighbor = e;
                        }
                }
                if(randNeighbor > -1) {
                        tiles_[blankLoc] = tiles_[randNeighbor];
                        tiles_[randNeighbor] = 0;
                        blankLoc = randNeighbor;
                }
        }
}

/** Copy constructor
 * Creates a new board and sets it equal to the parameter
 * 
 * @param b The board the new board object will copy
 */
Board::Board(const Board &b) {
        size_ = b.size_;
        tiles_ = new int[size_];
        for(int i = 0; i < size_; i++) {
                tiles_[i] = b.tiles_[i];
        }
}


Board::Board(int *tiles, int size) {
        tiles_ = tiles;
        size_ = size;
}

Board::~Board() {
        delete [] tiles_;
}

int* Board::getTiles() { return tiles_; }
int Board::getSize() { return size_;}


std::map<int, Board*> Board::potentialMoves() {
        std::map<int, Board*> moves;
        int dim = static_cast<int>(sqrt(size_));
        for(int i = 0; i < size_; i++) {
                if(tiles_[i] == 0) {
                        
                        //Moving up
                        if(i < size_ - dim) {
                                int* movedTiles = tiles_;
                                swap(movedTiles[i], movedTiles[i-dim]);
                                
                                Board* temp = new Board(movedTiles, size_);
                                moves.insert(std::pair<int, Board*>(movedTiles[i], temp));
                        }
                        
                        //Moving down
                        if(i >= dim) {
                                int* movedTiles = tiles_;
                                swap(movedTiles[i], movedTiles[i+dim]);
                                
                                Board* temp = new Board(movedTiles, size_);
                                moves.insert(std::pair<int, Board*>(movedTiles[i], temp));
                        }
                        
                        //Moving left
                        if(i % dim != 0) {
                                int* movedTiles = tiles_;
                                swap(movedTiles[i], movedTiles[i-1]);
                                
                                Board* temp = new Board(movedTiles, size_);
                                moves.insert(std::pair<int, Board*>(movedTiles[i], temp));
                        }
                        
                        //Moving right
                        if((i + 1) % dim != 0) {
                                int* movedTiles = tiles_;
                                swap(movedTiles[i], movedTiles[i+1]);
                                
                                Board* temp = new Board(movedTiles, size_);
                                moves.insert(std::pair<int, Board*>(movedTiles[i], temp));
                        }
                        
                        //Error case incase the seed breaks
                        else {
                                cout << "No available moves--Bad seed" << endl;
                                return moves;
                        }
                }
        }
        
        return moves;
}

/** Swaps the blank with the specified tile 
 *
 * @param tile The tile to move
 */
void Board::move(int tile) {
        if(tile >= size_ || tile <0) {
                cout << "Tile not found on board." << endl;
                return;
        }
        int loc = -1;
        int empty = -1;
        int dim = static_cast<int>(sqrt(size_));
        key=0;
        
        //Finds the location of the tile and the location  of the empty tile
        for(int i = 0; i < size_; i++) {
                if(tiles_[i] == tile)
                        loc = i;
                if(tiles_[i] == 0)
                        empty = i;
        }
        if(loc == -1 || empty == -1) {
                cout << "Number selected is not an option." << endl;
                return;
        }
        
        //Swaps tile to the left
        if((loc - 1 == empty && loc % dim != 0)) { 
                tiles_[empty] = tile;
                tiles_[loc] = 0;
        }
        
        //Swaps tile to the right
        else if (loc + 1 == empty && loc % dim != (dim - 1)) {
                tiles_[empty] = tile;
                tiles_[loc] = 0;
        }
        
        //Swaps above tile
        else if (loc - dim == empty) {
                tiles_[empty] = tile;
                tiles_[loc] = 0;
        }
        
        //Swaps below tile
        else if (loc + dim == empty) {
                tiles_[empty] = tile;
                tiles_[loc] = 0;
        }
        
        //Incase the user enters a tile that is not adjacent to any other tiles.
        else {
        //sets key
                key=1;
                return;
        }
}


bool Board::solved() {
        for(int i = 0; i < size_; i++) {
                if(tiles_[i] != i)
                        return false;
        }
        return true;
}

std::ostream& operator<<(std::ostream &os, const Board &b) {
        int dim = static_cast<int>(sqrt(b.size_));
        for(int i = 0; i < b.size_; i++) {
                if(i % dim == 0)
                        os << endl;
                if(b.tiles_[i] != 0)
                        os << setw(dim) << b.tiles_[i];               
                else {
                        for(int i = 0; i < dim; i++) {
                                os << " ";
                        }
                }
        }
        
        return os;
}

/** Operator ==
 * Checks two boards to see if they are identical
 * 
 * @param rhs The board reference to be checked against the current board. 
 * @return true Returns true if the boards are the same
 * @return false Returns false otherwise.
 */
bool Board::operator==(const Board& rhs) const {

        if(tiles_ == rhs.tiles_ && size_ == rhs.size_)
                return true;
        else
                return false;
                
}


bool Board::operator!=(const Board& rhs) const {
        if(tiles_ != rhs.tiles_ || size_ != rhs.size_)
                return true;
        else
                return false;
}



bool Board::operator<(const Board& rhs) const {
        if(size_ < rhs.size_) {
                return true;
        }
        bool val = false;
        for(int i=0; i < size_; i++){
                if(tiles_[i] < rhs.tiles_[i]){
                        
                        return true;
                }
                else if(tiles_[i] > rhs.tiles_[i]){
                       
                        return false;
                }
        }
        return val;
}

