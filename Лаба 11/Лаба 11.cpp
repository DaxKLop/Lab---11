#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
	char surname[30];
	char name[30];
	char fathername[30];
	char address[30];
	int group;
	float rating;
} student_t;

int menu();
void form();
void printon();
void addtostr();
void searchinstr();

int main()
{
	setlocale(LC_ALL, "russian");
	while (1)
	{
		switch (menu())
		{
		case 1:
			form();
			break;
		case 2:
			printon();
			break;
		case 3:
			addtostr();
			break;
		case 4:
			searchinstr();
			break;
		case 5:
			return 0;
		default:
			printf("\nНеверный выбор\n");
		}
	}
	return 0;
}

int menu()
{
	int k;
	printf("1)Формирование\n");
	printf("2)Печать\n");
	printf("3)Добавление\n");
	printf("4)Поиск\n");
	printf("5)Выход\n");
	printf("\nВаш выбор:\n");
	scanf_s("%d", &k);
	return k;
}


void enterStudent(student_t* student)
{
	printf("Введите фамилию:\n");
	scanf_s("%s", student->surname, sizeof(student->surname));
	printf("Введите имя:\n");
	scanf_s("%s", student->name, sizeof(student->name));
	printf("Введите отчество:\n");
	scanf_s("%s", student->fathername, sizeof(student->fathername));
	printf("Введите адрес:\n");
	scanf_s("%s", student->address, sizeof(student->address));
	printf("Введите № группы:\n");
	scanf_s("%d", &student->group, sizeof(student->group));
	printf("Введите рейтинг:\n");
	scanf_s("%f", &student->rating, sizeof(student->rating));
}

void printStudent(student_t* student)
{
	printf("Фамилия : %s\n", student->surname);
	printf("Имя : %s\n", student->name);
	printf("Отчество : %s\n", student->fathername);
	printf("Адрес : %s\n", student->address);
	printf("Группа : %d\n", student->group);
	printf("Рейтинг : %.2f\n", student->rating);
	printf("____________\n");
}

void form()
{
	FILE* f = NULL;
	fopen_s(&f, "student.txt", "wb");

	if (f == NULL)
	{
		printf("Ошибка открытия файла\n");
		return;
	}

	printf("Введите размерность списка структур:\n");

	int sch;
	scanf_s("%d", &sch);

	student_t* students = (student_t*)calloc(sch, sizeof(student_t));

	for (int i = 0; i < sch; i++)
	{
		enterStudent(&students[i]);
	}
	fwrite(students, sizeof(student_t), sch, f);
	fclose(f);
	free(students);
}

void addtostr()
{
	FILE* f = NULL;

	fopen_s(&f, "student.txt", "ab");

	if (f == NULL)
	{
		printf("Ошибка открытия файла\n");
		return;
	}

	int k;
	printf("Введите количество добавлений:\n");
	scanf_s("%d", &k);
	printf("\n");
	student_t* students = (student_t*)calloc(k, sizeof(student_t));


	for (int i = 0; i < k; i++)
	{
		enterStudent(&students[i]);
	}
	fwrite(students, sizeof(student_t), k, f);
	fclose(f);
	free(students);
}

bool readStudents(student_t** students, int* sch)
{
	FILE* f = NULL;
	fopen_s(&f, "student.txt", "rb");

	if (f == NULL)
	{
		printf("Ошибка открытия файла 1\n");
		return false;
	}
	fseek(f, 0, SEEK_END);
	*sch = ftell(f) / sizeof(student_t);
	fseek(f, 0, SEEK_SET);
	*students = (student_t*)calloc(*sch, sizeof(student_t));

	if (fread(*students, sizeof(student_t), *sch, f) != *sch)
	{
		fclose(f);
		free(*students);
		*students = NULL;
		printf("Ошибка открытия файла 2\n");
		return false;
	}

	fclose(f);
	return true;
}

void printon()

{
	student_t* students = NULL;
	int sch;
	if (!readStudents(&students, &sch))
		return;

	for (int i = 0; i < sch; i++)
	{
		printStudent(&students[i]);
	}
	free(students);
}

void searchinstr()
{
	student_t* students = NULL;
	int sch;
	if (!readStudents(&students, &sch))
		return;
	if (sch == 0)
	{
		printf("\nНет записей: \n");
		free(students);
		return;
	}

	char se[30];

	printf("\nВведите фамилию для поиска\n");
	scanf_s("%s", se, sizeof(se));

	bool isFound = false;
	for (int i = 0; i < sch; i++)
	{
		if (strcmp(students[i].surname, se) == 0)
		{
			printStudent(&students[i]);
			isFound = true;
		}
	}
	if (!isFound)
	{
		printf("Не найдено\n");
	}
	free(students);
}