#include <stdio.h>
#include <math.h>

#define EPSILON 0.001
#define MAX 66666

double f(double x, double y) {
    return pow(1 - x, 2) + 100 * pow(y - x * x, 2);
}

void gradient(double x, double y, double* grad_x, double* grad_y) {
    *grad_x = 2 * (x - 1) + 200 * (y - x * x) * (-2 * x);
    *grad_y = 200 * (y - x * x);
}

double goldenSectionSearch(double a, double b, double x1, double x2) {
    const double phi = (sqrt(5) - 1) / 2;

    double c = a + (1 - phi) * (b - a);
    double d = a + phi * (b - a);

    double f_c = f(x1 + c, x2);
    double f_d = f(x1 + d, x2);

    while (fabs(b - a) > EPSILON) {
        if (f_c < f_d) {
            b = d;
            d = c;
            c = a + (1 - phi) * (b - a);
            f_d = f_c;
            f_c = f(x1 + c, x2);
        } else {
            a = c;
            c = d;
            d = a + phi * (b - a);
            f_c = f_d;
            f_d = f(x1 + d, x2);
        }
    }

    return (a + b) / 2;
}
double golden_section_search(double a0, double b0,double x,double y) {
	double b=b0;
	double a=a0;
    const double phi = (sqrt(5)-1) / 2; // 黄金分割比例

    double x1 = phi*a+(1-phi)*b; // 计算内点1
    double x2 = a+b-x1; // 计算内点2
	int i=0;
//	f(x1 + c, x2)
    while (fabs(b - a) > EPSILON) {
    	i++;
    	double *p,*q;
    	gradient(x,y,p,q);
        if(f(x+x1*(*p),y+x2*(*q))<f(x+x1*(*p),y+x2*(*q))){
        	b=x2;
        	x2=x1;
        	x1=a+b-x2;
        }else{
        	a=x1;
        	x1=x2;
        	x2=a+b-x2;
        }
    }
	    return (a + b) / 2; // 返回极值点的估计值
}
void steepestDescent(double start_x, double start_y, double alpha) {
    double x = start_x;
    double y = start_y;
    double grad_x, grad_y;
    int i = 0;

    for (i = 0; i < MAX; i++) {
        gradient(x, y, &grad_x, &grad_y);
        double lambda = goldenSectionSearch(0.0, 1.0, x,y);
        x = x - lambda * grad_x;
        y = y - lambda * grad_y;
        if (sqrt(grad_x * grad_x + grad_y * grad_y) < EPSILON) {
            break;
        }
    }

    printf("Optimal point: x = %.2lf, y = %.2lf\n", x, y);
    printf("Number of iterations: %d\n", i);
}

int main() {
    double start_x = 1.0;
    double start_y = 1.1;
    double alpha = 0.75;

    steepestDescent(start_x, start_y, alpha);

    return 0;
}
