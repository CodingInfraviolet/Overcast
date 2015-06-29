#include "stdafx.h"
#include "matrixd.h"
#include <cmath>

namespace math
{
	template<class T> T dot(const tmp::_vec2<T>& v1, const tmp::_vec2<T>& v2)
	{
		return v1.x*v2.x + v1.y*v2.y;
	}

	template<class T> T dot(const tmp::_vec3<T>& v1, const tmp::_vec3<T>& v2)
	{
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}

	template<class T> T dot(const tmp::_vec4<T>& v1, const tmp::_vec4<T>& v2)
	{
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w;
	}

	template<class T> tmp::_vec3<T> cross(const tmp::_vec3<T>& v1, const tmp::_vec3<T>& v2)
	{
		return tmp::_vec3<T>(v1.y*v2.z - v1.z*v2.y,
			v1.z*v2.x - v1.x*v2.z,
			v1.x*v2.y - v1.y*v2.x);
	}

	//Force instantiatios for the following:
	template class tmp::_vec2<float>;
	template class tmp::_vec3<float>;
	template class tmp::_vec4<float>;
	template class tmp::_vec2<int>;
	template class tmp::_vec3<int>;
	template class tmp::_vec4<int>;
	template class tmp::_vec2<double>;
	template class tmp::_vec3<double>;
	template class tmp::_vec4<double>;
	template class tmp::_vec2<long long>;
	template class tmp::_vec3<long long>;
	template class tmp::_vec4<long long>;
	template class tmp::_vec2<short>;
	template class tmp::_vec3<short>;
	template class tmp::_vec4<short>;

	template float dot<float>(const tmp::_vec2<float>&, const tmp::_vec2<float>&);
	template float dot<float>(const tmp::_vec3<float>&, const tmp::_vec3<float>&);
	template float dot<float>(const tmp::_vec4<float>&, const tmp::_vec4<float>&);

	template double dot<double>(const tmp::_vec2<double>&, const tmp::_vec2<double>&);
	template double dot<double>(const tmp::_vec3<double>&, const tmp::_vec3<double>&);
	template double dot<double>(const tmp::_vec4<double>&, const tmp::_vec4<double>&);

	template int dot<int>(const tmp::_vec2<int>&, const tmp::_vec2<int>&);
	template int dot<int>(const tmp::_vec3<int>&, const tmp::_vec3<int>&);
	template int dot<int>(const tmp::_vec4<int>&, const tmp::_vec4<int>&);

	template long long dot<long long>(const tmp::_vec2<long long>&, const tmp::_vec2<long long>&);
	template long long dot<long long>(const tmp::_vec3<long long>&, const tmp::_vec3<long long>&);
	template long long dot<long long>(const tmp::_vec4<long long>&, const tmp::_vec4<long long>&);

	template short dot<short>(const tmp::_vec2<short>&, const tmp::_vec2<short>&);
	template short dot<short>(const tmp::_vec3<short>&, const tmp::_vec3<short>&);
	template short dot<short>(const tmp::_vec4<short>&, const tmp::_vec4<short>&);

	template tmp::_vec3<float> cross<float>(const tmp::_vec3<float>&, const tmp::_vec3<float>&);
	template tmp::_vec3<double> cross<double>(const tmp::_vec3<double>&, const tmp::_vec3<double>&);
	template tmp::_vec3<int> cross<int>(const tmp::_vec3<int>&, const tmp::_vec3<int>&);
	template tmp::_vec3<int> cross<int>(const tmp::_vec3<int>&, const tmp::_vec3<int>&);
	template tmp::_vec3<long long> cross<long long>(const tmp::_vec3<long long>&, const tmp::_vec3<long long>&);
	template tmp::_vec3<short> cross<short>(const tmp::_vec3<short>&, const tmp::_vec3<short>&);
	//

	const matReal matOne = 1, matTwo = 2, matThree = 3;

	namespace tmp
	{

		template<class T> _vec2<T>::_vec2()
		{
			reset();
		}

		template<class T> _vec2<T>::_vec2(const T x_, const T y_)
		{
			x = x_;
			y = y_;
		}

		template<class T> _vec2<T>::_vec2(const T n)
		{
			x = n;
			y = n;
		}

		template<class T> matReal _vec2<T>::angle() const
		{
			return matReal(std::atan2(y, x));
		}

		template<class T> T _vec2<T>::lengthSquared() const
		{
			return x*x + y*y;
		}

		template<class T> matReal _vec2<T>::length() const
		{
			return matReal(std::sqrt(x*x + y*y));
		}

		template<class T> matReal _vec2<T>::distance(const _vec2<T>& v) const
		{
			return matReal(std::sqrt((x - v.x)*(x - v.x) + (y - v.y)*(y - v.y)));
		}

		template<class T> T _vec2<T>::distanceSquared(const _vec2<T>& v) const
		{
			return (x - v.x)*(x - v.x) + (y - v.y)*(y - v.y);
		}

		template<class T> _vec2<T> _vec2<T>::operator * (const T n) const
		{
			return _vec2<T>(x*n, y*n);
		}

		template<class T> _vec2<T> _vec2<T>::operator / (const T n) const
		{
			return _vec2<T>(x / n, y / n);
		}

		template<class T> _vec2<T> _vec2<T>::operator + (const T n) const
		{
			return _vec2<T>(x + n, y + n);
		}

		template<class T> _vec2<T> _vec2<T>::operator - (const T n) const
		{
			return _vec2<T>(x - n, y - n);
		}

		template<class T> void  _vec2<T>::operator *= (const T n)
		{
			x *= n;
			y *= n;
		}

		template<class T> void _vec2<T>::operator /= (const T n)
		{
			x /= n;
			y /= n;
		}

		template<class T> void _vec2<T>::operator += (const T n)
		{
			x += n;
			y += n;
		}

		template<class T> void _vec2<T>::operator -= (const T n)
		{
			x -= n;
			y -= n;
		}

		template<class T> bool _vec2<T>::operator == (const _vec2<T>& vec) const
		{
			return x == vec.x && y == vec.y;
		}

		template<class T> bool _vec2<T>::operator == (T f) const
		{
			return x == f && y == f;
		}

		template<class T> bool _vec2<T>::operator != (const _vec2<T>& vec) const
		{
			return x != vec.x || y != vec.y;
		}

		template<class T> bool _vec2<T>::operator != (T f) const
		{
			return x != f || y != f;
		}

		template<class T> _vec2<T>& _vec2<T>::normalize()
		{
			matReal lenDivisor = matOne / length();
			x = T(x * lenDivisor);
			y = T(y * lenDivisor);
			return *this;
		}

		template<class T> _vec2<T> _vec2<T>::operator + (const _vec2<T>& vec) const
		{
			return _vec2<T>(x + vec.x, y + vec.y);
		}

		template<class T> _vec2<T> _vec2<T>::operator - (const _vec2<T>& vec) const
		{
			return _vec2<T>(x - vec.x, y - vec.y);
		}

		template<class T> _vec2<T> _vec2<T>::operator * (const _vec2<T>& vec) const
		{
			return _vec2<T>(x*vec.x, y*vec.y);
		}

		template<class T> _vec2<T> _vec2<T>::operator / (const _vec2<T>& vec) const
		{
			return _vec2<T>(x / vec.x, y / vec.y);
		}

		template<class T> void _vec2<T>::operator += (const _vec2<T>& vec)
		{
			x += vec.x;
			y += vec.y;
		}

		template<class T> void _vec2<T>::operator -= (const _vec2<T>& vec)
		{
			x -= vec.x;
			y -= vec.y;
		}

		template<class T> void _vec2<T>::operator *= (const _vec2<T>& vec)
		{
			x *= vec.x;
			y *= vec.y;
		}

		template<class T> void _vec2<T>::operator /= (const _vec2<T>& vec)
		{
			x /= vec.x;
			y /= vec.y;
		}

		template<class T> _vec2<T> _vec2<T>::xy() const { return _vec2<T>(x, y); }
		template<class T> _vec2<T> _vec2<T>::yx() const { return _vec2<T>(y, x); }

		template<class T> void _vec2<T>::reset()
		{
			x = 0;
			y = 0;
		}

		template<class T> _vec3<T>::_vec3()
		{
			reset();
		}

		template<class T> _vec3<T>::_vec3(const T x_, const T y_, const T z_)
		{
			x = x_;
			y = y_;
			z = z_;
		}


		template<class T> _vec3<T>::_vec3(const T t)
		{
			x = t;
			y = t;
			z = t;
		}

		template<class T> T _vec3<T>::lengthSquared() const
		{
			return x*x + y*y + z*z;
		}

		template<class T> matReal _vec3<T>::length() const
		{
			return matReal(std::sqrt(x*x + y*y + z*z));
		}

		template<class T> matReal _vec3<T>::distance(const _vec3<T>& v) const
		{
			return matReal(std::sqrt((x - v.x)*(x - v.x) + (y - v.y)*(y - v.y) + (z - v.z)*(z - v.z)));
		}

		template<class T> T _vec3<T>::distanceSquared(const _vec3<T>& v) const
		{
			return (x - v.x)*(x - v.x) + (y - v.y)*(y - v.y) + (z - v.z)*(z - v.z);
		}

		template<class T> _vec3<T> _vec3<T>::operator * (const T n) const
		{
			return _vec3<T>(x*n, y*n, z*n);
		}

		template<class T> _vec3<T> _vec3<T>::operator / (const T n) const
		{
			return _vec3<T>(x / n, y / n, z / n);
		}

		template<class T> _vec3<T> _vec3<T>::operator + (const T n) const
		{
			return _vec3<T>(x + n, y + n, z + n);
		}

		template<class T> _vec3<T> _vec3<T>::operator - (const T n) const
		{
			return _vec3<T>(x - n, y - n, z - n);
		}

		template<class T> void _vec3<T>::operator *= (const T n)
		{
			x *= n;
			y *= n;
			z *= n;
		}

		template<class T> void _vec3<T>::operator /= (const T n)
		{
			x /= n;
			y /= n;
			z /= n;
		}

		template<class T> void _vec3<T>::operator += (const T n)
		{
			x += n;
			y += n;
			z += n;
		}

		template<class T> void _vec3<T>::operator -= (const T n)
		{
			x -= n;
			y -= n;
			z -= n;
		}

		template<class T>
		bool _vec3<T>::operator == (const _vec3<T>& vec) const
		{
			return x == vec.x && y == vec.y && z == vec.z;
		}

		template<class T> bool _vec3<T>::operator == (T f) const
		{
			return x == f && y == f && z == f;
		}

		template<class T> bool _vec3<T>::operator != (const _vec3<T>& vec) const
		{
			return x != vec.x || y != vec.y || z != vec.z;
		}

		template<class T> bool _vec3<T>::operator != (T f) const
		{
			return x != f || y != f || z != f;
		}

		template<class T> _vec3<T>& _vec3<T>::normalize()
		{
			matReal lenDivisor = matOne / length();
			x = T(x * lenDivisor);
			y = T(y * lenDivisor);
			z = T(z * lenDivisor);
			return *this;
		}

		template<class T> _vec3<T> _vec3<T>::operator + (const _vec3<T>& vec) const
		{
			return _vec3<T>(x + vec.x, y + vec.y, z + vec.z);
		}

		template<class T> _vec3<T> _vec3<T>::operator - (const _vec3<T>& vec) const
		{
			return _vec3<T>(x - vec.x, y - vec.y, z - vec.z);
		}

		template<class T> _vec3<T> _vec3<T>::operator * (const _vec3<T>& vec) const
		{
			return _vec3<T>(x*vec.x, y*vec.y, z*vec.z);
		}

		template<class T> _vec3<T> _vec3<T>::operator / (const _vec3<T>& vec) const
		{
			return _vec3<T>(x / vec.x, y / vec.y, z / vec.z);
		}

		template<class T> void _vec3<T>::operator += (const _vec3<T>& vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}

		template<class T> void _vec3<T>::operator -= (const _vec3<T>& vec)
		{
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
		}

		template<class T> void _vec3<T>::operator *= (const _vec3<T>& vec)
		{
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
		}

		template<class T> void _vec3<T>::operator /= (const _vec3<T>& vec)
		{
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
		}

		template<class T> _vec3<T>& _vec3<T>::rotate(const matReal angle, const _vec3<matReal>& axis)
		{
			mat4 rotationmat;
			rotationmat = math::createRotationMatrix(angle, axis);

			return (*this = (rotationmat*_vec4<T>(x,y,z,1)).xyz());
		}

		template<class T> void _vec3<T>::reset()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		template<class T> _vec3<T> _vec3<T>::xyz() const { return _vec3<T>(x, y, z); }
		template<class T> _vec3<T> _vec3<T>::xzy() const { return _vec3<T>(x, z, y); }
		template<class T> _vec3<T> _vec3<T>::yxz() const { return _vec3<T>(y, x, z); }
		template<class T> _vec3<T> _vec3<T>::yzx() const { return _vec3<T>(y, z, x); }
		template<class T> _vec3<T> _vec3<T>::zxy() const { return _vec3<T>(z, x, y); }
		template<class T> _vec3<T> _vec3<T>::zyx() const { return _vec3<T>(z, y, x); }

		template<class T> _vec2<T> _vec3<T>::xy() const { return _vec2<T>(x, y); }
		template<class T> _vec2<T> _vec3<T>::yx() const { return _vec2<T>(y, x); }
		template<class T> _vec2<T> _vec3<T>::xz() const { return _vec2<T>(x, z); }
		template<class T> _vec2<T> _vec3<T>::zx() const { return _vec2<T>(z, x); }
		template<class T> _vec2<T> _vec3<T>::yz() const { return _vec2<T>(y, z); }
		template<class T> _vec2<T> _vec3<T>::zy() const { return _vec2<T>(z, y); }

		template<class T> _vec4<T>::_vec4()
		{
			reset();
		}

		template<class T> _vec4<T>::_vec4(const T x_, const T y_, const T z_, const T w_)
		{
			x = x_;
			y = y_;
			z = z_;
			w = w_;
		}

		template<class T> _vec4<T>::_vec4(const T t)
		{
			x = t;
			y = t;
			z = t;
			w = t;
		}

		template<class T> T _vec4<T>::lengthSquared() const
		{
			return x*x + y*y + z*z + w*w;
		}

		template<class T> matReal _vec4<T>::length() const
		{
			return matReal(std::sqrt(x*x + y*y + z*z + w*w));
		}

		template<class T>
		matReal _vec4<T>::distance(const _vec4<T>& v) const
		{
			return matReal(sqrt((x - v.x)*(x - v.x) + (y - v.y)*(y - v.y) + (z - v.z)*(z - v.z) + (w - v.w)*(w - v.w)));
		}

		template<class T> T _vec4<T>::distanceSquared(const _vec4<T>& v) const
		{
			return (x - v.x)*(x - v.x) + (y - v.y)*(y - v.y) + (z - v.z)*(z - v.z) + (w - v.w)*(w - v.w);
		}

		template<class T> _vec4<T> _vec4<T>::operator * (const T n) const
		{
			return _vec4<T>(x*n, y*n, z*n, w*n);
		}

		template<class T> _vec4<T> _vec4<T>::operator / (const T n) const
		{
			return _vec4<T>(x / n, y / n, z / n, w / n);
		}

		template<class T> _vec4<T> _vec4<T>::operator + (const T n) const
		{
			return _vec4<T>(x + n, y + n, z + n, w + n);
		}

		template<class T> _vec4<T> _vec4<T>::operator - (const T n) const
		{
			return _vec4<T>(x - n, y - n, z - n, w - n);
		}

		template<class T> void _vec4<T>::operator *= (const T n)
		{
			x *= n;
			y *= n;
			z *= n;
			w *= n;
		}

		template<class T> void  _vec4<T>::operator /= (const T n)
		{
			x /= n;
			y /= n;
			z /= n;
			w /= n;
		}

		template<class T> void  _vec4<T>::operator += (const T n)
		{
			x += n;
			y += n;
			z += n;
			w += n;
		}

		template<class T> void  _vec4<T>::operator -= (const T n)
		{
			x -= n;
			y -= n;
			z -= n;
			w -= n;
		}

		template<class T> bool _vec4<T>::operator == (const _vec4<T>& vec) const
		{
			return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
		}

		template<class T> bool _vec4<T>::operator == (T f) const
		{
			return x == f && y == f &&z == f && w == f;
		}

		template<class T> bool _vec4<T>::operator != (const _vec4<T>& vec) const
		{
			return x != vec.x || y != vec.y || z != vec.z || w != vec.w;
		}

		template<class T> bool _vec4<T>::operator != (T f) const
		{
			return x != f || y != f || z != f || w != f;
		}

		template<class T> _vec4<T>& _vec4<T>::normalize()
		{
			matReal lenDivisor = matOne / length();
			x = T(x * lenDivisor);
			y = T(y * lenDivisor);
			z = T(z * lenDivisor);
			w = T(w * lenDivisor);
			return *this;
		}

		template<class T> _vec4<T> _vec4<T>::operator + (const _vec4<T>& vec) const
		{
			return _vec4<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
		}

		template<class T> _vec4<T> _vec4<T>::operator - (const _vec4<T>& vec) const
		{
			return _vec4<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
		}

		template<class T>
		_vec4<T> _vec4<T>::operator * (const _vec4<T>& vec) const
		{
			return _vec4<T>(x*vec.x, y*vec.y, z*vec.z, w*vec.w);
		}

		template<class T> _vec4<T> _vec4<T>::operator / (const _vec4<T>& vec) const
		{
			return _vec4<T>(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
		}

		template<class T> void _vec4<T>::operator += (const _vec4<T>& vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
			w += vec.w;
		}
		template<class T> void _vec4<T>::operator -= (const _vec4<T>& vec)
		{
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			w -= vec.w;
		}

		template<class T> void _vec4<T>::operator *= (const _vec4<T>& vec)
		{
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
			w *= vec.w;
		}

		template<class T> void _vec4<T>::operator /= (const _vec4<T>& vec)
		{
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
			w /= vec.w;
		}

		template<class T> void _vec4<T>::reset()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		template<class T> _vec4<T> _vec4<T>::xyzw() const { return _vec4<T>(x, y, z, w); }
		template<class T> _vec4<T> _vec4<T>::xywz() const { return _vec4<T>(x, y, w, z); }
		template<class T> _vec4<T> _vec4<T>::xzwy() const { return _vec4<T>(x, z, w, y); }
		template<class T> _vec4<T> _vec4<T>::xzyw() const { return _vec4<T>(x, z, y, w); }
		template<class T> _vec4<T> _vec4<T>::xwzy() const { return _vec4<T>(x, w, z, y); }
		template<class T> _vec4<T> _vec4<T>::xwyz() const { return _vec4<T>(x, w, y, z); }
		template<class T> _vec4<T> _vec4<T>::yxzw() const { return _vec4<T>(y, x, z, w); }
		template<class T> _vec4<T> _vec4<T>::yxwz() const { return _vec4<T>(y, x, w, z); }
		template<class T> _vec4<T> _vec4<T>::yzwx() const { return _vec4<T>(y, z, w, x); }
		template<class T> _vec4<T> _vec4<T>::yzxw() const { return _vec4<T>(y, z, x, w); }
		template<class T> _vec4<T> _vec4<T>::ywzx() const { return _vec4<T>(y, w, z, x); }
		template<class T> _vec4<T> _vec4<T>::ywxz() const { return _vec4<T>(y, w, x, z); }
		template<class T> _vec4<T> _vec4<T>::zyxw() const { return _vec4<T>(z, y, x, w); }
		template<class T> _vec4<T> _vec4<T>::zywx() const { return _vec4<T>(z, y, w, x); }
		template<class T> _vec4<T> _vec4<T>::zxwy() const { return _vec4<T>(z, x, w, y); }
		template<class T> _vec4<T> _vec4<T>::zxyw() const { return _vec4<T>(z, x, y, w); }
		template<class T> _vec4<T> _vec4<T>::zwxy() const { return _vec4<T>(z, w, x, y); }
		template<class T> _vec4<T> _vec4<T>::zwyx() const { return _vec4<T>(z, w, y, x); }
		template<class T> _vec4<T> _vec4<T>::wyzx() const { return _vec4<T>(w, y, z, x); }
		template<class T> _vec4<T> _vec4<T>::wyxz() const { return _vec4<T>(w, y, x, z); }
		template<class T> _vec4<T> _vec4<T>::wzxy() const { return _vec4<T>(w, z, x, y); }
		template<class T> _vec4<T> _vec4<T>::wzyx() const { return _vec4<T>(w, z, y, x); }
		template<class T> _vec4<T> _vec4<T>::wxzy() const { return _vec4<T>(w, x, z, y); }
		template<class T> _vec4<T> _vec4<T>::wxyz() const { return _vec4<T>(w, x, y, z); }

		template<class T> _vec3<T> _vec4<T>::xyz() const { return _vec3<T>(x, y, z); }
		template<class T> _vec3<T> _vec4<T>::xzy() const { return _vec3<T>(x, z, y); }
		template<class T> _vec3<T> _vec4<T>::yxz() const { return _vec3<T>(y, x, z); }
		template<class T> _vec3<T> _vec4<T>::yzx() const { return _vec3<T>(y, z, x); }
		template<class T> _vec3<T> _vec4<T>::zxy() const { return _vec3<T>(z, x, y); }
		template<class T> _vec3<T> _vec4<T>::zyx() const { return _vec3<T>(z, y, x); }
		template<class T> _vec3<T> _vec4<T>::wyz() const { return _vec3<T>(w, y, z); }
		template<class T> _vec3<T> _vec4<T>::wzy() const { return _vec3<T>(w, z, y); }
		template<class T> _vec3<T> _vec4<T>::ywz() const { return _vec3<T>(y, w, z); }
		template<class T> _vec3<T> _vec4<T>::yzw() const { return _vec3<T>(y, z, w); }
		template<class T> _vec3<T> _vec4<T>::zwy() const { return _vec3<T>(z, w, y); }
		template<class T> _vec3<T> _vec4<T>::zyw() const { return _vec3<T>(z, y, w); }
		template<class T> _vec3<T> _vec4<T>::xyw() const { return _vec3<T>(x, y, w); }
		template<class T> _vec3<T> _vec4<T>::xwy() const { return _vec3<T>(x, w, y); }
		template<class T> _vec3<T> _vec4<T>::yxw() const { return _vec3<T>(y, x, w); }
		template<class T> _vec3<T> _vec4<T>::ywx() const { return _vec3<T>(y, w, x); }
		template<class T> _vec3<T> _vec4<T>::wxy() const { return _vec3<T>(w, x, y); }
		template<class T> _vec3<T> _vec4<T>::wyx() const { return _vec3<T>(w, y, x); }
		template<class T> _vec3<T> _vec4<T>::xwz() const { return _vec3<T>(x, w, z); }
		template<class T> _vec3<T> _vec4<T>::xzw() const { return _vec3<T>(x, z, w); }
		template<class T> _vec3<T> _vec4<T>::wxz() const { return _vec3<T>(w, x, z); }
		template<class T> _vec3<T> _vec4<T>::wzx() const { return _vec3<T>(w, z, x); }
		template<class T> _vec3<T> _vec4<T>::zxw() const { return _vec3<T>(z, x, w); }
		template<class T> _vec3<T> _vec4<T>::zwx() const { return _vec3<T>(z, w, x); }

		template<class T> _vec2<T> _vec4<T>::xy() const { return _vec2<T>(x, y); }
		template<class T> _vec2<T> _vec4<T>::yx() const { return _vec2<T>(y, x); }
		template<class T> _vec2<T> _vec4<T>::xz() const { return _vec2<T>(x, z); }
		template<class T> _vec2<T> _vec4<T>::zx() const { return _vec2<T>(z, x); }
		template<class T> _vec2<T> _vec4<T>::xw() const { return _vec2<T>(x, w); }
		template<class T> _vec2<T> _vec4<T>::wx() const { return _vec2<T>(w, x); }
		template<class T> _vec2<T> _vec4<T>::yz() const { return _vec2<T>(y, z); }
		template<class T> _vec2<T> _vec4<T>::zy() const { return _vec2<T>(z, y); }
		template<class T> _vec2<T> _vec4<T>::wz() const { return _vec2<T>(w, z); }
		template<class T> _vec2<T> _vec4<T>::zw() const { return _vec2<T>(z, w); }

		_mat4::_mat4()
		{
			reset();
		}

		_mat4::_mat4(const matReal n)
		{
			reset();
			m[0][0] = n; m[1][1] = n;
			m[2][2] = n; m[3][3] = n;
		}

		_mat4::_mat4(const matReal m00, const matReal m10, const matReal m20, const matReal m30,
			const matReal m01, const matReal m11, const matReal m21, const matReal m31,
			const matReal m02, const matReal m12, const matReal m22, const matReal m32,
			const matReal m03, const matReal m13, const matReal m23, const matReal m33)
		{
			m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
			m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
			m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
			m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
		}

		void _mat4::reset()
		{
			m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
			m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
			m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
			m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
		}

		_mat4 _mat4::operator * (const _mat4& p) const
		{
			return _mat4(
				m[0][0] * p.m[0][0] + m[1][0] * p.m[0][1] + m[2][0] * p.m[0][2] + m[3][0] * p.m[0][3],
				m[0][0] * p.m[1][0] + m[1][0] * p.m[1][1] + m[2][0] * p.m[1][2] + m[3][0] * p.m[1][3],
				m[0][0] * p.m[2][0] + m[1][0] * p.m[2][1] + m[2][0] * p.m[2][2] + m[3][0] * p.m[2][3],
				m[0][0] * p.m[3][0] + m[1][0] * p.m[3][1] + m[2][0] * p.m[3][2] + m[3][0] * p.m[3][3],
				m[0][1] * p.m[0][0] + m[1][1] * p.m[0][1] + m[2][1] * p.m[0][2] + m[3][1] * p.m[0][3],
				m[0][1] * p.m[1][0] + m[1][1] * p.m[1][1] + m[2][1] * p.m[1][2] + m[3][1] * p.m[1][3],
				m[0][1] * p.m[2][0] + m[1][1] * p.m[2][1] + m[2][1] * p.m[2][2] + m[3][1] * p.m[2][3],
				m[0][1] * p.m[3][0] + m[1][1] * p.m[3][1] + m[2][1] * p.m[3][2] + m[3][1] * p.m[3][3],
				m[0][2] * p.m[0][0] + m[1][2] * p.m[0][1] + m[2][2] * p.m[0][2] + m[3][2] * p.m[0][3],
				m[0][2] * p.m[1][0] + m[1][2] * p.m[1][1] + m[2][2] * p.m[1][2] + m[3][2] * p.m[1][3],
				m[0][2] * p.m[2][0] + m[1][2] * p.m[2][1] + m[2][2] * p.m[2][2] + m[3][2] * p.m[2][3],
				m[0][2] * p.m[3][0] + m[1][2] * p.m[3][1] + m[2][2] * p.m[3][2] + m[3][2] * p.m[3][3],
				m[0][3] * p.m[0][0] + m[1][3] * p.m[0][1] + m[2][3] * p.m[0][2] + m[3][3] * p.m[0][3],
				m[0][3] * p.m[1][0] + m[1][3] * p.m[1][1] + m[2][3] * p.m[1][2] + m[3][3] * p.m[1][3],
				m[0][3] * p.m[2][0] + m[1][3] * p.m[2][1] + m[2][3] * p.m[2][2] + m[3][3] * p.m[2][3],
				m[0][3] * p.m[3][0] + m[1][3] * p.m[3][1] + m[2][3] * p.m[3][2] + m[3][3] * p.m[3][3]);
		}

		template<class T>
		_vec4<T> _mat4::operator* (const _vec4<T>& vec) const
		{
			return _vec4<T>(
				T(m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z + m[3][0] * vec.w),
				T(m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z + m[3][1] * vec.w),
				T(m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z + m[3][2] * vec.w),
				T(m[0][3] * vec.x + m[1][3] * vec.y + m[2][3] * vec.z + m[3][3] * vec.w));
		}

		_mat4 _mat4::operator* (const matReal n) const
		{
			return _mat4(
				m[0][0] * n, m[0][1] * n, m[0][2] * n, m[0][3] * n,
				m[1][0] * n, m[1][1] * n, m[1][2] * n, m[1][3] * n,
				m[2][0] * n, m[2][1] * n, m[2][2] * n, m[2][3] * n,
				m[3][0] * n, m[3][1] * n, m[3][2] * n, m[3][3] * n);
		}

		_mat4 _mat4::operator+ (const mat4& p) const
		{
			return _mat4(
				m[0][0] + p.m[0][0], m[0][1] + p.m[0][1],
				m[0][2] + p.m[0][2], m[0][3] + p.m[0][3],
				m[1][0] + p.m[1][0], m[1][1] + p.m[1][1],
				m[1][2] + p.m[1][2], m[1][3] + p.m[1][3],
				m[2][0] + p.m[2][0], m[2][1] + p.m[2][1],
				m[2][2] + p.m[2][2], m[2][3] + p.m[2][3],
				m[3][0] + p.m[3][0], m[3][1] + p.m[3][1],
				m[3][2] + p.m[3][2], m[3][3] + p.m[3][3]);
		}

		_mat4 _mat4::operator- (const mat4& p) const
		{
			return _mat4(
				m[0][0] - p.m[0][0], m[0][1] - p.m[0][1],
				m[0][2] - p.m[0][2], m[0][3] - p.m[0][3],
				m[1][0] - p.m[1][0], m[1][1] - p.m[1][1],
				m[1][2] - p.m[1][2], m[1][3] - p.m[1][3],
				m[2][0] - p.m[2][0], m[2][1] - p.m[2][1],
				m[2][2] - p.m[2][2], m[2][3] - p.m[2][3],
				m[3][0] - p.m[3][0], m[3][1] - p.m[3][1],
				m[3][2] - p.m[3][2], m[3][3] - p.m[3][3]);
		}

		_mat4 _mat4::operator / (const matReal n) const
		{
			return _mat4(
				m[0][0] / n, m[0][1] / n, m[0][2] / n, m[0][3] / n,
				m[1][0] / n, m[1][1] / n, m[1][2] / n, m[1][3] / n,
				m[2][0] / n, m[2][1] / n, m[2][2] / n, m[2][3] / n,
				m[3][0] / n, m[3][1] / n, m[3][2] / n, m[3][3] / n);
		}

		_mat4 _mat4::operator+ (const matReal n) const
		{
			return _mat4(
				m[0][0] + n, m[0][1] + n, m[0][2] + n, m[0][3] + n,
				m[1][0] + n, m[1][1] + n, m[1][2] + n, m[1][3] + n,
				m[2][0] + n, m[2][1] + n, m[2][2] + n, m[2][3] + n,
				m[3][0] + n, m[3][1] + n, m[3][2] + n, m[3][3] + n);
		}

		_mat4 _mat4::operator- (const matReal n) const
		{
			return _mat4(
				m[0][0] - n, m[0][1] - n, m[0][2] - n, m[0][3] - n,
				m[1][0] - n, m[1][1] - n, m[1][2] - n, m[1][3] - n,
				m[2][0] - n, m[2][1] - n, m[2][2] - n, m[2][3] - n,
				m[3][0] - n, m[3][1] - n, m[3][2] - n, m[3][3] - n);
		}

		void _mat4::operator *= (const _mat4& p)
		{
			matReal t1, t2, t3, t4;
			t1 = m[0][0] * p.m[0][0] + m[1][0] * p.m[0][1] + m[2][0] * p.m[0][2] + m[3][0] * p.m[0][3];
			t2 = m[0][0] * p.m[1][0] + m[1][0] * p.m[1][1] + m[2][0] * p.m[1][2] + m[3][0] * p.m[1][3];
			t3 = m[0][0] * p.m[2][0] + m[1][0] * p.m[2][1] + m[2][0] * p.m[2][2] + m[3][0] * p.m[2][3];
			t4 = m[0][0] * p.m[3][0] + m[1][0] * p.m[3][1] + m[2][0] * p.m[3][2] + m[3][0] * p.m[3][3];
			m[0][0] = t1; m[1][0] = t2; m[2][0] = t3; m[3][0] = t4;
			t1 = m[0][1] * p.m[0][0] + m[1][1] * p.m[0][1] + m[2][1] * p.m[0][2] + m[3][1] * p.m[0][3];
			t2 = m[0][1] * p.m[1][0] + m[1][1] * p.m[1][1] + m[2][1] * p.m[1][2] + m[3][1] * p.m[1][3];
			t3 = m[0][1] * p.m[2][0] + m[1][1] * p.m[2][1] + m[2][1] * p.m[2][2] + m[3][1] * p.m[2][3];
			t4 = m[0][1] * p.m[3][0] + m[1][1] * p.m[3][1] + m[2][1] * p.m[3][2] + m[3][1] * p.m[3][3];
			m[0][1] = t1; m[1][1] = t2; m[2][1] = t3; m[3][1] = t4;
			t1 = m[0][2] * p.m[0][0] + m[1][2] * p.m[0][1] + m[2][2] * p.m[0][2] + m[3][2] * p.m[0][3];
			t2 = m[0][2] * p.m[1][0] + m[1][2] * p.m[1][1] + m[2][2] * p.m[1][2] + m[3][2] * p.m[1][3];
			t3 = m[0][2] * p.m[2][0] + m[1][2] * p.m[2][1] + m[2][2] * p.m[2][2] + m[3][2] * p.m[2][3];
			t4 = m[0][2] * p.m[3][0] + m[1][2] * p.m[3][1] + m[2][2] * p.m[3][2] + m[3][2] * p.m[3][3];
			m[0][2] = t1; m[1][2] = t2; m[2][2] = t3; m[3][2] = t4;
			t1 = m[0][3] * p.m[0][0] + m[1][3] * p.m[0][1] + m[2][3] * p.m[0][2] + m[3][3] * p.m[0][3];
			t2 = m[0][3] * p.m[1][0] + m[1][3] * p.m[1][1] + m[2][3] * p.m[1][2] + m[3][3] * p.m[1][3];
			t3 = m[0][3] * p.m[2][0] + m[1][3] * p.m[2][1] + m[2][3] * p.m[2][2] + m[3][3] * p.m[2][3];
			t4 = m[0][3] * p.m[3][0] + m[1][3] * p.m[3][1] + m[2][3] * p.m[3][2] + m[3][3] * p.m[3][3];
			m[0][3] = t1; m[1][3] = t2; m[2][3] = t3; m[3][3] = t4;
		}

		void _mat4::operator *= (const matReal n)
		{
			m[0][0] *= n; m[0][1] *= n; m[0][2] *= n; m[0][3] *= n;
			m[1][0] *= n; m[1][1] *= n; m[1][2] *= n; m[1][3] *= n;
			m[2][0] *= n; m[2][1] *= n; m[2][2] *= n; m[2][3] *= n;
			m[3][0] *= n; m[3][1] *= n; m[3][2] *= n; m[3][3] *= n;
		}

		void _mat4::operator /= (const matReal n)
		{
			m[0][0] /= n; m[0][1] /= n; m[0][2] /= n; m[0][3] /= n;
			m[1][0] /= n; m[1][1] /= n; m[1][2] /= n; m[1][3] /= n;
			m[2][0] /= n; m[2][1] /= n; m[2][2] /= n; m[2][3] /= n;
			m[3][0] /= n; m[3][1] /= n; m[3][2] /= n; m[3][3] /= n;
		}

		void _mat4::operator += (const _mat4& p)
		{
			m[0][0] += p.m[0][0]; m[0][1] += p.m[0][1];
			m[0][2] += p.m[0][2]; m[0][3] += p.m[0][3];
			m[1][0] += p.m[1][0]; m[1][1] += p.m[1][1];
			m[1][2] += p.m[1][2]; m[1][3] += p.m[1][3];
			m[2][0] += p.m[2][0]; m[2][1] += p.m[2][1];
			m[2][2] += p.m[2][2]; m[2][3] += p.m[2][3];
			m[3][0] += p.m[3][0]; m[3][1] += p.m[3][1];
			m[3][2] += p.m[3][2]; m[3][3] += p.m[3][3];
		}

		void _mat4::operator += (const matReal n)
		{
			m[0][0] += n; m[0][1] += n; m[0][2] += n; m[0][3] += n;
			m[1][0] += n; m[1][1] += n; m[1][2] += n; m[1][3] += n;
			m[2][0] += n; m[2][1] += n; m[2][2] += n; m[2][3] += n;
			m[3][0] += n; m[3][1] += n; m[3][2] += n; m[3][3] += n;
		}

		void _mat4::operator  -= (const _mat4& p)
		{
			m[0][0] -= p.m[0][0]; m[0][1] -= p.m[0][1];
			m[0][2] -= p.m[0][2]; m[0][3] -= p.m[0][3];
			m[1][0] -= p.m[1][0]; m[1][1] -= p.m[1][1];
			m[1][2] -= p.m[1][2]; m[1][3] -= p.m[1][3];
			m[2][0] -= p.m[2][0]; m[2][1] -= p.m[2][1];
			m[2][2] -= p.m[2][2]; m[2][3] -= p.m[2][3];
			m[3][0] -= p.m[3][0]; m[3][1] -= p.m[3][1];
			m[3][2] -= p.m[3][2]; m[3][3] -= p.m[3][3];
		}

		void _mat4::operator  -= (const matReal n)
		{
			m[0][0] -= n; m[0][1] -= n; m[0][2] -= n; m[0][3] -= n;
			m[1][0] -= n; m[1][1] -= n; m[1][2] -= n; m[1][3] -= n;
			m[2][0] -= n; m[2][1] -= n; m[2][2] -= n; m[2][3] -= n;
			m[3][0] -= n; m[3][1] -= n; m[3][2] -= n; m[3][3] -= n;
		}

		bool _mat4::operator == (const _mat4& p) const
		{
			return
				m[0][0] == p.m[0][0] && m[0][1] == p.m[0][1] &&
				m[0][2] == p.m[0][2] && m[0][3] == p.m[0][3] &&
				m[1][0] == p.m[1][0] && m[1][1] == p.m[1][1] &&
				m[1][2] == p.m[1][2] && m[1][3] == p.m[1][3] &&
				m[2][0] == p.m[2][0] && m[2][1] == p.m[2][1] &&
				m[2][2] == p.m[2][2] && m[2][3] == p.m[2][3] &&
				m[3][0] == p.m[3][0] && m[3][1] == p.m[3][1] &&
				m[3][2] == p.m[3][2] && m[3][3] == p.m[3][3];
		}

		bool _mat4::operator != (const _mat4& p) const
		{
			return
				m[0][0] != p.m[0][0] || m[0][1] != p.m[0][1] ||
				m[0][2] != p.m[0][2] || m[0][3] != p.m[0][3] ||
				m[1][0] != p.m[1][0] || m[1][1] != p.m[1][1] ||
				m[1][2] != p.m[1][2] || m[1][3] != p.m[1][3] ||
				m[2][0] != p.m[2][0] || m[2][1] != p.m[2][1] ||
				m[2][2] != p.m[2][2] || m[2][3] != p.m[2][3] ||
				m[3][0] != p.m[3][0] || m[3][1] != p.m[3][1] ||
				m[3][2] != p.m[3][2] || m[3][3] != p.m[3][3];
		}

		_mat3::_mat3()
		{
			reset();
		}

		_mat3::_mat3(const matReal n)
		{
			reset();
			m[0][0] = n;
			m[1][1] = n;
			m[2][2] = n;
		}

		_mat3::_mat3(const matReal m00, const matReal m10, const matReal m20,
			const matReal m01, const matReal m11, const matReal m21,
			const matReal m02, const matReal m12, const matReal m22)
		{
			m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
			m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
			m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
		}

		void _mat3::reset()
		{
			m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
			m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
			m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
		}

		_mat3 _mat3::operator * (const _mat3& p) const
		{
			return _mat3(
				m[0][0] * p.m[0][0] + m[1][0] * p.m[0][1] + m[2][0] * p.m[0][2],
				m[0][0] * p.m[1][0] + m[1][0] * p.m[1][1] + m[2][0] * p.m[1][2],
				m[0][0] * p.m[2][0] + m[1][0] * p.m[2][1] + m[2][0] * p.m[2][2],

				m[0][1] * p.m[0][0] + m[1][1] * p.m[0][1] + m[2][1] * p.m[0][2],
				m[0][1] * p.m[1][0] + m[1][1] * p.m[1][1] + m[2][1] * p.m[1][2],
				m[0][1] * p.m[2][0] + m[1][1] * p.m[2][1] + m[2][1] * p.m[2][2],

				m[0][2] * p.m[0][0] + m[1][2] * p.m[0][1] + m[2][2] * p.m[0][2],
				m[0][2] * p.m[1][0] + m[1][2] * p.m[1][1] + m[2][2] * p.m[1][2],
				m[0][2] * p.m[2][0] + m[1][2] * p.m[2][1] + m[2][2] * p.m[2][2]);
		}

		vec3 _mat3::operator* (const vec3& vec) const
		{
			return vec3(
				m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z,
				m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z,
				m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z);
		}

		_mat3 _mat3::operator* (const matReal n) const
		{
			return _mat3(
				m[0][0] * n, m[0][1] * n, m[0][2] * n,
				m[1][0] * n, m[1][1] * n, m[1][2] * n,
				m[2][0] * n, m[2][1] * n, m[2][2] * n);
		}

		_mat3 _mat3::operator+ (const _mat3& p) const
		{
			return _mat3(
				m[0][0] + p.m[0][0], m[0][1] + p.m[0][1], m[0][2] + p.m[0][2],
				m[1][1] + p.m[1][1], m[1][0] + p.m[1][0], m[1][2] + p.m[1][2],
				m[2][0] + p.m[2][0], m[2][1] + p.m[2][1], m[2][2] + p.m[2][2]);
		}

		_mat3 _mat3::operator- (const _mat3& p) const
		{
			return _mat3(
				m[0][0] - p.m[0][0], m[0][1] - p.m[0][1], m[0][2] - p.m[0][2],
				m[1][1] - p.m[1][1], m[1][0] - p.m[1][0], m[1][2] - p.m[1][2],
				m[2][0] - p.m[2][0], m[2][1] - p.m[2][1], m[2][2] - p.m[2][2]);
		}

		_mat3 _mat3::operator / (const matReal n) const
		{
			return _mat3(
				m[0][0] / n, m[0][1] / n, m[0][2] / n,
				m[1][0] / n, m[1][1] / n, m[1][2] / n,
				m[2][0] / n, m[2][1] / n, m[2][2] / n);
		}

		_mat3 _mat3::operator+ (const matReal n) const
		{
			return _mat3(
				m[0][0] + n, m[0][1] + n, m[0][2] + n,
				m[1][0] + n, m[1][1] + n, m[1][2] + n,
				m[2][0] + n, m[2][1] + n, m[2][2] + n);
		}

		_mat3 _mat3::operator- (const matReal n) const
		{
			return _mat3(
				m[0][0] - n, m[0][1] - n, m[0][2] - n,
				m[1][0] - n, m[1][1] - n, m[1][2] - n,
				m[2][0] - n, m[2][1] - n, m[2][2] - n);
		}

		void _mat3::operator *= (const _mat3& p)
		{
			matReal t1, t2, t3;
			t1 = m[0][0] * p.m[0][0] + m[1][0] * p.m[0][1] + m[2][0] * p.m[0][2];
			t2 = m[0][0] * p.m[1][0] + m[1][0] * p.m[1][1] + m[2][0] * p.m[1][2];
			t3 = m[0][0] * p.m[2][0] + m[1][0] * p.m[2][1] + m[2][0] * p.m[2][2];
			m[0][0] = t1; m[1][0] = t2; m[2][0] = t3;
			t1 = m[0][1] * p.m[0][0] + m[1][1] * p.m[0][1] + m[2][1] * p.m[0][2];
			t2 = m[0][1] * p.m[1][0] + m[1][1] * p.m[1][1] + m[2][1] * p.m[1][2];
			t3 = m[0][1] * p.m[2][0] + m[1][1] * p.m[2][1] + m[2][1] * p.m[2][2];
			m[0][1] = t1; m[1][1] = t2; m[2][1] = t3;
			t1 = m[0][2] * p.m[0][0] + m[1][2] * p.m[0][1] + m[2][2] * p.m[0][2];
			t2 = m[0][2] * p.m[1][0] + m[1][2] * p.m[1][1] + m[2][2] * p.m[1][2];
			t3 = m[0][2] * p.m[2][0] + m[1][2] * p.m[2][1] + m[2][2] * p.m[2][2];
			m[0][2] = t1; m[1][2] = t2; m[2][2] = t3;
		}

		void _mat3::operator *= (const matReal n)
		{
			m[0][0] *= n; m[0][1] *= n; m[0][2] *= n;
			m[1][0] *= n; m[1][1] *= n; m[1][2] *= n;
			m[2][0] *= n; m[2][1] *= n; m[2][2] *= n;
		}

		void _mat3::operator /= (const matReal n)
		{
			m[0][0] /= n; m[0][1] /= n; m[0][2] /= n;
			m[1][0] /= n; m[1][1] /= n; m[1][2] /= n;
			m[2][0] /= n; m[2][1] /= n; m[2][2] /= n;
		}

		void _mat3::operator += (const _mat3& p)
		{
			m[0][0] += p.m[0][0]; m[0][1] += p.m[0][1]; m[0][2] += p.m[0][2];
			m[1][0] += p.m[1][0]; m[1][1] += p.m[1][1]; m[1][2] += p.m[1][2];
			m[2][0] += p.m[2][0]; m[2][1] += p.m[2][1]; m[2][2] += p.m[2][2];
		}

		void _mat3::operator += (const matReal n)
		{
			m[0][0] += n; m[0][1] += n; m[0][2] += n;
			m[1][0] += n; m[1][1] += n; m[1][2] += n;
			m[2][0] += n; m[2][1] += n; m[2][2] += n;
		}

		void _mat3::operator  -= (const _mat3& p)
		{
			m[0][0] -= p.m[0][0]; m[0][1] -= p.m[0][1]; m[0][2] -= p.m[0][2];
			m[1][0] -= p.m[1][0]; m[1][1] -= p.m[1][1]; m[1][2] -= p.m[1][2];
			m[2][0] -= p.m[2][0]; m[2][1] -= p.m[2][1]; m[2][2] -= p.m[2][2];
		}

		void _mat3::operator  -= (const matReal n)
		{
			m[0][0] -= n; m[0][1] -= n; m[0][2] -= n;
			m[1][0] -= n; m[1][1] -= n; m[1][2] -= n;
			m[2][0] -= n; m[2][1] -= n; m[2][2] -= n;
		}

		bool _mat3::operator == (const _mat3& p) const
		{
			return
				m[0][0] == p.m[0][0] && m[0][1] == p.m[0][1] && m[0][2] == p.m[0][2] &&
				m[1][0] == p.m[1][0] && m[1][1] == p.m[1][1] && m[1][2] == p.m[1][2] &&
				m[2][0] == p.m[2][0] && m[2][1] == p.m[2][1] && m[2][2] == p.m[2][2];
		}

		bool _mat3::operator != (const _mat3& p) const
		{
			return
				m[0][0] != p.m[0][0] || m[0][1] != p.m[0][1] || m[0][2] != p.m[0][2] ||
				m[1][0] != p.m[1][0] || m[1][1] != p.m[1][1] || m[1][2] != p.m[1][2] ||
				m[2][0] != p.m[2][0] || m[2][1] != p.m[2][1] || m[2][2] != p.m[2][2];
		}

		_mat2::_mat2()
		{
			reset();
		}

		_mat2::_mat2(const matReal n)
		{
			reset();
			m[0][0] = n; m[1][1] = n;
		}

		_mat2::_mat2(const matReal m00, const matReal m10,
			const matReal m01, const matReal m11)
		{
			m[0][0] = m00; m[0][1] = m01;
			m[1][0] = m10; m[1][1] = m11;
		}

		void _mat2::reset()
		{
			m[0][0] = 1; m[0][1] = 0;
			m[1][0] = 0; m[1][1] = 1;
		}

		_mat2 _mat2::operator * (const _mat2& p) const
		{
			return _mat2(
				m[0][0] * p.m[0][0] + m[1][0] * p.m[0][1],
				m[0][0] * p.m[1][0] + m[1][0] * p.m[1][1],
				m[0][1] * p.m[0][0] + m[1][1] * p.m[0][1],
				m[0][1] * p.m[1][0] + m[1][1] * p.m[1][1]);
		}

		vec2 _mat2::operator* (const vec2& vec) const
		{
			return vec2(
				m[0][0] * vec.x + m[1][0] * vec.y,
				m[0][1] * vec.x + m[1][1] * vec.y);
		}

		_mat2 _mat2::operator* (const matReal n) const
		{
			return _mat2(
				m[0][0] * n, m[0][1] * n,
				m[1][0] * n, m[1][1] * n);
		}

		_mat2 _mat2::operator+ (const _mat2& p) const
		{
			return _mat2(
				m[0][0] + p.m[0][0], m[0][1] + p.m[0][1],
				m[1][0] + p.m[1][0], m[1][1] + p.m[1][1]);
		}

		_mat2 _mat2::operator- (const _mat2& p) const
		{
			return _mat2(
				m[0][0] - p.m[0][0], m[0][1] - p.m[0][1],
				m[1][0] - p.m[1][0], m[1][1] - p.m[1][1]);
		}

		_mat2 _mat2::operator / (const matReal n) const
		{
			return _mat2(
				m[0][0] / n, m[0][1] / n,
				m[1][0] / n, m[1][1] / n);
		}

		_mat2 _mat2::operator+ (const matReal n) const
		{
			return _mat2(
				m[0][0] + n, m[0][1] + n,
				m[1][0] + n, m[1][1] + n);
		}

		_mat2 _mat2::operator- (const matReal n) const
		{
			return _mat2(
				m[0][0] - n, m[0][1] - n,
				m[1][0] - n, m[1][1] - n);
		}

		void _mat2::operator *= (const _mat2& p)
		{
			matReal t1, t2;
			t1 = m[0][0] * p.m[0][0] + m[1][0] * p.m[0][1];
			t2 = m[0][0] * p.m[1][0] + m[1][0] * p.m[1][1];
			m[0][0] = t1; m[1][0] = t2;
			t1 = m[0][1] * p.m[0][0] + m[1][1] * p.m[0][1];
			t2 = m[0][1] * p.m[1][0] + m[1][1] * p.m[1][1];
			m[0][1] = t1; m[1][1] = t2;
		}

		void _mat2::operator *= (const matReal n)
		{
			m[0][0] *= n; m[0][1] *= n;
			m[1][0] *= n; m[1][1] *= n;
		}

		void _mat2::operator /= (const matReal n)
		{
			m[0][0] /= n; m[0][1] /= n;
			m[1][0] /= n; m[1][1] /= n;
		}

		void _mat2::operator += (const _mat2& p)
		{
			m[0][0] += p.m[0][0]; m[0][1] += p.m[0][1];
			m[1][0] += p.m[1][0]; m[1][1] += p.m[1][1];
		}

		void _mat2::operator += (const matReal n)
		{
			m[0][0] += n; m[0][1] += n;
			m[1][0] += n; m[1][1] += n;
		}

		void _mat2::operator  -= (const _mat2& p)
		{
			m[0][0] -= p.m[0][0]; m[0][1] -= p.m[0][1];
			m[1][0] -= p.m[1][0]; m[1][1] -= p.m[1][1];
		}

		void _mat2::operator  -= (const matReal n)
		{
			m[0][0] -= n; m[0][1] -= n;
			m[1][0] -= n; m[1][1] -= n;
		}

		bool _mat2::operator == (const _mat2& p) const
		{
			return
				m[0][0] == p.m[0][0] && m[0][1] == p.m[0][1] &&
				m[1][0] == p.m[1][0] && m[1][1] == p.m[1][1];
		}

		bool _mat2::operator != (const _mat2& p) const
		{
			return
				m[0][0] != p.m[0][0] || m[0][1] != p.m[0][1] ||
				m[1][0] != p.m[1][0] || m[1][1] != p.m[1][1];
		}

	}


	inline mat4 createRotationMatrix(matReal angle, const vec3& axis)
	{
		mat4 out;
		matReal c = cos(angle);
		matReal s = sin(angle);
		matReal iC = 1 - c;

		out.m[0][0] = axis.x*axis.x + (1 - axis.x*axis.x)*c;
		out.m[0][1] = iC*axis.x*axis.y + axis.z*s;
		out.m[0][2] = iC*axis.x*axis.z - axis.y*s;
		out.m[0][3] = 0;
		out.m[1][0] = iC*axis.x*axis.y - axis.z*s;
		out.m[1][1] = axis.y*axis.y + (1 - axis.y*axis.y)*c;
		out.m[1][2] = iC*axis.y*axis.z + axis.x*s;
		out.m[1][3] = 0;
		out.m[2][0] = iC*axis.x*axis.z + axis.y*s;
		out.m[2][1] = iC*axis.y*axis.z - axis.x*s;
		out.m[2][2] = axis.z*axis.z + (1 - axis.z*axis.z)*c;
		out.m[2][3] = 0; out.m[3][0] = 0;
		out.m[3][1] = 0; out.m[3][2] = 0;
		out.m[3][3] = 1;

		return out;
	}

	mat4 createTranslationMatrix(vec3& trans)
	{
		mat4 out;
		out.m[3][0] = trans.x;
		out.m[3][1] = trans.y;
		out.m[3][2] = trans.z;
		return out;
	}

	mat4 createScaleMatrix(vec3& scale)
	{
		mat4 out;
		out.m[0][0] = scale.x;
		out.m[1][1] = scale.y;
		out.m[2][2] = scale.z;
		return out;
	}

	mat4 createScaleMatrix(matReal scale)
	{
		mat4 out;
		out.m[0][0] = scale;
		out.m[1][1] = scale;
		out.m[2][2] = scale;
		return out;
	}

	mat4 createProjectionMatrix(const matReal fov, const matReal width,
		const matReal height, const matReal znear, const matReal zfar)
	{
		mat4 out;
		matReal tanHalfFOV = tan(fov / decltype(fov)(2));
		out.m[1][1] = decltype(fov)(1) / tanHalfFOV;
		out.m[0][0] = -out.m[1][1]/(width / height);
		out.m[2][2] = (-znear-zfar) / (znear-zfar);
		out.m[3][2] = (2*zfar*znear) / (znear-zfar); //Why 2* ?
		out.m[2][3] = 1;
		out.m[3][3] = 0; //1,0 changes bug... Not working now? What?
		return out;
	}

	mat4 createOrthoProjectionMatrix(const matReal left_, const matReal right_,
		const matReal bottom_, const matReal top_, const matReal near_, const matReal far_)
	{
		mat4 out;
		out.m[0][0] = decltype(left_)(2) / (right_ - left_);
		out.m[1][1] = decltype(left_)(2) / (top_ - bottom_);
		out.m[2][2] = -decltype(left_)(2) / (far_ - near_);
		out.m[3][0] = -((right_ + left_) / (right_ - left_));
		out.m[3][1] = -((top_ + bottom_) / (top_ - bottom_));
		out.m[3][2] = (far_ + near_) / (far_ - near_);
		return out;
	}

}