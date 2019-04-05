#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

#define MAX 20000
#define BUFFER_SIZE 200
#define CAPACITY 100


typedef struct webLog {

	char IP[CAPACITY];
	char Time[CAPACITY];
	char URL[CAPACITY];
	char Staus[CAPACITY];

}WebLog;

void read();
void print();
WebLog webLogs[MAX];
int n = 0;
int print_num = 0;
char delim[] = ",[\0\n";
char category[4][BUFFER_SIZE];

int compareTime(const void *p, const void *q);
int compareIp(const void *p, const void *q);
int compareMonth(char *p, char *q);

int main() {

	char command[BUFFER_SIZE];
	char *buffer, *token;

	while (1) {
		printf("$ ");
		scanf("%s", command);
		if (strcmp(command, "read") == 0)
			read();

		else if (strcmp(command, "sort") == 0)
		{
			char kinds[BUFFER_SIZE];
			scanf("%s", kinds);

			if (strcmp(kinds, "-t") == 0)
			{
				qsort(webLogs, n, sizeof(WebLog), compareTime);
				print_num = 1;
			}
			else if (strcmp(kinds, "-ip") == 0)
			{
				qsort(webLogs, n, sizeof(WebLog), compareIp);
				print_num = 2;
			}
		}

		else if (strcmp(command, "print") == 0)
			print();
		else if (strcmp(command, "exit") == 0)
			break;
	}

}

void print() {
	if (print_num == 1)
	{
		for (int i = 0; i < n - 1; i++) {
			printf("%s\n", webLogs[i].Time);
			printf("\tIP: %s\n", webLogs[i].IP);
			printf("\tURL: %s\n", webLogs[i].URL);
			printf("\tStatus: %s\n", webLogs[i].Staus);
		}
	}

	else if (print_num == 2)
	{
		for (int i = 0; i < n - 1; i++) {
			printf("%s\n", webLogs[i].IP);
			printf("\tIP: %s\n", webLogs[i].Time);
			printf("\tURL: %s\n", webLogs[i].URL);
			printf("\tStatus: %s\n", webLogs[i].Staus);
		}
	}


}

void read() {

	char fileName[CAPACITY];
	char buffer[BUFFER_SIZE];

	scanf("%s", fileName);

	FILE*fp = fopen(fileName, "r");

	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	fgets(buffer, BUFFER_SIZE, fp);
	buffer[strlen(buffer) - 1] = '\0';

	char *token = strtok(buffer, delim);
	strcpy(category[0], token);
	token = strtok(NULL, delim);
	strcpy(category[1], token);
	token = strtok(NULL, delim);
	strcpy(category[2], token);
	token = strtok(NULL, delim);
	strcpy(category[3], token);

	
	while (!feof(fp))
	{
		fgets(buffer, BUFFER_SIZE, fp);
		buffer[strlen(buffer) - 1] = '\0';

		token = strtok(buffer, delim);
		strcpy(webLogs[n].IP, token);
		token = strtok(NULL, delim);
		strcpy(webLogs[n].Time, token);
		token = strtok(NULL, delim);
		strcpy(webLogs[n].URL, token);
		token = strtok(NULL, delim);
		strcpy(webLogs[n].Staus, token);

		n++;
	}
	fclose(fp);

}

int compareTime(const void *p, const void *q)
{
	char x[BUFFER_SIZE], y[BUFFER_SIZE];
	char *t1[6], *t2[6];
	strcpy(x, ((WebLog*)p)->Time);
	strcpy(y, ((WebLog*)q)->Time);

	t1[0] = strtok(x, "/");
	t1[1] = strtok(NULL, "/");
	t1[2] = strtok(NULL, ":");
	t1[3] = strtok(NULL, "\0");

	t2[0] = strtok(y, "/");
	t2[1] = strtok(NULL, "/");
	t2[2] = strtok(NULL, ":");
	t2[3] = strtok(NULL, "\0");

	if (strcmp(t1[2], t2[2]) != 0)
		return (strcmp(t1[2], t2[2]));

	if (compareMonth(t1[1], t2[1]) != 0) {
		return compareMonth(t1[1], t2[1]);
	}
	strcmp(t1[0], t2[0]);
	if (strcmp(t1[0], t2[0]) != 0) {
		return (strcmp(t1[0], t2[0]));
	}

	return (strcmp(t1[3], t2[3]));
}
int compareIp(const void *p, const void *q)
{
	if(strcmp(((WebLog *)p)->IP, ((WebLog *)q)->IP) != 0)
		return (strcmp(((WebLog *)p)->IP, ((WebLog *)q)->IP));
	return compareTime(p, q);
}

int compareMonth(char *p, char *q) {

	char *Month[12] = { "Jan","Feb","Mer","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
	int A = 0, B = 0;
	for (int i = 0; i < 12; i++) {
		if (strcmp(p, Month[i]) == 0)
			A = i;
		if (strcmp(q, Month[i]) == 0)
			B = i;
	}
	return A - B;

}