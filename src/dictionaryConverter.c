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
	
	if(!strcmp(argv[1],"dct")){
		fp1 = fopen("output.dct", "r");
		fp2 = fopen("output2.dct", "w");

		if(fp1 == NULL || fp2 == NULL){
			printf("file open error\n");
			return 1;
		}
			
		while(1){
                        if(feof(fp1)!=0){
                                printf("file ended\n");
                                break;
                        }

			fgets(pstr, 100, fp1);
			if(!strcmp(pstr, "0\n")){
				printf("start\n");
			}	
		}
	}
	else{
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
	
		int i=0;
		fprintf(fp2, "%d\n", i++);
		while(1){
			if(feof(fp1)!=0){
				printf("file ended\n");
				break;
			}
			fgets(pstr, 100, fp1);
		
			char *st = NULL;
			st = strtok(pstr, "\t");
			while(st)
			{
				printf("st:%s\n",st);
				fprintf(fp2, "%s\n", strlwr(st));
				st = strtok(NULL, "\t");
			}
			fprintf(fp2, "%d\n",i++ );
		}
		
		fclose(fp1);
		fclose(fp2);
		printf("output.dct file created\n");
	
		return 0;
	}
}
