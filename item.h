// ITEM STRUCTURE
struct ITEM
{
	float price;
	char code[10];
	char name[50];
	int quantity;
};

// GET METHOD ( FSCAN & FGETS & FSEEK ) :: void
void itemGetQuery(char *code, char *name, float *price) 
{
	fseek(fobj, 19, SEEK_CUR);
	fgets(code, 10, fobj);
	fseek(fobj, 5, SEEK_CUR);
	fgets(name, 50, fobj);
	fscanf(fobj, "price=%f\n", price);
	strtok(name, "\n");
	strtok(code, "\n");
}

// STRING FOR Saving Format :: CHAR*
char* itemPostQuery() { return "STRUCT(ITEM)\ncode=%s\nname=%s\nprice=%.2f\n"; }

// CONSTRUCTOR METHOD ( CREATE STRUCTURE WITH PARAMETERS) :: void
//  PARAMETERS =>
//   struct ITEM *item = the struct variables we want to assign to
//   char* code = code of ITEM ( PRIMARY KEY & NON REPEATABLE )
//   char* name = name of ITEM
//   float price = per price of ITEM
//   int quantity = the quantity of ITEM
// 	END PARAMETERS
void createItem(struct ITEM *item, char* code, char* name, float price, int quantity)
{
	strcpy(item->code, code);
	strcpy(item->name, name);
	item->price = price;
	item->quantity = quantity;
}

// GETTER ( STRUCTURE FROM FILESYSTEM WITH SPECIFY CODE ) :: void 
//  PARAMETERS =>
//   struct ITEM *item = the struct variables we want to assign to
//   char* pcode = the code that at already save at filesystem
//   int quantity = the quantity when get the item ( always be 1 if no other use. ) [ Also for initalize quantity only ]
// End PARAMETERS
void getItemFromFile(struct ITEM *item, char* pcode, int quantity)
{
	char code[10];
	char name[50];
	float price;
	
	fobj = fopen("fs\\items.txt", "r");
	while (!feof(fobj))
	{
		itemGetQuery(code, name, &price);
		if (strcmp(code, pcode) == 0)
		{
			strcpy(item->code, code);
			item->price = price;
			strcpy(item->name, name);
			item->quantity = quantity;
			break;
		}
	}
	fclose(fobj);
}

// CHECK METHOD ( CHECK STRUCTURE EXISTS IN FILE ) :: boolean (int)
//  PARAMETERS =>
//   char* pcode = the code that need to check exists in file or not
// END PARAMETERS
int checkCodeExists(char* pcode)
{
	char code[10];
	char name[50];
	float price;
	int boolean = false;
	fobj = fopen("fs\\items.txt", "r");
	while (!feof(fobj))
	{
		itemGetQuery(code, name, &price);
		if (strcmp(code, pcode) == 0)
		{
			boolean = true;
			break;
		}
	}
	fclose(fobj);
	return boolean;
}        
                                                                       
// SAVE METHOD ( SAVE STRUCTURE TO FILE ) :: void
//  PARAMETERS =>
//   struct item it = that structure want to save to filesystem
// 	END PARAMETERS                                                     
void saveItem(struct ITEM it)                                                   
{                                                                               
	fobj = fopen("fs\\items.txt", "a+");                                  
	fprintf(fobj, itemPostQuery(), it.code, it.name, it.price);           
	fclose(fobj);                                                               
}                 
                                                              
// DISPLAY METHOD ( DISPLAY ITEMS THAT IN STOCK ) :: void                                             
void displayStock()                                                             
{   
	fobj = fopen("fs\\items.txt", "r");
	char code[10];
	char name[50];
	float price;
	printf("\n###################### STOCKS #########################");             
	printf("\n#     CODE     #        NAME        #      PRICE      #");
	printf("\n#######################################################");              
	while (!feof(fobj))
	{
		itemGetQuery(code, name, &price);
		printf("\n#%*s%*s", 7 + strlen(code) / 2, code, 7 - strlen(code) / 2, " ");
		printf("#%*s%*s", 10 + strlen(name) / 2, name, 10 - strlen(name) / 2, " ");
		printf("#%12.2f%s#", price, "     ");
	} 
	printf("\n#######################################################\n");              
	fclose(fobj); 
}
