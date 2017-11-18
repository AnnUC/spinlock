#include <stdio.h>
#include <stdlib.h>

int main() {
	int i = 1;
	long li = i;
	li = (li<<32) + 1;
	printf("%ld\n",li);
}
