#ifndef __GRAPHIC_TYPE__HEADER__
#define __GRAPHIC_TYPE__HEADER__

#include "includes.h"

namespace lycee {

	template<typename _Ty>
	class Point;
	
	template<typename _Ty>
	class Size;
	
	template<typename _Ty>
	class Range;
	
	template<typename _Ty>
	class Graph;
	
	enum GraphType {
		Opened,
		Closed,
	};

	template<typename _Ty>
	class Point {
	public:
		typedef _Ty					value_type;
		typedef Point<_Ty>			this_type;

		value_type x;
		value_type y;

		Point() : x(), y() { }
		Point(const value_type &_x, const value_type &_y) : x(_x), y(_y) { }
		Point(const this_type &pt) : x(pt.x), y(pt.y) { }
	
		this_type& operator =(const this_type &rhs) {
			if (this != &rhs) {
				this->x = rhs.x;
				this->y = rhs.y;
			}
			return *this;
		}

		double length() const {
			return sqrt(x*x + y*y);
		}

		this_type& operator +=(const this_type &rhs) {
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}

		this_type& operator -=(const this_type &rhs) {
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}

		this_type& operator *=(const value_type &rhs) {
			this->x *= rhs;
			this->y *= rhs;
			return *this;
		}

		this_type& operator /=(const value_type &rhs) {
			this->x /= rhs;
			this->y /= rhs;
			return *this;
		}
	};

	template<typename _Ty>
	Point<_Ty> distance(const Point<_Ty> &lhs, const Point<_Ty> &rhs) {
		return Point<_Ty>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	typedef Point<int> PointI;
	typedef Point<unsigned int> PointU;
	typedef Point<long> PointL;
	typedef Point<unsigned long> PointUL;
	typedef Point<double> PointD;
	typedef Point<float> PointF;

	// --------------------------------------------------------------------------------

	template<typename _Ty>
	class Range {

	};


}	// lycee
#endif	// __GRAPHIC_TYPE__HEADER__