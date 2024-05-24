#pragma once
#include "Iterator.h"
#include "Cluster.h"
template<class Type>
class IteratorDecorator :
    public Iterator<Type>
{
protected:
    Iterator<Type>* It;
public:
    IteratorDecorator(Iterator<Type> *it){
        It = it;
    }
    virtual void First() { It->First(); }
    virtual void Next() { It->Next(); }
    virtual bool IsDone() const { return It->IsDone(); }
    virtual Type GetCurrent() { return It->GetCurrent(); }
    ~IteratorDecorator() { delete It; }
};

