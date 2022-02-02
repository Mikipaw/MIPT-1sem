#include <stdio.h>
#include <math.h>
#include <assert.h>

#define true 1
#define false 0

/*!
 * @mainpage
 *  \brief     Solve square equation
 *  \details   This program is used to solve the square equations ax^2 + bx + c = 0
 *  \author    Michael Pavlov
 *  \author    Mikhail Pavlov
 *  \version   C99
 *  \date      09.2020
 *  \pre       First initialize the system.
 *  \bug       No
 *  \warning   Improper use can crash your application
 *  \copyright GNU Public License.
 */

const int INFINITIVE   = -8;
const int NO_SOLUTIONS = -10;


/*!
*  \function int solving_linear_equation(double a, double b, double* x)
*  \brief A solving linear equation ax + b = 0 function.
*  \param a a double.
*  \param b a double.
*  \param x a double pointer - solution.
*  \return an integer - number of solutions.
*/
int solving_linear_equation(double a, double b,
                            double* x);

/*!
*  \function int solving_square_equation(double a, double b, double c, double* x1, double* x2)
*  \brief A solving square equation ax^2 + bx + c = 0 function.
*  \param a a double.
*  \param b a double.
*  \param c a double.
*  \param x1 a double pointer - first  solution.
*  \param x2 a double pointer - second solution.
*  \return an integer - number of solutions.
*/
int solving_square_equation(double a, double b, double c,
                            double* x1, double* x2);


double input_double(char var_name);
int input_int(char var_name);

//!Checking for equality of 2 double numbers.
int IsEqual(double var_name, double number);

void Test_linear_equation();
void Test_square_equation();
void Test();

void Interface();

int main() {
    Test();
    Interface();
    return 0;
}

double input_double(char var_name){
    printf("Enter %c:\n", var_name);
    double result = 0;
    assert(scanf("%lf", &result) == 1);
    return result;
}

int IsEqual(double var_name, double number){
    double epsilon = 10e-6;
    if(var_name < number + epsilon && var_name > number - epsilon) return true;
    else return false;
}

int input_int(char var_name){
    printf("Enter %c:\n", var_name);

    int result = 0;
    assert(scanf("%d", &result));

    return result;
}

int solving_square_equation(double a, double b, double c, double* x1, double* x2){

    assert (x1 != NULL);
    assert (x1 != x2);

    if (!a){
        *x2 = NAN;
        return solving_linear_equation(b, c, x1);
    }
    else if(c == 0){
        *x1 = 0;
        return solving_linear_equation(a, b, x2) + 1;
    }
    double D = b*b - 4 * a * c;
    if(D < 0){
        *x1 = NAN;
        *x2 = NAN;
        return NO_SOLUTIONS;
    }
    if(IsEqual(D, 0)){
        *x1 = -b*1.00 / (2*a);
        *x2 = NAN;
        return 1;
    }
    *x1 = (-b - sqrt(D))/(2*a);
    *x2 = (-b + sqrt(D))/(2*a);
    return 2;
}

int solving_linear_equation(double a, double b, double* x){
    if (IsEqual(a, 0) &&  IsEqual(b, 0)) return INFINITIVE;
    if (IsEqual(a, 0) && !IsEqual(b, 0)) return NO_SOLUTIONS;
    *x = -b/a;
    return 1;
}

void Test_linear_equation(){
    double a = 0, b = 0;
    double x = NAN;
    int result = solving_linear_equation(a, b, &x);
    assert(INFINITIVE == result);

    b = 138994;
    result = solving_linear_equation(a, b, &x);
    assert(result == NO_SOLUTIONS);

    a = 22, b = 0;
    result = solving_linear_equation(a, b, &x);
    assert(result == 1);
    assert(IsEqual(x, 0));

    a = 20, b = 13;
    result = solving_linear_equation(a, b, &x);
    assert(result == 1);
    assert(IsEqual(x, -0.65));

    a = 9, b = -11;
    result = solving_linear_equation(a, b, &x);
    assert(result == 1);
    assert(x > 1.222 && x < 1.223);

    fprintf(stderr, "Test linear equation is OK!\n");

}

void Test_square_equation() {
    double a = 0, b = 0, c = 0;
    double x1 = NAN, x2 = NAN;
    int result = solving_square_equation(a, b, c, &x1, &x2);
    assert(result == INFINITIVE);

    c = -12;
    result = solving_square_equation(a, b, c, &x1, &x2);
    assert(result == NO_SOLUTIONS);

    b = 12;
    x2 = 0;
    result = solving_square_equation(a, b, c, &x1, &x2);
    assert(result == 1);
    assert(IsEqual(x1, 1) && isnan(x2));

    a = 1, c = 0;
    result = solving_square_equation(a, b, c, &x1, &x2);
    assert(result == 2);
    assert(IsEqual(x1, 0) && IsEqual(x2, -12));

    c = 36;
    result = solving_square_equation(a, b, c, &x1, &x2);
    assert(result == 1);
    assert(IsEqual(x1, -6) && isnan(x2));

    b = -13;
    result = solving_square_equation(a, b, c, &x1, &x2);
    assert(result == 2);
    assert(IsEqual(x1, 4) && IsEqual(x2, 9));

    c = 120;
    x1 = 0, x2 = 0;
    result = solving_square_equation(a, b, c, &x1, &x2);
    assert(result == NO_SOLUTIONS);
    assert(isnan(x1) && isnan(x2));

    c = 3.3;
    b = -3.7;
    x1 = 0, x2 = 0;
    result = solving_square_equation(a, b, c, &x1, &x2);
    assert(result == 2);
    assert(IsEqual(x1, 1.5) && IsEqual(x2, 2.2));

    fprintf(stderr, "Test square equation is OK!\n");
}

void Test(){
    Test_linear_equation();
    Test_square_equation();
    fprintf(stderr, "\nAll tests are OK!\n");
}

void Interface(){
    double a = 0, b = 0, c = 0;
    int number_of_solutions = 0;

    //#User have to enter coefficients in console.
    a = input_double('a');
    b = input_double('b');
    c = input_double('c');

    //#Program shows the result equation.
    if     (b >= 0 && c >= 0) printf("Your equation is:\n %.2lfx^2 + %.2lfx + %.2lf = 0\n", a, +b, +c);
    else if(b <  0 && c >= 0) printf("Your equation is:\n %.2lfx^2 - %.2lfx + %.2lf = 0\n", a, -b, +c);
    else if(b >= 0 && c <  0) printf("Your equation is:\n %.2lfx^2 + %.2lfx - %.2lf = 0\n", a, +b, -c);
    else if(b <  0 && c <  0) printf("Your equation is:\n %.2lfx^2 - %.2lfx - %.2lf = 0\n", a, -b, -c);

    double x1 = NAN;
    double x2 = NAN;

    number_of_solutions = solving_square_equation(a, b, c, &x1, &x2);
    if (number_of_solutions == NO_SOLUTIONS){
        printf ("There are no solutions\n");
        return;
    }

    //#Program shows the results.
    if (number_of_solutions >= 0)          printf("Number of solutions: %d\n", number_of_solutions);
    if       (isnan(x2) && !isnan(x1))     printf("Solution is %lf\n", x1);
    else if (!isnan(x2))                   printf("Solutions are %lf and %lf\n", x1, x2);
    if (number_of_solutions == INFINITIVE) printf("There are infinite number of solutions\n");
}
