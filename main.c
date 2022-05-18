#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"

extern void testroot(int argc, const char *argv[], int i);
extern void testInteg(int argc, const char *argv[], int i);
extern int keys[];

// precision-constant for root calculation
double eps1 = 0.0001;
// precision-constant for integral calculation
double eps2 = 0.0001;


// calculate f(x)-g(x)=0 root with eps1-precision on segment [a; b]
// using signs of 1st and 2st derivatives. Tangent method
double root(double (*f)(double), double (*g)(double),
            double (*f1)(double), double (*g1)(double),
            double a, double b, double eps) {

    // Prepare values for F'() and F''() signs checking
    double fga = f(a) - g(a);
    double fgb = f(b) - g(b);
    double fmid = f((a + b) / 2) - g((a + b) / 2);
    double midf = (fga + fgb) / 2;
    int cond1 = (fga < 0);
    int cond2 = (fmid < midf);
    double c;
    unsigned long long cnt = 0;

    // F'(x) * F''(x) < 0
    if(cond1 ^ cond2) {
        c = a;
        while((f(c + eps) - g(c + eps)) * (f(c) - g(c)) > 0) {
            c = c - (f(c) - g(c)) / (f1(c) - g1(c));
            cnt++;
        }
    }

    // F'(x) * F''(x) > 0
    else {
        c = b;
        while((f(c - eps) - g(c - eps)) * (f(c) - g(c)) > 0) {
            c = c - (f(c) - g(c)) / (f1(c) - g1(c));
            cnt++;
        }
    }
    if(keys[0])
    	printf("Roots: (%0.5lf, %0.5lf)\n", c, f(c) - g(c));
    if(keys[1])
    	printf("Iterations: %lld\n", cnt);

    return c;
}


// Calculate definite integral of function f on segment [a, b]
// with eps2-precision
double integral(double (*f)(double), double a, double b, double eps) {
    int n = 10;
    double h1 = (b - a) / n;
    double s1 = f(a) / 2 + f(b) / 2;
    double s2 = 0;

    // first partition
    for(int i = 1; i < n; i++)
        s1 += f(a + i*h1);
    double i2n = 0;
    double in = s1 * h1;

    // increase n, integral approximation
    while(1) {
        s2 = 0;
        for(int i = 0; i < n; i++)
            s2 += f(a + i*h1 + h1/2);

        i2n = (s1 + s2) * h1 / 2;

        if(fabs(i2n - in) < eps * 3)
            break;
        n *= 2;
        h1 = h1 / 2;
        in = i2n;
        s1 += s2;
    }

    return i2n;
}


// getting intersection roots of (f1, f3), (f2, f3), (f1, f2)
// calculation square via integral
void run(void) {
    double p1 = root(f1, f3, pf1, pf3, 0.1, 1, eps1);
    double p2 = root(f2, f3, pf2, pf3, 1, 2, eps1);
    double p3 = root(f1, f2, pf1, pf2, 2, 3, eps1);

    double s1 = integral(f1, p1, p2, eps2) - integral(f3, p1, p2, eps2);
    double s2 = integral(f1, p2, p3, eps2) - integral(f2, p2, p3, eps2);
    double s = s1 + s2;

	printf("Area: %0.3lf\n", s);
}


// execution options processing, call appropriate functions
int main(int argc, const char * argv[]) {
	// running with "-help" flag
	if(argc >= 2 && strcmp(argv[1], "--help") == 0) {
		printf("--help and -h\n");
        printf("--root and -r\n");
        printf("--iterations and -i\n");
        printf("--test-root and -R\n");
        printf("--test-integral and -I\n");
		return 0;
	}
	// other options
	for(int i = 1; i < argc; i++) {
		if(strcmp(argv[i], "--root") == 0)
			keys[0] = 1;
		else if(strcmp(argv[i], "--iterations") == 0)
			keys[1] = 1;
		else if(strcmp(argv[i], "--test-root") == 0)
			testroot(argc, argv, i + 1);
		else if(strcmp(argv[i], "--test-integral") == 0) {
			testInteg(argc, argv, i + 1);
			return 0;
		}
	}

	// default execution
    run();
    return 0;
}
