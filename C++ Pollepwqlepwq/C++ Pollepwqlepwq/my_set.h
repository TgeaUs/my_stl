#pragma once
#ifndef _MY_SET_H_
#define _MY_SET_H_
#include "my_allocator.h"
#include "my_functional.h"
#include "my_tree.h"
namespace MySet
{
	template <typename key,typename compare=MyFunctional::less<key>,typename allocator=MyAllocator::allocator<key>>
	class set
	{
	public:
		using key_type = key;
		using value_type = key;
		using key_compare = compare;
		using value_compare = compare;
	private:
		using rep_type = MyTree::rb_tree<key_type, value_type, MyFunctional::identity<value_type>, key_compare>;
		rep_type T;  // red-black tree representing set


	public:
		using pointer			= typename rep_type::const_pointer;
		using const_pointer		= typename rep_type::const_pointer;
		using reference			= typename rep_type::const_reference;
		using const_reference	= typename rep_type::const_reference;
		using iterator			= typename rep_type::const_iterator;
		using const_iterator	= typename rep_type::const_iterator;
		using size_type			= typename rep_type::size_type;
		using difference_type	= typename rep_type::difference_type;
		using allocator_type	= typename rep_type::allocator_type;

		set() :T() {}

		//µü´úÆ÷
		iterator begin()const { return T.begin(); }
		iterator end()const { return T.end(); }
		//ÈÝÁ¿
		bool empty() const { return T.empty(); }
		size_type size() const { return T.size(); }
		size_type max_size() const { return T.max_size(); }



		MyPair::pair<iterator,bool> insert(const value_type& x)
		{
			MyPair::pair<typename rep_type::iterator, bool> p = T.insert_unique(x);
			return MyPair::pair<iterator, bool>(p.first, p.second);
		}
	};
}
#endif // !_MY_SET_H_
