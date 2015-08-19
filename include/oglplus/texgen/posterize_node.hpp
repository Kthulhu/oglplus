/**
 *  @file oglplus/texgen/posterize_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_POSTERIZE_NODE_HPP
#define OGLPLUS_TEXGEN_POSTERIZE_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/adaptive_output.hpp>
#include <oglplus/texgen/constant_output.hpp>

namespace oglplus {
namespace texgen {

class PosterizeNode;

class PosterizeOutputSlot
 : public BaseOutputSlot
{
private:
	friend class PosterizeNode;

	FallbackInputSlot<AdaptiveConstantOutputSlot,true> _input;
	FallbackInputSlot<ConstantOutputSlot<Vec4f>, true> _levels;
public:
	PosterizeOutputSlot(Node& parent);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;
};

class PosterizeNode
 : public SingleBaseOutputNode
{
private:
	PosterizeOutputSlot _output;
public:
	PosterizeNode(void);

	PosterizeNode& SetLevels(Vec4f offset);

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t i)
	OGLPLUS_OVERRIDE;

	BaseOutputSlot& SingleOutput(void)
	OGLPLUS_OVERRIDE;
};


} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/posterize_node.ipp>
//#endif

#endif // include guard
