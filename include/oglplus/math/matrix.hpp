/**
 *  @file oglplus/math/matrix.hpp
 *  @brief A matrix class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_MATRIX_1107121519_HPP
#define OGLPLUS_MATRIX_1107121519_HPP

#include <oglplus/config/compiler.hpp>
#include <oglplus/math/vector.hpp>
#include <oglplus/math/angle.hpp>
#include <oglplus/math/quaternion.hpp>
#include <eagine/math/tmat.hpp>
#include <eagine/math/matrix_ctrs.hpp>

namespace oglplus {

template <typename T, unsigned R, unsigned C>
using Matrix = ::eagine::math::tmat<T, R, C, true>;

#ifdef GL_FLOAT
typedef Matrix<GLfloat, 2, 2> Mat2f;
typedef Matrix<GLfloat, 3, 3> Mat3f;
typedef Matrix<GLfloat, 4, 4> Mat4f;
#endif

#ifdef GL_DOUBLE
typedef Matrix<GLdouble, 2, 2> Mat2d;
typedef Matrix<GLdouble, 3, 3> Mat3d;
typedef Matrix<GLdouble, 4, 4> Mat4d;
#endif

template <unsigned I, typename T, unsigned R, unsigned C>
static inline
Vector<T, C> Row(const eagine::math::matrix<T,R,C,true>& m)
{
	return ::eagine::math::row<I>(m);
}

template <typename T, unsigned R, unsigned C>
static inline
Vector<T, C> Row(const eagine::math::matrix<T,R,C,true>& m, unsigned i)
{
	return ::eagine::math::row(m, i);
}

template <typename T, unsigned R, unsigned C>
static inline
Matrix<T, C, R> Transposed(const eagine::math::matrix<T,R,C,true>& m)
{
	return eagine::math::transpose(m);
}

/// Class implementing model transformation matrix named constructors
/** The static member functions of this class can be used to construct
 *  various model transformation matrices.
 *
 *  @ingroup math_utils
 */
template <typename T>
class ModelMatrix
 : public eagine::math::matrix<T, 4, 4, true>
{
private:
	typedef eagine::math::matrix<T, 4, 4, true> Base;
public:
	ModelMatrix(void) = default;

	ModelMatrix(const Base& base)
	 : Base(base)
	{ }

	static inline
	auto Translation(const Vector<T, 3>& d)
	{
		return eagine::math::translation<Base>{d._v}();
	}

	static inline
	auto Translation(T dx, T dy, T dz)
	{
		return eagine::math::translation<Base>(dx, dy, dz)();
	}

	static inline
	auto TranslationX(T d)
	{
		return eagine::math::translation_x<Base>(d)();
	}

	static inline
	auto TranslationY(T d)
	{
		return eagine::math::translation_y<Base>(d)();
	}

	static inline
	auto TranslationZ(T d)
	{
		return eagine::math::translation_z<Base>(d)();
	}

	static inline
	auto RotationX(Angle<T> a)
	{
		return eagine::math::rotation_x<Base>(a)();
	}

	static inline
	auto RotationY(Angle<T> a)
	{
		return eagine::math::rotation_y<Base>(a)();
	}

	static inline
	auto RotationZ(Angle<T> a)
	{
		return eagine::math::rotation_z<Base>(a)();
	}

	static inline
	auto RotationA(const Vector<T,3>& axis, Angle<T> angle)
	{
		return eagine::math::rotation_a<Base>(axis, angle)();
	}

	static inline
	auto ReflectionX(bool r = true)
	{
		return eagine::math::reflection_x<Base>(r)();
	}

	static inline
	auto ReflectionY(bool r = true)
	{
		return eagine::math::reflection_y<Base>(r)();
	}

	static inline
	auto ReflectionZ(bool r = true)
	{
		return eagine::math::reflection_z<Base>(r)();
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY || defined(GL_FLOAT)
/// Model transformation float matrix
/**
 *  @ingroup math_utils
 */
typedef ModelMatrix<GLfloat> ModelMatrixf;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || defined(GL_DOUBLE)
/// Model transformation double precision matrix
/**
 *  @ingroup math_utils
 */
typedef ModelMatrix<GLdouble> ModelMatrixd;
#endif

/// Class implementing camera matrix named constructors
/** The static methods of this class can be used for the construction
 *  of various camera matrices.
 *
 *  @ingroup math_utils
 */
template <typename T>
class CameraMatrix
 : public eagine::math::matrix<T, 4, 4, true>
{
private:
	typedef eagine::math::matrix<T, 4, 4, true> Base;
public:
	CameraMatrix(void) = default;

	CameraMatrix(const Base& base)
	 : Base(base)
	{ }

	static inline
	auto Perspective(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	)
	{
		return eagine::math::perspective<Base>(
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		)();
	}

	static inline
	auto PerspectiveX(
		Angle<T> xfov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		return eagine::math::perspective<Base>::x(
			xfov,
			aspect,
			z_near,
			z_far
		)();
	}

	static inline
	auto PerspectiveY(
		Angle<T> yfov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		return eagine::math::perspective<Base>::y(
			yfov,
			aspect,
			z_near,
			z_far
		)();
	}

	static inline
	auto Ortho(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	)
	{
		return eagine::math::ortho<Base>(
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		)();
	}

	static inline
	auto OrthoX(
		Angle<T> xfov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		return eagine::math::ortho<Base>::x(
			xfov,
			aspect,
			z_near,
			z_far
		)();
	}

	static inline
	auto OrthoY(
		Angle<T> yfov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		return eagine::math::ortho<Base>::y(
			yfov,
			aspect,
			z_near,
			z_far
		)();
	}

	static inline
	auto LookingAt(
		const Vector<T, 3>& eye,
		const Vector<T, 3>& target
	)
	{
		return eagine::math::looking_at_y_up<Base>(
			eye,
			target
		)();
	}

	static inline
	auto LookingAt(
		const Vector<T, 3>& eye,
		const Vector<T, 3>& target,
		const Vector<T, 3>& up
	)
	{
		return eagine::math::looking_at<Base>(
			eye,
			target,
			up
		)();
	}

	static inline
	auto Orbiting(
		const Vector<T, 3>& target,
		T radius,
		Angle<T> azimuth,
		Angle<T> elevation
	)
	{
		return eagine::math::orbiting_y_up<Base>(
			target,
			radius,
			azimuth,
			elevation
		)();
	}

	static inline
	auto ScreenStretch(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top
	)
	{
		return eagine::math::screen_stretch<Base>(
			x_left,
			x_right,
			y_bottom,
			y_top
		)();
	}

	static inline
	auto ScreenTile(
		unsigned x,
		unsigned y,
		unsigned nx,
		unsigned ny
	)
	{
		return eagine::math::screen_stretch<Base>::tile(x, y, nx, ny)();
	}

	static inline
	auto Pitch(Angle<T> a)
	{
		return eagine::math::pitch<Base>(a)();
	}

	static inline
	auto Yaw(Angle<T> a)
	{
		return eagine::math::yaw<Base>(a)();
	}

	static inline
	auto Roll(Angle<T> a)
	{
		return eagine::math::roll<Base>(a)();
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY || defined(GL_FLOAT)
/// Camera matrix using float numbers
/**
 *  @ingroup math_utils
 */
typedef CameraMatrix<GLfloat> CamMatrixf;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || defined(GL_DOUBLE)
/// Camera matrix using double precition numbers
/**
 *  @ingroup math_utils
 */
typedef CameraMatrix<GLdouble> CamMatrixd;
#endif

template <typename T>
inline
eagine::math::matrix<T,4,4,true>
Inverse(eagine::math::matrix<T,4,4, true> m)
{
	eagine::math::matrix<T,4,4,true> i = eagine::math::identity<
		eagine::math::matrix<T,4,4,true>
	>()();
	eagine::math::gauss_jordan(m, i);
	return m;
}

template <typename T>
inline
Vector<T, 3>
CameraPosition(eagine::math::matrix<T,4,4, true> m)
{
	eagine::math::matrix<T,4,4,true> i = eagine::math::identity<
		eagine::math::matrix<T,4,4,true>
	>()();
	if(eagine::math::gauss_jordan(m, i))
	{
		return Vector<T,3>(eagine::math::column<3>(i));
	}
	return Vector<T,3>();
}

template <typename T>
inline
Vector<T, 3>
CameraDirection(const eagine::math::matrix<T,4,4,true>& m)
{
	using eagine::math::row;
	return -Vector<T, 3>(Row(m, 2));
}

#ifdef NEVER_DEFINED
template <typename T>
class ModelMatrix
 : public Matrix<T, 4, 4>
{
private:
	typedef Matrix<T, 4, 4> Base;
public:
	struct Scale_ { };

	ModelMatrix(Scale_, T sx, T sy, T sz)
	 : Base(oglplus::Nothing())
	{
		InitMatrix4x4(
			*this,
			  sx, T(0), T(0), T(0),
			T(0),   sy, T(0), T(0),
			T(0), T(0),   sz, T(0),
			T(0), T(0), T(0), T(1)
		);
	}

	/// Constructs a scale matrix
	static inline ModelMatrix Scale(T sx, T sy, T sz)
	{
		return ModelMatrix(Scale_(), sx, sy, sz);
	}

	ModelMatrix(RotationA_, Quaternion<T> quat)
	 : Base(oglplus::Nothing())
	{
		quat.Normalize();
		const T a = quat.At(0);
		const T x = quat.At(1);
		const T y = quat.At(2);
		const T z = quat.At(3);
		InitMatrix4x4(
			*this,
			1-2*y*y-2*z*z,  2*x*y-2*a*z,    2*x*z+2*a*y,    T(0),
			2*x*y+2*a*z,    1-2*x*x-2*z*z,  2*y*z-2*a*x,    T(0),
			2*x*z-2*a*y,    2*y*z+2*a*x,    1-2*x*x-2*y*y,  T(0),
			T(0),           T(0),           T(0),           T(1)
		);
	}

	/// Constructs a rotation matrix from a quaternion
	static inline ModelMatrix RotationQ(const Quaternion<T>& quat)
	{
		return ModelMatrix(RotationA_(), quat);
	}

};

template <typename T>
class CameraMatrix
 : public Matrix<T, 4, 4>
{
private:
	typedef Matrix<T, 4, 4> Base;
public:

	/// Constructs an identity matrix
	CameraMatrix(void) = default;

	CameraMatrix(const Base& base)
	 : Base(base)
	{ }

	Vector<T, 3> Position(void) const
	{
		return Vector<T,3>(Inverse(*this).Col(3).Data(), 3);
	}

	Vector<T, 3> Direction(void) const
	{
		return -Vector<T, 3>(this->Row(2).Data(), 3);
	}

	struct Perspective_ { };

	CameraMatrix(
		Perspective_,
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	): Base(oglplus::Nothing())
	{
		T m00 = (T(2) * z_near) / (x_right - x_left);
		T m11 = (T(2) * z_near) / (y_top - y_bottom);
		T m22 = -(z_far + z_near) / (z_far - z_near);

		T m20 = (x_right + x_left) / (x_right - x_left);
		T m21 = (y_top + y_bottom) / (y_top - y_bottom);
		T m23 = -T(1);

		T m32 = -(T(2) * z_far * z_near) / (z_far - z_near);

		InitMatrix4x4(
			*this,
			 m00, T(0),  m20, T(0),
			T(0),  m11,  m21, T(0),
			T(0), T(0),  m22,  m32,
			T(0), T(0),  m23, T(0)
		);
	}

	/// Constructs a perspective projection matrix
	/** Creates a new perspective matrix from @p x_left, @p x_right,
	 *  @p y_botton, @p y_top, @p z_near and @p z_far values.
	 */
	static inline CameraMatrix Perspective(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	)
	{
		return CameraMatrix(
			Perspective_(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	/// Constructs a perspective projection matrix
	/** Creates a new perspective matrix from x-axis @p xfov angle,
	 *  x/y @p aspect ratio and z-axis @p z_near and @p z_far planes
	 */
	static inline CameraMatrix PerspectiveX(
		Angle<T> xfov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		assert(aspect > T(0));
		assert(xfov > Radian<T>(T(0)));

		T x_right = z_near * Tan(xfov * T(0.5));
		T x_left = -x_right;

		T y_bottom = x_left / aspect;
		T y_top = x_right / aspect;

		return CameraMatrix(
			Perspective_(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	/// Constructs a perspective projection matrix
	/** Creates a new perspective matrix from y-axis @p yfov angle,
	 *  x/y @p aspect ratio and z-axis @p z_near and @p z_far planes
	 */
	static inline CameraMatrix PerspectiveY(
		Angle<T> yfov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		assert(aspect > T(0));
		assert(yfov > Angle<T>::Radians(T(0)));

		T y_top = z_near * Tan(yfov * T(0.5));
		T y_bottom = -y_top;

		T x_left = y_bottom * aspect;
		T x_right = y_top * aspect;

		return CameraMatrix(
			Perspective_(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	struct Ortho_ { };

	CameraMatrix(
		Ortho_,
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	): Base(oglplus::Nothing())
	{
		T m00 =  T(2) / (x_right - x_left);
		T m11 =  T(2) / (y_top - y_bottom);
		T m22 = -T(2) / (z_far - z_near);

		T m30 = -(x_right + x_left) / (x_right - x_left);
		T m31 = -(y_top + y_bottom) / (y_top - y_bottom);
		T m32 = -(z_far + z_near)   / (z_far - z_near);

		InitMatrix4x4(
			*this,
			 m00, T(0), T(0),  m30,
			T(0),  m11, T(0),  m31,
			T(0), T(0),  m22,  m32,
			T(0), T(0), T(0), T(1)
		);
	}

	/// Constructs an orthographic projection matrix
	/** Creates a new orthographic matrix from the x-axis @p x_left, @p x_right,
	 *  y-axis @p y_bottom, @p y_top and z-axis @p z_near and @p z_far values
	 */
	static inline CameraMatrix Ortho(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	)
	{
		return CameraMatrix(
			Ortho_(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	/// Constructs an orthographic projection matrix
	/** Creates a new orthographic matrix from x-axis @p width,
	 *  x/y @p aspect ratio and z-axis @p z_near and @p z_far planes
	 */
	static inline CameraMatrix OrthoX(
		T width,
		T aspect,
		T z_near,
		T z_far
	)
	{
		assert(aspect > T(0));
		assert(width > T(0));

		T x_right = width / T(2);
		T x_left = -x_right;

		T y_bottom = x_left / aspect;
		T y_top = x_right / aspect;

		return CameraMatrix(
			Ortho_(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	/// Constructs an orthographic projection matrix
	/** Creates a new orthographic matrix from y-axis @p height,
	 *  x/y @p aspect ratio and z-axis @p z_near and @p z_far planes
	 */
	static inline CameraMatrix OrthoY(
		T height,
		T aspect,
		T z_near,
		T z_far
	)
	{
		assert(aspect > T(0));
		assert(height > T(0));

		T y_top = height / T(2);
		T y_bottom = -y_top;

		T x_left = y_bottom * aspect;
		T x_right = y_top * aspect;

		return CameraMatrix(
			Ortho_(),
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	struct ScreenStretch_ { };

	CameraMatrix(
		ScreenStretch_,
		T x_left,
		T x_right,
		T y_bottom,
		T y_top
	): Base(oglplus::Nothing())
	{
		assert((x_right - x_left) != T(0));
		assert((y_top - y_bottom) != T(0));

		T m00 =  T(2) / (x_right - x_left);
		T m11 =  T(2) / (y_top - y_bottom);

		T m30 = -(x_right + x_left) / (x_right - x_left);
		T m31 = -(y_top + y_bottom) / (y_top - y_bottom);

		InitMatrix4x4(
			*this,
			 m00, T(0), T(0),  m30,
			T(0),  m11, T(0),  m31,
			T(0), T(0), T(1), T(0),
			T(0), T(0), T(0), T(1)
		);
	}

	/// Constructs a matrix for stretching NDCs after projection
	/** ScreenStretch constructs a matrix that can be used to stretch
	 *  the normalized device coordinates after projection is applied.
	 */
	static inline CameraMatrix ScreenStretch(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top
	)
	{
		return CameraMatrix(
			ScreenStretch_(),
			x_left,
			x_right,
			y_bottom,
			y_top
		);
	}

	/// Constructs a matrix for stretching NDCs after projection
	/** ScreenTile constructs a matrix, that divides the screen into
	 *  rectangular tiles with the specified divisions and stretches
	 *  the normalized device coordinates to show the specified tile.
	 *
	 *  @pre (x >= 0) && (nx > 0) && (y >= 0) && (ny >= 0)
	 */
	static inline CameraMatrix ScreenTile(
		unsigned x,
		unsigned y,
		unsigned nx,
		unsigned ny
	)
	{
		assert(x < nx);
		assert(y < ny);

		return CameraMatrix(
			ScreenStretch_(),
			-T(1)+T(2*(x+0))/T(nx),
			-T(1)+T(2*(x+1))/T(nx),
			-T(1)+T(2*(y+0))/T(ny),
			-T(1)+T(2*(y+1))/T(ny)
		);
	}

	struct LookingAt_ { };

	CameraMatrix(
		LookingAt_,
		const Vector<T, 3>& eye,
		const Vector<T, 3>& target
	): Base(oglplus::Nothing())
	{
		assert(eye != target);
		Vector<T, 3> z = Normalized(eye - target);
		T zx = z[0];
		T zz = z[2];
		Vector<T, 3> t(zz, T(0), -zx);
		Vector<T, 3> y = Normalized(Cross(z, t));
		Vector<T, 3> x = Cross(y, z);

		InitMatrix4x4(
			*this,
			x[0], x[1], x[2],
			-Dot(eye, x),

			y[0], y[1], y[2],
			-Dot(eye, y),

			z[0], z[1], z[2],
			-Dot(eye, z),

			T(0), T(0), T(0), T(1)
		);
	}

	/// Constructs a 'look-at' matrix from eye and target positions
	static inline CameraMatrix LookingAt(
		const Vector<T, 3>& eye,
		const Vector<T, 3>& target
	)
	{
		return CameraMatrix(LookingAt_(), eye, target);
	}

	CameraMatrix(
		LookingAt_,
		const Vector<T, 3>& eye,
		const Vector<T, 3>& target,
		const Vector<T, 3>& up
	): Base(oglplus::Nothing())
	{
		assert(eye != target);
		Vector<T, 3> z = Normalized(eye - target);
		T dupz = Dot(up, z);
		assert(dupz < 0.9 && dupz >-0.9);
		Vector<T, 3> y = Normalized(
			dupz != 0.0?
			up-z*dupz:
			up
		);
		Vector<T, 3> x = Cross(y, z);

		InitMatrix4x4(
			*this,
			x[0], x[1], x[2],
			-Dot(eye, x),

			y[0], y[1], y[2],
			-Dot(eye, y),

			z[0], z[1], z[2],
			-Dot(eye, z),

			T(0), T(0), T(0), T(1)
		);
	}

	/// Constructs 'look-at' matrix from eye and target positions and up vector
	static inline CameraMatrix LookingAt(
		const Vector<T, 3>& eye,
		const Vector<T, 3>& target,
		const Vector<T, 3>& up
	)
	{
		return CameraMatrix(LookingAt_(), eye, target, up);
	}

	struct Orbiting_ { };

	CameraMatrix(
		Orbiting_,
		const Vector<T, 3>& target,
		T radius,
		Angle<T> azimuth,
		Angle<T> elevation
	)
	{
		Vector<T, 3> z(
			Cos(elevation) * Cos(azimuth),
			Sin(elevation),
			Cos(elevation) *-Sin(azimuth)
		);
		Vector<T, 3> x(
			-Sin(azimuth),
			T(0),
			-Cos(azimuth)
		);
		Vector<T, 3> y = Cross(z, x);

		InitMatrix4x4(
			*this,
			x[0], x[1], x[2],
			Dot(x, z) * -radius - Dot(x, target),

			y[0], y[1], y[2],
			Dot(y, z) * -radius - Dot(y, target),

			z[0], z[1], z[2],
			Dot(z, z) * -radius - Dot(z, target),

			T(0), T(0), T(0), T(1)
		);

	}

	/// Constructs a matrix from target, radius, azimuth and elevation
	static inline CameraMatrix Orbiting(
		const Vector<T, 3>& target,
		T radius,
		Angle<T> azimuth,
		Angle<T> elevation
	)
	{
		return CameraMatrix(
			Orbiting_(),
			target,
			radius,
			azimuth,
			elevation
		);
	}

};

#endif // NEVER_DEFINED

} // namespace oglplus

#endif // include guard