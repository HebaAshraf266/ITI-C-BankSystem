/*Heba Ashraf*/

#include <stdio.h>

typedef struct Node {
	char Name[60];
	int National_ID;
	int Age;
	char Address[60];	
	char Guardian[60];
	int GuardianNationalId;
	long long Balance;
	char AccountStatus[10];
	///generated automatically
	char Password[9];
	long long  BankAccountId;
	struct Node *pnext;
}tNode;


char* randomPasswordGeneration();
tNode* CreateAccount();
void OpenExistingAccout();
void MakeTransaction ( tNode *sendingcurrent );
tNode* CheckUser(long long ID);
void PrintList();
void ChangeAccountStatus(tNode *sendingcurrent);
void GetCash (tNode *sendingcurrent);
void Deposite ( tNode *sendingcurrent );
void ClientWindow();
void changePassword ( tNode *current );
void ReturnToMenu ();

/*Heba Ashraf*/
