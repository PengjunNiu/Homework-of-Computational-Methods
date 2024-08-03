#include "stdio.h"
#include "math.h"
#define eps 1e-10
/*Powered by: Niu Pengjun*/
int zeros(double a,double b, double c);
bool function(double a,double b, double c,double x,double e);
double x1,x2;
#define eps 1e-10
int main()
{	while(1){
	double a,b,c,e;
	printf("Input a,b,c e:\n");
	scanf("%lf %lf %lf %lf",&a,&b,&c,&e);
	if(a){
		while(a>1e153||b>1e153||c>1e153){
			a/=2;b/=2;c/=2;
		}
	}
	int n=zeros(a,b,c);
	printf("total %d zeros\n",n);
	if(n==1){
		printf("We got: %lf\n",x1);
		if(function(a,b,c,x1,e)){
			printf("Maybe %lf meet the requirement!\n\n",x1);
		}
	}else if(n==2){
		printf("We got %lf %lf\n",x1,x2);
		if(function(a,b,c,x1,e)){
			printf("Maybe %lf meet the requirement!\n",x1);
		}
		if(function(a,b,c,x2,e)){
			printf("Maybe %lf meet the requirement!\n\n",x2);
		}
	}
}
    return 0;
}
int zeros(double a,double b, double c){
	if(a==0){
		if(b==0){
			return 0;
		}else{
			x1=-c/b;
			return 1;
		}
	}else if(b*b<4*a*c){
		return 0;
	}else if(fabs(b*b-4*a*c)<eps){
		x1=-b*(1/(2*a));
		return 1;
	}else{
		double d=sqrt(b*b-4*a*c);
		if(b>0){
			double temp1=1/(b+d),temp2=1/(2*a);
			x1=-2*c*temp1;
			x2=-(b+d)*temp2;
		}else{
			double temp1=1/(2*a),temp2=1/(-b+d);
			x1=(-b+d)*temp1;
			x2=2*c*temp2;
		}
		return 2;
	}
	return -1;
}
bool function(double a,double b, double c,double x,double e){
	if(fabs(a*x*x+b*x+c)<e){
		return true;
	};
	return false;
}
