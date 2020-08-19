#pragma once
#ifndef _MYTYPETRAITS_H_
#define _MYTYPETRAITS_H_
#define __STL_TEMPLATE_NULL template<>
namespace MyType_traits
{
	//��Щ���Ǳ�׼���Դ���� ����������ȡ ������ȡ��Ļ��������ǲ�����Ҫ�� �ر���ָ��
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

	//����ָ��
	template <class _Tp>
	struct __type_traits<_Tp*>
	{
		using     has_trivial_default_constructor	= __true_type;
		using     has_trivial_copy_constructor		= __true_type;
		using     has_trivial_assignment_operator	=__true_type;
		using     has_trivial_destructor	= __true_type;
		using     is_POD_type				= __true_type;
	};	
	//���ڿ�ʼ��ָ��� �ػ�����
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
