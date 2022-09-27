#include "System.h"
#include "Shop.h"

void Initialize()
{
	system("mode con cols=100 lines=60");
	Shop();
}

int main()
{
	Initialize();
}