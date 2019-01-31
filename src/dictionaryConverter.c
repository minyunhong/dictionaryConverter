#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *strlwr(char *str)
{
	unsigned char *p = (unsigned char*)str;
	while(*p)
	{
		*p = tolower((unsigned char)*p);
		p++;
	}
	return str;
}

int main( int argc, char *argv[] )
{ 
	FILE *fp1, *fp2;
	char pstr[100];
	char *st = NULL;
	int splitNumber = 1;
	int atoiChar;
	int flag = 0, startFlag = 0;

	if(!strcmp(argv[1],"output.dct"))
	{
		printf("output.dct open!!\n");
		fp1 = fopen("output.dct", "r");
		fp2 = fopen("final.dct", "w");

		if(fp1 == NULL || fp2 == NULL)
		{
			printf("file open error\n");
			return 1;
		}

		while(1)
		{
			if(feof(fp1)!=0)
			{
				printf("file ended\n");
				break;
			}
			fgets(pstr,sizeof(pstr),fp1);
			pstr[strlen(pstr)-2] = '\0';
			st = strtok(pstr, "  //");
			atoiChar = atoi(pstr);

			if(atoiChar == splitNumber) // split number check
			{
				flag = 0; // check same word
				if(atoiChar == 1)// [data] start check
					startFlag = 1;

				strcpy(pstr, "!pronounce ");
				//!pronounce print option
				if(splitNumber == 1)
					fprintf(fp2, "%s", pstr);
				else
					fprintf(fp2, ";\n%s", pstr);
				splitNumber++;
			}
			else if(startFlag == 1)
			{
				if(flag == 0)
				{
					fprintf(fp2, "%s ", st);
					st = strtok(NULL, "  //");
					fprintf(fp2, "\"%s\"", st);
					
					flag = 1;
				}
				else if(flag == 1)
				{
					st = strtok(NULL, "  //");
					fprintf(fp2, "\n| \"%s\"", st);
				}
			}
			else
			{
				while(st != NULL)
				{
					fprintf(fp2, "%s\n", st);
					st = strtok(NULL, "  //");
				}
			}
		}

		splitNumber = 0;
		fclose(fp1);
		fclose(fp2);
		printf("final.dct file created\n");
	}
	else
	{
		int idx = 1;
		fp1 = fopen(argv[1], "r");
		fp2 = fopen("output.dct", "w");

		if(fp1 == NULL || fp2 == NULL)
		{
			printf("file open error\n");
			return 1;
		}

		fprintf(fp2, "[Header]\n");
		fprintf(fp2, "Language=%s\n\n", argv[2]);
		fprintf(fp2, "[SubHeader]\n");
		fprintf(fp2, "Content=UNDEFINED\nRepresentation=EDCT_REPR_SZ_STRING\n\n");
		fprintf(fp2, "[Data]\n");
		fprintf(fp2, "%d\n", idx++);

		while(1)
		{
			if(feof(fp1)!=0)
			{
				printf("file ended\n");
				break;
			}
			fgets(pstr, sizeof(pstr), fp1);

			pstr[strlen(pstr)-2] = '\0';
			st = strtok(pstr, "\t");
			while(st)
			{
				fprintf(fp2, "%s\n", strlwr(st));
				st = strtok(NULL, "\t");
			}
			fprintf(fp2, "%d\n", idx++);
		}

		fclose(fp1);
		fclose(fp2);
		printf("output.dct file created\n");

	}

	return 0;
}
