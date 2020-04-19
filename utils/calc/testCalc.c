
#include <stdio.h> /*printf*/
#include <math.h> /*NAN*/

#include "calc.h" /*sort function*/

#define CORRECT "\033[32m correct \033[0m" /*print correct in green*/
#define WRONG "\033[31m wrong \033[0m" /*print wrong in red*/
#define TEST(a) (a ? CORRECT : WRONG) /*check TEST return value*/

int main(int argc, char *argv[])
{
	double result = 0;
    calcInit ();
	result = Calculate("((-4))");
	printf ("%s = %.2f :%s\n", "((-4))", result, TEST(result == -4));


	result = Calculate("((3 + 2) ^ 2 * 2)");
	printf ("%s = %.2f :%s\n", "(3 + 2) ^ 2 * 2", result, TEST(result == 50));


	result = Calculate("1 + 0 - 2 + 5");
	printf ("%s = %.2f :%s\n", "1 + 0 - 2 + 5", result, TEST(result == 4));


	result = Calculate("8 / 2 * 1 + 5");
	printf ("%s = %.2f :%s\n", "8 / 2 * 1 + 5", result, TEST(result == 9));


	result = Calculate("2 ^ 2 ^ 0");
	printf ("%s = %.2f :%s\n", "2 ^ 2 ^ 0", result, TEST(result == 2));


	result = Calculate("(-8) + (-4)");
	printf ("%s = %.2f :%s\n", "(-8) + (- 4)", result, TEST(result == -12));

	result = Calculate("((-8) + (- 4)) * 0");
	printf ("%s = %.2f :%s\n", "((-8) + (-4 )   ) *   0", result, TEST(result == 0));

	result = Calculate("9-9");
	printf ("%s = %.2f :%s\n", "9 -9", result, TEST(result == 0));

	result = Calculate("9 / 0");
	printf ("%s = %.2f :%s\n", "9 / 0", result, TEST(!(result == result)));

	result = Calculate("8 ^ 2- 3 / ( 4- 8 / 2)");
	printf ("%s = %.2f :%s\n", "8 ^ 2- 3 / ( 4 - 8 / 2)", result, TEST(!(result == result)));


	result = Calculate("-12 - 5");
	printf ("%s = %.2f :%s\n", "-12-5", result, TEST(result == -17));

	result = Calculate("(12 + 5)-(6- 5)");
	printf ("%s = %.2f :%s\n", "(12 + 5) - (6 - 5)", result, TEST(result == 16));

	result = Calculate("-12 * -5");
	printf ("%s = %.2f :%s\n", "-12 * -5", result, TEST(result == 60));



	return 0;
}
