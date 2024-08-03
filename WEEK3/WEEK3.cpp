#include<stdio.h>
#include<math.h>
#define a 0
#define b 1
#define e 1.e-15
//�˴�ֱ��define��a/b/e������ɸ�
double fai(double x) {
	//���㷨�� x=0.25*exp(x) ����fai(x)�ɸ���ʵ���������
	return 0.25 * exp(x);
}
double function(){  
	int i;
	double x0 = (a + b) / 2, x1, x2, x, y, d;
	x1 = fai(x0);
	for (i = 0; i < 64; i++) {
		x2 = fai(x1);
		if (fabs(x2 - x1) < e) {
			printf("Totally %d times.\n", i);
			printf("We got the answer: %.16lf", x2);
			return 1;
		}
		d = x2 - 2 * x1 + x0;
		if (fabs(d) > 1.e-20) {
			x = (x0 * x2 - x1 * x1) / d;
			y = fai(x);
			if (fabs(x - y) < e) {
				printf("Totally %d times.\n", i);
				printf("We got the answer: %.16lf", x2);
				return 1;
			}
		}
		x0 = x1;
		x1 = x2;
	}
}

int main() {
	function();
	return 0;
}
