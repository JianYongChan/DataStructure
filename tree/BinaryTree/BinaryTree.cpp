#include<iostream>
#include<utility>
#include<initializer_list>
#include"BinaryTree.h"
	
int main()
{
	BinaryTree<int>iTree{7,3,4,8,9,34};
	iTree.printTree();
	std::cout<<std::endl;
	std::cout<<"Max:"<<iTree.findMax()<<std::endl;
	std::cout<<"Min:"<<iTree.findMin()<<std::endl;
	iTree.insert(13);
	iTree.printTree();
	std::cout<<std::endl;
	iTree.remove(8);
	iTree.printTree();
	std::cout<<std::endl;
}


