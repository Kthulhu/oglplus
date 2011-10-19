/**
 *  @file oglplus/uniform_block.hpp
 *  @brief Named uniform block wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_UNIFORM_BLOCK_1107121519_HPP
#define OGLPLUS_UNIFORM_BLOCK_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/error.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/program.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/string.hpp>

#include <cassert>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1 || GL_ARB_uniform_buffer_object

/// Encapsulates shader uniform block operations
/**
 *  @ingroup shader_variables
 */
class UniformBlock
 : public FriendOf<ProgramOps>
{
protected:
	GLuint _program;
	GLint _index;

	friend class FriendOf<UniformOps>;

	static GLenum _translate_ref(Shader::Kind shader_kind)
	{
		switch(shader_kind)
		{
			case Shader::Kind::Vertex:
			return GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER;
#if GL_VERSION_4_0 || GL_ARB_tessellation_shader
			case Shader::Kind::TessControl:
			return GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER;
			case Shader::Kind::TessEvaluation:
			return GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER;
#endif // tessellation shader
			case Shader::Kind::Geometry:
			return GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER;
			case Shader::Kind::Fragment:
			return GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER;
		}
		return 0;
	}

	static GLenum _translate_max(Shader::Kind shader_kind)
	{
		switch(shader_kind)
		{
			case Shader::Kind::Vertex:
			return GL_MAX_VERTEX_UNIFORM_BLOCKS;
#if GL_VERSION_4_0 || GL_ARB_tessellation_shader
			case Shader::Kind::TessControl:
			return GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS;
			case Shader::Kind::TessEvaluation:
			return GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS;
#endif // tessellation shader
			case Shader::Kind::Geometry:
			return GL_MAX_GEOMETRY_UNIFORM_BLOCKS;
			case Shader::Kind::Fragment:
			return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
		}
		return 0;
	}

	void _check(const GLchar* identifier) const
	{
		ThrowOnError(OGLPLUS_ERROR_INFO(GetUniformBlockIndex));
		if(_index == GLint(-1))
		{
			ThrowOnError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive uniform block",
				OGLPLUS_ERROR_INFO(GetUniformBlockIndex),
				Error::PropertyMap({
					{"identifier", identifier}
				})
			);
		}
	}
public:
	/// Reference a uniform block at @p index in the @p program
	UniformBlock(const ProgramOps& program, GLint index)
	 : _program(FriendOf<ProgramOps>::GetName(program))
	 , _index(index)
	{ }

	/// Reference a uniform block @p identifier in the @p program
	UniformBlock(const ProgramOps& program, const GLchar* identifier)
	 : _program(FriendOf<ProgramOps>::GetName(program))
	 , _index(::glGetUniformBlockIndex(_program, identifier))
	{
		_check(identifier);
	}

	/// Reference a uniform block @p identifier in the @p program
	UniformBlock(const ProgramOps& program, const String& identifier)
	 : _program(FriendOf<ProgramOps>::GetName(program))
	 , _index(::glGetUniformBlockIndex(_program, identifier.c_str()))
	{
		_check(identifier.c_str());
	}

	/// Return the maximum number of uniform blocks for a @p shader_kind
	static GLuint MaxIn(Shader::Kind shader_kind)
	{
		GLint result;
		::glGetIntegerv(_translate_max(shader_kind), &result);
		AssertNoError(OGLPLUS_ERROR_INFO(GetIntegerv));
		assert(result >= 0);
		return GLuint(result);
	}

	/// Returns true if this uniform block is referenced by @p shader_kind
	bool ReferencedBy(Shader::Kind shader_kind) const
	{
		GLint result;
		::glGetActiveUniformBlockiv(
			_program,
			_index,
			_translate_ref(shader_kind),
			&result
		);
		AssertNoError(OGLPLUS_ERROR_INFO(GetActiveUniformBlockiv));
		return result == GL_TRUE;
	}

	/// Returns the size of the uniform block
	GLuint DataSize(void) const
	{
		GLint result;
		::glGetActiveUniformBlockiv(
			_program,
			_index,
			GL_UNIFORM_BLOCK_DATA_SIZE,
			&result
		);
		AssertNoError(OGLPLUS_ERROR_INFO(GetActiveUniformBlockiv));
		assert(result >= 0);
		return GLuint(result);
	}

	void Binding(UniformBufferBindingPoint binding) const
	{
		::glUniformBlockBinding(
			_program,
			_index,
			GLuint(binding)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(UniformBlockBinding));
	}
};

#endif // uniform buffer object

} // namespace oglplus

#endif // include guard
