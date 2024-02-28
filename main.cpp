#include "pch.h"
#include <iostream>
using namespace std;

double friction = 1;
double dt = 0.01;
double punch = 1;


class Mob
{
private:
	double a;
	double vx;
	double vy;
	Object target;

public:
	void Retarget(Object aims[], Pointer pointers[])
	{
		double mindist = 100000000;
		int L = Len(aims);
		for (int i = 0; i < L; i++)
		{
			if (Dist(this, aims[i]) < mindist && Sees(this, aims[i]))
			{
				mindist = Dist(this, aims[i]);
				this->target = aims[i];
			}
		}
		L = Len(pointers);
		for (int i = 0; i < L; i++)
		{

			if (Dist(this, pointers[i]) + pointers[i].getDistance() < mindist && Sees(this, pointers[i]))
			{
				mindist = Dist(this, pointers[i]) + pointers[i].getDistance();
				this->target = pointers[i];
			}
		
		}
	}
	void Velocity(Object punchable[])
	{
		ax = this->a * (this->target.getX() - this->x) / sqrt(pow(this->target.getX() - this->x, 2) + pow(this->target.getY() - this->y, 2));
		ay = this->a * (this->target.getY() - this->y) / sqrt(pow(this->target.getX() - this->x, 2) + pow(this->target.getY() - this->y, 2));
		int L = Len(punchable);
		for (int i = 0; i < L; i++)
		{
			if (this->r + punchable[i].r > Dist(this, punchable[i]))
			{
				ax += punch * (punchable[i].getX() - this->x) / sqrt(pow(punchable[i].getX() - this->x, 2) + pow(punchable[i].getY() - this->y, 2));
				ay += punch * (punchable[i].getY() - this->y) / sqrt(pow(punchable[i].getX() - this->x, 2) + pow(punchable[i].getY() - this->y, 2));
			}
		}
		this->vx += ax * dt;
		this->vy += ay * dt;
	}
	void Move()
	{
		this->x += this->vx * dt;
		this->y += this->vy * dt;
	}
};

class Pointer
{
private:
	int checked;
	Object target;
	double distance;

public:

	void ClearTarget()
	{
		this->checked = 0;
	}
	double getDistance()
	{
		return this->distance;
	}
	void Retarget(Object aims[], Pointer pointers[])
	{
		if (this->checked == 0)
		{
			double mindist = 100000000;
			int L = Len(aims);
			for (int i = 0; i < L; i++)
			{
				if (Dist(this, aims[i]) < mindist && Sees(this, aims[i]))
				{
					mindist = Dist(this, aims[i]);
					this->target = aims[i];
				}
			}
			L = Len(pointers);
			for (int i = 0; i < L; i++)
			{
				if (pointers[i].checked == 0)
				{
					pointers[i].Retarget(aims, pointers);
				}
				else
				{
					if (Dist(this, pointers[i]) + pointers[i].distance < mindist && Sees(this, pointers[i]))
					{
						mindist = Dist(this, pointers[i]) + pointers[i].distance;
						this->target = pointers[i];
					}
				}
			}
			this->checked = 1;
			this->distance = mindist;
		}
	}
};

void PointersRetarget(Object aims[], Pointer pointers[])
{
	int L = Len(pointers);
	for (int i = 0; i < L; i++)
	{
		pointers[i].ClearTarget();
	}
	for (int i = 0; i < L; i++)
	{
		pointers[i].Retarget(aims, pointers);
	}
}



int main()
{
    cout << "Hello World!\n"; 
}

