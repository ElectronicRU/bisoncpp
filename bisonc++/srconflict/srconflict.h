#ifndef _INCLUDED_SRCONFLICT_
#define _INCLUDED_SRCONFLICT_

#include <iosfwd>
#include <vector>

#include "../rmreduction/rmreduction.h"
#include "../next/next.h"

class SRConflict
{
    friend std::ostream &operator<<(std::ostream &out, 
                                    SRConflict const &conflict);

    Next::Vector const &d_nextVector;           // the Next objects describing
                                                // states to transit to

    StateItem::Vector const &d_itemVector;      // the items which have S/R
                                                // conflicts with the
                                                // reducible items

    std::vector<size_t> const &d_reducible;     // the indices of the
                                                // reducible rules
    
    RmReduction::Vector     d_rmReduction;      // Vector of reducible rules
                                                // to remove for this conflict
    std::vector<size_t>     d_rmShift;          // vector of indices of items
                                                // to remove having shift
                                                // conflicts 

    static size_t  s_nConflicts;                // the number of S/R conflicts
                                                // that could not be solved by
                                                // preference/association
                                                // decisions. 
    public:
        SRConflict(Next::Vector const &next, 
                   StateItem::Vector const &stateItem, 
                   std::vector<size_t> const &reducible);

        void inspect();
                            // returns # of shifts that were removed
        size_t removeShifts(Next::Vector &nextVector);

        void removeReductions(StateItem::Vector &itemVector);

        static size_t nConflicts();

    private:
        std::ostream &insert(std::ostream &out) const;
        void processShiftReduceConflict(Next::ConstIter const &next, 
                                        size_t itemIdx);
        bool differentLHSs(Symbol const *reducibleLHS, 
                            std::vector<size_t> const &shiftableItemIndices);

        static void visitReduction(size_t idx, SRConflict &context);
};

inline size_t SRConflict::nConflicts()
{
    return s_nConflicts;
}

inline std::ostream &operator<<(std::ostream &out, SRConflict const &conflict)
{
    return conflict.insert(out);
}

#endif
