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
    return a*a;
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
double g(double x)
{
    return 64;
}
int main (void)
{
    double b = root(f, g, 0, 100, 0.00001);
    printf("%f\n", b);
    double a = integral(r, -10, 10, 0.00001);
    printf("%f", a);
    return 0;
}
