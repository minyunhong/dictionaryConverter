#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *strlwr(char *str){
	unsigned char *p = (unsigned char*)str;
	while(*p){
		*p = tolower((unsigned char)*p);
		p++;
	}
	return str;
}

int main( int argc, char *argv[] ){ 
	FILE *fp1, *fp2;
	char pstr[100];
	char strPron[] = "!pronounce ";
	char *st = NULL;
	int splitNumber = 1;
	int atoiChar;
	int flag = 0, startFlag = 0;

	if(!strcmp(argv[1],"output.dct"))
	{
		printf("output.txt open!!\n");
		fp1 = fopen("output.dct", "r");
		fp2 = fopen("output2.dct", "w");

		if(fp1 == NULL || fp2 == NULL){
			printf("file open error\n");
			return 1;
		}

		while(1)
		{
			if(feof(fp1)!=0){
				printf("file ended\n");
				break;
			}
			fgets(pstr,sizeof(pstr),fp1);
			pstr[strlen(pstr)-2] = '\0';
			st = strtok(pstr, "  //");
			atoiChar = atoi(pstr);

			if(atoiChar == splitNumber) // split number check
			{
				printf("splitNumber %d,startFlag %d flag %d\n", splitNumber, startFlag, flag);
				flag = 0; // check same word
				if(atoiChar == 1)// [data] start check
				{
					printf("start!\n");
					startFlag = 1;
				}
				strcpy(pstr,strPron);
				
				//!pronounce print option
				if(splitNumber == 1) fprintf(fp2, "%s", pstr);
				else	 			 fprintf(fp2, ";\n%s", pstr);
				splitNumber++;
			}
			else if(startFlag == 1)
			{
				if(flag == 0)
				{
					while(st != NULL)
					{
						fprintf(fp2, "\"%s\" ", st);
						st = strtok(NULL, "  //");
					}
					flag = 1;
				}
				else if(flag == 1)
				{
					st = strtok(NULL, "  //");
					fprintf(fp2, "\n|\"%s\"", st);
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
		printf("output2.dct file created\n");

	}// end of output.txt
	else
	{
		fp1 = fopen(argv[1], "r");
		fp2 = fopen("output.dct", "w");

		if(fp1 == NULL || fp2 == NULL){
			printf("file open error\n");
			return 1;
		}

		fprintf(fp2, "[Header]\n");
		fprintf(fp2, "Language=%s\n\n", argv[2]);
		fprintf(fp2, "[SubHeader]\n");
		fprintf(fp2, "Content=UNDEFINED\nRepresentation=EDCT_REPR_SZ_STRING\n\n");
		fprintf(fp2, "[Data]\n");

		int i=1;
		fprintf(fp2, "%d\n", i++);
		while(1){
			if(feof(fp1)!=0){
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
			fprintf(fp2, "%d\n",i++ );
		}

		fclose(fp1);
		fclose(fp2);
		printf("output.dct file created\n");

	}//end of input.txt
	return 0;
}
