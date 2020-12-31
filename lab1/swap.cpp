#include <stdio.h>
void swap(int* a, int* b) {

	int temp = *a;

	*a = *b;
	*b = temp;

}



int main() {

	int x;
	int y;

	scanf("%d%d", &x, &y);

	printf("int x = %d, int y = %d\n", x, y);


	swap(&x, &y);

	printf("int x = %d, int y = %d\n", x, y);





	return 0;
}