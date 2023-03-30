#include "sdatabase.h"
#include "fifo.h"
#include <string.h>
#include <stdio.h>

fifo_t fifo_buf;
student_t student[students_count];
int i ,j ;

// student database initialization
void student_init(){
	fifo_init(&fifo_buf , student , students_count);
}
// Enter student's data
void Enter_sData(student_t* student){
	DPRINTF("Enter student's unique ID : ");
	DSCANF("%d",&(student->ID));
	DPRINTF("Enter student's first name : ");
	gets(student->first_name);
	/*DPRINTF("Enter student's last name : ");
	gets(student->last_name);*/
	DPRINTF("Enter student's GPA : ");
	DSCANF("%f",&(student->GPA));
	for (i =0 ; i<courses_count ; i++){
		DPRINTF("Enter student's registered course_ID : ");
		DSCANF("%d",&(student->course_ID[i]));
	}
}
// Printing student's data
void Print_sData(student_t* student){
	DPRINTF("==========The Student's informations : ==========\n");
	DPRINTF("	Student's ID : %d \n",student->ID);
	DPRINTF("	Student's first name : %s \n",student->first_name);
	DPRINTF("	Student's last name : %s \n",student->last_name);
	DPRINTF("	Student's GPA : %f \n",student->GPA);
	DPRINTF("	Student's registered course_ID : ")
	for (i =0 ; i<courses_count ; i++)
		DPRINTF("%d ",student->course_ID[i]);
	DPRINTF("\n");
}

void Add_Student(){
	student_t stud;
	Enter_sData (&stud);
	if(fifo_search_studentID(&fifo_buf , &stud , stud.ID)){
		DPRINTF("[ERROR] Sorry , This student's ID is already taken \n");
	}
	else{
		unsigned int status = fifo_enqueue(&fifo_buf , stud);
		if (status == FIFO_NULL){
			DPRINTF("[ERROR] The Student's database is not found \n");
		}
		else if (status == FIFO_FULL){
			DPRINTF("[ERROR] The Student's database is not full \n");
		}
		else{
			DPRINTF("[INFO] The Student's informations are added successfully \n");
		}
	}
}
void Find_Student_byID(){
	student_t* stud;
	unsigned int id;
	DPRINTF("Please Enter The required student's ID : \n");
	DSCANF("%d ",&id);
	if(fifo_search_studentID(&fifo_buf , stud , id))
		Print_sData(stud);
	else
		DPRINTF("[ERROR] Student Not Found \n");

}
void Find_Student_byFirstName(){
	student_t* stud = fifo_buf.tail;
	unsigned char* fName;
	DPRINTF("Please Enter The required student's First Name : \n");
	gets(fName);
	for(i=0 ; i<fifo_buf.count ; i++){
		if (strcmp(stud->first_name , fName)==0){
			Print_sData(stud);
			return;
		}
		else{
			if (stud == (fifo_buf.base+(fifo_buf.length * sizeof(element_type))))
				stud = fifo_buf.base;
			else
				stud++;
		}
	}
	DPRINTF("[ERROR] Student Not Found \n");
}
void Count_Students_inCourse(){
	student_t* stud = fifo_buf.tail;
	unsigned int cid;
	DPRINTF("Please Enter The required course's ID : \n");
	DSCANF("%d ",&cid);
	for(i=0 ; i<fifo_buf.count ; i++){
		for (j=0 ; j<stud->course_ID ; j++){
			if (stud->course_ID[j] == cid){
				Print_sData(stud);
				break;
			}
		}
		if (stud == (fifo_buf.base+(fifo_buf.length * sizeof(element_type))))
			stud = fifo_buf.base;
		else
			stud++;
	}

}
void Count_Students(){
	DPRINTF("[INFO] Total numbers of students : %d \n",fifo_buf.count);
}
void Delete_Student(){
	student_t* stud = fifo_buf.tail;
	unsigned int id;
	DPRINTF("Please Enter The required student's ID to delete : \n");
	DSCANF("%d ",&id);
	if(fifo_search_studentID(&fifo_buf , &stud , id)){
		for( i=0 ; i<fifo_buf.count ; i++){
			if (stud->ID == id){
				unsigned int status = fifo_dequeue(&fifo_buf , stud);
				if (status == FIFO_NULL){
					DPRINTF("[ERROR] The Student's database is not found \n");
				}
				else if (status == FIFO_EMPTY){
					DPRINTF("[ERROR] The Student's database is empty \n");
				}
				else{
					DPRINTF("[INFO] The Student's informations are deleted successfully \n");
				}
			}
			if (stud == (fifo_buf.base+(fifo_buf.length * sizeof(element_type))))
				stud = fifo_buf.base;
			else
				stud++;
		}
	}
	else
		DPRINTF("[ERROR] This student's ID is not found \n");
}
void Update_Student(){
	student_t* stud = fifo_buf.tail;
	unsigned int id;
	DPRINTF("Please Enter The required student's ID to update : \n");
	DSCANF("%d ",&id);
	unsigned int option;
	DPRINTF("Please choose The required student's info to update : 1. Update ID \n 2. Update First Name \n 3. Update Last Name \n 4. Update GPA \n 5. Update Registered Course ID \n");
	DSCANF("%d ",&option);
	for( i=0 ; i< fifo_buf.count ; i++){
		if (stud->ID == id){
			Print_sData(stud);
			switch(option){
				case 1 : DPRINTF("Enter the new ID : \n");			DSCANF("%d",&stud->ID);	break;
				case 2 : DPRINTF("Enter the new first name : \n");	gets(stud->first_name);	break;
				case 3 : DPRINTF("Enter the new last name : \n");	gets(stud->last_name);	break;
				case 4 : DPRINTF("Enter the new GPA : \n");			DSCANF("%f",&stud->GPA);	break;
				case 5 : DPRINTF("Enter the new CourseID : \n");
						 for(int i=0 ; i< courses_count ; i++)
							 DSCANF("%d",&stud->course_ID[i]);
						 																	break;
				default : DPRINTF("You entered wrong option \n");							break;
			}
			DPRINTF("==========The updated student's informations : ========= \n");
			Print_sData(stud);
		}
		else{
			if (stud == (fifo_buf.base+(fifo_buf.length * sizeof(element_type))))
				stud = fifo_buf.base;
			else
				stud++;
		}
	}
}
void View_Students(){
	if (fifo_buf.count == 0){
		DPRINTF ("[ERROR] The Student's database is empty \n");
	}
	else{
		student_t* stud = fifo_buf.tail;
		for( i=0 ; i<fifo_buf.count ; i++){
			Print_sData(stud);
			if (stud == (fifo_buf.base+(fifo_buf.length * sizeof(element_type))))
				stud = fifo_buf.base;
			else
				stud++;
		}
	}
}
