#include <stdio.h>
#include <math.h>
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1)
{
    double F(double x)
    {
        return f(x) - g(x);
    }
    if (((f(a) - g(a))*(f((a+b)/2) - g((a+b)/2) - (f(a) - g(a) + f(b) - g(b))/2)) > 0)
    {
        double c = (a*(f(b) - g(b)) - b*(f(a) - g(a)))/(f(b) - g(b) - f(a) + f(b));
        while (((f(c) - g(c))*(f(c+eps1) - g(c+eps1))) > 0)
        {
            c = (c*(f(b) - g(b)) - b*(f(c) - g(c)))/(f(b) - g(b) - f(c) + g(c));
        }
        return c;
    }
    else
    {
        double c = (a*(f(b) - g(b)) - b*(f(a) - g(a)))/(f(b) - g(b) - f(a) + g(a));
        while (((f(c) - g(c))*(f(c-eps1) - g(c-eps1))) > 0)
        {
            c = (a*(f(c) - g(c)) - c*(f(a) - g(a)))/(f(c) - g(c) - f(a) + g(a));
        }
        return c;
    }
}
double r(double a)
{
    return a*a - 3;
}
double integral(double (*f)(double), double a, double b, double eps2)
{
    int n = 10;
    double f1 = 0;
    double f2 = 0;
    double h = (b-a)/n;
    for (int i = 0; i < n; i++)
    {
        f1 += (f(a+i*h) + f(a+i*h+h))/2;
    }
    f1 *= h;
    while (1)
    {
        n *= 2;
        f2 = 0;
        h = (b-a)/n;
        for (int i = 1; i < n; i+=2)
        {
            f2 += f(a+i*h);
        }
        f2 *= h;
        f2 += f1/2;
        if (fabs(f1-f2)/3 < eps2)
        {
            return f2;
        }
        f1 = f2;
    }
}
double f(double x)
{
    return (x*x)*x;
}
double f2(double x)
{
    return -(x*x);
}
double g(double x)
{
    return 64;
}
double g2(double x)
{
    return -25;
}
double r2(double x)
{
    return 1/x;
}
int main (void)
{
    printf("root: f = x^3, g = 64, a = 0, b = 100, eps1 = 0.00001: \n");
    double b = root(f, g, 0, 100, 0.00001);
    printf("%f\n", b);
    printf("root: f = -x^2, g = -25, a = 1, b = 20, eps1 = 0.0001: \n");
    b = root(f2, g2, 1, 20, 0.0001);
    printf("%f\n", b);
    printf("integral: x^2-3, a = -10, b = 10, eps2 = 0.00001\n");
    b = integral(r, -10, 10, 0.00001);
    printf("%f\n", b);
    printf("integral: 1/x, a = 1, b = 12, eps2 = 0.001\n");
    b = integral(r2, 1, 12, 0.001);
    printf("%f", b);
    return 0;
}
