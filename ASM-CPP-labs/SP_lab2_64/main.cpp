#include <stdio.h>
#include <math.h>
extern "C" double fullprog(double, float, float);
int main()
{
	float c, d;
	double a, res;
	printf("Enter numbers:\n");
	printf("a = ");
	scanf_s("%lf", &a);
	printf("c = ");
	scanf_s("%f", &c);
	printf("d = ");
	scanf_s("%f", &d);

	if (c > d) {
		if ((d < 0) || (4 * d * a + 1 == 0)) {
			printf("Error!");
			return 0;
		}
		else {
			res = (a + c / d - sqrt(28 * d)) / (4 * d * a + 1);
			printf("\nResult is: %lf\n", res);
		}
	}
	else {
		if ((d < -24) || (d == 0) || (2 * a * c - 4 == 0)) {
			printf("Error!");
			return 0;
		}
		else {
			res = (c / d - sqrt(24 + d) + a) / (2 * a * c - 4);
			printf("\nResult is: %lf\n", res);
		}
	}
	res = fullprog(a, c, d);
	printf("\nResult of fullprog is: %lf\n", res);
	return 0;
}