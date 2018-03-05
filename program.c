#include "init.h"
#include "repeat_handler.h"
#include "item.h"
#include "receipt.h"

int askOption()
{
	int option;
	printf("\n#- #- #- Option Selection -# -# -#");
	printf("\nSelect your option ( 1- 5 ) :");
	printf("\n	1. Create Item");
	printf("\n	2. Shoppy");
	printf("\n	3. View Receipt History");
	printf("\n	4. View List Item");
	printf("\n	5. Quit Program");
	
	option = askIntegerBetween("\nInput your selection : ", "Invalid selection!", "%d", 1, 5);
	switch (option)
	{
		//#DECLARE
		// opt1 
		char name[50], opt1 = ' ', code[10];
		float price;
		struct ITEM it;
		// opt2
		char buyer[50], rcp_id[5], opt2[10];
		int struct_size = 0, q;
		struct ITEM *items, item;
		float total_price = 0;
		// opt3
		char opt3;
		//#ENDDECLARE
		case 5:
			printf("\n#PROGRAM : Welcome next time use ~ ~ :D ");
			return 0;
		case 4:
			displayStock();
			return 4;
		case 3:
			do
			{
				char pcode[10];
				struct RECEIPT rcp;
				for (;;)
				{
					printf("\n#- #- #- View Receipt -# -# -#\n");
					fflush(stdin);
					printf("Input Receipt's ID (S to Stop) : ");
					gets(pcode);
					if (strcmp(pcode, "S") == 0 || strcmp(pcode, "s") == 0)
					{
						goto ENDRCP;
					}
					if (checkReceiptIDExists(pcode) == true)
					{
						printReceiptHistory(pcode);
						break;
					}
					else
					{
						printf("\nReceipt ID #%s doesn't exists!", pcode);
					}
				}
				ENDRCP:
				printf("\nDo you want view another receipt? [Y to Continue] : ");
				fflush(stdin);
				scanf("%c", &opt3);
			}
			while (opt3 == 'Y' || opt3 == 'y');
			return 3;
		case 2:
			printf("\n#- #- #- #- #- Shoppy -# -# -# -# -#\n");
			printf("Input customer's name : ");
			fflush(stdin);
			gets(buyer);
			
			for (;;)
			{	
				displayStock();
				displayRCP(buyer, struct_size, items, total_price);
				printf("\nInput item's code (S to STOP): ");
				fflush(stdin);
				gets(opt2);
				if (strcmp(opt2, "s") == 0 || strcmp(opt2 , "S") == 0)
				{
					goto ENDLOOP;
				}
				
				while (checkCodeExists(opt2) == false)
				{
					printf("Item not exists!\n");
					fflush(stdin);
					printf("Input item's code (S to STOP): ");
					gets(opt2);
					if (strcmp(opt2, "s") == 0 || strcmp(opt2 , "S") == 0)
					{
						goto ENDLOOP;
					}
				}
				
				q = askInteger("Input item's quantity : ", "Please input a correct number (etc 1, 2)\n", "%d");
				
				getItemFromFile(&item, opt2, q);
				total_price += item.price * item.quantity;
				items[struct_size] = item;
				struct_size += 1;
				items = realloc(items, sizeof(struct ITEM) * sizeof(struct_size));
			}
			ENDLOOP:
			for (;;)
			{
				fflush(stdin);
				printf("Input receipt's id : ");
				gets(rcp_id);
				if (checkReceiptIDExists(rcp_id) == false)
				{
					break;
				}
				printf("\nReceipt ID #%s already exists!\n", rcp_id);
			}
			saveReceipt(rcp_id, buyer, total_price, struct_size, items);
			return 2;
		case 1:
			do
			{
				printf("\n#- #- #- #- Create Item -# -# -# -#");
				fflush(stdin);
				printf("\nInput your item's code : ");
				gets(code);
				
				if (checkCodeExists(code) == false)
				{
					fflush(stdin);
					printf("Input your item's name : ");
					gets(name);
					
					price = askFloat(("Input your item's price : RM "), "\nPlease input a correct price ( etc : 15 or 1.5 )\n", "%f");
					printf("#PROGRAM: Created New Item\n ITEM #%s\n CODE #%s\n PRICE #%.2f", code , name ,price);
					printf("\n#- #- #- END CREATE Item -# -# -#");
					createItem(&it, code, name, price, 1);
					saveItem(it);
					opt1 = 'N';
				}
				else
				{
					printf("Code #%s has already exists in inventory!", code);
					opt1 = 'Y';
				}
				
				if (opt1 != 'Y' && opt1 != 'y')
				{
					printf("\n#PROGRAM : Do you want to continue create item? [Y/N] : ");
					fflush(stdin);
					scanf("%c", &opt1);
				}
			}
			while (opt1 == 'Y' || opt1 == 'y');
			return 1;
	}
}

int main()
{
	checkFileExists();
	char c;
	printf("\n#PROGRAM : Welcome to the shoppy program.");
	do
	{
		if (askOption() == 0)
		{
			break;
		}
		printf("\n#PROGRAM : Do you want continue to program? [Y to Continue] : ");
		fflush(stdin);
		scanf("%c", &c);
	}
	while (c == 'Y' || c == 'y');
	return 0;
}
