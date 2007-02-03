#include "writer.ih"

void Writer::transitions(Next::Vector const &next, ostream &out)
{
    for_each(next.begin(), next.end(), 
             FnWrap1c<Next const &, ostream &>(transition, out));
}
