#include "puzzle_move.h"
#include "pmminlist.h"

/**
 * Default Constructor
 */
PMMinList::PMMinList() : slist_() {

}

/**
 * Destructor
 */
PMMinList::~PMMinList() {

}

/**
 * Adds the value val to the internal list in sorted
 * order from smallest to largest (if 
 * @param val Value to add to the sorted PuzzleMove list
 * @return nothing
 */
void PMMinList::push(PuzzleMove* pm) {
        //slist_ iterator
        std::list<PuzzleMove*>::iterator it = slist_.begin();
        for(it = it ; it != slist_.end(); ++it) {
                //f value in the list
                int itFVal = (*it)->g_ + (*it)->h_;
                
                //f value in incoming pm
                int f = pm->g_ + pm->h_;
                
                //Breaks the loop, allows us to add only one f value, otherise the loop continues
                if(f < itFVal)
                        break;
        }
        //Adds pm regardless.
        slist_.insert(it, pm);
}


PuzzleMove* PMMinList::top() {
        return slist_.front();
}


/**
 * Adds the value val to the internal list in sorted
 * order from smallest to largest
 * @param val Value to add to the sorted PuzzleMove list
 * @return nothing
 */
void PMMinList::pop()
{
  slist_.pop_front();
}

/**
 * Adds the value val to the internal list in sorted
 * order from smallest to largest
 * @param val Value to add to the sorted PuzzleMove list
 * @return reference to the minimum-scored PuzzleMove*
 */


