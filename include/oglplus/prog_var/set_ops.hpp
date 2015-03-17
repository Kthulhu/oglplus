/**
 *  .file oglplus/prog_var/set_ops.hpp
 *  .brief Program variable (uniform / vertex-attribute) helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROG_VAR_SET_OPS_1107121519_HPP
#define OGLPLUS_PROG_VAR_SET_OPS_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/boolean.hpp>
#include <oglplus/error/basic.hpp>
#include <oglplus/prog_var/callers.hpp>

#include <type_traits>
#include <cstddef>

namespace oglplus {

template <class OpsTag, class VarTag, class TypTag, class T, std::size_t M>
class ProgVarBaseSetOps;

template <typename OpsTag, typename VarTag, typename T, std::size_t M>
class ProgVarBaseSetOps<OpsTag, VarTag, tag::NativeTypes, T, M>
 : public ProgVarSetters<OpsTag, VarTag, tag::NativeTypes>
 , public ProgVarCallers<OpsTag, T>
{
private:
	typedef ProgVarSetters<OpsTag, VarTag, tag::NativeTypes> Setters;
	typedef ProgVarCallers<OpsTag, T> Callers;

	OGLPLUS_ERROR_REUSE_CONTEXT(Setters)

	typedef std::false_type _set_done;
	typedef std::true_type  _set_cont;

	template <std::size_t N>
	static std::integral_constant<bool,  (N > 4)> _set_mode(void)
	{
		return std::integral_constant<bool, (N > 4)>();
	}

	template <std::size_t N, typename V>
	static void _do_set_v(
		_set_cont,
		GLuint program,
		GLuint base_location,
		GLuint location,
		const V* v
	)
	{
		std::integral_constant<std::size_t, 4> nparam;
		Callers::_call_set_v(
			program,
			location,
			Setters::_fns_v(nparam, v),
			v
		);
		OGLPLUS_CHECK_CTXT(
			ProgVarError,
			Program(ProgramName(program)).
			Index(base_location)
		);
		_do_set_v<N - 4, V>(
			_set_mode<N - 4>(),
			program,
			base_location,
			location+1,
			v+4
		);
	}

	template <std::size_t N, typename V>
	static void _do_set_v(
		_set_done,
		GLuint program,
		GLuint base_location,
		GLuint location,
		const V* v
	)
	{
		std::integral_constant<std::size_t, N> nparam;
		Callers::_call_set_v(
			program,
			location,
			Setters::_fns_v(nparam, v),
			v
		);
		OGLPLUS_CHECK_CTXT(
			ProgVarError,
			Program(ProgramName(program)).
			Index(base_location)
		);
	}

	template <std::size_t N, typename V>
	static void _do_set_n(
		_set_done,
		GLuint program,
		GLuint base_location,
		GLuint location,
		GLsizei n,
		const V* v
	)
	{
		std::integral_constant<std::size_t, N> nparam;
		Callers::_call_set_vn(
			program,
			location,
			n,
			Setters::_fns_v(nparam, v),
			v
		);
		OGLPLUS_CHECK_CTXT(
			ProgVarError,
			Program(ProgramName(program)).
			Index(base_location)
		);
	}


	template <typename S, typename ... V>
	static void _do_set_t(
		_set_cont,
		GLuint program,
		GLuint base_location,
		GLuint location,
		S v0, S v1, S v2, S v3,
		V ... v
	)
	{
		std::integral_constant<std::size_t, 4> nparam;
		Callers::_call_set_t(
			program,
			location,
			Setters::_fns_t(nparam, &v0),
			v0, v1, v2, v3
		);
		OGLPLUS_CHECK_CTXT(
			ProgVarError,
			Program(ProgramName(program)).
			Index(base_location)
		);
		_do_set_t(
			_set_mode<sizeof...(V)>(),
			program,
			base_location,
			location+1,
			v...
		);
	}

	template <typename ... V>
	static void _do_set_t(
		_set_done,
		GLuint program,
		GLuint base_location,
		GLuint location,
		V ... v
	)
	{
		std::integral_constant<std::size_t, sizeof...(V)> nparam;
		Callers::_call_set_t(
			program,
			location,
			Setters::_fns_t(nparam, &v...),
			v...
		);
		OGLPLUS_CHECK_CTXT(
			ProgVarError,
			Program(ProgramName(program)).
			Index(base_location)
		);
	}

protected:

	template <typename ... V>
	static void _do_set(GLuint program, GLuint location, V ... v)
	{
		static_assert(
			(sizeof...(V) > 0) && (sizeof...(V) <= M),
			"Set requires 1 to M arguments"
		);
		_do_set_t(
			_set_mode<sizeof...(V)>(),
			program,
			location,
			location,
			v...
		);
		OGLPLUS_CHECK_CTXT(
			ProgVarError,
			Program(ProgramName(program)).
			Index(location)
		);
	}

	template <std::size_t Cols, typename V>
	static void _do_set(GLuint program, GLuint location, const V* v)
	{
		static_assert(
			(Cols > 0) && (Cols <= M),
			"The number of elements must be between 1 and M"
		);
		_do_set_v<Cols, V>(
			_set_mode<Cols>(),
			program,
			location,
			location,
			v
		);
	}

	template <std::size_t Cols, typename V>
	static void _do_set_many(GLuint prog, GLuint location, GLsizei n, const V*v)
	{
		static_assert(
			(Cols > 0) && (Cols <= M),
			"The number of elements must be between 1 and M"
		);
		_do_set_n<Cols, V>(
			_set_mode<Cols>(),
			prog,
			location,
			location,
			n,
			v
		);
	}
};

template <typename OpsTag, typename VarTag, typename T, std::size_t M>
class ProgVarBaseSetOps<OpsTag, VarTag, tag::MatrixTypes, T, M>
 : public ProgVarSetters<OpsTag, VarTag, tag::MatrixTypes>
 , public ProgVarCallers<OpsTag, T>
{
private:
	typedef ProgVarSetters<OpsTag, VarTag, tag::MatrixTypes> Setters;
	typedef ProgVarCallers<OpsTag, T> Callers;

	OGLPLUS_ERROR_REUSE_CONTEXT(Setters)
protected:
	template <std::size_t Cols, std::size_t Rows, typename V>
	static void _do_set_mat(
		GLuint program,
		GLuint location,
		GLsizei count,
		Boolean transpose,
		V* v
	)
	{
		static_assert(
			(Cols > 0) && (Cols <= 4),
			"The number of columns must be between 1 and 4"
		);
		static_assert(
			(Rows > 0) && (Rows <= 4),
			"The number of rows must be between 1 and 4"
		);
		std::integral_constant<std::size_t, Rows> rows;
		std::integral_constant<std::size_t, Cols> cols;
		Callers::_call_set_m(
			program,
			location,
			count,
			transpose._get(),
			Setters::_fns_v(cols, rows, v),
			v
		);
		OGLPLUS_CHECK_CTXT(
			ProgVarError,
			Program(ProgramName(program)).
			Index(location)
		);
	}

	template <std::size_t Cols, typename V, typename ... P>
	static void _do_set_mat_p(
		GLuint program,
		GLuint location,
		bool transpose,
		V v,
		P ... p
	)
	{
		static_assert(
			(Cols > 0) && (Cols <= 4),
			"The number of columns must be between 1 and 4"
		);
		static_assert(
			(sizeof...(P) + 1) % Cols == 0,
			"Not enough values for the last row"
		);
		V values[] = {v, V(p)...};
		_do_set_mat<Cols, (sizeof...(P) + 1) / Cols, V>(
			program,
			location,
			1,
			transpose,
			values
		);
	}
};

} // namespace oglplus

#endif // include guard