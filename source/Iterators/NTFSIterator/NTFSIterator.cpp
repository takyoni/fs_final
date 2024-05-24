#include "NTFSIterator.h"

Cluster NTFSIterator::GetCurrent()
{
    Cluster item;
    if (!ntfs->ReadCluster(&item, Cursor)) {
        throw std::invalid_argument("Error read cluster!");
    }
    return item;
}
