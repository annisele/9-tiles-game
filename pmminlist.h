#ifndef PMMINLIST_H
#define PMMINLIST_H
#include <list>

/**
 * PMMinList implements a sorted list of PuzzleMoves
 * based on their f-score (from smallest to largest)
 */
class PMMinList  {
        public:
  
                PMMinList();
                ~PMMinList();

                int size() const { return slist_.size(); }
                bool empty() const { return slist_.empty(); }
                void push(PuzzleMove* pm);
                void pop();
                PuzzleMove* top();

        private:
                std::list<PuzzleMove*> slist_;
};

#endif
