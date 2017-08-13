#ifndef BINARYTREE_H__
#define BINARYTREE_H__
#include<iostream>
#include<utility>
#include<initializer_list>

template<typename Object>
class BinaryTree
{
	private:
		struct BinaryNode
		{
			Object data;
			BinaryNode *left;
			BinaryNode *right;
			
			BinaryNode(const Object &obj=Object(),BinaryNode *l=nullptr,BinaryNode *r=nullptr):data(obj),left(l),right(r){}
			BinaryNode(Object &&obj,BinaryNode *l=nullptr,BinaryNode *r=nullptr):data(std::move(obj)),left(l),right(r){}
		};
		
	public:
		BinaryTree();
		BinaryTree(const BinaryTree &bTree);
		BinaryTree(const std::initializer_list<Object> &olist);
		BinaryTree& operator=(const BinaryTree &rhs);
		~BinaryTree();

		const Object& findMin()const;
		const Object& findMax()const;
		bool          isContain(const Object &x)const;
		void          printTree(std::ostream &os=std::cout);
		void          makeEmpty();
		void          insert(const Object &x);
		void          insert(Object &&x);
		void          remove(const Object &x);


	private:
		BinaryNode *root;

		void         insert(const Object &x,BinaryNode *&t);
		void         insert(Object &&x,BinaryNode *&t);
		void         remove(const Object &x,BinaryNode *&t);
		bool         isContain(const Object &x,BinaryNode *t)const;
		void         makeEmpty(BinaryNode *&t);
		void         printTree(BinaryNode *t,std::ostream &os);
		BinaryNode*  findMin(BinaryNode *t)const;
		BinaryNode*  findMax(BinaryNode *t)const;
		BinaryNode*  clone(BinaryNode *t)const;
};

template<typename Object>
BinaryTree<Object>::BinaryTree():root(new BinaryNode()){}

template<typename Object>
BinaryTree<Object>::BinaryTree(const BinaryTree &bTree){
	root=clone(bTree.root);
}

template<typename Object>
BinaryTree<Object>::BinaryTree(const std::initializer_list<Object> &olist):root(nullptr){
	for(auto it=olist.begin();it!=olist.end();it++){
		insert(*it);
	}
}

template<typename Object>
BinaryTree<Object>& BinaryTree<Object>::operator=(const BinaryTree &rhs){
	if(root=rhs.root){
		return *this;
	}
	makeEmpty();
	root=clone(rhs.root);
	return *this;
}

template<typename Object>
BinaryTree<Object>::~BinaryTree(){
	makeEmpty();
}

template<typename Object>
const Object& BinaryTree<Object>::findMin()const{
	return (findMin(root)->data);
}

template<typename Object>
const Object& BinaryTree<Object>::findMax()const{
	return (findMax(root)->data);
}

template<typename Object>
bool BinaryTree<Object>::isContain(const Object &x)const{
	return isContain(x,root);
}

template<typename Object>
void BinaryTree<Object>::printTree(std::ostream &os){
	printTree(root,os);
}

template<typename Object>
void BinaryTree<Object>::makeEmpty(){
	makeEmpty(root);
}

template<typename Object>
void BinaryTree<Object>::insert(const Object &x){
	insert(x,root);
}

template<typename Object>
void BinaryTree<Object>::insert(Object &&x){
	insert(std::move(x),root);
}

template<typename Object>
void BinaryTree<Object>::remove(const Object &x){
	remove(x,root);
}

/* private methods */

template<typename Object>
typename BinaryTree<Object>::BinaryNode* BinaryTree<Object>::findMin(BinaryNode *t)const{	
	if(t==nullptr){
		return nullptr;
	}
	if(t->left==nullptr){
		return t;
	}
	else{
		return findMin(t->left);
	}
}

template<typename Object>
typename BinaryTree<Object>::BinaryNode* BinaryTree<Object>::findMax(BinaryNode *t)const{
	if(t==nullptr){
		return nullptr;
	}
	if(t->right==nullptr){
		return t;
	}
	return findMax(t->right);
}

template<typename Object>
bool BinaryTree<Object>::isContain(const Object &x,BinaryNode *t)const{
	if(t==nullptr){
		return false;
	}
	if(x<t->data){
		return isContain(x,t->left);
	}
	else if(t->data<x){
		return isContain(x,t->right);
	}
	else{
		return true;
	}
}

template<typename Object>
void BinaryTree<Object>::insert(const Object &x,BinaryNode *&t){
      if(t==nullptr){
              t=new BinaryNode(x,nullptr,nullptr);
      }
      else if(t->data<x){
	      insert(x,t->right);
      }
      else if(x<t->data){
	      insert(x,t->left);
      }    
      else;//already exists,do nothing
}

template<typename Object>
void BinaryTree<Object>::insert(Object &&x,BinaryNode *&t){
      if(t==nullptr){
              t=new BinaryNode(std::move(x),nullptr,nullptr);
      }
      else if(t->data < x){
	      insert(std::move(x),t->right);
      }
      else if(x < t->data){
	      insert(std::move(x),t->left);
      }    
      else;//repeated element,do nothing
}

template<typename Object>
void BinaryTree<Object>::remove(const Object &x,BinaryNode *&t){
	if(t==nullptr){
		return; //not found , nothing to do
	}
	if(x<t->data){
		remove(x,t->left);
	}
	else if(t->data<x){
		remove(x,t->right);
	}
	else if((t->left != nullptr) && (t->right != nullptr)){//has two sons
		t->data=findMin(t->right)->data;
		remove(t->data,t->right);
	}
	else{//has only one son
		BinaryNode *oldNode=t;
		t=(t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

template<typename Object>
void BinaryTree<Object>::makeEmpty(BinaryNode *&t){
	if(t != nullptr){
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t=nullptr;
}

template<typename Object>
typename BinaryTree<Object>::BinaryNode* BinaryTree<Object>::clone(BinaryNode *t)const{
	if(t==nullptr){
		return nullptr;
	}
	else{
		return new BinaryNode(t->data,clone(t->left),clone(t->right));
	}
}

template<typename Object>
void BinaryTree<Object>::printTree(BinaryNode *t,std::ostream &os){
	if(t != nullptr){
		printTree(t->left,os);
		printTree(t->right,os);
		os<<t->data<<"  ";
	}
}

#endif /* BINARYTREE_H__ */
