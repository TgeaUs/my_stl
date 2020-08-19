#pragma once
#ifndef _MYALLOCATOR_H_
#define _MYALLOCATOR_H_
#include <iostream>
#include <new>
#include <cstddef> //ptrdiff_t


//�ڴ������ ��ͨ�Ľӹ�new
namespace MyAllocator
{
	template <typename _Tp>
	inline _Tp* _allocator(size_t size, _Tp*)
	{
		if (size == 0)
			std::cout << size;
#if ISDIALOGUE
		std::cout << "_allocator()������ڴ�������" << typeid(_Tp).name() << "\n""\n";
#endif
		_Tp *temp = static_cast<_Tp*>(::operator new(size * sizeof(_Tp))); //Ϊ�������ռ���С
		return temp;
	}
	template <typename _Tp>
	inline void _deallocator(_Tp* buffer)
	{
		if (buffer == nullptr)
			std::cout << "��";
		::operator delete(buffer);
	}

	template <typename _Tp>
	class allocator
	{
	public:
		using value_type	= _Tp;		//��ʾ�����������������
		using size_type		= size_t;	//��С
		using difference_type = ptrdiff_t;	//��ʾ���� ����������
		using reference = value_type&;		// ��û��ʹ�ù�
		using pointer	= value_type*;		// ��û��ʹ�ù�
		
		//�����ڴ� ���κ��������� �����new
		static _Tp* allocate(size_type n)
		{
			return _allocator(n,(value_type*)0);//ת������ �������������ķ�����
		}
		//�ͷ��ڴ� ���κ��������� �����delete
		static void deallocate(pointer p)
		{
			_deallocator(p);
		}
		static void deallocate(pointer first,pointer last)
		{
			std::cout << "�ҵ�������";
		}

	};

}
#endif // !_MYALLOCATOR_H_
