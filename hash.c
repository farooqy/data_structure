#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include <stdbool.h>
#include <time.h>
#define N 43
typedef struct student//structure of record
{
	char name[10];
	char sex[4];
	char number[12];
	char mail[50];
  bool filled;
  struct student *next;
}ST;

void Inittable(ST *hashTable);//Initialize the hash table
void Readfromfile(ST *hashTable);//Read data from txt file and build hash table
int Hashfun(char *number);// design the hash function based on the phone number
void Query(ST *hashTable,char *number);//Hash search based on phone number
int convert(char *number);//convert the string to integer(used in hash function design)
void cutstring(char *number,int start,int length,char *result);//get the part of a srting(used in hash function design)
void reverse(char *s);//reverse a string

int main()
{
	char number[30];
	ST A[N];
  ST hashTable[N];
	Inittable(hashTable);
  Readfromfile(hashTable);
	printf("please input phone number: ");
	scanf("%s",number);
	while(strcmp(number,"0")!=0)
	{
		//int x = Hashfun(number);
		clock_t t;
		t = clock();
    Query(hashTable, number);
		t = clock()-t;
		double time_take = ((double) t)/CLOCKS_PER_SEC;
		printf("\nIT TOOK %F SECONDS TO SEARCH IN THE TABLE\n", time_take);
		printf("\nplease input phone number: ");
	    scanf("%s",number);
	}
}
void Inittable(ST *hashTable)//Initialize the hash table
{
  int j;
  hashTable = malloc(sizeof(ST)*N);
  for(j=0; j<N; j++)
  {
    hashTable[j].filled = false;
  }
  printf("DONE INIT\n");
}
void Readfromfile(ST *hashTable)//Read data from txt file and build hash table
{
  FILE *ft;
  ft = fopen("info.txt", "r");
  if(!ft)
  {
    printf("FAILED TO OPEN FILE\n");
    return;
  }
  char *buffer = malloc(sizeof(char)*43);
  char cp_name[10], cp_sex[4], cp_num[12], cp_mail[50];
  int st_index =0, i;
  while((fgets(buffer, sizeof(buffer)*50, ft)) != NULL)
  {
    if(strlen(buffer) != 0)
    sscanf(buffer, "%s %s %s %s", cp_name, cp_sex, cp_num, cp_mail);
    printf("READ: %s", buffer);
    int hash_value = Hashfun(cp_num);
    ST *current = malloc(sizeof(ST));
    strcpy(current->name, cp_name);
    strcpy(current->sex, cp_sex);
    strcpy(current->number, cp_num);
    strcpy(current->mail, cp_mail);
    current->filled = true;
    current->next = NULL;
		ST *tempHash = &hashTable[hash_value];
    if(tempHash->filled == true)
    {
      //printf("THERE IS A COLLISION at %d SAVING AT NEXT \n\n\n",hash_value);
      while(tempHash->next!= NULL)
      {
        //printf("I AM PROBLEM HEREEEEEEEEEEEEEEEEEEEEEEE\n");
				//printf("PASSING BY: %s %s %s %s at %d\n",tempHash->name,tempHash->sex,
							 //tempHash->number,tempHash->mail, hash_value);
        tempHash = tempHash->next;
      }
      //printf("I REACH HREEE\n");
			tempHash->next = current;
      //printf("HASHED NEXT: %s %s %s %s at %d\n",tempHash->name,tempHash->sex, tempHash->number,
          // tempHash->mail, hash_value);
    }
    else
    {
      strcpy(tempHash->name, cp_name);
      strcpy(tempHash->sex, cp_sex);
      strcpy(tempHash->mail, cp_mail);
      strcpy(tempHash->number, cp_num);
      tempHash->filled = true;
      tempHash->next = NULL;
     // printf("HASHED: %s %s %s %s at %d\n",tempHash->name,tempHash->sex, tempHash->number,
           //tempHash->mail, hash_value);
    }
  }
}

int Hashfun(char *number)// design the hash function based on the phone number
{
  int len = strlen(number), i,j, n, asci, end, sum =0, hashVal;
  end = len-1;
  j = 0;
  for(i=0; i<len; i++)
  {
    n = number[i]+0-'0';
    j += (n*(number[i]+0));
   // printf("char %c is num %d ",number[i], n);
    asci = number[end]+0;
    end--;
    //printf("asci is %d\n", asci);
    sum += n*asci;
  }
  //if(sum == 2336 || sum == 2380 || sum == 2747)
  //{printf("\nHARD COLLISSION at %d and %d\n", sum, j); sum = 2380; j = 2492; } 
  //printf("SUM IS %d and %d\n", sum, j);
  //printf("HASH VALUE IS: %d\n", sum % 43);
  hashVal = (j+sum) % 43;
  //printf("HASH ACTUAL IS : %d\n", hashVal );
  return hashVal;
}
void Query(ST *hashTable,char *number)//Hash search based on phone number
{
  int hashVal = Hashfun(number);
	ST *tempTable = &hashTable[hashVal];
  if(tempTable->filled == true)
  {
    printf("THERE EXIST A RECORD:-\n");
    if(strcmp(tempTable->number, number) == 0 )
    {
      printf("FOUND EXACT: %s %s %s %s",tempTable->name,tempTable->sex,tempTable->number,tempTable->mail);
    }
    else
    {
      //printf("CARRY: %s %s %s %s\n",tempTable->name,tempTable->sex,tempTable->number,tempTable->mail);
      while(tempTable->next != NULL)
      {
        //printf("NEXT: %s %s %s %s\n",tempTable->name,tempTable->sex,
               //tempTable->number,tempTable->mail);
        tempTable = tempTable->next;
        if(strcmp(tempTable->number, number) == 0)
        {
           printf("FOUND AT NEXT: %s %s %s %s",tempTable->name,tempTable->sex,
                  tempTable->number,tempTable->mail);
          return;
        }
      }
      //printf("PREVIOUS: %s %s %s %s\n",tempTable->name,tempTable->sex,tempTable->number,tempTable->mail);
      printf("NO MATCH AFTER SEARCHING IN SIMILAR INDEX\n");
      return;
    }
  }
  else
  {
    printf("NO MATCH IS FOUND IN THE TABLE FOR %s \n", number);
    return;
  } 
}
