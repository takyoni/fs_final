#include "Cluster.h"
#include <iostream>
using namespace std;

Cluster::~Cluster()
{
    delete[] content;
}

FileTypeEnum Cluster::GetFileType()
{
    if (content[0] == 0x4D && content[1] == 0x5A) {
        return  FileTypeEnum::Exe;
    }
    else if (content[0] == 0x7F && content[1] == 0x45 && content[2] == 0x4C && content[3] == 0x46) {
        return  FileTypeEnum::Elf;
    }
    else if (content[0] == 0x25 && content[1] == 0x50 && content[2] == 0x44 && content[3] == 0x46) {
        return  FileTypeEnum::Pdf;
    }
    else if (content[0] == 0xFF && content[1] == 0xD8 && content[2] == 0xFF && content[3] == 0xE0) {
        return  FileTypeEnum::Jpeg;
    }
    return FileTypeEnum::Underfind;
}

Cluster::Cluster(BYTE* data, unsigned int num, unsigned int ClusterSize)
{
    content = new BYTE[ClusterSize];
    std::memcpy(content, data, sizeof(BYTE) * ClusterSize);
    clusterNum = num;
}
void Cluster::SetContent(BYTE* data,unsigned int ClusterSize)
{
    content = new BYTE[ClusterSize];
    std::memcpy(content, data, sizeof(BYTE) * ClusterSize);
}
