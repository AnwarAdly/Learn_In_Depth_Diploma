/*
 * sdatabase.h
 *
 *  Created on: 3 Feb 2023
 *      Author: DELL
 */

#ifndef SDATABASE_H_
#define SDATABASE_H_

#include <stdio.h>

#define DPRINTF(...)		{fflush(stdout);	  \
		 					 fflush(stdin); 	  \
		 					 printf(__VA_ARGS__); \
							 fflush(stdout); 	  \
							 fflush(stdin);}
#define DSCANF(...)			{fflush(stdout);	  \
		 					 fflush(stdin); 	  \
		 					 scanf(__VA_ARGS__);  \
							 fflush(stdout); 	  \
							 fflush(stdin);}

#define students_count 50
#define courses_count  3

typedef struct{
	unsigned char* first_name;
	unsigned char* last_name;
	unsigned int ID;
	float GPA;
	unsigned int* course_ID;
}student_t;

extern student_t student[students_count];

// init and auxiliary functions
void student_init();
void Enter_sData(student_t* student);
void Print_sData(student_t* student);

// student database functions prototypes
void Add_Student();
void Find_Student_byID();
void Find_Student_byFirstName();
void Count_Students_inCourse();
void Count_Students();
void Delete_Student();
void Update_Student();
void View_Students();


#endif /* SDATABASE_H_ */
