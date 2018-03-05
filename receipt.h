// RECEIPT STRUCTURE WITH FLEXIBLE ARRAY MEMBER
struct RECEIPT
{
	char receipt_id[10];
	char buyer[50];
	float total_price;
	int struct_size;
	struct ITEM items[];
};

// GET METHOD ( FSCAN & FGETS & FSEEK ) :: void
void receiptGetQuery(char *rcp_id, char *buyer, float *tp, int *sz)
{
	fseek(fobj, 24, SEEK_CUR);
	fgets(rcp_id, 10, fobj);
	fseek(fobj, 6, SEEK_CUR);
	fgets(buyer, 50, fobj);
	fscanf(fobj, "total_price=%f\nstruct_size=%d\n", tp, sz);
	strtok(rcp_id, "\n");
	strtok(buyer, "\n");
}
void nestedItemGetQuery(char *code, char *name, float *p, int *q)
{
	fseek(fobj, 26, SEEK_CUR);
	fgets(code, 10, fobj);
	fseek(fobj, 5, SEEK_CUR);
	fgets(name, 50, fobj);
	fscanf(fobj, "price=%f\nquantity=%d\n", p, q);
	strtok(code, "\n");
	strtok(name, "\n");
}

// STRING FOR Saving Format :: CHAR*
char* receiptPostQuery() { return "STRUCT(RECEIPT)\nrcp_id=%s\nbuyer=%s\ntotal_price=%.2f\nstruct_size=%d\n"; }
char* nestedItemPostQuery() { return "NESTED_STRUCT(ITEM)\ncode=%s\nname=%s\nprice=%.2f\nquantity=%d\n"; }

// CHECK METHOD ( CHECK STRUCTURE EXISTS IN FILE ) :: boolean (int)
//  PARAMETERS =>
//   char pcode[5] = the code that need to check exists in file or not
// END PARAMETERS
int checkReceiptIDExists(char pcode[10])
{
	char rcp_id[10], buyer[50];
	float tp;
	int struct_size = 0, boolean = false;
	struct ITEM items[struct_size];
	struct ITEM item;
	
	fobj = fopen("fs\\receipt.txt", "r");
	while (!feof(fobj))
	{
		receiptGetQuery(rcp_id, buyer, &tp, &struct_size);
		if (strcmp(pcode, rcp_id) == true)
		{
			boolean = true;
			break;
		}
		
		int i;
		char code[10];
		char name[50];
		float price;
		int q;
		for (i = 0; i < struct_size; i++)
		{
			nestedItemGetQuery(code, name, &price, &q);
			createItem(&item, code, name, price, q);
			items[i] = item;
		}
	}
	fclose(fobj);
	return boolean;
}

// SAVE METHOD ( SAVE STRUCTURE TO FILE ) :: void
//  PARAMETERS =>
//   char* rcp_id = receipt id that want to save
//   char* buyer = buyer's name that want to save
//   float total_price = the price want to save ( calculated )
//   int struct_size = struct size for flexible array member ( Item's structure )
//   struct ITEM items[struct_size] = array of the items that want to save
// 	END PARAMETERS
void saveReceipt(char* rcp_id, char* buyer, float total_price, int struct_size, struct ITEM items[struct_size])
{
	fobj = fopen("fs\\receipt.txt", "a+");
	fprintf(fobj, receiptPostQuery(), rcp_id, buyer, total_price, struct_size);
	int i;
	for (i = 0; i < struct_size; i++)
	{
		fprintf(fobj, nestedItemPostQuery(), items[i].code, items[i].name, items[i].price, items[i].quantity);
	}
	fclose(fobj);
}

// DISPLAY METHOD ( DISPLAY ITEMS THAT USER HAVE BOUGHT AND TOTAL_PRICE ) :: void
//  PARAMETERS =>
//   char* buyer = buyer's name for display
//   int struct_size = struct size for flexible array member ( Item's structure )
//   struct ITEM items[struct_size] = array of the items that want to user bought
//   float total_price = the price to display ( calculated )
// 	END PARAMETERS
void displayRCP(char* buyer, int struct_size, struct ITEM *items, float total_price)
{
	printf("\n #- #- #- #- #- #- #- RECEIPT -# -# -# -# -# -# -#");
	printf("\n Customer : %s", buyer);
	
	int i;
	for (i=0;i<struct_size;i++)
	{
		printf("\n Items #%d :", i + 1);
		printf("\n     Code : %s", items[i].code);
		printf("\n     Name : %s", items[i].name);
		printf("\n     Price : %.2f", items[i].price);
		printf("\n     Quantity : %d", items[i].quantity);
	}
	printf("\n Total_Price : %.2f", total_price);
	printf("\n #- #- #- #- #- #- END OF RECEIPT -# -# -# -# -# -#\n");
}

// DISPLAY METHOD ( PRINTF STRUCTURE FROM FILESYSTEM WITH SPECIFY RECEIPT ID ) :: void 
//  PARAMETERS =>
//   char pcode[5] = receipt id in filesystem ( fs/receipt.txt )
// End PARAMETERS
void printReceiptHistory(char pcode[10])
{	
	fobj = fopen("fs\\receipt.txt", "r");
	while (!feof(fobj))
	{
		char rcp_id[10];
		char buyer[50];
		float tp;
		int struct_size;
	
		char code[10];
		char name[50];
		float price;
		int q;
		
		receiptGetQuery(rcp_id, buyer, &tp, &struct_size);
		
		struct ITEM *items = malloc(sizeof(struct ITEM) * sizeof(struct_size));
		
		int i;
		for (i = 0; i < struct_size; i++)
		{
			struct ITEM item;
			nestedItemGetQuery(code, name, &price, &q);
			createItem(&item, code, name, price, q);
			items[i] = item;
		}
		
		if (strcmp(rcp_id, pcode) == true)
		{
			displayRCP(buyer, struct_size, items, tp);
			break;
		}
	}
	fclose(fobj);
}
