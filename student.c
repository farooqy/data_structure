#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>



typedef struct student
{
	char name[20];	
	int score;    
    struct student *next;
} Student_Data_Type;
int menu_select();//menu function
Student_Data_Type *Readfromfile(Student_Data_Type *head);//read from file and create a ordered list according to name
Student_Data_Type *Query(Student_Data_Type *head, char *name);//query according to name
Student_Data_Type *insert(Student_Data_Type *head, Student_Data_Type *p);//insert
Student_Data_Type *del(Student_Data_Type *head,char *name);//delete
void DisplayAll(Student_Data_Type *head);//display all records
char *Get_Student_Name();

int menu_select()
{
	char i;
	do{
		printf("1.create list(read from file)\n");
		printf("2.display all records\n");
		printf("3.insert a record\n");
		printf("4.delete a record\n");
		printf("5.query\n");		
		printf("0.exit\n");
		printf("Please input index(0-5):");
		i=getchar();		
	}while(i<'0' || i>'5');
	return (i-'0');	
}



int main()
{
	Student_Data_Type *head,*p;
	char temp[20];
	head=NULL;
	for(;;)
	{
		switch(menu_select())
		{
		case 1:
				system("clear");
			printf("[###] READING DATA OF STUDENTS FROM: \"data.txt\"\n");
			head = Readfromfile(head);
				break;
		case 2:
				system("clear");
			DisplayAll(head);
				break;
		case 3:		
				system("clear");
				char *Student_Insert = Get_Student_Name();
				int Score_Insert;printf("[###] ENTER SCORE: ");
				scanf("%d", &Score_Insert);
				strcpy(p->name, Student_Insert);
				p->score = Score_Insert;
				head = insert(head, p);
				break;
		case 4:			
				system("clear");
				char *Student_Delete = Get_Student_Name();
				head = del(head, Student_Delete);
				break;
		case 5:
				if(head == NULL)
				{
					system("clear");  
					printf("[###] LIST IS EMPTY NOTHING TO SEARCH\n");
					break;
				}
				char *Studnet_Query = Get_Student_Name();
				//printf("SEARCHING: %s\n", Studnet_Query);
			 p = Query(head, Studnet_Query);
			//	printf("FINISHED  PROCESSING\n");
			if(p != NULL )
			{
					system("clear"); 
				printf("[###] NAME: %s   SCORE: %d\n", p->name, p->score);
			}
			else
			{
				system("clear"); 
				printf("[###] THE STUDENT %s DOES NOT HAVE A RECORD\n",Studnet_Query);
			}
				break;
		
		case 0:
				system("clear");
			 printf("[!!!]GOOD BYE\n");
				exit(0);

		}
	}
}

Student_Data_Type *Readfromfile(Student_Data_Type *head)
{
	char names[100][20], cp_name[20];// a copy of names upto 100 students of 20 characters length for each name;
	int score[100], cp_score;//The corresponding score for each student;
	char buffer[30];
	int numOfStudent =0, i, j;
	FILE *fp;
	
	if((fp = fopen("data.txt", "r")) == NULL) //Error handle if it fails to open the file
	{
		int errnum = errno;
		fprintf(stderr, "[###] ERROR OPENING FILE: %s\n", strerror(errnum));
		exit(0);
	}
	while(fgets(buffer, sizeof(buffer), fp) != NULL) // read line by line and store each line into a buffer
	{
		sscanf(buffer, "%s %d", names[numOfStudent], &score[numOfStudent]);//format the read buffer into name and score array corresponding 
		                                                                     //to number  of student;
		printf("%s\n", buffer);
		numOfStudent++; // Increment number of student;
	}
	//printf("[###]SUCCESSFULLY CREATED TEMPORARY ARRAY TO STORE BEFORE CREATING LIST:-\n");
	//now sort the names before making the list;
	for(i=0; i< numOfStudent-1; i++)
	{
		for(j=i; j <numOfStudent; j++)
		{
			if(strcmp(names[i], names[j]) > 0) // if the name that was read first is greater than the latter, swap the two
			{
				strcpy(cp_name, names[i]);
				strcpy(names[i], names[j]);
				strcpy(names[j], cp_name);
				
				cp_score = score[i];
				score[i] = score[j];
				score[j] = cp_score;
			}
		}
	}
	//printf("SUCCESSFULLY SORTED THE ARRAY IN ORDER OF NAME\n");
	//now create the list from this array
	Student_Data_Type  *stack_buffer ;

	stack_buffer = NULL;
	for(i=0; i < numOfStudent; i++)
	{
		Student_Data_Type	*current =  malloc(sizeof(Student_Data_Type));
	strcpy(current->name, names[i]);
	current->score = score[i];
	current->next = NULL;
		//printf("CREATING LIST FOR %s %d \n", names[i], score[i]);
		if(head == NULL)
		{
			stack_buffer = current;
			head = current;
		}
		else
		{
			stack_buffer->next = current;
			stack_buffer = current;
		}
		//printf("SAVEDD: %s  %d\n", stack_buffer->name, stack_buffer->score);
	}
	printf("[###]LIST SUCCESSFULLY CREATED\n");
	return  head;
}
void DisplayAll(Student_Data_Type *head)
{
Student_Data_Type *stackbuffer = head;
printf("[###] DISPLAYING NAMES AND SCORE OF STUDENTS:- \n");
while(stackbuffer != NULL)
{
	printf("[###] %s <-----> %d\n", stackbuffer->name, stackbuffer->score);
  stackbuffer = stackbuffer->next;
}
	
}
Student_Data_Type *Query(Student_Data_Type *head, char *name)
{
	//printf("INSIDE QUERY NOW\n");
	Student_Data_Type *stackbuffer = head;
	//printf("SEARCHING FOR %s ", name);
	while(stackbuffer != NULL)
	{
		//printf("COMPARING: %s AND %s\n", stackbuffer->name, name);
		if(strcmp(stackbuffer->name, name) == 0)
		{
			printf("[###] FOUND A MATCH [###]\n");
			return stackbuffer;
		}
		stackbuffer = stackbuffer->next;
	}
	return NULL;
}

Student_Data_Type *insert(Student_Data_Type *head, Student_Data_Type *p)
{
	if(head == NULL)//if the head is empty then create list first then insert student
	{
		head = Readfromfile(head);
	}
	Student_Data_Type *bufferStack = head;
	bool inserted = false;
	while(bufferStack->next != NULL && strcmp(bufferStack->next->name, p->name) < 0)
	{
		bufferStack = bufferStack->next;
	}
	p->next = bufferStack->next;
	bufferStack->next = p;
	printf("[####] ADDED %s   %d\n",bufferStack->next->name, bufferStack->next->score);
	printf("[##] AND IS POINTING TO %s %d\n", bufferStack->next->next->name, bufferStack->next->next->score);
	inserted = true;
	return head;
}

Student_Data_Type *del(Student_Data_Type *head,char *name)
{
	if(head == NULL)
	{
		printf("[###] STACK IS EMPTY NOTHING TO DELETE\n");
		return NULL;
	}
	Student_Data_Type *bufferStack = head;
	Student_Data_Type *prev;
	prev = malloc(sizeof(Student_Data_Type));
	bool foundMatch = false;
	while(bufferStack->next != NULL)
	{
		if(strcmp(bufferStack->name, name) == 0)
		{
			printf("[###] DELETING %s FROM THE LIST\n", bufferStack->name);
			foundMatch = true;
			break;
		}
		else
		{
			prev = bufferStack;
			bufferStack = bufferStack->next;
		}
	}
	if(foundMatch)
	{
		prev->next = bufferStack->next;
		printf("[###] %s HAS BEEN DELETED \n", bufferStack->name);
	}
	else
		printf("[###] NO MATCH WAS FOUND. NOTHING WAS DELETED\n");
	return head;
}

char *Get_Student_Name()
{
	printf("[###]ENTER NAME PLZ: ");
	char *input = malloc(20);
	scanf("%s",input);
	//printf("SENT: %s", c);
	return input;
}
