#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* f;
int l_string;

//#define CARATTERI "0123456789"
#define CARATTERI "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 /*-+\\|!""£$%&/()='ל?^ט+י*עאשח°§,.-;:_<>@#[]€{}"

#define string_length(str) (str == NULL) ? 0 : strlen(str)

/*int lunghezza_stringa(char * str) {
	return (str == NULL) ? 0 : strlen(str);
}*/

void func(int num, char* prefix) {
	int len_prefix = string_length(prefix);
	if (num != 1) {
		for (int i = 0; i < l_string; i++) {
			char* new_base;
			int j;
			new_base = (char*)malloc(sizeof(char)*len_prefix + 2);
			for (j = 0; j < len_prefix; j++) {
				new_base[j] = prefix[j];
			}
			new_base[j] = CARATTERI[i];
			new_base[j + 1] = '\0';
			func(num - 1, new_base);
			free(new_base);
		}
		return;
	}
	//if (num != 1) return;
	for (int i = 0; i < l_string; i++) {
		/*if (l_base <= 0)
		{
			fprintf(f, "%c\n", CARATTERI[i]);
		}
		else {
			fprintf(f, "%s%c\n", base, CARATTERI[i]);
		}*/
		(len_prefix <= 0) ? fprintf(f, "%c\n", CARATTERI[i]) : fprintf(f, "%s%c\n", prefix, CARATTERI[i]);
	}
}

/*
* /start     NUMBER
* /end       NUMBER
* /prefix    STRING
* /file 	 STRING
* /append    
* /h         Shows the help
* /help      Shows the help
*/
int main(int argc, char *argv[]) {

	char *str_file = NULL;
	char * prefix = NULL;
	int start = 1;
	int end = -2;
	char mode[] = "w"; // w/a   write/append

	

	if (argc > 1) {
		int i;
		for (i = 1; i < argc; i+=2) {
			if ((strcmp(argv[i], "/h") == 0) || (strcmp(argv[i], "/help") == 0)) {
				printf("/start NUMBER\tStart chars number.\n");
				printf("/end NUMBER\tEnd chars number. (-1 for endless)\n");
				printf("/prefix NUMBER\tString prefix.\n");
				printf("/file STRING\tFile name.\n");
				printf("/append NUMBER\tIt will append in the file (file needed).\n");
				return 0;
			}
			if (strcmp(argv[i], "/start") == 0) {
				sscanf(argv[i+1], "%d", &start);
			}
			else if (strcmp(argv[i], "/end") == 0) {
				sscanf(argv[i+1], "%d", &end);
			}
			else if (strcmp(argv[i], "/prefix") == 0) {
				prefix = argv[i+1];
				//prefix = (char*)malloc(sizeof(char) * strlen(argv[i+1]) + 1);
				//strcpy(prefix, argv[i+1]);
			}
			else if (strcmp(argv[i], "/file") == 0) {
				str_file = argv[i+1];
			}
			else if (strcmp(argv[i], "/append") == 0) {
				mode[0] = 'a';
			}
		}

	}
	
	if (end == -2) {
		puts("How long will be the dictionary? ");
		scanf("%d", &end);
	}
	
	if (strcmp(mode, "a") == 0 && str_file != NULL)
		puts("Append mode ON.");

	if (str_file != NULL)
		f = fopen(str_file, (char*)mode);
	else
		f = stdout;

	l_string = string_length((char*)CARATTERI);
	
	for (int i = start; (i <= end) || (end == -1); i++) {
		if (f != stdout)
			printf("\nExecuting with %d chars.\n", i);
		func(i, prefix);
	}

	/*if (prefix != NULL) 
		free(prefix);*/
	
	fclose(f);

	printf("\n");
	return 0;
}

