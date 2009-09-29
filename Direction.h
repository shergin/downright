#pragma once

#include "math.h"
#define pi 3.1415926538

class CDirection
{
public:
	int x;
	int y;
	double GetAngle()
	{
        double a=atan2((double)y,(double)x);
		if(a<0)a+=2*pi;
		a=180*a/pi;
		return a;
	}
	double operator == (CDirection dir)
	{
		double r=GetAngle()-dir.GetAngle();
		if(r<0)r=-r;
		if(r>360)r-=360;
		if(r>180)r=360-r;
		return r;
	}
	bool operator != (const CDirection dir)
	{
		return true;
	}
};
