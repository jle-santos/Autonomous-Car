#include "stdafx.h"
#include "CCar.h"


CCar::CCar()
{
}

void CCar::drive()
{
	_motors.forward(2);	
}


CCar::~CCar()
{
}
