/*
 *  COPYRIGHT NOTICE
 *  Copyright (C) 2016 HuaHuan Electronics Corporation, Inc. All rights reserved
 *
 *  Author       	:fzs
 *  File Name        	:/home/kevin/works/projects/ACCUMULATION/C_Program/trees/tree.c
 *  Create Date        	:2017/11/09 09:54
 *  Last Modified      	:2017/11/09 09:54
 *  Description    	:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mytree{
	struct mytree *left;
	struct mytree *right;
	unsigned int data;
};

struct mytree *root=NULL;

int create_tree(struct mytree **node,int depth)
{
	static int value = 1;	
	if(NULL == *node)
		*node = malloc(sizeof(struct mytree));
	memset(*node, 0, sizeof(struct mytree));
	(*node)->data = value++;

	if(!(--depth))
	{
		printf("%d ",value-1);
		return 0;
	}
	create_tree(&(*node)->left,depth);
	create_tree(&(*node)->right,depth);

	return 0;
}

int preorder_traversal_tree(struct mytree *node)
{
	if(NULL == node)
	{
		//	printf("null\n");
		return 0;
	}
	printf("%d ",node->data);
	preorder_traversal_tree(node->left);
	preorder_traversal_tree(node->right);

	return 0;
}
int preorder_circul_traversal_tree(struct mystree *node)
{
	unsigned int stack[260];	
	if(NULL == node)
	{
		//	printf("null\n");
		return 0;
	}
	else
	{
		do{
			if(NULL != node)
				printf("%d ",node->data);
			push();
		printf("%d ",node->data);
		preorder_traversal_tree(node->left);
		preorder_traversal_tree(node->right);
	}

	return 0;
}

int inorder_traversal_tree(struct mytree *node)
{
	if(NULL == node)
	{
		//	printf("null\n");
		return 0;
	}
	inorder_traversal_tree(node->left);
	printf("%d ",node->data);
	inorder_traversal_tree(node->right);

	return 0;
}
int postorder_traversal_tree(struct mytree *node)
{
	if(NULL == node)
	{
		//	printf("null\n");
		return 0;
	}
	postorder_traversal_tree(node->left);
	postorder_traversal_tree(node->right);
	printf("%d ",node->data);

	return 0;
}

int main(int argc, unsigned char *argv[])
{
	int depth = 3;
	if(argc > 2)
		return 0;
	else if(argc == 2)
		depth = atoi(argv[1]);

	printf("leaf:\n");
	create_tree(&root, depth);	
	printf("\n\n");

	printf("preorder:\n");
	preorder_traversal_tree(root);
	printf("\n");

	printf("inorder:\n");
	inorder_traversal_tree(root);
	printf("\n");

	printf("postorder:\n");
	postorder_traversal_tree(root);
	printf("\n");

	return 0;	
}

