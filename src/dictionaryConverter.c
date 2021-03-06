#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUM    6
#define STR_LENG   255
char pronounce_list[MAX_NUM][STR_LENG] = {0};

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

int check_blank_words(char* pstr)
{
	if (pstr[0] == '\r' || pstr[0] == '\n' || pstr[0] == '\v' || pstr[0] == '\t')
		return true;
	else
		return false;
}

void remove_blank_words_end(char* pstr, char* renew)
{
	int len = strlen(pstr);
	memset(renew, 0, STR_LENG);
	while(len-1 >= 0){
		if(pstr[len-1] == ' ')
			len--;
		else
			break;
	}
	memcpy(renew, pstr, len);
}

int check_header_words(char* pstr)
{
	if(strstr(pstr, "[SubHeader]") || strstr(pstr, "Content=") || strstr(pstr, "Representation=") )
		return true;
	else
		return false; 
}

void initialize_pronounce_list()
{
	int i=0;
	for(i=0; i<MAX_NUM; i++)
		memset(pronounce_list[i], 0, STR_LENG);
}

bool duplicate_check(char *str, int cnt)
{
	int i=0;
	for(i=0; i<cnt; i++)
	{
		if(!strcmp(pronounce_list[i], str))
			return true;
	}
	return false;
}

int main( int argc, char *argv[] )
{ 
	FILE *fp1, *fp2;
	char pstr[STR_LENG];
	char word[STR_LENG];
	char *st = NULL;
	int splitNumber = 1;
	int atoiChar;
	int flag = 0, startFlag = 0;
	int cnt = 0;

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
			if(check_blank_words(pstr) == true || check_header_words(pstr) == true)
				continue;

			pstr[strlen(pstr)-2] = '\0';
			st = strtok(pstr, "//");
			atoiChar = atoi(pstr);
			if(atoiChar == splitNumber) // split number check
			{
				flag = 0; // check same word
				cnt = 0;
				initialize_pronounce_list();
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
					remove_blank_words_end(st,word);
					printf("st:%s! word:%s!\n",st,word);
					fprintf(fp2, "%s ", word);
	
					st = strtok(NULL, "//");
					remove_blank_words_end(st,word);
					strncpy(pronounce_list[cnt++], word, strlen(word));
					fprintf(fp2, "\"%s\"", word);
					
					flag = 1;
				}
				else if(flag == 1)
				{
					st = strtok(NULL, "//");
					remove_blank_words_end(st,word);
					if(!duplicate_check(word, cnt))
					{
						strncpy(pronounce_list[cnt++], word, strlen(word));
						fprintf(fp2, "\n| \"%s\"", word);
					}
				}
			}
			else
			{
				while(st != NULL)
				{
					fprintf(fp2, "%s\n", st);
					st = strtok(NULL, "//");
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
