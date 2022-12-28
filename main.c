/*Heba Ashraf*/

#include <stdio.h>
#include <string.h>
#include "FinalProject.h"

int main(){
	int Pass=123;
	char username[6]="Admin";
	int Admin_Password;
	char Admin_username[6];
	
	/* Display Menu */
	int x=1;
	int Mode;
		start:
		printf("\t \t \t \t \t --Welcome To IMT Bank System--\n");
		
		printf("For Admin Window         Press 1\n");
		printf("For Client Window        Press 2\n");
		printf("Enter your Choice: ");
		scanf ("%d",&Mode);
    while(x) {
			if (Mode==1){
				printf("Enter username: ");
				scanf(" %[^\n]s",&Admin_username);
				printf("Enter password: ");
				scanf("%d",&Admin_Password);
				if (Pass==Admin_Password && (strcmp(username,Admin_username)==0)){
					printf("****************************************************************\n");
					printf("Welcome to Admin Window          \n");
					printf("Create New Account         Press 1\n");
					printf("Open Exisiting Account     Press 2\n");
					printf("Exit System                Press 3\n");
					
					int Admin_Choice;
					printf("Enter your choice: ");
					scanf("%d",&Admin_Choice);
					printf("****************************************************************\n");
					
						if (Admin_Choice==1){
							CreateAccount();	
						}
					
						else if (Admin_Choice==2){
							OpenExistingAccout();	
						}
						
						else {
							goto start;	
						}		
				 }
				 else 
					 printf("Admin not exist\n ");
			}
			else if (Mode==2){
				 printf("****************************************************************\n");
				 printf("Welcome to Client Window          \n");
				 ClientWindow();
				 goto start;
			 }
			 
			else 
				x=0; 
		   
   }
}
















/*Heba Ashraf*/