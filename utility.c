#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "test.c"

extern double eps1;
extern double eps2;
extern double root(double (*f)(double), double (*g)(double), double (*f1)(double), double (*g1)(double),
                                                                            double a, double b, double eps);
extern double integral(double (*f)(double), double a, double b, double eps);

int keys[4] = {0, 0, 0, 0};

void testroot(int argc, const char *argv[], int i) {
    double (*f[6])(double) = {g0, g1, g2, g3, g4, g5};
    char *separate = ":";
    char param[100];
    int f1, f2;
    double a, b, eps, ans;
    int startParam = 0, endParam = strstr(argv[i], separate) - argv[i];
    strncpy(param, argv[i], endParam);
    f1 = atoi(param);

    startParam = endParam + 1;
    endParam = strstr(argv[i] + startParam, separate) - argv[i];
    strncpy(param, argv[i] + startParam, endParam - startParam);
    f2 = atoi(param);

    startParam = endParam + 1;
    endParam = strstr(argv[i] + startParam, separate) - argv[i];
    strncpy(param, argv[i] + startParam, endParam - startParam);
    a = atof(param);

    startParam = endParam + 1;
    endParam = strstr(argv[i] + startParam, separate) - argv[i];
    strncpy(param, argv[i] + startParam, endParam - startParam);
    b = atof(param);

    startParam = endParam + 1;
    endParam = strstr(argv[i] + startParam, separate) - argv[i];
    strncpy(param, argv[i] + startParam, endParam - startParam);
    eps = atof(param);

    startParam = endParam + 1;
    strncpy(param, argv[i] + startParam, strlen(argv[i] + startParam));
    ans = atof(param);

    double rootOfTest = root(f[f1-1], f[f2-1], f[f1+2], f[f2+2], a, b, eps);
    printf("Root:%lf\n", rootOfTest);
    double abs = fabs(rootOfTest - ans);
    double rel = abs / rootOfTest;
    printf("Abs: %0.4lf\n", abs);
    printf("Rel: %0.4lf\n", rel);
}

void testInteg(int argc, const char *argv[], int i) {
    double (*f[3])(double) = {g0, g1, g2};
    char *separate = ":";
    char param[100];
    int f1;
    double a, b, eps, ans;
    int startParam = 0, endParam = strstr(argv[i], separate) - argv[i];
    strncpy(param, argv[i], endParam);
    f1 = atoi(param);

    startParam = endParam + 1;
    endParam = strstr(argv[i] + startParam, separate) - argv[i];
    strncpy(param, argv[i] + startParam, endParam - startParam);
    a = atof(param);

    startParam = endParam + 1;
    endParam = strstr(argv[i] + startParam, separate) - argv[i];
    strncpy(param, argv[i] + startParam, endParam - startParam);
    b = atof(param);

    startParam = endParam + 1;
    endParam = strstr(argv[i] + startParam, separate) - argv[i];
    strncpy(param, argv[i] + startParam, endParam - startParam);
    eps = atof(param);

    startParam = endParam + 1;
    strncpy(param, argv[i] + startParam, strlen(argv[i] + startParam));
    ans = atof(param);

    double integ = integral(f[f1-1], a, b, eps);
    printf("integral: %0.4lf\n", integ);
    double abs = fabs(integ - ans);
    double rel = abs / integ;
    printf("Abs: %0.4lf\n", abs);
    printf("Rel: %0.4lf\n", rel);
}

