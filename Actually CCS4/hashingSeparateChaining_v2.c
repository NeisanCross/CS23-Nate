/*
	The is a modified version of the hashingSeparateChaining program. In this program, insert_Data(), search_Data(),
	and delete_Data() functions do not have the entire hash table as parameter but only the row from the hash table
	whose index corresponds to the calculated index from the hash function. That is why when the actual parameter is an 
	indexed array because only one row is passed as parameter. Since passing a single row is passed by value, the 
	actual parameter of insert_Data() and delete_Data() functions has the address operator (&) and the corresponding
	formal parameter has the indirection operator (*).
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define S 5
#define K 7
#define LH 10
#define FLUSH while (getchar() != '\n')

typedef struct
{
	char personId[S]; // key
	char personName[30];
}PERSON;

typedef struct node *nd;
struct node
{
	PERSON person;
	nd prev;
	nd next;
}NODE;

typedef struct
{
	nd right;    
}TABLE;

void init_Table(TABLE []);
int convertString_Option3(char []);
bool insert_Data(TABLE *, PERSON ) ;
int hash_Truncation(int);
PERSON input_Data(void);
void input_Search_Key(char []);
nd search_Data(TABLE, char []);
void display_Data(nd);
void delete_Data(TABLE *, nd *);
void display_All_Data(TABLE []);

int main(void)
{
	int choice, key, index;
	bool found, inserted;
	char chrKey[S];
	PERSON per;
	TABLE hashTable[LH];
	nd ptr;
	
	init_Table(hashTable);
	do{
		system("cls");
		printf("\t1] Add new data\n");
		printf("\t2] Search a data\n");
		printf("\t3] Delete a data\n");
		printf("\t4] List all data\n");
		printf("\t5] Exit\n\n");
		printf("\tChoice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:	per = input_Data();
					key = convertString_Option3(per.personId);
					index = hash_Truncation(key); 
					inserted = insert_Data(&hashTable[index],per);
					if(inserted)
						printf("\n\n\tData was successfully inserted...");
					else
						printf("\n\n\tError: system failed to insert the data...");
						getch();
					break;
			case 2: input_Search_Key(chrKey);
					key = convertString_Option3(chrKey);
					index = hash_Truncation(key);
					ptr = search_Data(hashTable[index], chrKey);
					if(ptr != NULL)
						display_Data(ptr);
					else
						{
							printf("\n\n\tError: Data not found...");
							getch();
						}
					break;
			case 3: input_Search_Key(chrKey);
					key = convertString_Option3(chrKey);
					index = hash_Truncation(key);
					ptr = search_Data(hashTable[index], chrKey);
					if (ptr != NULL)
						delete_Data(&hashTable[index], &ptr);
					else
					{
						printf("\n\n\tError: Data not found...");
						getch();
					}
					break;
			case 4: display_All_Data(hashTable); 
					break;
			case 5: printf("\n\n\tThis program will close in 5 seconds...");
					sleep(5);
					break;
			default:printf("\n\tInvalid choice...\n\tTry again...");
					sleep(2);
		}
	}while (choice != 5);
}

PERSON input_Data(void)
{
	PERSON p;
	
	FLUSH;
	printf("\n\n\tIdentification: ");
	gets(p.personId);
	printf("\n\tName: ");
	gets(p.personName);
	return p;
}

void input_Search_Key(char chrKey[])
{
	FLUSH;
	printf("\n\n\tInput search value: ");
	gets(chrKey);
	return;
}

void init_Table(TABLE hashTable[])
{
	int j;
	
	for(j = 0; j < LH;j++)
	{
		hashTable[j].right = NULL;
	}
		
	return;
}

int convertString_Option3(char chrKey[])
{
	int L, key = 0, i;
	
	L = strlen(chrKey);
	
	for(i = 0;i < L; i++)
	{
		key = key + (chrKey[L - i - 1] * pow(K,i));
	}
	return key;
}

int hash_Truncation(int key)
{
	int index;
	
	index = key % 10; // extract the last  digit (single digit index)
	return index;
}

bool insert_Data(TABLE *hash, PERSON per)
{
	bool inserted = false;
	nd temp = malloc(sizeof(NODE));
	temp->person = per;
	temp->next = NULL;
		
	if (hash->right != NULL)
	{
		temp->next = hash->right;
		hash->right->prev = temp;
	}
		
	hash->right = temp;
	inserted = true;
	return inserted;
}


nd search_Data(TABLE hash, char chrKey[]) //search_Data(hashTable, chrKey, index)
{
	int comp;
	nd ptr = hash.right;
	
	while(ptr != NULL)
	{
		comp = strcmp(chrKey,ptr->person.personId);
		if(comp == 0)
			break;
		ptr = ptr->next;
		
	}
	return ptr;
}

void display_Data(nd ptr)
{
	system("cls");
	printf("\n\n\tIdentification: %s",ptr->person.personId);
	printf("\n\tName: %s",ptr->person.personName);
	getch();
	return;
}

void delete_Data(TABLE *hash, nd *ptr)
{
	char ans;
	
	display_Data(*ptr); // display the data for visual validation by the user
	printf("\n\n\tDo you want to proceed deleting the data (Y/N)?");
	scanf(" %c",&ans);
	if(toupper(ans) == 'Y')
	{
		if(*ptr == hash->right)
			hash->right = (*ptr)->next;
		else
		{
			(*ptr)->prev->next = (*ptr)->next;
			if ((*ptr)->next != NULL)
				(*ptr)->next->prev = (*ptr)->prev;
		}	
		free(*ptr);
	}	
	else
	{
		printf("\n\n\tData is not delted, press any key to return to main...");
		getch();
	}
	return;
} 

void display_All_Data(TABLE hashTable[])
{
	int j;
	nd ptr;
	system("cls");
	printf("\n\n\tindex\tIdentification\tName");
	for(j = 0; j < LH; j++)
	{
		ptr = hashTable[j].right;
		printf("\n\t%d",j);
		while(ptr != NULL)
		{
			printf("\t%s\t%s\n",ptr->person.personId,ptr->person.personName);
			ptr = ptr->next;
		}
	}
	getch();
	return;
}
