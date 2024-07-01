#include <stdio.h>

int main()
{
	int price = 0;
	printf("Please enter the amount($)");
	scanf("%d", &price);
	int change = 100 - price;
	printf("The change is $%d", change);
	return 0;
}
