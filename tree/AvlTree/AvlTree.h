#ifndef AVLTREE_H__
#define AVLTREE_H__
#include<iostream>
#include<utility>
#include<initializer_list>

template<typename Object>
class AvlTree
{
	private:
		struct AvlNode
		{
			Object   data;
			AvlNode *left;
			AvlNode *right;
			int      height;
			AvlNode(const Object &d=Object(),AvlNode *l=nullptr,AvlNode *r=nullptr,int h=0):
				data(d),left(l),right(r),height(h){}
			AvlNode(Object &&d,AvlNode *l=nullptr,AvlNode *r=nullptr,int h=0):
				data(std::move(d)),left(l),right(r),height(h){}
		};

	public:
		AvlTree ();
		AvlTree (const AvlTree &aTree);
		AvlTree (const std::initializer_list<Object> &olist);
		AvlTree& operator=(const AvlTree &rhs);
		~AvlTree();

		const Object& findMin()const;
		const Object& findMax()const;
		void          insert(const Object &x);
		void          insert(Object &&x);
		void          remove(const Object &x);
		void          printTree(std::ostream &os=std::cout)const;

	private:
		AvlNode *root;

		int      height(AvlNode *t)const;
		int      max(int a,int b)const;
		AvlNode* findMin(AvlNode *t)const;
		AvlNode* findMax(AvlNode *t)const;
		void     insert(const Object &x,AvlNode *&t);
		void     insert(Object &&x,AvlNode *&t);
		void     remove(const Object &x,AvlNode *&t);
		void     printTree(AvlNode *t,std::ostream &os=std::cout)const;
		void     single_rotate_with_left_child(AvlNode *&k2);
		void     single_rotate_with_right_child(AvlNode *&k2);
		void     double_rotate_with_left_child(AvlNode *&k3);
		void     double_rotate_with_right_child(AvlNode *&k3);
		void     balance(AvlNode *&t);
		void     pre_order_travelsal(AvlNode *t,std::ostream &os=std::cout)const;
		void     in_order_travelsal(AvlNode *t,std::ostream &os=std::cout)const;
		void     post_order_travelsal(AvlNode *t,std::ostream &os=std::cout)const;
		void     makeEmpty(AvlNode *&t);
		AvlNode* clone(AvlNode *t)const;
};

#endif /* AVLTREE_H__ */
