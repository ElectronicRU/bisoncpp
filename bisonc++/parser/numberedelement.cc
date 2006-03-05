#include "parser.ih"

// pos points to $ in what must be $i

bool Parser::numberedElement(unsigned pos, unsigned nElements) 
{
    int idx;                // extract the index, determine its length
    unsigned length  = 1 + extractIndex(&idx, pos + 1);

    string const &idxType = d_rules.sType(idx);

    if (idx <= 0)                   // type of the $i can't be determined
    {
        if (!d_negativeDollarIndices)
            lineMsg() << "In " << d_rules.name() << 
                        ": cannot determine default type of $" << 
                        idx << warning;
    }
    else if (idx > static_cast<int>(nElements)) // $i refers beyond this rule
            lineMsg() << "In  " << d_rules.name() << 
                        ": $" << idx << " used, but the rule has only " << 
                        nElements << " elements" << err;
    else if (!idxType.length())     // $i has no default type
            lineMsg() << "$" << idx << " of `" << d_rules.name() << 
                         "' has no default type-association" << warning;
        
    ostringstream os;
    os << s_semanticValueStack << "[" << indexToOffset(idx, nElements) << "]";
    string replacement = os.str();

    if (idxType.length())
        replacement += "." + idxType;

    d_block.replace(pos, length, replacement);

    return false;           // this is not a $$ variant.
}