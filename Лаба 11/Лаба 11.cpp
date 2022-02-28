#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <Windows.h>

typedef struct 
{
	char surname[30];
	char initials[30];
	char birthday[30];
	char receipt_date[30];
	float math_score;
	float physics_grade;
	float computer_science_assessment;
} student_t;

int menu();
void form();
void printonAll();
void addtostr();
void searchinstr();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	while (1)
	{
		switch (menu())
		{
		case 1:
			form();
			break;
		case 2:
			printonAll();
			break;
		case 3:
			addtostr();
			break;
		case 4:
			searchinstr();
			break;
		case 5:
			printf("Студенты с Фамилий начинающаяся на А");
			printNameStartWithA();
			break;
		case 6:
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
	printf("5)Задание\n");
	printf("6)Выход\n");
	printf("\nВаш выбор:\n");
	scanf_s("%d", &k);
	return k;
}


void enterStudent(student_t* student)
{
	printf("Введите фамилию:\n");
	scanf_s("%s", student->surname,sizeof(student->surname));
	printf("Введите инициалы:\n");
	scanf_s("%s", student->initials,sizeof(student->initials));
	printf("Введите день рождения:\n");
	scanf_s("%s", student->birthday,sizeof(student->birthday));
	printf("Введите дату поступлени:\n");
	scanf_s("%s", student->receipt_date,sizeof(student->receipt_date));
	printf("Введите оценку по математике:\n");
	scanf_s("%f", &student->math_score,sizeof(student->math_score));
	printf("Введите оценку по физике:\n");
	scanf_s("%f", &student->physics_grade,sizeof(student->physics_grade));
	printf("Введите оценку по информатике:\n");
	scanf_s("%f", &student->computer_science_assessment,sizeof(student->computer_science_assessment));
}

void printStudent(student_t* student, int *flag)
{
	if (*flag == 1)
	{
	printf("Фамилия : %s\n", student->surname);
	printf("Инициалы : %s\n", student->initials);
	printf("День рождения (в формате 	DD.MM.YYYY)     : %s\n", student->birthday);
	printf("Дата поступления (в формате 	DD.MM.YYYY)    : %s\n", student->receipt_date);
	printf("Оценка по математике : %.2f\n", student->math_score);
	printf("Оценка по физике : %.2f\n", student->physics_grade);
	printf("Оценка по физике : %.2f\n", student->computer_science_assessment);
	printf("____________\n");
	}
	else if (*flag == 2)
	{
		printf("Фамилия : %s\n", student->surname);
		printf("Инициалы : %s\n", student->initials);
		printf("День рождения (в формате 	DD.MM.YYYY)     : %s\n", student->birthday);
	}
}

void form()
{
	FILE* f = NULL;
	fopen_s(&f, "student.dat", "w");

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

	fopen_s(&f, "student.dat", "a");

	if (f == NULL)
	{
		printf("Ошибка открытия файла\n");
		return;
	}
	
	int k;
	printf("Введите количество добавлений:\n");
	scanf_s("%d", &k);
	printf("\n");
	student_t* students = (student_t*)calloc( k, sizeof(student_t));


	for (int i = 0; i < k; i++)
	{
		enterStudent(&students[i]);
	}
	fwrite(students, sizeof(student_t), k, f);
	fclose(f);
	free(students);
}

bool readStudents(student_t** students, int *sch)
{
	FILE* f = NULL;
	fopen_s(&f, "student.dat", "r");

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

void printonAll()

{
	student_t* students = NULL;
	int sch, flag = 1;
	if (!readStudents(&students, &sch)) 
		return;
		
	for (int i = 0; i < sch; i++)
	{
		printStudent(&students[i], &flag);
	}
	free(students);
}

void searchinstr()
{
	student_t* students = NULL;
	int sch, flag = 1;
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
	scanf_s("%s", se,sizeof(se));

	bool isFound = false;
	for (int i = 0; i < sch; i++)
	{
		if (strcmp(students[i].surname, se) == 0)
		{
			printStudent(&students[i], &flag);
			isFound = true;
		}
	}
	if (!isFound)
		{
			printf("Не найдено\n");
		}
	free(students);
}
void printNameStartWithA()

{
	student_t* students = NULL;
	int sch, flag = 2;
	char str2[2] = "A";
	char *istr[100];
	if (!readStudents(&students, &sch))
		return;

	for (int i = 0; i < sch; i++)
	{
		*istr = strstr(students[i].surname, str2);
		if (*istr - students[i].surname + 1 == 1)
		printStudent(&students[i], &flag);
	}
	free(students);
}
