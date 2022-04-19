/**
 * print Celsius-Fahrenheit table
 * F = 9 / 5 * C + 32
 */

#include <stdio.h>

static float lower = -20;
static float upper = 150;
static float step = 10;

int main() {
	float fahr, celsius;

	puts("Celsius\tFahrenheit");
	celsius = lower;
	while (celsius <= upper) {
		fahr = 9.0 / 5.0 * celsius + 32.0;
		printf("%7.0f\t%10.1f\n", celsius, fahr);
		celsius += step;
	}
}
