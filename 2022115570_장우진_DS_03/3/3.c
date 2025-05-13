#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[10];
	int age;
	float salary;
}humanBeing;


int humansEqual(humanBeing* person1, humanBeing* person2);
void re(char* c);


int main()
{
	humanBeing person1, person2;
	
	printf("Input person1's name, age salary: ");
	fgets(person1.name, sizeof(person1.name), stdin);
	person1.name[strcspn(person1.name, "\n")] = '\0';
	scanf("%d", &person1.age);
	getchar();
	scanf("%f", &person1.salary);
	getchar();
	
	
	printf("Input person2's name, age salary: ");
	fgets(person2.name, sizeof(person2.name), stdin);
	person2.name[strcspn(person2.name, "\n")] = '\0';
	scanf("%d", &person2.age);
	getchar();
	scanf("%f", &person2.salary);
	getchar();


	re(person1.name);
	re(person2.name);


	humanBeing* p1 = &person1;
	humanBeing* p2 = &person2;

	if (humansEqual(p1, p2)) printf("The two human beings are the same\n");
	else printf("The two human beings are not the same\n");

	return 0;
}

int humansEqual(humanBeing* person1, humanBeing* person2)
{
	if ((strcmp(person1->name, person2->name) == 0)
		&& (person1->age == person2->age) &&
		(person1->salary == person2->salary)) return 1;
	else return 0;
}

void re(char* c)
{
	int buffer = 0;
	for (int i = 0; c[i] != '\0'; i++)
	{
		if (c[i] != ' ') c[buffer++] = c[i];
	}
	c[buffer] = '\0';
}
