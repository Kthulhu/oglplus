//  File doc/quickbook/eglplus/quickref/enums/texture_target.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/eglplus/texture_target.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_texture_target
namespace eglplus {

enum class TextureTarget : EGLenum
{
	NoTexture = EGL_NO_TEXTURE,
	Texture2d = EGL_TEXTURE_2D
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<TextureTarget> __EnumValueName<TextureTarget>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(TextureTarget);
#endif

} // namespace eglplus
//]