#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
	int height;
	int below;
}node;

int len=0;
int flag=0;

int height(node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}

node* newNode(int key)
{
	node* noda = (node*)malloc(sizeof(node));
	noda->key = key;
	noda->left = NULL;
	noda->right = NULL;
	noda->height = 1;
	noda->below = 1;
	return(noda);
}

node *rightRotate(node *y)
{
	node *x = y->left;
	node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;

	y->below = call(y->left) + call(y->right) + 1;
	x->below = call(x->left) + call(x->right) + 1;

	return x;
}

node *leftRotate(node *x)
{
	node *y = x->right;
	node *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;

	x->below = call(x->left) + call(x->right) + 1;
	y->below = call(y->left) + call(y->right) + 1;

	return y;
}

int getBalance(node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

node* insert(node* node, int key)
{
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left  = insert(node->left, key);
	else
		node->right = insert(node->right, key);

	node->height = max(height(node->left), height(node->right)) + 1;
	node->below = call(node->left) + call(node->right) + 1;

	int balance = getBalance(node);

	// Left Left Case
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && key > node->left->key)
	{
		node->left =  leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

node * minValueNode(node* noda)
{
	node* current = noda;

	while (current->left != NULL)
		current = current->left;

	return current;
}

node* deleteNode(node* root, int key)
{
	if (root == NULL)
		return root;

	if ( key < root->key )
		root->left = deleteNode(root->left, key);

	else if( key > root->key )
		root->right = deleteNode(root->right, key);

	else
	{
		flag = 1;
		if( (root->left == NULL) || (root->right == NULL) )
		{
			node *temp = root->left ? root->left : root->right;

			if(temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;

			free(temp);
		}
		else
		{
			node* temp = minValueNode(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);
		}
	}

	if (root == NULL)
		return root;

	root->height = max(height(root->left), height(root->right)) + 1;
	root->below = call(root->left) + call(root->right) + 1;

	int balance = getBalance(root);

	// Left Left Case
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left =  leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

void preOrder(node *root)
{
	if(root != NULL)
	{
		printf("%d ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

int count(node *root, int a)
{
	if(root==NULL)
		return(0);
	int c=0;
	int ret=0;
	if(root->left != NULL)
		c = root->left->below;
	if(a  > root->key)
	{
		ret += c+1;
		ret += count(root->right, a);
	}
	else
		ret += count(root->left, a);
	return ret;
}

int kth(node *root, int k)
{
	int a=0;
	if(root->left != NULL)
		a = root->left->below;
	if(k == a+1)
		return root->key;
	else
	{
		if(a+1 < k)
			return kth(root->right, k-a-1);
		else
			return kth(root->left, k);
	}
}

int locate(node *root, int a)
{
	if(root==NULL)
		return(0);

	if(root->key < a)
	{
		int b = locate(root->right, a);
		return b;
	}
	else if(root->key > a)
	{
		int b = locate(root->left, a);
		return b;
	}
	else
		return 1;
}

int call(node *a)
{
	if(a==NULL)
		return(0);
	return a->below;
}

int main(void)
{
	node *root=NULL;
	int q;
	scanf("%d", &q);
	while(q--)
	{
		char c;
		int d;
		int ans;
		scanf(" %c %d", &c, &d);
		if(c=='I')
		{
			int m = locate(root, d);
			if(m==0)
			{
				root = insert(root, d);
				len++;
			}
		}
		else if(c=='C')
		{
			ans = count(root, d);
			printf("%d\n", ans);
		}
		else if(c=='K')
		{
			if(d <= len)
			{
				ans = kth(root, d);
				printf("%d\n", ans);
			}
			else
				printf("invalid\n");
		}
		else if(c=='D')
		{
			flag=0;
			root = deleteNode(root, d);
			if(flag==1)
				len--;
		}
		//printf("the root is %d\n", root->key);
		//preOrder(root);
	}
	return(0);
}