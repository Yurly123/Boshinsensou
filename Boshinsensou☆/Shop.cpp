#include "Shop.h"

using namespace std;

void Shop()
{
	while (true)
	{
		PrintLine();
		PrintL("[1] [2]");
		GetInput({ 1,2 });
	}
}