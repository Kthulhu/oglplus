//  File doc/quickbook/eglplus/quickref/enums/context_attrib.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/eglplus/context_attrib.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_context_attrib
namespace eglplus {

enum class ContextAttrib : EGLenum
{
	MajorVersion                    = EGL_CONTEXT_MAJOR_VERSION,
	MinorVersion                    = EGL_CONTEXT_MINOR_VERSION,
	Flags                           = EGL_CONTEXT_FLAGS,
	OpenGLProfileMask               = EGL_CONTEXT_OPENGL_PROFILE_MASK,
	OpenGLResetNotificationStrategy = EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<ContextAttrib> __EnumValueName<ContextAttrib>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(ContextAttrib);
#endif

} // namespace eglplus
//]