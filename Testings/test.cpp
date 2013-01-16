#include <cstdio>
#include <NumericAttribute.h>

int main()
{
	NumericAttribute numAttr("Rado", 13);

	printf("%s: %d", numAttr.getName().cstr(), numAttr.getValue());

	return 0;
}