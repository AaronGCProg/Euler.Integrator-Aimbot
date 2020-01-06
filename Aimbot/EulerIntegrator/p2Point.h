// ----------------------------------------------------
// Point class    -----------
// ----------------------------------------------------

#ifndef __P2POINT_H__
#define __P2POINT_H__

#include "p2Defs.h"
#include <math.h>
template<class TYPE>
class p2Point
{
public:

	TYPE x, y;

	p2Point()
	{}

	p2Point(const p2Point<TYPE>& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	p2Point(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;
	}

	p2Point& create(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;

		return(*this);
	}

	// Math ------------------------------------------------

	//Operators between p2Points-------
	p2Point operator -(const p2Point &v) const
	{
		p2Point r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	p2Point operator + (const p2Point &v) const
	{
		p2Point r;

		r.x = x + v.x;
		r.y = y + v.y;

		return(r);
	}

	p2Point operator * (const p2Point& v) const
	{
		p2Point r;

		r.x = x * v.x;
		r.y = y * v.y;

		return(r);
	}

	const p2Point& operator -=(const p2Point &v)
	{
		x -= v.x;
		y -= v.y;

		return(*this);
	}

	const p2Point& operator +=(const p2Point &v)
	{
		x += v.x;
		y += v.y;

		return(*this);
	}

	bool operator ==(const p2Point& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator !=(const p2Point& v) const
	{
		return (x != v.x || y != v.y);
	}
	//Operators w/ Template -----------

	p2Point operator - (const TYPE& v) const
	{
		p2Point r;

		r.x = x - v;
		r.y = y - v;

		return(r);
	}

	p2Point operator + (const TYPE& v) const
	{
		p2Point r;

		r.x = x + v;
		r.y = y + v;

		return(r);
	}

	p2Point operator * (const TYPE& v) const
	{
		p2Point r;

		r.x = x * v;
		r.y = y * v;

		return(r);
	}


	const p2Point& operator +=(const TYPE& v)
	{
		x += v;
		y += v;

		return(*this);
	}

	const p2Point& operator -=(const TYPE& v)
	{
		x -= v;
		y -= v;

		return(*this);
	}

	const p2Point& operator *=(const TYPE& v)
	{
		x *= v;
		y *= v;

		return(*this);
	}



	// Utils ------------------------------------------------
	bool IsZero() const
	{
		return (x == 0 && y == 0);
	}

	p2Point& SetToZero()
	{
		x = y = 0;
		return(*this);
	}

	p2Point& Negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}

	p2Point& Abs()
	{
		x = abs(x);
		y = abs(y);

		return(*this);
	}

	p2Point GetInverse()
	{
		p2Point r;
		r.x = -x;
		r.y = -y;

		return(r);
	}


	double Dot(p2Point& v)
	{
		return((x * v.x) + (y * v.y));
	}

	double Module()
	{
		return sqrtf((x * x) + (y * y));
	}

	void Normalize()
	{
		double mod = Module();
		x = (x / mod);
		y = (y / mod);
	}


	// Distances ---------------------------------------------
	TYPE DistanceTo(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return sqrtf((fx*fx) + (fy*fy));
	}

	TYPE DistanceNoSqrt(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (fx*fx) + (fy*fy);
	}

	TYPE DistanceManhattan(const p2Point& v) const
	{
		return abs(v.x - x) + abs(v.y - y);
	}
};

typedef p2Point<int> iPoint;
typedef p2Point<float> fPoint;
typedef p2Point<double> dPoint;

#endif // __P2POINT_H__