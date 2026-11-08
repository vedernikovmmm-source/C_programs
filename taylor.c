#include <stdio.h>
#include <math.h>

#define MAX_TAYLOR_TERMS 1000

typedef struct {
    const char *name;
    double (*reference)(double);
    double (*taylor)(double, int);
    double (*precision)(double, int);
} Function;

double exp_taylor(double x, int n);
double sin_taylor(double x, int n);
double cos_taylor(double x, int n);
double csc_taylor(double x, int n);

double csc(double x) {
    return 1.0 / sin(x);
}

double exp_precision(double x, int n) {
    return fabs(exp(x) - exp_taylor(x, n));
}

double sin_precision(double x, int n) {
    return fabs(sin(x) - sin_taylor(x, n));
}

double cos_precision(double x, int n) {
    return fabs(cos(x) - cos_taylor(x, n));
}

double csc_precision(double x, int n) {
    return fabs(1.0 / sin(x) - csc_taylor(x, n));
}

double exp_taylor(double x, int n) {
    double sum = 1.0; 
    double term = 1.0; 

    for (int i = 1; i < n; i++) {
        term *= x / i; 
        sum += term;   
    }

    return sum;
}
double sin_taylor(double x, int n) {
    x = remainder(x, 2.0 * M_PI);
    double sum = 0.0; 
    double term = x;   

    for (int i = 1; i <= n; i++) {
        sum += term;    
        term *= -x * x / ((2 * i) * (2 * i + 1)); 
    }

    return sum;
}
double cos_taylor(double x, int n) {
    x = remainder(x, 2.0 * M_PI);
    double sum = 1.0; 
    double term = 1.0; 

    for (int i = 1; i < n; i++) {
        term *= -x * x / ((2 * i - 1) * (2 * i)); 
        sum += term;    
    }

    return sum;
}
double csc_taylor(double x, int n) {
    static double coefficients[MAX_TAYLOR_TERMS];
    static int coefficients_initialized = 0;

    if (n < 1 || fabs(sin(x)) < 1e-12) {
        return NAN;
    }

    if (n > MAX_TAYLOR_TERMS) {
        n = MAX_TAYLOR_TERMS;
    }

    if (!coefficients_initialized) {
        coefficients[0] = 1.0;
        for (int k = 1; k < MAX_TAYLOR_TERMS; k++) {
            double inverse_factorial = 1.0;
            double coefficient = 0.0;
            for (int j = 1; j <= k; j++) {
                inverse_factorial /= (2.0 * j - 1.0) * (2.0 * j);
                double sign = j % 2 == 1 ? 1.0 : -1.0;
                coefficient += sign * coefficients[k - j] * inverse_factorial;
            }
            coefficients[k] = coefficient;
        }
        coefficients_initialized = 1;
    }

    double reduced_x = remainder(x, 2.0 * M_PI);
    double sign = reduced_x < 0.0 ? -1.0 : 1.0;
    double t = fabs(reduced_x) - M_PI / 2.0;
    double sum = 1.0;
    double term = 1.0;

    for (int i = 1; i < n; i++) {
        term *= coefficients[i] / coefficients[i - 1] * t * t;
        sum += term;
    }

    return sign * sum;
}

Function functions[] = {
    {"exp(x)", exp, exp_taylor, exp_precision},
    {"sin(x)", sin, sin_taylor, sin_precision},
    {"cos(x)", cos, cos_taylor, cos_precision},
    {"csc(x)", csc, csc_taylor, csc_precision}
};

int main() {
    int choice;
    double x;
    double tolerance;
    int max_terms;

    printf("Choose function:\n");
    printf("0 - exp(x)\n");
    printf("1 - sin(x)\n");
    printf("2 - cos(x)\n");
    printf("3 - csc(x)\n");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid choice\n");
        return 1;
    }

    if (choice < 0 || choice > 3) {
        printf("Invalid choice\n");
        return 1;
    }

    printf("Enter x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Invalid x value\n");
        return 1;
    }
    if (!isfinite(x)) {
        printf("x must be a finite number\n");
        return 1;
    }

    printf("Enter calculation tolerance (at least 0.000001): ");
    if (scanf("%lf", &tolerance) != 1) {
        printf("Invalid precision\n");
        return 1;
    }

    if (!isfinite(tolerance) || tolerance < 0.000001) {
        printf("Tolerance must be a finite number greater than or equal to 0.000001\n");
        return 1;
    }

    printf("Enter maximum number of terms (1-1000): ");
    if (scanf("%d", &max_terms) != 1) {
        printf("Invalid maximum number of terms\n");
        return 1;
    }

    if (max_terms < 1 || max_terms > MAX_TAYLOR_TERMS) {
        printf("Maximum number of terms must be between 1 and 1000\n");
        return 1;
    }

    Function f = functions[choice];

    double actual;

    if (choice == 3) {
        if (fabs(sin(x)) < 1e-12) {
            printf("csc(x) is undefined for this x\n");
            return 1;
        }
        actual = 1.0 / sin(x);
    } else {
        actual = f.reference(x);
    }

    if (!isfinite(actual)) {
        printf("The reference value is outside the representable range.\n");
        return 1;
    }

    int terms = 1;
    double result = f.taylor(x, terms);
    double error = f.precision(x, terms);

    while ((!isfinite(error) || error > tolerance) && terms < max_terms) {
        terms++;
        result = f.taylor(x, terms);
        error = f.precision(x, terms);
    }

    printf("\nFunction: %s\n", f.name);
    printf("Requested tolerance: %.12g\n", tolerance);
    printf("Maximum terms: %d\n", max_terms);
    printf("Terms used: %d\n", terms);
    printf("Taylor result: %.12g\n", result);
    printf("Reference value: %.12g\n", actual);
    printf("Absolute error: %.12g\n", error);

    if (!isfinite(error) || error > tolerance) {
        printf("Tolerance was not reached before the maximum number of terms.\n");
    } else {
        printf("Requested tolerance reached.\n");
    }

    return 0;
}