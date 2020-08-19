#pragma once
#ifndef _MYTYPETRAITS_H_
#define _MYTYPETRAITS_H_
#define __STL_TEMPLATE_NULL template<>
namespace MyType_traits
{
	//这些都是标准库的源代码 叫做类型萃取 就是萃取你的基础类型是不是重要的 特别是指针
	struct __true_type {};
	struct __false_type {};
	template <class _Tp>
	struct __type_traits {
		using     this_du__true_typemmy_member_must_be_first = __true_type;
		using     has_trivial_default_constructor	= __false_type;
		using     has_trivial_copy_constructor		= __false_type;
		using     has_trivial_assignment_operator	= __false_type;
		using     has_trivial_destructor			= __false_type;
		using     is_POD_type						= __false_type;
	};

	//泛化指针
	template <class _Tp>
	struct __type_traits<_Tp*>
	{
		using     has_trivial_default_constructor	= __true_type;
		using     has_trivial_copy_constructor		= __true_type;
		using     has_trivial_assignment_operator	=__true_type;
		using     has_trivial_destructor	= __true_type;
		using     is_POD_type				= __true_type;
	};	
	//现在开始无指针的 特化类型
	__STL_TEMPLATE_NULL
	struct __type_traits<bool>
	{
		using     has_trivial_default_constructor = __true_type;
		using     has_trivial_default_constructor	= __true_type;
		using     has_trivial_copy_constructor		= __true_type;
		using     has_trivial_assignment_operator	=__true_type;
		using     has_trivial_destructor	= __true_type;
		using     is_POD_type				= __true_type;
	};
	__STL_TEMPLATE_NULL
	struct __type_traits<char>
	{
		using     has_trivial_default_constructor	= __true_type;
		using     has_trivial_copy_constructor		= __true_type;
		using     has_trivial_assignment_operator	=__true_type;
		using     has_trivial_destructor	= __true_type;
		using     is_POD_type				= __true_type;
	};
	__STL_TEMPLATE_NULL
		struct __type_traits<signed char>
	{
		using     has_trivial_default_constructor = __true_type;
		using     has_trivial_copy_constructor = __true_type;
		using     has_trivial_assignment_operator = __true_type;
		using     has_trivial_destructor = __true_type;
		using     is_POD_type = __true_type;
	};
	__STL_TEMPLATE_NULL
		struct __type_traits<unsigned char>
	{
		using     has_trivial_default_constructor = __true_type;
		using     has_trivial_copy_constructor = __true_type;
		using     has_trivial_assignment_operator = __true_type;
		using     has_trivial_destructor = __true_type;
		using     is_POD_type = __true_type;
	};
	__STL_TEMPLATE_NULL
		struct __type_traits<wchar_t>
	{
		using     has_trivial_default_constructor = __true_type;
		using     has_trivial_copy_constructor = __true_type;
		using     has_trivial_assignment_operator = __true_type;
		using     has_trivial_destructor = __true_type;
		using     is_POD_type = __true_type;
	};

};

#endif // !_MYTYPETRAITS_H_
