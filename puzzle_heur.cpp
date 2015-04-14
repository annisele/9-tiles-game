#include "puzzle_heur.h"
#include <cmath>
#include <cstdlib>

/** compute
@param current tile
@param size of tile list*/
int ManhattanHeuristic::compute(int* tiles, int size) {

        int dim = sqrt(size);
        int row = 0;    //Row distance
        int col = 0;    //Column distance
        int m = 0;              //Total Manhattan distance
        
        //goes through the array and computes the Manhattan distance 
        for(int cnt = 0; cnt < size; cnt++) {
                //Skips the empty space
                if(tiles[cnt] == 0)
                        continue;
                row = abs((tiles[cnt] % dim) - (cnt % dim));    //Absolute value of the row - the current location
                col = abs((tiles[cnt] / dim) - (cnt / dim));    //Absolute value of the column - the current location
                m += row + col;
        }
        return m;
}


int OutOfPlaceHeuristic::compute(int* tiles, int size) {
        int o = 0; //Total number of out of place tiles
        
        //goes through the board and counts the number of moves tiles
        for(int cnt = 0; cnt < size; cnt++) {
                //Skips the empty space
                if(tiles[cnt] == 0)
                        continue;
                //Counts each space with a mismatched tile
                if(tiles[cnt] != cnt)
                        o++;
        }
        return o;
}
