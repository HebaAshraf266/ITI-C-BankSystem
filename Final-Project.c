/*Heba Ashraf*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "FinalProject.h"

//Head
tNode *Head=NULL;

//######################################################################## Admin Window ###################################################################//

///Function to generate random password
char* randomPasswordGeneration(){
    int i = 0;
    int randomizer = 0;

    // the numbers will be different every time
    srand((unsigned int)(time(NULL)));
    // Array of numbers
    char numbers[] = "0123456789";
  
    // Array of small alphabets
    char letter[] = "abcdefghijklmnoqprstuvwyzx";
  
    // Array of capital alphabets
    char LETTER[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
  
    // Array of all the special symbols
    char symbols[] = "!@#$^&*?";
  
    // Stores the random password
    static char password[8];
  
    randomizer = rand() % 4;
  
    for (i = 0; i < 8; i++) {
        if (randomizer == 1) {
            password[i] = numbers[rand() % 10];
            randomizer = rand() % 4;
        }
        else if (randomizer == 2) {
            password[i] = symbols[rand() % 8];
            randomizer = rand() % 4;
        }
        else if (randomizer == 3) {
            password[i] = LETTER[rand() % 26];
            randomizer = rand() % 4; 
        }
        else {
            password[i] = letter[rand() % 26];
            randomizer = rand() % 4;
        }
    }
	password[9]='\0';
	return password;
}

//************************************************************* --- CREATE ACCOUNT --- *****************************************************************//
///Function to create Account
tNode* CreateAccount(){
	static long long BankAccountId=1000000000;

	tNode NewAcc;
		//scan account data
		strcpy(NewAcc.AccountStatus,"Active");

		printf("Enter The client's information\n");
		printf("Enter client's Name: ");
		scanf(" %[^\n]s",&NewAcc.Name);
		printf("Enter client's National ID: ");
		scanf("%d",&NewAcc.National_ID);
		printf("Enter client's Age: ");
		scanf("%d",&NewAcc.Age);
		
		if ((NewAcc.Age)<21){
			printf("Thie client < 21 please enter the gurdian's name: ");
			scanf(" %[^\n]s",&NewAcc.Guardian);
			printf("Enter the gurdian's national ID:");
			scanf("%d",&NewAcc.GuardianNationalId);
		}
		
		printf("Enter client's Address: ");
		scanf(" %[^\n]s",&NewAcc.Address);
		printf("Enter client's Balance: ");
		scanf("%lld",&NewAcc.Balance);

		tNode *NewNode=(tNode*)malloc(sizeof(tNode));
		
		//check heap
		if (NewNode==NULL){
			printf("Failed process");
			return 0;
		}
		
		//add data to node in list
		else {
			strcpy(NewNode->Name,NewAcc.Name);
			strcpy(NewNode->Address,NewAcc.Address);
			strcpy(NewNode->Guardian,NewAcc.Guardian);
			strcpy(NewNode->AccountStatus,NewAcc.AccountStatus);
			
			NewNode->Balance=NewAcc.Balance;
			NewNode->Age=NewAcc.Age;
			NewNode->National_ID=NewAcc.National_ID;
			NewNode->GuardianNationalId=NewAcc.GuardianNationalId;
			NewNode->BankAccountId = BankAccountId;
			 
			printf("New Account has been created Successfully\n");
			printf("Account Status= %s\n",NewNode->AccountStatus);			
			printf("Bank Account Id= %lld\n",NewNode->BankAccountId);
			
			strcpy(NewAcc.Password,randomPasswordGeneration());
			strcpy(NewNode->Password,NewAcc.Password);
			printf("Password: %s\n",NewNode->Password);
			BankAccountId++;
			
			NewNode->pnext=Head;
			Head=NewNode;
		}
	return NewNode;
} 
 
//************************************************************* --- OPEN EXISTING ACCOUT --- *****************************************************************//
///Function to OPEN EXISTING ACCOUT
void OpenExistingAccout(){
	int y;
	//PrintList();
	long long AccountId;
	
	start:
	printf("Please Enter your Bank Account ID: ");
	scanf("%lld",&AccountId);
	
	tNode*current=Head; //point to first node 
	
	//check exist of ID
	current = CheckUser(AccountId); 
	int OpenChoice;	

	if ( current != NULL ) // LIST EXIST 
	{
		y=1;
			while (y){
				if (current->BankAccountId==AccountId){
					printf("\n****************************************************************\n");		
					printf("Make Transacation          Press 1\n");
					printf("Change Account Status      Press 2\n");
					printf("Get Cash                   Press 3\n");
					printf("Deposite in Account        Press 4\n");
					printf("Return to main menu        Press 5\n");
					
					printf("Enter your choice: ");
					scanf("%d",&OpenChoice); 
					printf("****************************************************************\n");	
					
						if (OpenChoice==1){ //Make Transacation 
							MakeTransaction( current );
							//PrintList(); //--> To show changes
						}
						
						else if (OpenChoice==2){ //Change Account Status 
							ChangeAccountStatus( current );
							//PrintList();
						 }
						
						
						 else if (OpenChoice==3){ //Get Cash
							GetCash ( current );
							//PrintList();
						 }
						
						 else if (OpenChoice==4){ //Deposite in Account 	
							Deposite ( current );
							//PrintList();
						 }
						
						 else if (OpenChoice==5){ //Return to main menu 
							y=0;
						 }
					}
					
				else{
				printf("Wrong ID, Make sure you have an account\n");
				goto start;
				}
		   }
		current=current->pnext;	
	}
 }
 
 ///Function to Make Transaction
void MakeTransaction ( tNode *sendingcurrent ){ 
	
	long long AmountOfMoney,SendAccountID;
	
	printf("Enter the Bank Account ID you want to transfer money to: \n");
	scanf("%lld",&SendAccountID); 
	
	//2nd node (2nd Account)
	tNode*current2=Head;
	
	//loop to find 2nd account with (SendAccountID)
	while (current2!=NULL && current2->BankAccountId!=SendAccountID ){

		current2=current2->pnext;
	}
	
	//check if ID exist in list && check status of 2 Accounts
	if ( current2->BankAccountId==SendAccountID && (strcmp(current2->AccountStatus,"Active")==0) 
		&& (strcmp(sendingcurrent->AccountStatus,"Active")==0)){
		printf("Enter amount of money to transfer it to the this account: \n");
		scanf("%lld",&AmountOfMoney);
		
			if ( AmountOfMoney <= sendingcurrent->Balance ){ 
				printf("Transaction process has been done successfully\n");
				
				sendingcurrent -> Balance -= AmountOfMoney;
				printf("Your current balance= %lld\n",sendingcurrent->Balance);
				
				current2 -> Balance += AmountOfMoney;
				//printf("New Balance of the receiver= %lld\n",current2->Balance); 	
			}
			
			else
				printf("There is no enough money ,Failed transaction process\n");
	}
	
	else 
		printf("Failed Process, one of these account is closed or restricted\n");
 } 
 
//Function check ID
tNode* CheckUser( long long ID ){
	
	tNode *current=Head;
	
	while( current->pnext!= NULL ){ 
	
		if (current->BankAccountId==ID){
			return current;
	    }
	
		current=current->pnext;
	}
	//return node of sending ID
	return current;
}

//Function Print List
void PrintList(){
	tNode *current = Head;
	while (current!=NULL){
		//printf("Address in memory= %X\n",current);
		printf("User Name: %s\n",current->Name);
		printf("National ID: %d\n",current->National_ID);
		printf("Password: %s\n",current->Password);
		printf("AccountID: %lld\n",current->BankAccountId);
		printf("Age: %d\n",current->Age);
		printf("Address: %s\n",current->Address);
		printf("Balance: %lld\n",current->Balance);
		printf("AccountStatus: %s\n",current->AccountStatus); 
		current=current->pnext;
	}	
} 
 
//Function to change Account Status
 void ChangeAccountStatus(tNode *sendingcurrent){
	 
	int Stauts;
	printf("Set Account to Active State         Press 1\n");
	printf("Set Account to Restricted State     Press 2\n");
	printf("Set Account to Closed               Press 3\n");
	printf("Enter your chouce: ");
	scanf("%d", &Stauts);
		
		if (Stauts == 1) 
		{
			strcpy(sendingcurrent->AccountStatus,"Active");
		} 
		else if (Stauts == 2) 
		{
			strcpy(sendingcurrent->AccountStatus,"Restricted");
		}
		else if (Stauts == 3)
		{
			strcpy(sendingcurrent->AccountStatus,"Closed");
		}	
 } 

//Function to Get Cash
void GetCash (tNode *sendingcurrent){ 
	
	long long AmountOfMoney;
	
		printf("Enter the amount of money you want: ");
		scanf("%lld",&AmountOfMoney);
		if ( AmountOfMoney <= sendingcurrent -> Balance  ){ //check status
			sendingcurrent -> Balance -= AmountOfMoney;
			printf("Succsseful process \n");
			printf("Your current Balance: %lld\n",sendingcurrent->Balance);	
		}
} 


//Function to Deposite in account
void Deposite ( tNode *sendingcurrent ){

	long long AmountOfMoney;
	printf("Enter the amount of money you want to deposite: ");
	scanf("%lld",&AmountOfMoney);
	sendingcurrent -> Balance += AmountOfMoney;
	printf("Succsseful process \n");
	printf("Your current Balance: %lld\n",sendingcurrent->Balance);	
	sendingcurrent = sendingcurrent->pnext;
} 

//######################################################################## CLIENT WINDOW ##############################################################//
//Function for client feature 
void ClientWindow(){
	long long AccountId;
	int y=1;
	
	start:
	printf("Please Enter your Bank Account ID: ");
	scanf("%lld",&AccountId);
	
	tNode*current=Head;
	current = CheckUser(AccountId);
	int OpenChoice;
	
	if ( current != NULL )
	{	
		while(y){
			if (current->BankAccountId==AccountId){
				printf("****************************************************************\n");	
				printf("Make Transacation          Press 1\n");
				printf("Change Account Password    Press 2\n");
				printf("Get Cash                   Press 3\n");
				printf("Deposite in Account        Press 4\n");
				printf("Return to main menu        Press 5\n");
				
				printf("Enter your choice: ");
				scanf("%d",&OpenChoice);
				printf("****************************************************************\n");	
				
					if (OpenChoice==1){ //Make Transacation 
						MakeTransaction ( current );
						PrintList();
					}
					
					else if (OpenChoice==2){ //Change Account Status 
						changePassword ( current );
						//PrintList();
					 }
					
					
					 else if (OpenChoice==3){ //Get Cash
						 GetCash ( current );
						 //PrintList();
					 }
					
					 else if (OpenChoice==4){ //Deposite in Account 	
						 Deposite ( current );
						 //PrintList();
					 }
					
					 else if (OpenChoice==5){ //Return to main menu 
						 y=0;
					 }
			}

			else{
				printf("Wrong ID, Make sure you have an account\n");
				goto start;
				}			
	    }
		current=current->pnext;
	}
}
 
//Function to change password 
void changePassword ( tNode *current ){
	
	char NewPass[9];
	char CuurentPass[9];
	int counter =1;
	
	CuurentPass[9]='\0';
	
	while (counter <=3){
		
		printf("Enter current password: ");
		scanf(" %[^\n]s",&CuurentPass);
		
		if(strcmpi(CuurentPass,current->Password)==0){
			printf("Enter your New Password: ");
			scanf(" %[^\n]s",&NewPass);
			NewPass[9]='\0';
			strcpy(current->Password,NewPass);
			printf("Password has been changed Successfully\n");
			break;
		}
		
		else 
			printf("Incorrect password, Try again\n");	
		
		counter++;
		
		if (counter==3){
			printf("Account locked\n");
			break;
		}
    }
}

/*Heba Ashraf*/
