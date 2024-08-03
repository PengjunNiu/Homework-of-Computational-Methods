#include <stdio.h>
#include <math.h>

double riemann_integral(double (*f)(double), double a, double b, int n) {
    double dx = (b - a) / n;  // ����ÿ��С���εĿ��
    double sum = 0.0;
    double x;

    for (int i = 0; i < n; i++) {
        x = a + i * dx;  // ����ÿ��С���ε���߽�
        sum += f(x) * dx;  // �߶ȳ��Կ�ȣ��ۼӵ��ܺ���
    }

    return sum;
}

double lagrange_integral(double (*f)(double),double a, double b){
	double c=(2*a+b)/3;
	double d=(a+2*b)/3;
	return (b-a)/8*(f(a)+3*f(c)+3*f(d)+f(b));
}

// ʾ��������f(x) = x^2
double example_function(double x) {
    return x * x;
}


int main() {
    double a = 0.0;  // ��������
    double b = 1.0;  // ��������
    int n = 100000;     // С���ε�����

    double result_riemann = riemann_integral(example_function, a, b, n);
    double result_lagrange = lagrange_integral(example_function, a, b);

    printf("riemann_result : %.4lf\n", result_riemann);
    printf("lagrange_result: %.4lf\n", result_lagrange);

    return 0;
}
