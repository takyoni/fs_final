#pragma once
#include "Iterator.h"
#include "FS.h"
class NTFSIterator :
    public Iterator<Cluster>
{
private:
	FS* ntfs;
    unsigned int Count;
    unsigned int Cursor;
public:
	NTFSIterator(FS* fsItem) :Iterator(fsItem->ClusterCount()) {
        ntfs = fsItem;
        Count = ntfs->ClusterCount();
        Cursor = 0;
    }
    void First() { Cursor = 0; }
    void Next() { Cursor ++; }
    bool IsDone() const { return (Cursor >= Count); }
    Cluster GetCurrent();
};

