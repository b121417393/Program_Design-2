#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void removed(char a[], char b[], int N){
	int i, j;

	for (i = 0; i < N - 1; i++){
		if (a[i] == ' ')
			continue;
		else
			break;
	}

	for (j = 0; i < N - 1; i++, j++)
		if (a[i] == ' ')
			if (a[i - 1] == ' ')
				j--;
			else
				b[j] = a[i];
		else
			b[j] = a[i];

	if (b[j - 1] == ' '){
		b[j - 1] = '\n';
		b[j] = '\0';
	}
	else{
		b[j] = '\n';
		b[j + 1] = '\0';
	}
}

int main(int argc, char *argv[]){

	char *spat = {0}, *tpat = {0}, *temp = {0};
	char str[1024][1024] = {{0}}, newstr[1024][1024] = {{0}};
	int i = 0, count = 0, j = 1, len = 0;
	int substitute = 0, lower = 0, remove = 0;

	while (fgets(str[i], 1024, stdin) != NULL){
		i++;
		count++;
	}

	while (j < argc){

		if (strcmp(argv[j], "-s") == 0){
			substitute = 1;
			j++;
		}

		else if (strcmp(argv[j], "-l") == 0){
			lower = 1;
			j++;
		}

		else if (strcmp(argv[j], "-r") == 0){
			remove = 1;
			j++;
		}

		else{
			spat = argv[j];
			tpat = argv[j + 1];
			j += 2;
		}
	}

	if (remove == 1){
		for (i = 0; i < count; i++){
			removed(str[i], newstr[i], strlen(str[i]));
			strcpy(str[i], newstr[i]);
			memset(newstr[i], 0, 1024);
		}
	}

	if (substitute == 1){
		for (i = 0; i < count; i++){
			if ((temp = strstr(str[i], spat)) != NULL){
				for (j = 0; (temp = strstr(str[i] + j, spat)) != NULL; j++){
					if (str[i] + j == temp){
						strcat(newstr[i], tpat);
						j += strlen(spat) - 1;
					}
					else
						newstr[i][j] = str[i][j];
				}
				strcat(newstr[i], str[i] + j);
			}
			else
				strcpy(newstr[i], str[i]);
		}

		for (i = 0; i < count; i++){
			strcpy(str[i], newstr[i]);
			memset(newstr[i], 0, 1024);
		}
	}

	if (lower == 1){
		for (i = 0; i < count; i++){
			len = strlen(str[i]);
			for (j = 0; j < len; j++)
				newstr[i][j] = tolower(str[i][j]);
			newstr[i][j] = '\0';
		}

		for (i = 0; i < count; i++){
			strcpy(str[i], newstr[i]);
			memset(newstr[i], 0, 1024);
		}
	}

	for (i = 0; i < count; i++)
		printf("%s", str[i]);

	return 0;
}
