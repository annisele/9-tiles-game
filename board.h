#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <functional>

/** Board Class
 * This class handles the board. It handles the board's size, dimensions,
 * potential moves, and moving. */
class Board {
        public:
                Board(); 
                Board(int size, int numInitMoves, int seed);
                Board(const Board &b);
                Board(int *tiles, int size);
                ~Board();

                void move(int tile);
                std::map<int, Board*> potentialMoves(); 
                bool solved();

                // Operators
                friend std::ostream& operator<<(std::ostream &os, const Board &b);
                bool operator==(const Board& rhs) const;
                bool operator<(const Board& rhs) const;
                bool operator!=(const Board& rhs) const;
  
                // Accessors
                int* getTiles();
                int getSize();
                int key;
                

        private:
                int *tiles_;
                int size_;
};

struct BoardLessThan : public std::binary_function<const Board*, const Board*,bool> {
        bool operator()(const Board *b1, const Board *b2) const {
                return *b1 < *b2;
        }
};



#endif
