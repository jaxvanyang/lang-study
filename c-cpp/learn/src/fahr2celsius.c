/**
 * print Fahrenheit-Celsius table
 * C = 5 / 9 * (F - 32)
 */

#include <stdio.h>

static float lower = 0;
static float upper = 300;
static float step = 20;

int main() {
	float fahr, celsius;

	puts("Fahrenheit\tCelsius");
	fahr = lower;
	while (fahr <= upper) {
		celsius = (5.0 / 9.0) * (fahr - 32.0);
		printf("%10.0f\t%7.1f\n", fahr, celsius);
		fahr += step;
	}
}
