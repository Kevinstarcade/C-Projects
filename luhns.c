#include <stdio.h>
#include <stdlib.h>

int luhns() {
	
	int sum1 = 0;
	int sum2 = 0;
	int toggle = 0;
	char prevChar = getchar();

	for (char c = getchar(); c != '\n'; prevChar = c, c = getchar(), toggle = !toggle) {
		int altSum = 2*(prevChar - '0');
		if (altSum >= 10) altSum -= 9;
		// printf("p: %c, c: %c, altSum: %i\n", prevChar, c, altSum);

		if (toggle){
			sum1 += prevChar - '0';
			sum2 += altSum;
		} else {
			sum2 += prevChar - '0';
			sum1 += altSum;
		}
	}

	// printf("sum1: %d, sum2: %d, toggle: %d, pchar: %c", sum1, sum2, toggle, prevChar);
	
	if (toggle) return (9*sum1)%10 == (prevChar - '0');
	return (9*sum2)%10 == (prevChar - '0');
}

int main() {
	if (luhns()) printf("Valid\n");
	else printf("Invalid\n");
	return 0;
}
