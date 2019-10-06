#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define MaxString 10000000

//The structure of the stored data
struct ramdomstring
{
	char content[7];
};
typedef struct ramdomstring Ramdomstring;

//-n compare function
int compare(char *string1, char *string2)
{

	int i = 0, len = 0;
	int a = -1, b = -1;

	//Find the first number and set it
	len = strlen(string1);
	for (i = 0; i < len; i++)
		if (string1[i] >= 48 && string1[i] <= 57)
		{
			a = atoi(string1 + i);
			break;
		}

	//Find the first number and set it
	len = strlen(string2);
	for (i = 0; i < len; i++)
		if (string2[i] >= 48 && string2[i] <= 57)
		{
			b = atoi(string2 + i);
			break;
		}

	//If string have number a,b>=0 , no number a,b=-1
	//return 1 if it need to exchange , return 0 doesn't exchange
	if (a == -1 && b == -1)
		if (strcmp(string1, string2) > 0)
			return 1;
		else
			return 0;

	else if (a == -1 && b != -1)
		return 0;

	else if (a != -1 && b == -1)
		return 1;

	else if (a != -1 && b != -1)
		if (a > b)
			return 1;
		else
			return 0;
	else
		printf("error\n");

	//Basically won't go here
	return -1;
}

//Generate random numbers 65~90 or 97~122 for ASCII(A~Z , a~z)
int randomnumber(void)
{

	int i = 0, j = 0;

	i = (rand() % 26) + 65;
	j = (rand() % 2);

	if (j == 0)
		return i;
	else
		return i + 32;
}

//Generate a random string of length 1~6
void string_generator(Ramdomstring *randomstring1, Ramdomstring *randomstring2, Ramdomstring *randomstring3)
{

	int i = 0, j = 0;
	int cnt = 0;
	srand(time(NULL));

	for (i = 0; i < MaxString; i++)
	{
		cnt = (rand() % 6 + 1);
		for (j = 0; j < cnt; j++)
			randomstring1[i].content[j] = randomnumber();
		randomstring1[i].content[j] = '\0';

		strcpy(randomstring2[i].content, randomstring1[i].content);
		strcpy(randomstring3[i].content, randomstring1[i].content);
	}
}

//Qsort's , Mergesort's , Heatsort's compare function
int autocompare(const void *string1, const void *string2)
{
	const Ramdomstring *temp1 = string1;
	const Ramdomstring *temp2 = string2;

	return strcmp(temp1->content, temp2->content);
}

//Main function
int main(int argc, char *argv[])
{

	//Reading data from a file or from stdin
	if (argc == 1 || strcmp(argv[1], "-n") == 0)
	{

		//Reading data from a file
		if (argc == 3)
		{
			FILE *fp;
			char input[2048][20] = {{0}};
			char temp[20];
			int i = 0, j = 0, count = 0;

			//Open file
			fp = fopen(argv[2], "r+");

			//Reading data
			while (fgets(input[i], 20, fp) != NULL)
			{
				if (input[i][strlen(input[i]) - 1] == '\n')
					input[i][strlen(input[i]) - 1] = '\0';
				i++, count++;
			}

			//bubble sort
			for (i = count - 1; i > 0; i--)
				for (j = 0; j < i; j++)
					if (compare(input[j], input[j + 1]) == 1)
					{
						strcpy(temp, input[j + 1]);
						strcpy(input[j + 1], input[j]);
						strcpy(input[j], temp);
					}

			for (i = 0; i < count; i++)
				printf("%s\n", input[i]);

			fclose(fp);
		}

		//Reading data from stdin
		else
		{

			char input[2048][20] = {{0}};
			char temp[20];
			int i = 0, j = 0, count = 0;

			//Reading data
			while (fgets(input[i], 20, stdin) != NULL)
			{
				if (input[i][strlen(input[i]) - 1] == '\n')
					input[i][strlen(input[i]) - 1] = '\0';
				i++, count++;
			}

			//bubble sort
			for (i = count - 1; i > 0; i--)
				for (j = 0; j < i; j++)
					if (compare(input[j], input[j + 1]) != 0)
					{
						strcpy(temp, input[j + 1]);
						strcpy(input[j + 1], input[j]);
						strcpy(input[j], temp);
					}

			for (i = 0; i < count; i++)
				printf("%s\n", input[i]);
		}
	}

	else if (strcmp(argv[1], "-a") == 0)
	{

		Ramdomstring *randomstring1 = malloc(MaxString * sizeof(randomstring1));
		Ramdomstring *randomstring2 = malloc(MaxString * sizeof(randomstring2));
		Ramdomstring *randomstring3 = malloc(MaxString * sizeof(randomstring3));

		//Generate three identical random strings
		string_generator(randomstring1, randomstring2, randomstring3);

		struct timeval qsort_start, qsort_end;
		struct timeval mergesort_start, mergesort_end;
		struct timeval heapsort_start, heapsort_end;
		unsigned long qsort_diff, mergesort_diff, heapsort_diff;

		//Calculation function execution time
		gettimeofday(&qsort_start, NULL);
		qsort(randomstring1, MaxString, sizeof(randomstring1[0]), autocompare);
		gettimeofday(&qsort_end, NULL);
		qsort_diff = 1000 * (qsort_end.tv_sec - qsort_start.tv_sec) + (qsort_end.tv_usec - qsort_start.tv_usec) / 1000;

		//Calculation function execution time
		gettimeofday(&mergesort_start, NULL);
		mergesort(randomstring2, MaxString, sizeof(randomstring2[0]), autocompare);
		gettimeofday(&mergesort_end, NULL);
		mergesort_diff = 1000 * (mergesort_end.tv_sec - mergesort_start.tv_sec) + (mergesort_end.tv_usec - mergesort_start.tv_usec) / 1000;

		//Calculation function execution time
		gettimeofday(&heapsort_start, NULL);
		heapsort(randomstring3, MaxString, sizeof(randomstring3[0]), autocompare);
		gettimeofday(&heapsort_end, NULL);
		heapsort_diff = 1000 * (heapsort_end.tv_sec - heapsort_start.tv_sec) + (heapsort_end.tv_usec - heapsort_start.tv_usec) / 1000;

		for(int i=0;i<MaxString;i++)
			printf("%s\n",randomstring1[i].content);

		printf("---------------\n");
		printf("Q Sort:%ld²@¬í\n", qsort_diff);
		printf("Merge Sort:%ld²@¬í\n", mergesort_diff);
		printf("Heap Sort:%ld²@¬í\n", heapsort_diff);
		printf("Q Sort ©M Merge Sort®É¶¡®t:%ld²@¬í\n", mergesort_diff - qsort_diff);

		free(randomstring1);
		free(randomstring2);
		free(randomstring3);

	}

	else if (strcmp(argv[1], "-h") == 0)
	{
		printf("-n:Numeral comparison\n");
		printf("-a:Random number/string generator\n");
		printf("-h:Help usage\n");
	}

	return 0;
}
