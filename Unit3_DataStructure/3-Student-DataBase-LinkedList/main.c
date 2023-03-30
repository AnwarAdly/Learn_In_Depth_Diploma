/*
 * main.c
 *
 *  Created on: 6 Jan 2023
 *      Author: DELL
 */


#include "main.h"

void main(){
	while(1){
		DPRINTF("\n==========Student DataBase=========");
		DPRINTF("\n \t Choose any option you need ");
		DPRINTF("\n 1: Add a student ");
		DPRINTF("\n 2: Delete a student ");
		DPRINTF("\n 3: View all students ");
		DPRINTF("\n 4: Delete all students ");
		DPRINTF("\n 5: Get entered index node ");
		DPRINTF("\n 6: Get length of list ");
		DPRINTF("\n 7: Get entered node from end ");
		DPRINTF("\n \t Enter option number : ");
		gets(temp);
		DPRINTF("\n ===================================");
		switch(atoi(temp)){
		case 1: Add_Student();					break;
		case 2: Delete_Student();				break;
		case 3: View_Students();				break;
		case 4: Delete_All();					break;
		case 5: GetNth();						break;
		case 6: Get_Length();					break;
		case 7: GetNthFromEnd();				break;
		default: DPRINTF("\n Wrong Option ");	break;
		}
	}
}
