using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab5PSP
{
    static class FibCalculator
    {

        public static int F(int n)
        {
            n++;
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
            return Math.Cos(x);
        }

        public static double Fib(double a, double b, int n)
        {
            double a1 = a;
            double b1 = b;

            for (int i = 1; i <= n; i++)
            {
                double L = a1 + 1.0 * F(n - i - 1) / F(n - i + 1) * (b1 - a1);
                double M = a1 + 1.0 * F(n - i) / F(n - i + 1) * (b1 - a1);

                double FL = Fun(L);
                double FM = Fun(M);

                if (FL < FM) b1 = M;
                else a1 = L;

                Console.WriteLine($"{FL}:{FM}");
            }

            return (a1 + b1) / 2;
        }
    }
}