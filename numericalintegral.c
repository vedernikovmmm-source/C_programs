#include <math.h>
#include <stdio.h>
#include <string.h>

double Integral(double (*f)(double), 
    double from, 
    double to, 
    double step)
{
    double sum = 0;
    if (from > to)
    {
        return -Integral(f, to, from, step);
    }
    for (double x = from; x < to; x += step)
    {
        double s = (f(x) + f(x + step)) * step / 2;
        sum += s;
    }
    return sum;
    
}

double square(double x)
{
    return x * x;
}

double cube(double x)
{
    return x * x * x;
}

int main()
{
    double res;
    double from, to, step;
    double (*f)(double);
    char chs[20];
    printf("Function (sin, cos, tan, asin, acos, atan, exp, log (aka ln), sqrt, square, cube): ");
    scanf("%s", chs);
    if (strcmp(chs, "sin") == 0)
        f = sin;
    else if (strcmp(chs, "cos") == 0)
        f = cos;
    else if (strcmp(chs, "sqrt") == 0)
        f = sqrt;
    else if (strcmp(chs, "square") == 0)
        f = square;
    else if (strcmp(chs, "cube") == 0)
        f = cube;
    else if (strcmp(chs, "tan") == 0)
        f = tan;
    else if (strcmp(chs, "exp") == 0)
        f = exp;
    else if (strcmp(chs, "log") == 0)
        f = log;
    else if (strcmp(chs, "asin") == 0)
        f = asin;
    else if (strcmp(chs, "acos") == 0)
        f = acos;
    else if (strcmp(chs, "atan") == 0)
        f = atan;
    else
    {
        printf("Unknown function\n");
        return 1;
    }
    printf("From: ");
    scanf("%lf", &from);
    if (f == log && from <= 0)
    {
        printf("Error: log(x) requires x > 0\n");
        return 1;
    }

    printf("To: ");
    scanf("%lf", &to);

    printf("Step: ");
    scanf("%lf", &step);

    res = Integral(f, from, to, step);

    printf("Result: %lf\n", res);

    return 0;
}