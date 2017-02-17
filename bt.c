#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
  char data[5];
  struct node * left;
  struct node * right;
} BT;
int menu_select();
BT *create();
void showtree(BT *T);//output BT 
void preorder(BT *T);//use preorder way to traverse BT
void inorder(BT *T);//use inorder way to traverse BT
void postorder(BT *T);//use postorder way to traverse BT
void layorder(BT *T);//to traverse BT layer by layer
int height(BT *T);//compute the height of BT
void getLevel(BT * TT, int level);// print given level
void swaptree(BT *T);//exchange the left and right brantch in BT
void leafToRoot(BT *T, BT *leaf);
void traverse(BT *T);
void insert(BT *TREE, char *val);
BT *deltree(BT *T);//free all the node in the BT
BT *GLOBAL;
int main()
{
  BT *T;
	BT *TM = malloc(sizeof(BT));
	strcpy(TM->data, "6"); 
	GLOBAL = malloc(sizeof(BT));
	while(1)
	{
		switch(menu_select())
		{
			case 1: system("clear"); T = create();printf("I WAS TO RETURN %s AS THE ROOT \n", T->data);break;
			case 2: system("clear"); printf("\n");showtree(T);printf("\n");break;
			case 3: system("clear"); printf("The Heigh is: %d and the number of leaves are: %d \n", height(T)-1, height(T)+(height(T)-1));break;
			case 4: system("clear"); if(strlen(T->data) == 0 || T == NULL){printf("TREE IS EMPTY "); return 0;}
				printf("SHOWING BT IN ALL ORDERS \n");
				printf("PREORDER: ");preorder(T);
				printf("\nINORDER: "); inorder(T);
				printf("\nPOSTORDER: ");postorder(T);
				printf("\nLAYORDER: ");layorder(T);
				printf("\n");
				break;
			case 5: system("clear"); swaptree(T);printf("DONE SWAPPING\n");break;
			case 6: system("clear"); GLOBAL = T; traverse(T);printf("\n");break;
			case 7: system("clear"); T = deltree(T);printf("DELETED ALL NODES\n");break;
			default: printf("\n\n UKNOWON COMMAND EXITING \n\n"); return 0;
		}
	}
}

int menu_select()
{
		printf("1.create BT\n");
		printf("2.show BT\n");
		printf("3.property of BT\n");
		printf("4.traverse BT\n");
		printf("5.swap left and right branch\n");		
		printf("6.show the ways from leaf to root\n");
		printf("7.destruct BT\n");
		printf("any.exit\n");
		printf("please input number(0-7): ");
  int choice;
  scanf("%d",&choice);
  return choice;
}
void traverse(BT *T)
{
	if(T == NULL || strlen(T->data) ==0)
	{
		//printf("TREE IS EMPTY\n");
		return;
	}
	else
	{
		if(T->left)
			postorder(T->left);
		if(T->right)
			postorder(T->right);
		leafToRoot(GLOBAL, T);
	}
}
BT *create()
{
  printf("PLEASE ENTER IN PREORDER AND A COMMA \",\" AFTER EVERY NODE\n");
  printf("THE LEFT WILL BE LESS AND THE RIGHT WILL BE MORE THAN THE ROOT: ");
  BT *TR; int i,j, nodeCounter = 0, index =0;
  char preOrderArr[50], nodeArr[40][5] ={0};
  scanf("%s",preOrderArr);
  int totalSize = strlen(preOrderArr);
  //printf("TOTAL SIZE IS: %d \n", totalSize);
  char *strH = malloc(sizeof(char)*5);
  for(i =0; i<totalSize; i++)
  {
    if(preOrderArr[i] == ',')
    {
			nodeArr[nodeCounter][index] ='\0';
      index = 0;
      nodeCounter++;
      continue;
    }
    nodeArr[nodeCounter][index] = preOrderArr[i];
    index++;
  }
	TR = malloc(sizeof(BT));
  for(j =0; j<=nodeCounter; j++)
    insert(TR, nodeArr[j]);
  
  return TR;
}
void insert(BT *TREE, char *val)
{
  //printf("DOIING INSERT\n");
  int i, count =0;
	//printf("Carrying %s as root and %s as node to inssert \n",TREE->data, val);
  if(TREE->data == NULL || strlen(TREE->data) == 0)
  {
		strcpy(TREE->data, val);
		//printf("ROOT HAS BEEN SET TO %s\n", TREE->data);
  }
  else if(atoi(val) < atoi(TREE->data))
  {
    //printf("I AM LEFT VALUE\n");
    if(TREE->left == NULL)
    {
      //printf("I WILL INSERT %s TO THE LEFT\n", val);
      TREE->left = malloc(sizeof(BT));
      strcpy(TREE->left->data, val);
    }
    else
      insert(TREE->left, val);
  }
  else if(atoi(val) >= atoi(TREE->data) )
  {
    //printf("I AM RIGHT VALUE\n");
    if(TREE->right == NULL)
    {
      //printf("I WILL INSERT %s TO THE RIGHT\n", val);
      TREE->right = malloc(sizeof(BT));
      strcpy(TREE->right->data, val);
    }
    else
    insert(TREE->right, val);
  }
  //else
    //printf("I AM A PROBLEM\n");
}
void preorder(BT *T)//use preorder way to traverse BT
{
	if(T == NULL || strlen(T->data) ==0)
	{
		//printf("TREE IS EMPTY\n");
		return;
	}
	else
	{
		printf("%s, ",T->data);
		if(T->left)
			preorder(T->left);
		if(T->right)
			preorder(T->right);
	}
}

void inorder(BT *T)//use inorder way to traverse BT
{
	if(T == NULL || strlen(T->data) ==0)
	{
		//printf("TREE IS EMPTY\n");
		return;
	}
	else
	{
		if(T->left)
			inorder(T->left);
			printf("%s, ",T->data);
		if(T->right)
			inorder(T->right);
	}
}
void postorder(BT *T)//use postorder way to traverse BT
{
	if(T == NULL || strlen(T->data) ==0)
	{
		//printf("TREE IS EMPTY\n");
		return;
	}
  else
	{
		if(T->left)
			postorder(T->left);
		if(T->right)
			postorder(T->right);
		printf("%s, ",T->data);
	}
}

void layorder(BT *T)//to traverse BT layer by layer
{
  int h = height(T);
	int i;
	for(i =0; i<= h;  i++)
		getLevel(T, i);
}

int height(BT *T)//compute the height of BT
{
  if(T == NULL || strlen(T->data) == 0)
		return 0;
	else
	{
		/* compute the height of each subtree */
		int lheight = height(T->left);
		int rheight = height(T->right);
		/* use the larger one */
		if (lheight > rheight)
			return(lheight+1);
		else return(rheight+1);
    }
}
void getLevel(BT * TT, int level)
{
	if(TT == NULL || strlen(TT->data) ==0)
	{
		//printf("TREE IS EMPTY\n");
		return;
	}
	else if(level == 1)
		printf("%s, ",TT->data);
	else if(level > 1)
	{
		getLevel(TT->left, level-1);
		getLevel(TT->right, level-1);
	}
}
void leafToRoot(BT *T, BT *leaf)
{
	//printf("NODE IS %s \n",leaf->data);
	//printf("ROOT IS %s \n", T->data);
  if(T == NULL || leaf == NULL)
		return;
	else
	{
		int h = height(leaf);
		//printf("Heigh of the leaf is: %d \n", h);
		if(T->left && atoi(leaf->data ) < atoi(T->data))
			{
				//printf("MVOING PAST LEFT: %s \n", T->data);
					leafToRoot(T->left, leaf);
			}
		else if(T->right && atoi(leaf->data ) >= atoi(T->data))
			{
				//printf("MVOING PAST RIGHT: %s \n", T->data);
				leafToRoot(T->right, leaf);
				printf("%s,",T->data);
			}
	}
}

void swaptree(BT *T)//exchange the left and right brantch in BT
{
	BT *temp = malloc(sizeof(BT));
	temp->left = T->right;
	temp->right = T->left;
	T->left = temp->left;
	T->right = temp->right;
}
BT *deltree(BT *T)//free all the node in the BT
{
	BT *tmp = malloc(sizeof(BT));
	if(T != NULL)
	{
		tmp = deltree(T->left);
		free(T->data);
		tmp = deltree(T->right);
		free(T);
	}
	T = tmp;
	return T;
}

void showtree(BT *T)//output BT using brackets
{
	if(T == NULL || strlen(T->data) ==0)
	{
		//printf("TREE IS EMPTY\n");
		return;
	}
	printf("%s", T->data);
	if(T->left || T->right)
	{
		printf("(");
		showtree(T->left);
		printf(",");
		showtree(T->right);
		printf(")");
	}
	
}





