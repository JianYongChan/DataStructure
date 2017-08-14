/*
 * =====================================================================================
 *
 *       Filename:  AvlTree.cpp
 *
 *    Description:  The test file of AvlTree.
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
#include<iostream>
#include<utility>
#include<initializer_list>
#include"AvlTree.h"

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
}
