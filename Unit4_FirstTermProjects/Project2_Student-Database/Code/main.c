/*
 * main.c
 *
 *  Created on: 3 Feb 2023
 *      Author: DELL
 */

#include "sdatabase.h"
#include <stdio.h>


void main(void){
	DPRINTF("==============WELCOME TO STUDENT DATABASE==============\n");
	student_init();
	int option , flag=1;
	while(flag){
        DPRINTF("=================================================\n");
        DPRINTF("Choose the task you want to perform \n");
        DPRINTF("1. Add the student's informations \n");
        DPRINTF("2. Search the student's informations by ID \n");
        DPRINTF("3. Search the student's informations by First Name \n");
        DPRINTF("4. How many students registered in course \n");
        DPRINTF("5. The total number of students \n");
        DPRINTF("6. Delete the student's informations by ID\n");
        DPRINTF("7. Update the student's informations by ID\n");
        DPRINTF("8. Show All Students\n");
        DPRINTF("9. To Exit\n");
        DPRINTF("Enter you choice to perform the task: ");

        DSCANF("%d", &option);
        DPRINTF("=================================================\n");

        switch (option)
        {
            case 1:
                Add_Student();
                break;

            case 2:
                Find_Student_byID();
                break;

            case 3:
                Find_Student_byFirstName();
                break;

            case 4:
                Count_Students_inCourse();
                break;

            case 5:
                Count_Students();
                break;

            case 6:
                Delete_Student();
                break;

            case 7:
                Update_Student();
                break;

            case 8:
                View_Students();
                break;

            case 9:
               	flag=0;
                break;

            default:
            	DPRINTF("[ERROR] You entered wrong option \n");
                break;
        }
	}
}
