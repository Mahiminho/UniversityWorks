// X = A4 / 4 + C2 - D1 * 2 + K
#include <stdio.h>
#include <cstdint>
extern "C" int calc(long long, long long, long long);
extern "C" int K = 0x616;
int main()
{
	int32_t A, res;
	int16_t C;
	int8_t D;
	//long long A, C, D, res;
	printf("Limiting the values:\nA : [-2147483648;2147483647]\nC : [-32768;32767]\nD : [-128;127]\n\n");
	printf("Enter numbers:\n");
	printf("A = ");
	//scanf_s("%lli", &A);
	scanf_s("%d", &A);
	printf("C = ");
	//scanf_s("%lli", &C);
	scanf_s("%hd", &C);
	printf("E = ");
	//scanf_s("%lli", &D);
	scanf_s("%hhd", &D);
	//if (A < -2147483648 || A > 2147483647 || C < -32768 || C > 32767 || D < -128 || D > 127) {
	//	printf("ERROR\n");
	//	return 0;
	//}
	printf("\nA4 / 4 + C2 - D1 * 2 + K = %d\n", (A / 4 + C - D * 2 + K));
	res = calc(A, C, D);
	printf("\nResult of procedure calc is: %d\n", res);
	return 0;
}
