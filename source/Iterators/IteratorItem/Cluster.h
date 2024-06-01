#pragma once
#include <iostream>
#include "windows.h"
using namespace std;
enum class FileTypeEnum { Underfind, Exe, Pdf, Elf, Jpeg };
class Cluster
{
private:
	unsigned int clusterNum = 0;
	BYTE* content = NULL;

public:
	void SetClusterNum(unsigned int num) {clusterNum = num;}
	void SetContent(BYTE* arr, unsigned int ClusterSize);
	BYTE* GetContent() { return content; };
	unsigned int GetNum() const { return clusterNum; };
	FileTypeEnum GetFileType();
	Cluster(BYTE* data, unsigned int num, unsigned int ClusterSize);
	Cluster() {};
	~Cluster();
};

