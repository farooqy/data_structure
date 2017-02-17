#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define N 50
typedef struct mystack
{
	int a[N] ;
	int top ;
}ST;

int isempty(ST *t);
int isfull(ST *t);
int gettop(ST *t);
int pop(ST *t);
void push(ST *t,int x);
void transfer(char *in,char *post);
int compute(char *post);
int checkPriority(int x);
void showALL (char *arr);

int main()
{
	char s1[N],s2[N];
	printf("please input infix express: ");
	scanf("%s",s1);
	//printf("THE SIZE IS %d\n",strlen(s1) );
	transfer(s1,s2);
	printf("the postfix express is:\n");
	printf("%s\n",s2);
  int result = compute(s2);
  if(result != -999)
  printf("\nTHE FINAL ANSWER IS %d \n", result);
}
void transfer(char *in,char *post)
{
	ST *tempStack;
	int i,j;
	int arraySize = strlen(in);
	//printf("TRANSFERING INFIX OF SIZE %d TO POSTFIX\n",arraySize);
	if(!(tempStack = (ST *)(malloc(sizeof(ST)))))
		printf("FAILED TO MAKE MEM FOR STACK\n");
	//initialize tempStack to know its empty easily
	tempStack->a[0] = -999;
	tempStack->top = 0;
	int postCounter =0;
	bool rightBracketIn = false;
  //printf("The top elem is : %d\n",tempStack->a[tempStack->top]);
  i =0;
	for(i; i < arraySize; i++)
	{
		//printf("CARRYING: %c OF PRIORITY: %d\n",in[i], checkPriority(in[i]+0));
		int currentNum = checkPriority(in[i]+0);
		if(currentNum  == 3)
		{
			post[postCounter] = in[i];
			//printf("[*POST*]: CONVERTED %c\n",post[postCounter]);
			postCounter++;
		}
		else if(currentNum == 2)
		{
			if(isempty(tempStack) == 0)
			{
				push(tempStack,(in[i]+0));
				//printf("[#PUSHED#]: %d INTO EMPTY STACK \n", tempStack->a[tempStack->top]);
			}
			else
			{
				while(checkPriority(tempStack->a[tempStack->top]) <= currentNum && tempStack->a[tempStack->top] != '('+0 && isempty(tempStack) != 0)
				{
					//printf("[@POPPING@]: %d FROM STACK INDEX %d\n",tempStack->a[tempStack->top], tempStack->top);
					post[postCounter] = tempStack->a[tempStack->top];
			    //printf("[*POST*]: CONVERTED %c\n",post[postCounter]);
					tempStack->top = pop(tempStack);
          //printf("**** TOP IS NOW %d ****\n",tempStack->top);
					postCounter++;
				}
				push(tempStack,(in[i]+0));
				//printf("[#PUSHED#]: %d INTO STACK \n", tempStack->a[tempStack->top]);
			}
		}
		else if(currentNum == 1)
		{
			if(isempty(tempStack) == 0)
			{
				push(tempStack,(in[i]+0));
				//printf("[#PUSHED#]: %d INTO EMPTY STACK \n", tempStack->a[tempStack->top]);
			}
			else
			{
				while(checkPriority(tempStack->a[tempStack->top]) <= currentNum && tempStack->a[tempStack->top] != '('+0 && isempty(tempStack) != 0)
				{
					//printf("[@POPPING@]: %d FROM STACK INDEX %d\n",tempStack->a[tempStack->top], tempStack->top);
					post[postCounter] = tempStack->a[tempStack->top];
			    //printf("[*POST*]: CONVERTED %c\n",post[postCounter]);
					tempStack->top = pop(tempStack);
          //printf("**** TOP IS NOW %d ****\n",tempStack->top);
					postCounter++;
				}
				push(tempStack,(in[i]+0));
				//printf("[#PUSHED#]: %d INTO STACK \n", tempStack->a[tempStack->top]);
			}
		}
		else if(currentNum == 0)
		{
			if(in[i] == '(')
			{
				push(tempStack,(in[i]+0));
				//printf("[#PUSHED#]: %d \"(\" INTO STACK \n", tempStack->a[tempStack->top]);
			}
			else
			{
				while(tempStack->a[tempStack->top] != '('+0)
				{
					post[postCounter] = tempStack->a[tempStack->top];
          //printf("[*POST*]: CONVERTED %c\n",post[postCounter]);
					postCounter++;
					//printf("[@POPPING@]: %d FROM STACK \n",tempStack->a[tempStack->top]);
					tempStack->top = pop(tempStack);
				}
				//printf("[@POPPING@]: %d FROM STACK \n",tempStack->a[tempStack->top]);
				tempStack->top = pop(tempStack);
			}
		}
	}
	while(tempStack->top != -1)
	{
		post[postCounter] = tempStack->a[tempStack->top];
    //printf("[*POST*]: CONVERTED %c\n",post[postCounter]);
		postCounter++;
		//printf("[@POPPING@]: %d FROM STACK \n",tempStack->a[tempStack->top]);
		tempStack->top = pop(tempStack);
	}
	printf("\nDONE READING\n");
	showALL(post);
}
int checkPriority(int x)
{
	switch(x)
	{
		case 40:
			return 0;
		case 41:
			return 0;
		case 42:
			return 1;
		case 37:
			return 1;
		case 47:
			return 1;
		case 43:
			return 2;
		case 45:
			return 2;
		default:
			return 3;
	}
}
int isempty(ST *t)
{
	if(t->a[t->top] == -999 || t->top < 0)
		return 0;
	else
		return 1;
}
int isfull(ST *t)
{

	if(t->top == N-1)
		return t->top;
	else
		return 0;
}
int gettop(ST *t)
{
	return (t->a[t->top]);
}
void push(ST *t,int x)
{
	int g =isfull(t);
	if(g)
	{
		printf("The stuck is full, can not perform push operation!\n");
		exit(0);
	}
	if(t->top == 0 && t->a[t->top] == -999)
	t->a[t->top] = x;
	else
	{
		t->top++;
		t->a[t->top] = x;
	}
}
int pop(ST *t)
{
	if(t->top == -1 || t->a[t->top] == -999)
	{
		printf("Stack is empty, nothing to pop from the stack");
		return 0;
	}
  t->top = t->top-1;
	return t->top;
}
void showALL (char *arr)
{
	int sizeOfArr = strlen(arr), i;
  //printf("SHOWING ARRAYS OF SIZE %d\n", sizeOfArr);
	for(i =0; i<sizeOfArr; i++)
	{
		printf("%c ",arr[i]);
	}
	printf("\n");
}
int compute(char * post)
{
  ST *stackPost = malloc(sizeof(ST));
  int sizeofPost = strlen(post), i;
  printf("\n***COMPUTING EXPRESSION OF SIZE %d ***\n", sizeofPost); 
  int answer;
  for(i=0; i < sizeofPost; i++)
  {
    answer = 0;
    int elemToPush = post[i] +0-'0';
    int currentNum = checkPriority(post[i]+0);
    //printf("CARRYING ELEM %c of PRIORITY %d \n", post[i], currentNum);
    if(currentNum == 3)
    {
      push(stackPost, elemToPush);
      //printf("[*PUSHED*]: %d INTO STACK AT INDEX %d \n", stackPost->a[stackPost->top], stackPost->top);
    }
    else
    {
      if(currentNum != 0 && currentNum != 1 && currentNum != 2)
      {
        printf("[!!ERROR!!] THERE IS UKNOWN EXPRESSION %c TO COMPUTE. \n", post[i]);
        return -999;
      }
      else
      {
        if(stackPost->top < 1)
        {
          printf("INSUFFICIENT NUMBERS FOR OPERATION TO COMPUTE *REMEMBER TWO DEGIT NUMBER IS NOT SUPPORTED\n");
          return -999;
        }
        else
        {
          int second = stackPost->a[stackPost->top];
          stackPost->top = pop(stackPost);
          int first = stackPost->a[stackPost->top];
          stackPost->top = pop(stackPost);
          switch(post[i])
          {
            case '+': answer = first + second; break;
            case '-': answer = first - second; break;
            case '*': answer = first * second; break;
            case '/': answer = first / second; break;
            case '%': answer = first % second; break;
          }
        }
      }
      push(stackPost,answer);
      //printf("[*PUSHED*]: %d AS ANSWER AT INDEX %d \n", stackPost->a[stackPost->top], stackPost->top);
    }
  }
  return answer;
}
