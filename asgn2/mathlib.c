#include <stdio.h>
#include <math.h> // Only using M_PI
#include <unistd.h>
#include "mathlib.h"

#define MY_PI M_PI //3.141592653589793
#define EPSILON (1/10000000000)
#define MY_INF 50

/*factorial function*/
double fact_fun(double x){
	double k;
	double fact_num = 1;
	for (k = 1; k <= x; ++k){
		fact_num = fact_num*k;
	}
	return fact_num;

}

/*power function*/
double pow_fun(double x, double my_pow){
	double k;
	double pow_num = 1;
	for (k = 1; k <= my_pow; ++k){
		pow_num = pow_num*x;
	}
	return pow_num;
}

/*exp function*/
static double Exp(double x) {
	double t = 1.0;
	double y = 1.0;

	for (double k = 1.0; t > EPSILON; k += 1.0) {
		t *= x / k;
		y += t;
	}
	return y;
}

/*my_sin*/
double my_sin(double x){
	double val = 0;
	double k;
	for (k = 0; k <= MY_INF; ++k){
		val = val + (pow_fun(-1, k)) * (pow_fun(x, (2*k + 1))) / fact_fun(2*k + 1);
	}
	return val;
}

/*my_cos*/
double my_cos(double x){
	double val = 0;
	double k;
	for (k = 0; k <= MY_INF; ++k){
		val = val + (pow_fun(-1, k)) * (pow_fun(x, (2*k))) / fact_fun(2*k);
	}
	return val;
}

/*my_arcsin*/
double my_arcsin(double x){
        double val = 0;
        double k;

	if (x > 1 || x < -1){
		printf("x is outside of the range.\n");
		return 0;
	}

	for (k = 0; k <= MY_INF; ++k){
		val = val + (fact_fun(2*k) * pow_fun(x, (2*k+1))) /
			(pow_fun(2, (2*k)) * fact_fun(k) * fact_fun(k) * (2*k + 1) );
 	}
	return val;
}

/*my_arccos*/
double my_arccos(double x){
	double val = 0;
	
	if (x > 1 || x < -1){
		printf("x is outside of the range.\n");
		return 0;
	}

	val = MY_PI/2 - my_arcsin(x);

	return val;
}

/*my_arctan*/
double my_arctan(double x){
	double val = 0;
	double k;

	if (x < 0){
		printf("x is outside of the range.\n");
      		return 0;
	}

	for (k = 0; k <= MY_INF; ++k){
		val = val + ( pow_fun(2, (2*k)) * fact_fun(k) * fact_fun(k) * pow_fun(x, (2*k + 1)) )/
			( fact_fun(2*k + 1) * pow_fun((1 + x*x), (k + 1)) );
     	}
     	return val;
}

/*my_log*/
// f(x)  = exp(x)
// f(x)' = d(exp(x))/dx = exp(x)
// Xn+1 = Xn - f(x)/f(x)'
// Using Newton-Raphson method optimizing for f(exp)
// Xn+1 = Xn - (f(x)-f(exp))/f(x)'
// Xn+1 = Xn + (-f(x)+f(exp))/f(x)' taking negative sign inside the bracket
// Xn+1 = Xn + (f(exp) - -f(x))/f(x)'
double my_log(double x){
	double val = 1;
	double k;
	double y;

  	y = x; // Using y for readability

  	for (k = 0; k <= MY_INF; ++k){
    	// Get exp value
    	val = val + (y - Exp(val)) / Exp(val);
  	}	

	return val;
}

