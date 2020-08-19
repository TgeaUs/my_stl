#pragma once
#ifndef _MYALLOCATOR_H_
#define _MYALLOCATOR_H_
#include <iostream>
#include <new>
#include <cstddef> //ptrdiff_t


//内存分配器 普通的接管new
namespace MyAllocator
{
	template <typename _Tp>
	inline _Tp* _allocator(size_t size, _Tp*)
	{
		if (size == 0)
			std::cout << size;
#if ISDIALOGUE
		std::cout << "_allocator()分配的内存类型是" << typeid(_Tp).name() << "\n""\n";
#endif
		_Tp *temp = static_cast<_Tp*>(::operator new(size * sizeof(_Tp))); //为了连续空间打大小
		return temp;
	}
	template <typename _Tp>
	inline void _deallocator(_Tp* buffer)
	{
		if (buffer == nullptr)
			std::cout << "空";
		::operator delete(buffer);
	}

	template <typename _Tp>
	class allocator
	{
	public:
		using value_type	= _Tp;		//表示你这个迭代器的类型
		using size_type		= size_t;	//大小
		using difference_type = ptrdiff_t;	//表示距离 两个迭代器
		using reference = value_type&;		// 从没有使用过
		using pointer	= value_type*;		// 从没有使用过
		
		//分配内存 无任何特殊意义 纯粹的new
		static _Tp* allocate(size_type n)
		{
			return _allocator(n,(value_type*)0);//转化类型 这是两个参数的分配器
		}
		//释放内存 无任何特殊意义 纯粹的delete
		static void deallocate(pointer p)
		{
			_deallocator(p);
		}
		static void deallocate(pointer first,pointer last)
		{
			std::cout << "我到这里了";
		}

	};

}
#endif // !_MYALLOCATOR_H_
