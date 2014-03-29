#ifndef _H_STORMY_H_FOR_SHANNON_COMPLEX_HEADER_
#define _H_STORMY_H_FOR_SHANNON_COMPLEX_HEADER_

#include <math.h>

class ComplexNumber
{
public:
	ComplexNumber()
	{
		real=img=0;
	}

	ComplexNumber(double real, double img)
	{
		this->real=real;this->img=img;
	}

	ComplexNumber multiply(ComplexNumber n)
	{
		// (x + yi)(u + vi) = (xu – yv) + (xv + yu)i.
		ComplexNumber result;
		result.real = (real*n.real - img*n.img);
		result.img = (real*n.img + img*n.real);
		return result;
	}
	ComplexNumber add(ComplexNumber n)
	{
		ComplexNumber result(n.real+real, n.img+img);
		return result;
	}
	double length()
	{
		return sqrt(real*real+img*img);
	}

	double real, img;
};

#endif
