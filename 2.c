#include <stdio.h>
#include <math.h>
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1)
{
    double F(double x)
    {
        return f(x) - g(x);
    }
    if ((F(a) < 0 && (F((a+b)/2) < (F(a) + F(b))/2)) || (F(a) > 0 && (F((a+b)/2) > (F(a) + F(b))/2)))
    {
        double c = (a*F(b) - b*F(a))/(F(b) - F(a));
        while ((F(c)*F(c+eps1)) > 0)
        {
            c = (c*F(b) - b*F(c))/(F(b) - F(c));
        }
        return c;
    }
    else
    {
        double c = (a*F(b) - b*F(a))/(F(b) - F(a));
        while ((F(c)*F(c-eps1)) > 0)
        {
            c = (a*F(c) - c*F(a))/(F(c) - F(a));
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
    double nsum(int n, double (*f)(double), double a, double b)
    {
        double h = (b-a)/n;
        double sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += (f(a+i*h) + f(a+i*h+h))/2;
        }
        sum *= h;
        return sum;
    }
    f1 = nsum(10, f, a, b);
    double nxt(int n, double (*f)(double), double a, double b, double ff) //n Ч дл€ новой суммы
    {
        double h = (b - a)/n;
        double sum = 0;
        for (int i = 1; i < n; i+=2)
        {
            sum += f(a+i*h);
        }
        sum *= h;
        sum += ff/2;
        return sum;
    }
    while (1)
    {
        n *= 2;
        f2 = nxt(n, f, a, b, f1);
        if (fabs(f1-f2)/3 < eps2)
        {
            return f2;
        }
        f1 = f2;
    }
}
double f(double x)
{
    return x*x;
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
