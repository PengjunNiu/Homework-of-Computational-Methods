#include <stdio.h>
#include <math.h>

double riemann_integral(double (*f)(double), double a, double b, int n) {
    double dx = (b - a) / n;  // 计算每个小矩形的宽度
    double sum = 0.0;
    double x;

    for (int i = 0; i < n; i++) {
        x = a + i * dx;  // 计算每个小矩形的左边界
        sum += f(x) * dx;  // 高度乘以宽度，累加到总和中
    }

    return sum;
}

double lagrange_integral(double (*f)(double),double a, double b){
	double c=(2*a+b)/3;
	double d=(a+2*b)/3;
	return (b-a)/8*(f(a)+3*f(c)+3*f(d)+f(b));
}

// 示例函数：f(x) = x^2
double example_function(double x) {
    return x * x;
}


int main() {
    double a = 0.0;  // 积分下限
    double b = 1.0;  // 积分上限
    int n = 100000;     // 小矩形的数量

    double result_riemann = riemann_integral(example_function, a, b, n);
    double result_lagrange = lagrange_integral(example_function, a, b);

    printf("riemann_result : %.4lf\n", result_riemann);
    printf("lagrange_result: %.4lf\n", result_lagrange);

    return 0;
}
