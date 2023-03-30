#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"

#define DPRINTF(...)		{fflush(stdout); \
		fflush(stdin); \
		printf(__VA_ARGS__); \
		fflush(stdout); \
		fflush(stdin);}

struct sData{
	int ID;
	char name[20];
	float height;
};

struct student{
	struct sData student;
	struct student* NextStudent;
};

struct student* FirstStudent = NULL;
char temp[20];

void Add_Student(){
	struct student* NewStudent;
	struct student* LastStudent;
	if (FirstStudent == NULL){ //if list is empty so create the first node
		NewStudent = (struct student*) malloc (sizeof(struct student));
		FirstStudent = NewStudent;
	}
	else{ // if list has last nodes so first go to last node then add new node to others
		LastStudent = FirstStudent ;
		while (LastStudent->NextStudent)
			LastStudent = LastStudent->NextStudent;
		NewStudent = (struct student*) malloc (sizeof(struct student));
		LastStudent->NextStudent=NewStudent;
	}
	//fill the new node
	DPRINTF("\n Enter the ID : ");
	gets(temp);
	NewStudent->student.ID = atoi(temp);
	DPRINTF("\n Enter student full name : ");
	gets(NewStudent->student.name);
	DPRINTF("\n Enter the height : ");
	gets(temp);
	NewStudent->student.height = atof(temp);
	//set the next node to null
	NewStudent->NextStudent = NULL;
}

int Delete_Student (){
	int selected_id;
	DPRINTF("\n Enter the selected ID : ");
	gets(temp);
	selected_id = atoi(temp);
	if(FirstStudent){
		struct student* PreviousStudent = NULL;
		struct student* SelectedStudent = FirstStudent;
		while(SelectedStudent){
			if(SelectedStudent->student.ID == selected_id){
				if(PreviousStudent)
					PreviousStudent->NextStudent = SelectedStudent->NextStudent;
				else
					FirstStudent = SelectedStudent->NextStudent;
				free (SelectedStudent);
				return 1;
			}
			PreviousStudent = SelectedStudent;
			SelectedStudent = SelectedStudent->NextStudent;
		}
	}
	DPRINTF("\n Can not find student id");
	return 0;
}

void View_Students(){
	int count =0;
	struct student* CurrentStudent = FirstStudent;
	if (FirstStudent == NULL)
		DPRINTF("\n Empty List");
	while(CurrentStudent){
		DPRINTF("\n Record number : %d",count+1);
		DPRINTF("\n ID : %d",CurrentStudent->student.ID);
		DPRINTF("\n Name : %s",CurrentStudent->student.name);
		DPRINTF("\n Height : %f",CurrentStudent->student.height);
		CurrentStudent = CurrentStudent->NextStudent;
		count++;
	}
}

void Delete_All(){
	struct student* CurrentStudent = FirstStudent;
	if (FirstStudent == NULL)
		DPRINTF("\n Empty List");
	while(CurrentStudent){
		struct student* TempStudent = CurrentStudent;
		CurrentStudent = CurrentStudent->NextStudent;
		free(TempStudent);
	}
	FirstStudent = NULL;
}

void GetNth(){
	int index , count=0;
	DPRINTF("\n Enter the selected index : ");
	gets(temp);
	index = atoi(temp);
	struct student* CurrentStudent = FirstStudent;
	if (FirstStudent == NULL)
		DPRINTF("\n Empty List");
	while(CurrentStudent){
		if(count == index){
			DPRINTF("\n Student ID : %d",CurrentStudent->student.ID);
			DPRINTF("\n Student Name : %s",CurrentStudent->student.name);
			DPRINTF("\n Student Height : %f",CurrentStudent->student.height);
			break;
		}
		else{
			count++;
			CurrentStudent = CurrentStudent->NextStudent;
		}
	}
}

void Get_Length (){
	int count=0;
	struct student* CurrentStudent = FirstStudent;
	if (FirstStudent == NULL)
		DPRINTF("\n Empty List");
	while(CurrentStudent){
		CurrentStudent=CurrentStudent->NextStudent;
		count++;
	}
	DPRINTF("\n Length of linked list : %d ",count);
}

void GetNthFromEnd (){
	int n , count;
	DPRINTF("\n Enter the selected node : ");
	gets(temp);
	n = atoi(temp);
	struct student* mai = FirstStudent;		\\main pointer that we searched about
	struct student* ref  = FirstStudent;	\*reference pointer go to until count = n 
											  then go with main ptr step by step until
											  ref reach the null node at the end 
											  so the main is in Nth node from end *\
	if (FirstStudent == NULL)
		DPRINTF("\n Empty List");
	while(ref){
		for(count=0;count <= n;count++)
			ref = ref->NextStudent;
		mai = mai->NextStudent;
		ref = ref->NextStudent;
	}
	DPRINTF("\n Student ID : %d",mai->student.ID);
	DPRINTF("\n Student Name : %s",mai->student.name);
	DPRINTF("\n Student Height : %f",mai->student.height);
}
