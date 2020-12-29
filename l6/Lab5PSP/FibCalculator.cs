using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab5PSP
{
    static class FibCalculator
    {
        const double epsilon = 1e-3;

        static int F(int n)
        {
            int f, f1 = 1, f2 = 1, m = 0;
            while (m < n - 1)
            {
                f = f1 + f2;
                f1 = f2;
                f2 = f;
                ++m;
            }
            return f1;
        }

        static double Fun(double x)
        {
            return Math.Pow(Math.E, -1) - Math.Cos(x);
        }

        public static double Fib(double a, double b)
        {
            double x1, x2, _x, xf1, xf2;
            int k = 0;
            int N = 0;
            double fn1 = 1, fn2 = 1, fn, f = (b - a) / epsilon;

            while (fn1 < f)
            {
                fn = fn1 + fn2;
                fn1 = fn2;
                fn2 = fn;
                ++N;
            }
            bool bix;
            int ix = N & 1;
            if (ix == 1)
                bix = true;
            else
                bix = false;
            x1 = a + (double)F(N - 2) / F(N) * (b - a) - (bix ? -1 : 1) * epsilon / F(N);
            x2 = a + (double)F(N - 1) / F(N) * (b - a) + (bix ? -1 : 1) * epsilon / F(N);
            xf1 = Fun(x1);
            xf2 = Fun(x2);
        P:
            ++k;
            if (xf1 >= xf2)
            {
                ix = (N - k) & 1;
                if (ix == 1)
                    bix = true;
                else
                    bix = false;
                a = x1;
                x1 = x2;
                xf1 = xf2;
                x2 = a + (double)F(N - k - 1) / F(N - k) * (b - a) + (bix ? -1 : 1) * epsilon / F(N - k);
                xf2 = Fun(x2);
            }
            else
            {
                ix = (N - k) & 1;
                if (ix == 1)
                    bix = true;
                else
                    bix = false;
                b = x2;
                x2 = x1;
                xf2 = xf1;
                x1 = a + (double)F(N - k - 2) / F(N - k) * (b - a) - (bix ? -1 : 1) * epsilon / F(N - k);
                xf1 = Fun(x1);
            }
            if (Math.Abs(b - a) <= epsilon)
            {
                _x = (a + b) / 2;
                double result = Fun(_x);
                return result;
            }
            else
                goto P;
        }
    }
}
