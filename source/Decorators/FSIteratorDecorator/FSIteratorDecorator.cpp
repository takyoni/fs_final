#include "FSIteratorDecorator.h"

void FSIteratorDecorator::First()
{
	It->First();
	while (!It->IsDone() && It->GetCurrent().GetFileType() != TargetFile) {
		It->Next();
	}

}
void FSIteratorDecorator::Next()
{
	do {
		It->Next();
	} while (!It->IsDone() && It->GetCurrent().GetFileType() != TargetFile);
}
