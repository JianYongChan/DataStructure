#include<iostream>
#include<utility>
#include<initializer_list>
#include"AvlTree.h"

static const int ALLOWED_IMBALANCE = 1;

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
	return *this;
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
	k2->left = k1->right; // reversing this expression with below is wrong 
	k1->right = k2;
	k2->height = max(height(k2->left),height(k2->right)) + 1;
	k2 = k1;
}


template<typename Object>
void AvlTree<Object>::single_rotate_with_right_child(AvlNode *&k2){
	AvlNode *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;	
	k2->height = max(height(k2->left),height(k2->right)) + 1;
        k2 = k1;
}

template<typename Object>
void AvlTree<Object>::double_rotate_with_left_child(AvlNode *&k3){
	single_rotate_with_right_child(k3->left);
	single_rotate_with_left_child(k3);
}

template<typename Object>
void AvlTree<Object>::double_rotate_with_right_child(AvlNode *&k3){
	single_rotate_with_left_child(k3->right);
	single_rotate_with_right_child(k3);
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
	os<<"pre_order_travelsal:"<<std::endl;
	pre_order_travelsal(t,os);
	os<<std::endl;
	os<<"in_order_travelsal:"<<std::endl;
	in_order_travelsal(t,os);
	os<<std::endl;
	os<<"post_order_travelsal:"<<std::endl;
	post_order_travelsal(t,os);
	os<<std::endl;
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

int main()
{
	AvlTree<int>iaTree{7,3,4,9,13,34,17,97,44,30,25,1,38,20,26,19,27,59,83,45,36,10,43,77};
	iaTree.printTree();
	std::cout<<"after inserting 11:"<<std::endl;
	iaTree.insert(11);
	iaTree.printTree();
	iaTree.remove(4);
	std::cout<<"after removing 4:"<<std::endl;
	iaTree.printTree();
	std::cout<<"Min: "<<iaTree.findMin()<<std::endl;
	std::cout<<"Max: "<<iaTree.findMax()<<std::endl;
	iaTree.insert(11);
	iaTree.insert(12);
	iaTree.printTree();
}
