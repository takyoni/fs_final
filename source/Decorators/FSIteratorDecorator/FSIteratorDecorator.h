#pragma once
#include "IteratorDecorator.h"
#include "Cluster.h"
#include <iostream>
class FSIteratorDecorator:public IteratorDecorator<Cluster>
{
private:
	FileTypeEnum TargetFile;
public:
	FSIteratorDecorator(Iterator<Cluster>*it, FileTypeEnum targetFile): IteratorDecorator(it){
		TargetFile = targetFile;
	}
	void First();
	void Next();
};

