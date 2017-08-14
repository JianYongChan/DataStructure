/*
 * =====================================================================================
 *
 *       Filename:  A.h
 *
 *    Description:  The header file of AvlTree.
 *
 *        Version:  1.0
 *        Created:  08/14/2017 05:04:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ctom
 *   Organization:  iEach
 *
 * =====================================================================================
 */
#ifndef AVLTREE_H__
#define AVLTREE_H__
#include <iostream>
#include <utility>
#include <initializer_list>

static const int ALLOWED_IMBALANCE = 1;

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
		AvlNode* findMin(AvlNode *t)const;
		AvlNode* findMax(AvlNode *t)const;

		
};

/* public methods */
template<typename Object>
AvlTree<Object>::AvlTree():root(nullptr){}

template<typename Object>
AvlTree<Object>::AvlTree(const AvlTree &aTree){
	root=clone(aTree.root);
}

template<typename Object>
AvlTree<Object>::AvlTree(const std::initializer_list<Object> &olist):root(nullptr){
	for(auto it=olist.begin();it!=olist.end();it++){
		insert(*it);
	}
}

template<typename Object>
AvlTree<Object>& AvlTree<Object>::operator=(const AvlTree &rhs){
	if(root == rhs.root){
		return *this;
	}
	makeEmpty();
	root=clone(rhs.root);
	return *this;//need to complete;
}

template<typename Object>
AvlTree<Object>:: ~AvlTree(){
	makeEmpty(root);
}

template<typename Object>
const Object& AvlTree<Object>::findMin()const{
	return findMin(root)->data;
}

template<typename Object>
const Object& AvlTree<Object>::findMax()const{
	return findMax(root)->data;
}

template<typename Object>
void AvlTree<Object>::insert(const Object &x){
	insert(x,root);
}

template<typename Object>
void AvlTree<Object>::insert(Object &&x){
	insert(std::move(x),root);
}

template<typename Object>
void AvlTree<Object>::remove(const Object &x){
	remove(x,root);
}

template<typename Object>
void AvlTree<Object>::printTree(std::ostream &os)const{
	printTree(root,os);
}


/* private methods */
template<typename Object>
int AvlTree<Object>::max(int a,int b)const{
	return (a > b) ? a : b;
}

template<typename Object>
int AvlTree<Object>::height(AvlNode *t)const{
	return (t == nullptr) ? -1 : t->height;
}

template<typename Object>
typename AvlTree<Object>::AvlNode* AvlTree<Object>::findMin(AvlNode *t)const{
	if(t == nullptr){
		return nullptr;
	}
	if(t->left == nullptr){
		return t;
	}
	return findMin(t->left);
}

template<typename Object>
typename AvlTree<Object>::AvlNode* AvlTree<Object>::findMax(AvlNode *t)const{
	if(t == nullptr){
		return nullptr;
	}
	if(t->right == nullptr){
		return t;
	}
	return findMax(t->right);
}

template<typename Object>
void AvlTree<Object>::balance(AvlNode *&t){
	if(t == nullptr){
		return;
	}
	if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE){
		if(height(t->left->left) >= height(t->left->right)){
			single_rotate_with_left_child(t);
		}
		else{
			double_rotate_with_left_child(t);
		}
	}
	else if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE){
		if(height(t->right->right) >= height(t->right->left)){
			single_rotate_with_right_child(t);
		}
		else{
			double_rotate_with_right_child(t);
		}
	}
	t->height = max(height(t->left),height(t->right)) + 1;
}

template<typename Object>
void AvlTree<Object>::single_rotate_with_left_child(AvlNode *&k2){
	AvlNode *k1 = k2->left;
	k2->left    = k1->right; // reversing this expression with below is wrong 
	k1->right   = k2;
	k2->height  = max(height(k2->left),height(k2->right)) + 1;
	k2          = k1;
}


template<typename Object>
void AvlTree<Object>::single_rotate_with_right_child(AvlNode *&k2){
	AvlNode *k1 = k2->right;
	k2->right   = k1->left;
	k1->left    = k2;	
	k2->height  = max(height(k2->left),height(k2->right)) + 1;
        k2          = k1;
}
#if 0
template<typename Object>
void AvlTree<Object>::double_rotate_with_left_child(AvlNode *&k3){
	single_rotate_with_right_child(k3->left);
	single_rotate_with_left_child(k3);
}
#endif
template<typename Object>
void AvlTree<Object>::double_rotate_with_right_child(AvlNode* &k3){
	AvlNode *gp = k3;
	AvlNode *p  = k3->right;
	AvlNode *s  = k3->right->left;
	gp->right   = s->left;
	p->left     = s->right;
	s->left     = gp;
	s->right    = p;
	k3          = s;
}

#if 0
template<typename Object>
void AvlTree<Object>::double_rotate_with_right_child(AvlNode *&k3){
	single_rotate_with_left_child(k3->right);
	single_rotate_with_right_child(k3);
}
#endif 
template<typename Object>
void AvlTree<Object>::double_rotate_with_left_child(AvlNode* &k3){
	AvlNode *gp = k3;
	AvlNode *p  = k3->left;
	AvlNode *s  = k3->left->right;
	gp->left    = s->right;
	p->right    = s->left;
	s->left     = p;
	s->right    = gp;
	k3          = s;
}


template<typename Object>
void AvlTree<Object>::insert(const Object &x,AvlNode *&t){
	if(t == nullptr){
		t=new AvlNode(x);
	}
	else if(t->data<x){
		insert(x,t->right);
	}
	else if(x<t->data){
		insert(x,t->left);
	}
	else;//the element to be inserted has already exist in the tree,so nothing to do
	balance(t);
}

template<typename Object>
void AvlTree<Object>::insert(Object &&x,AvlNode *&t){
	if(t == nullptr){
		t=new AvlNode(std::move(x));
	}
	else if(t->data<x){
		insert(std::move(x),t->right);
	}
	else if(x<t->data){
		insert(std::move(x),t->left);
	}
	else;//the element to be inserted has already exist in the tree,so nothing to do
	balance(t);
}

template<typename Object>
void AvlTree<Object>::remove(const Object &x,AvlNode *&t){
	if(t == nullptr){
		return ;
	}
	if(x < t->data){
		remove(x,t->left);
	}
	else if(t->data < x){
		remove(x,t->right);
	}
	else if((t->left != nullptr) && (t->right != nullptr)){//the node found has two sons
			t->data=findMin(t->right)->data;
			remove(t->data,t->right);
	}
	else{//the node found is a leaf or has only one son
			AvlNode *oldNode = t;
			t=(t->left != nullptr) ? t->left : t->right;
			delete oldNode;
	}
	balance(t);
}

template<typename Object>
void AvlTree<Object>::post_order_travelsal(AvlNode *t,std::ostream &os)const{
	if(t != nullptr){
		post_order_travelsal(t->left);
		post_order_travelsal(t->right);
		os<<t->data<<"  ";
	}
}

template<typename Object>
void AvlTree<Object>::pre_order_travelsal(AvlNode *t,std::ostream &os)const{
	if(t != nullptr){
		os<<t->data<<"  ";
		pre_order_travelsal(t->left);
		pre_order_travelsal(t->right);
	}
}

template<typename Object>
void AvlTree<Object>::in_order_travelsal(AvlNode *t,std::ostream &os)const{
	if(t != nullptr){
		in_order_travelsal(t->left);
		os<<t->data<<"  ";
		in_order_travelsal(t->right);
	}
}

template<typename Object>
void AvlTree<Object>::printTree(AvlNode *t,std::ostream &os)const{//postorder traversal
	os<<"pre_order_travelsal:\n";
	pre_order_travelsal(t,os);
	os<<'\n';
	os<<"in_order_travelsal:\n";
	in_order_travelsal(t,os);
	os<<'\n';
	os<<"post_order_travelsal:\n";
	post_order_travelsal(t,os);
	os<<'\n';
}

template<typename Object>
void AvlTree<Object>::makeEmpty(AvlNode *&t){
	if(t != nullptr){
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t=nullptr;
}


template<typename Object>
typename AvlTree<Object>::AvlNode* AvlTree<Object>::clone(AvlNode *t)const{
	if(t == nullptr){
		return nullptr;
	}
	else{
		return new AvlNode(t->data,t->height,t->left,t->right);
	}
}

#endif /* AVLTREE_H__ */
