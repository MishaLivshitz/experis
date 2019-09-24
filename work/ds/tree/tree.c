#include "tree.h"

typedef struct node
{
	int m_data;
	struct node* m_left;
	struct node* m_right;
	struct node* m_father;
}Node;

struct tree
{
	int magicNum;
	Node* m_root;
};

static Node* CreateNode(int _data)
{
	Node* node = NULL;

	if(NULL == (node = (Node*)calloc(1,sizeof(Node))))
	{
		return NULL;
	}
		
	node->m_data=_data;

	return node;	
}

static void DestroyNode(Node** node)
{
	free(*node);
	*node=NULL;
}

static void PrintNode(Node* node,FILE* file)
{
	if(NULL==file)
	{
		printf("%d ",node->m_data);
	}
	else
	{
		fprintf(file, "%d ", node->m_data);
	}
	
}	

static void PostOrderTraverse(Node* _root, TreeAction _treeAction)
{
	if(NULL==_root)
	{
		return;
	}

	PostOrderTraverse(_root->m_left,_treeAction);
	PostOrderTraverse(_root->m_right,_treeAction);

	switch(_treeAction)
	{
		case DESTROY:
			DestroyNode(&_root);
			break;
	
		case PRINT:
			PrintNode(_root,NULL);
			break;
	}
	
	return;
}

static void PreOrderTraverse(Node* _root)
{
	if(NULL==_root)
	{
		return;
	}

	PrintNode(_root,NULL);
	PreOrderTraverse(_root->m_left); 
	PreOrderTraverse(_root->m_right);	
	
	return;
}

static void InOrderTraverse(Node* _root,FILE* _file)
{
	if(NULL==_root)
	{
		return;
	}
	
	InOrderTraverse(_root->m_left, _file);
	PrintNode(_root,_file);
	InOrderTraverse(_root->m_right, _file);

	return; 
}

static ADTErr TraverseTree(Tree* _tree,TreeTraverse _traverseMode,TreeAction _treeAction,FILE* _file)
{
	switch(_traverseMode)
	{

		case PRE_ORDER:
			PreOrderTraverse(_tree->m_root);
			break;

		case IN_ORDER:
			InOrderTraverse(_tree->m_root,_file);
			break;

		case POST_ORDER:
			PostOrderTraverse(_tree->m_root,_treeAction);
			break;
	} 
}

static Node* FindFather(Node* _root,int _data)
{
	
	while(NULL != _root)
	{
		if(_root->m_data > _data)
		{
			if(_root->m_left==NULL)
			{
				break;
			}
			else
			{
				_root=_root->m_left;
			}
		}
		else if(_root->m_data < _data)
		{
			if(_root->m_right==NULL)
			{
				break;
			}
			else
			{
				_root=_root->m_right;
			}
		}
		else
		{
			return NULL;
		}
	}
	return _root;
}

Tree* TreeCreate()
{
	Tree* tree = NULL;
	 
	if(NULL == (tree = (Tree*)calloc(1,sizeof(Tree))))
	{
		return NULL;
	}

	tree->magicNum = MAGIC_NUM_ACTIVE;

	return tree;
}

void TreeDestroy(Tree* _tree)
{
	if(NULL!=_tree && _tree->magicNum == MAGIC_NUM_ACTIVE)
	{
		TraverseTree(_tree,POST_ORDER,DESTROY,NULL);
		_tree->magicNum = MAGIC_NUM_INACTIVE;
		free(_tree);
	}
}

ADTErr TreeInsert(Tree* _tree, int _data)
{
	Node* newNode=NULL;
	Node* father=NULL;

	if(NULL == _tree || _tree->magicNum !=MAGIC_NUM_ACTIVE)
	{
		return ERR_NOT_INITIALIZED;
	}

	if(NULL == (newNode = CreateNode(_data)))
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	if(_tree->m_root==NULL)
	{
		_tree->m_root = newNode;
		return ERR_OK;
	}

	father = FindFather(_tree->m_root,_data);

	if (NULL == father)
	{
		DestroyNode(&newNode);
		return ERR_EXIST;
	}
	if(father->m_data>_data)
	{
		father->m_left = newNode;
	}
	else
	{
		father->m_right = newNode;
	}

	newNode->m_father=father;

	return ERR_OK;
}

bool TreeIsDataFound(Tree* _tree,int _data)
{
	if(NULL == _tree || _tree->magicNum !=MAGIC_NUM_ACTIVE)
	{
		return FALSE;
	}

	return NULL==FindFather(_tree->m_root,_data);

}

void TreePrint(Tree* _tree,TreeTraverse _traverseMode)
{
	FILE* file=NULL;
	if(NULL == _tree || _tree->magicNum !=MAGIC_NUM_ACTIVE)
	{
		return;
	}
	
	if(_traverseMode==IN_ORDER)
	{
		file = fopen(FILE_NAME,"w");
		TraverseTree(_tree,IN_ORDER,PRINT,file);
		fclose(file);
		return;
	}
	
	TraverseTree(_tree,_traverseMode,PRINT,file);
	putchar('\n');
	
	return;
}
