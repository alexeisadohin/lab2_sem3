#ifndef ISORTER_H
#define ISORTER_H

#include "Sequence.h"
#include "ShrdPtr.h"

template <typename T, typename Comparator>
class ISorter {
public:
    virtual void Sort(ShrdPtr<Sequence<T>> sequence, Comparator comp) = 0;
};

#endif //ISORTER_H
