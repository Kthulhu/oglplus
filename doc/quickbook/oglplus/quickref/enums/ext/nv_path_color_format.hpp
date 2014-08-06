//  File doc/quickbook/oglplus/quickref/enums/ext/nv_path_color_format.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/ext/nv_path_color_format.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_ext_nv_path_color_format
namespace oglplus {

enum class PathNVColorFormat : GLenum
{
	Luminance      = GL_LUMINANCE,
	Alpha          = GL_ALPHA,
	Intensity      = GL_INTENSITY,
	LuminanceAlpha = GL_LUMINANCE_ALPHA,
	RGB            = GL_RGB,
	RGBA           = GL_RGBA
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<PathNVColorFormat> __EnumValueName<PathNVColorFormat>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(PathNVColorFormat);
#endif

} // namespace oglplus
//]