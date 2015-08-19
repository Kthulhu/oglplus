/**
 *  @file oglplus/texgen/checker_node.ipp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/config/basic.hpp>
#include <cassert>

namespace oglplus {
namespace texgen {

OGLPLUS_LIB_FUNC
CheckerOutputSlot::
CheckerOutputSlot(Node& parent)
 : BaseOutputSlot(parent)
 , _coord(parent, "Coordinate")
 , _repeat(parent, "Repeat", Vec3f(8,8,8))
{ }

OGLPLUS_LIB_FUNC
const char*
CheckerOutputSlot::
TypeName(void)
{
	return "Checker";
}

OGLPLUS_LIB_FUNC
SlotDataType
CheckerOutputSlot::
ValueType(void)
{
	return SlotDataType::Int;
}

OGLPLUS_LIB_FUNC
std::ostream&
CheckerOutputSlot::
Definitions(std::ostream& result, CompileContext& context)
{
	_coord.Definitions(result, context);
	_repeat.Definitions(result, context);

	const SlotDataType v3 = SlotDataType::FloatVec3;

	result << "int ";
	AppendId(result);
	result << "(vec3 po, vec3 so)\n";
	result << "{\n";
	result << "	vec3 c = ";
	ConversionPrefix(result, _coord.ValueType(), v3);
	_coord.Expression(result, context) << "(po, so)";
	ConversionSuffix(result, _coord.ValueType(), v3,0,0,0,0) << ";\n";
	result << "	c *= ";
	ConversionPrefix(result, _repeat.ValueType(), v3);
	_repeat.Expression(result, context) <<"(po, so)";
	ConversionSuffix(result, _repeat.ValueType(), v3) << ";\n";
	result << "	return ((int(c.x)%2+int(c.y)%2+int(c.z)%2)%2);\n";
	result << "}\n";
	return result;
}

OGLPLUS_LIB_FUNC
CheckerNode::
CheckerNode(void)
 : _output(*this)
{ }

OGLPLUS_LIB_FUNC
CheckerNode&
CheckerNode::
SetRepeat(Vec3f scale)
{
	_output._repeat.Fallback().SetValue(scale);
	return *this;
}

OGLPLUS_LIB_FUNC
std::size_t
CheckerNode::
InputCount(void)
{
	return 2;
}

OGLPLUS_LIB_FUNC
InputSlot&
CheckerNode::
Input(std::size_t i)
{
	assert(i < InputCount());
	if(i == 0) return _output._coord;
	return _output._repeat;
}

OGLPLUS_LIB_FUNC
BaseOutputSlot&
CheckerNode::
SingleOutput(void)
{
	return _output;
}

} // namespace texgen
} // namespace oglplus

