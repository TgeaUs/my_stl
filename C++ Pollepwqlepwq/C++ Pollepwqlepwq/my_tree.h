#pragma once
#ifndef _MY_TREE_H_
#define _MY_TREE_H_
#include "my_allocator.h"
#include "my_pair.h"
namespace MyTree
{

	//此篇章为map set multiset/map的底层容器
	//Start: 2020/8/14

	//End::2020 /8/18
	
		
	
	
	using rb_tree_Color_type = bool;
	const rb_tree_Color_type rb_tree_red = false; //红色
	const rb_tree_Color_type rb_tree_black = true; //黑色




	struct rb_tree_node_base
	{
		using color_type = rb_tree_Color_type;
		using base_ptr = rb_tree_node_base*;

		color_type color;
		base_ptr parent; //父亲
		base_ptr left;
		base_ptr right;

		static base_ptr minimum(base_ptr x)
		{
			while (x->right != 0)
			{
				x = x->right;
			}
			return x;
		}

		static base_ptr maximum(base_ptr x)
		{
			while (x->left != 0)
			{
				x = x->left;
			}
			return x;
		}
	};
	template<typename value>
	class rb_tree_node :public rb_tree_node_base
	{
	public:
		using like_type = rb_tree_node<value>;
		value value_field;
	};

	//个人感觉这里设计有问题 在insert的时候 类型是rb_tree_node
	//如果设计继承 基本没办法转型
	template<typename value>
	class rb_tree_iterator :public rb_tree_node<value>
	{
	public:
		//前进
		void increment()
		{
			if (node->right != 0)
			{
				node = node->right;
				while (node->left != 0)
				{
					node = node->left;
				}
			}
			else
			{
				base_ptr y = node->parent;
				while (node == y->right)
				{
					node = y;
					y = y->parent;
				}
				if (node->right != y)
				{
					node = y;
				}
			}
		}
		void decrement()
		{
			if (node->color == rb_tree_red && node->parent->parent == node)
			{
				node = node->right;
			}
			else if (node->left != 0)
			{
				base_ptr y = node->left;
				while (y->right != 0)
					y = y->right;
				node = y;
			}
			else
			{
				base_ptr y = node->parent;
				while (node == y->left)
				{
					node = y;
					y = y->parent;
				}
				node = y;
			}
		}
	public:
		using value_type = value;
		using reference = value&;
		using iterator_category = MyIterator_traits::bidirectional_iterator_tag;

		using self = rb_tree_iterator<value>;
		using base_ptr = rb_tree_node_base*;
		using link_type = rb_tree_node<value>*;
		using iterator = rb_tree_iterator<value>;
		base_ptr node;

		rb_tree_iterator(link_type __x) { node = __x; }
		rb_tree_iterator() {}

		reference operator*() const { return static_cast<link_type>(node)->value_field; }

		self& operator++() { increment(); return *this; }
		self& operator--() { decrement(); return *this; }

		self operator++(int)
		{
			self temp = *this;
			increment();
			return temp;
		}

		self operator--(int)
		{
			self temp = *this;
			decrement();
			return temp;
		}
		bool operator!=(const self& x)
		{
			return node != x.node;
		}

		bool operator==(const self& x)
		{
			return node == x.node;
		}
	};



	

	template<
		typename key,
		typename value,
		typename keyOfvalue,
		typename compare,
		typename allocator = MyAllocator::allocator<value>>
		class rb_tree
	{
	public:
		using size_type = value;
		using size_t = size_type;
		using reference = value&;
		using const_reference = const value&;
		using pointer = value*;
		using const_pointer		= const value*;
		using difference_type	= ptrdiff_t;
		using self = rb_tree<key, value, keyOfvalue, compare>;

		using base_ptr = rb_tree_node_base*;
		//获取节点
		using link_type = rb_tree_node<value>*;
		using tree_node_allocator = MyAllocator::allocator<rb_tree_node<value>>;

		//迭代器
		using iterator		 = rb_tree_iterator<value>;
		using const_iterator =rb_tree_iterator<value>;
		using allocator_type = allocator;

	protected:
		size_type node_count;
		compare key_compare;
		link_type header;

		using color_type = rb_tree_Color_type;

		static color_type& color(link_type x) { return x->color; } //取得颜色
		link_type get_node() const { return tree_node_allocator::allocate(1); } //取得内存
		link_type& root()const { return (link_type&)header->parent; }                   //取得根節點
		link_type& leftmost()const { return (link_type&)header->left; }
		link_type& rightmost()const { return (link_type&)header->right; }

		//获取节点的操作
		static reference get_value(link_type x) { return x->value_field; }
		static const key& get_key(link_type x) { return keyOfvalue()(get_value(x)); }
		static link_type& get_left(link_type x) { return (link_type&)x->left; }
		static link_type& get_right(link_type x) { return (link_type&)x->right; }
		static link_type& get_parent(link_type x) { return (link_type&)x->parent; }


		static const key& get_key(base_ptr __x)
		{
			return keyOfvalue()(get_value(link_type(__x)));
		}
		//数据的操作
		//获取节点 并且分配内存+值
		link_type create_node(const value& x)
		{
			link_type temp = get_node();
			try
			{
				MyConstruct::construct(&temp->value_field, x);

			}
			catch (...)
			{
				throw std::bad_alloc();
			}
			return temp;
		}
	private:
		void empty_initialize()
		{
			//header节点设置为红色
			color(header) = rb_tree_red;
			root() = 0; //根节点设置成 空
			leftmost() = header;
			rightmost() = header;
		}
	public:
		//base=rb_tree_base里面装着header 分配一个内存并指向它 作为一个空元素
		rb_tree() :node_count(), key_compare()
		{
			header = get_node();
			empty_initialize();
		}
		rb_tree(const compare& comp, const allocator_type& a) :node_count(0), key_compare(comp)
		{
			header = get_node();
			empty_initialize();
		}
		iterator begin()				{ return static_cast<iterator*>(leftmost()); }
		const_iterator begin() const	{ return leftmost(); }
		iterator end()					{ return header; }
		const_iterator end() const		{ return header; }
		bool empty() const { return node_count == 0; }
		size_type size() const { return node_count; }
		size_type max_size() const { return size_type(-1); }
		//1=旋转点 2=root
		void rb_tree_rotate_left(rb_tree_node_base* x, rb_tree_node_base*& root)
		{
			rb_tree_node_base* y = x->right;
			x->right = y->left;
			if (y->left != 0)
				y->left->parent = x;
			y->parent = x->parent;
			if (x == root)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}
		//1=旋转点 2=root
		void rb_tree_rotate_right(rb_tree_node_base* x, rb_tree_node_base*& root)
		{
			rb_tree_node_base* y = x->left;
			x->left = y->right;
			if (y->right != 0)
				y->right->parent = x;
			y->parent = x->parent;
			if (x == root)
				root = y;
			else if (x == x->parent->left)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		//此函数 调整颜色并保持平衡
		//1=新增节点 2=根节点
		void rb_tree_rebalance(rb_tree_node_base* x, rb_tree_node_base*& root)
		{
			x->color = rb_tree_red; //新增的节点一定是红色
			while (x != root && x->parent->color == rb_tree_red)
			{
				//左边
				if (x->parent == x->parent->parent->left)
				{
					rb_tree_node_base* y = x->parent->parent->right;
					if (y && y->color == rb_tree_red)
					{
						x->parent->color = rb_tree_black;
						y->color = rb_tree_black;
						x->parent->parent->color = rb_tree_red;
						x = x->parent->parent;
					}
					else//无伯父节点
					{
						//如果是LR 先左在右
						if (x == x->parent->right)
						{
							x = x->parent;
							rb_tree_rotate_left(x, root);
						}
						//如果不是LR 直接改颜色 LL右旋
						x->parent->color = rb_tree_black;
						x->parent->parent->color = rb_tree_red;
						rb_tree_rotate_right(x->parent->parent, root);
					}
				}
				else //右边
				{
					base_ptr y = x->parent->parent->left; //save
					if (y && y->color == rb_tree_red) //x的父节点是否为红色
					{
						x->parent->color = rb_tree_black; //把父节点变为黑色
						y->color = rb_tree_black;        //叔叔设置成黑色
						x->parent->parent->color = rb_tree_red; //祖父变红
						x = x->parent->parent;//？？？
					}
					else//无伯父节点
					{
						//如果是RL 先右在左
						if (x == x->parent->left)
						{
							x = x->parent;
							rb_tree_rotate_right(x, root);
						}
						//如果不是RR 直接改颜色 RR右旋
						x->parent->color = rb_tree_black;
						x->parent->parent->color = rb_tree_red;
						rb_tree_rotate_left(x->parent->parent, root);
					}
				}

			}
			root->color = rb_tree_black;

		}


		// 1=参数的插入位置    2=父节点           3=插入的元素
		iterator _insert(base_ptr _x_root, base_ptr _y_header, const value& _x)
		{
			link_type _x_new_root = (link_type)_x_root;
			link_type _y_new_header = (link_type)_y_header;
			link_type _z_new_nodeData;

			//判断是不是根节点 || xrootnew不是最后一个 || compare的大小是怎么样的 小=1=true 大=0=false
			if (_y_new_header == header || _x_new_root != 0 || compare()(_x, get_key(_y_new_header)))
			{
				_z_new_nodeData = create_node(_x);
				get_left(_y_new_header) = _z_new_nodeData; //挂载到左节点

				//如果一个元素都没有 那么插入的元素就是父节点
				if (_y_new_header == header)
				{
					root() = _z_new_nodeData;
					rightmost() = _z_new_nodeData;
				}
				else if (_y_new_header == leftmost())
				{
					leftmost() = _z_new_nodeData; //保持header->leftmost指向最小的节点
				}
			}
			else
			{
				_z_new_nodeData = create_node(_x);
				get_right(_y_new_header) = _z_new_nodeData;
				if (_y_new_header == rightmost())
					rightmost() = _z_new_nodeData; //保持 header->leftmost指向最大的节点
			}
			get_parent(_z_new_nodeData) = _y_new_header;
			get_left(_z_new_nodeData) = 0;
			get_right(_z_new_nodeData) = 0;

			//这里暂且有一个平衡 先不写
			rb_tree_rebalance(_z_new_nodeData, header->parent);
			++node_count; //计数 有几个节点
			return static_cast<iterator*>(_z_new_nodeData);
		}


		iterator insert_equal(const value& x)
		{
			link_type y_header = header;
			link_type x_root = root();
			while (x_root != 0)
			{
				y_header = x_root;

				if (compare()(keyOfvalue()(x), get_key(x_root))) //默认升序
				{
					x_root = get_left(x_root);
				} //小的往左边
				else
				{
					x_root = get_right(x_root);
				} //大的往右边

			}
			return _insert(x_root, y_header, x); //然后插入
		}

		MyPair::pair<iterator,bool>
			insert_unique(const value& v)
		{
			link_type y = header;
			link_type  x = root();
			bool comp = true;
			while (x != 0)
			{
				y = x;
				comp = key_compare(keyOfvalue()(v), get_key(x));
				x = comp ? get_left(x) : get_right(x);
			}
			iterator j = iterator(y);
			if (comp)
				if (j == begin())
					return MyPair::pair<iterator, bool>(_insert(x, y, v), true);
				else
					--j;
			if (key_compare(get_key(j.node), keyOfvalue()(v)))
				return MyPair::pair<iterator, bool>(_insert(x, y, v), true);
			return MyPair::pair<iterator, bool>(j, false);
		}
	};
}
#endif // ! _MY_TREE_H_


