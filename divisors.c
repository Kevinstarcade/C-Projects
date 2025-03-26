#include<stdio.h>

void divisors(int num) {
	if (num >= 1) {
		printf("1");
		for (int i = 2; i <= num; ++i) {
			if (num % i == 0) {
				printf(" %d", i);
			}
		}
	}
	printf("\n");
}

int main() {
	int num;
	scanf("%d", &num);
	divisors(num);
	return 0;
}
