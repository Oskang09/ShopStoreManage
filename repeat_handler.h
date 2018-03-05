float askFloat(char* askmsg, char* wronginputmsg, char* scanformat)
{
	float f;
	printf(askmsg);
	fflush(stdin);
	scanf(scanformat, &f);
	if (f + 1.0 == 1.0f)
	{
		printf(wronginputmsg);
		return askFloat(askmsg, wronginputmsg, scanformat);
	}
	return f;
}

int askInteger(char* askmsg, char* wronginputmsg, char* scanformat)
{
	int i;
	printf(askmsg);
	fflush(stdin);
	scanf(scanformat, &i);
	if (i == 0)
	{
		printf(wronginputmsg);
		return askInteger(askmsg, wronginputmsg, scanformat);
	}
	return i;
}

int askIntegerBetween(char* askmsg, char* wronginputmsg, char* scanformat, int from, int to)
{
	int i = askInteger(askmsg, wronginputmsg, scanformat);
	if (i < from || i > to)
	{
		printf(wronginputmsg);
		askIntegerBetween(askmsg, wronginputmsg,  scanformat, from, to);
	}
	return i;
}
