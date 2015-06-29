#pragma once
#include "stdafx.h"
namespace math
{
	template<class T> bool fltcmp(T a, T b)
	{
		const T epsilon = 0.00000001;
		return std::abs(a - b) > epsilon;
	}


	class Quaternion
	{
	public:
		matReal w, x, y, z;

		Quaternion()
		{
			reset();
		}

		Quaternion(matReal w_, matReal x_, matReal y_, matReal z_)
		{
			w = w_;
			x = x_;
			y = y_;
			z = z_;
		}

		Quaternion(matReal t)
		{
			w = t;
			x = t;
			y = t;
			z = t;
		}

		Quaternion& fromAxisRotation(const vec3& axis, const matReal angle)
		{
			matReal hanfA = angle / matReal(2);
			matReal sinAng = std::sin(hanfA);
			w = std::cos(hanfA);
			x = axis.x*sinAng;
			y = axis.y*sinAng;
			z = axis.z*sinAng;
			normalize();
			return *this;
		}

		//Returns quaternion to rotate start to end.
		//Dodgy
		Quaternion fromRotationBetweenVectors(vec3 start, vec3 dest)
		{
			start.normalize();
			dest.normalize();

			matReal cosTheta = dot(start, dest);
			vec3 rotationAxis;
			if (cosTheta < -1 + 0.000001f) //if in opposide directions
			{
				rotationAxis = cross(vec3(0, 0, 1), start);
				if (rotationAxis.lengthSquared() < 0.00000001f)
					rotationAxis = cross(vec3(1, 0, 0), start);
				rotationAxis.normalize();
				return fromAxisRotation(rotationAxis, PIf);
			}

			rotationAxis = cross(start, dest);
			matReal s = sqrt((1 + cosTheta) * 2);
			matReal invs = 1 / s;

			return Quaternion(s*0.5f, rotationAxis.x*invs, 
				rotationAxis.y*invs, rotationAxis.z*invs);
		}

		//Dodgy
		Quaternion& lookAt(vec3 target, vec3 up)
		{
			target.normalize();
			up.normalize();


			Quaternion rot = fromRotationBetweenVectors(vec3(0, 0, 1), target);
			vec3 right = cross(target, up);
			vec3 desiredUp = cross(right, target);
			
			Quaternion newUpQ = rot*vec3(0, 1, 0);
			vec3 newUp(newUpQ.x, newUpQ.y, newUpQ.z);
			Quaternion rot2 = fromRotationBetweenVectors(newUp, desiredUp);
			*this = rot2*rot;
			return *this;
		}

		vec4 toAxisRotation() const
		{
			Quaternion tmp = *this;
			matReal angle = 2 * std::acos(tmp.w);
			matReal sqrtw = std::sqrt(1 - tmp.w*tmp.w);

			if (sqrtw < 0.00000001) //In this case, axis doesn't matter:
				return vec4(tmp.x, tmp.y, tmp.z, angle);
			else
				return vec4(tmp.x / sqrtw, tmp.y / sqrtw, tmp.z / sqrtw, angle);
		}

		matReal lengthSquared() const
		{
			return  w*w + x*x + y*y + z*z;
		}

		matReal length() const
		{
			return matReal(std::sqrt(w*w + x*x + y*y + z*z));
		}
		
		Quaternion& normalize()
		{
			matReal lenDivisor = 1.f / length();
			w = w * lenDivisor;
			x = x * lenDivisor;
			y = y * lenDivisor;
			z = z * lenDivisor;
			return *this;
		}

		Quaternion conjugate() const
		{
			return Quaternion(w, -x, -y, -z);
		}

		Quaternion inverse() const
		{
			Quaternion out = conjugate();
			out /= lengthSquared();
			return out;
		}

		Quaternion operator * (const Quaternion& b) const
		{
		return Quaternion(
			w * b.w - x * b.x - y * b.y - z * b.z,
			w * b.x + x * b.w + y * b.z - z * b.y,
			w * b.y - x * b.z + y * b.w + z * b.x,
			w * b.z + x * b.y - y * b.x + z * b.w );
		}

		Quaternion operator / (matReal f) const
		{
			return Quaternion(w / f, x / f, y / f, z / f);
		}

		Quaternion operator * (matReal f) const
		{
			return Quaternion(w * f, x * f, y * f, z * f);
		}

		Quaternion operator * (const vec3& b) const
		{
			return Quaternion(
				x * b.x - y * b.y - z * b.z,
				w * b.x + y * b.z - z * b.y,
				w * b.y - x * b.z + z * b.x,
				w * b.z + x * b.y - y * b.x);
		}

		Quaternion operator /= (matReal f)
		{
			w /= f;
			x /= f;
			y /= f;
			z /= f;
		}

		Quaternion operator *= (matReal f)
		{
			w *= f;
			x *= f;
			y *= f;
			z *= f;
		}

		void rotateVector(vec3& v)
		{
			Quaternion out = operator*(v)* conjugate();
			v= vec3(out.x, out.y, out.z);
		}

		mat4 toMatrix() const
		{
			matReal rotX2 = x * 2, rotY2 = y * 2, rotZ2 = z * 2;
			return mat4(
				1 - rotY2*y - rotZ2*z, rotX2*y - rotZ2*w, rotX2*z + rotY2*w, 0,
				rotX2*y + rotZ2*w, 1 - rotX2*x - rotZ2*z, rotY2*z - rotX2*w, 0,
				rotX2*z - rotY2*w, rotY2*z + rotX2*w, 1 - rotX2*x - rotY2*y, 0,
				0, 0, 0, 1
				);
		}

		void reset()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 1;
		}
	};

}