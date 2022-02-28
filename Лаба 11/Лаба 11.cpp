#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
using namespace std;

typedef struct 
{
	char surname[30];
	char initials[30];
	char birthday[30];
	char receipt_date[30];
	int math_mark;
	int physics_mark;
	int computer_science_mark;
} student_t;

int menu();
void form();
void printAllStudents();
void addtostr();
void searchStudentBySurname();
void printStudentWithNameStartWithA();

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
			printAllStudents();
			break;
		case 3:
			addtostr();
			break;
		case 4:
			searchStudentBySurname();
			break;
		case 5:
			printf("Студенты с Фамилий начинающаяся на А\n");
			printStudentWithNameStartWithA();
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


void enterOnlyLetterString(char* s)
{
	int i = 0;
	while (1)
	{
		s[i] = _getch();
		if (s[i] == 13) break;
		if (((((int)s[i] >= 65 && (int)s[i] <= 90) || ((int)s[i] >= 97 && (int)s[i] <= 122) || ((int)s[i] <= -1 && (int)s[i] >= -64))))
		{
			cout << s[i];
			i++;
		}
	}
	s[i] = '\0';
}

void enterInitials(char* s)
{
	int i = 0;
	while (1)
	{
		s[i] = _getch();
		if (s[i] == 13) break;
		if (((((int)s[i] >= 65 && (int)s[i] <= 90) || ((int)s[i] <= -23 && (int)s[i] >= -64) || s[i] == '.')))
		{
			cout << s[i];
			i++;
		}
	}
	s[i] = '\0';
}

void enterDate(char* s)
{
	int i = 0;
	while (1)
	{
		s[i] = _getch();
		if (s[i] == 13) break;
		if (((int)s[i] >= 48 && (int)s[i] <= 57) || s[i] == '.')
		{
			cout << s[i];
			i++;
		}
	}
	s[i] = '\0';
}

void enterMarks(char* s)
{
	int i = 0;
	while (1)
	{
		s[i] = _getch();
		if (s[i] == 13) break;
		if (((int)s[i] >= 48 && (int)s[i] <= 57) || s[i] == ',')
		{
			cout << s[i];
			i++;
		}
	}
	s[i] = '\0';
}

void enterStudent(student_t* student)
{
	printf("Введите фамилию:\n");
	enterOnlyLetterString(student->surname);
	printf("\nВведите инициалы:\n");
	enterInitials(student->initials);
	printf("\nВведите день рождения (в формате 	DD.MM.YYYY) :\n");
	enterDate(student->birthday);
	printf("\nВведите дату поступлени (в формате 	DD.MM.YYYY) :\n");
	enterDate(student->receipt_date);
	printf("\nВведите оценку по математике:\n");
	scanf_s("%d", &student->math_mark,sizeof(student->math_mark));
	fseek(stdin, 0, SEEK_END);
	printf("Введите оценку по физике:\n");
	scanf_s("%d", &student->physics_mark,sizeof(student->physics_mark));
	fseek(stdin, 0, SEEK_END);
	printf("Введите оценку по информатике:\n");
	scanf_s("%d", &student->computer_science_mark,sizeof(student->computer_science_mark));
	fseek(stdin, 0, SEEK_END);
}

void printStudent(student_t* student)
{
	
	printf("Фамилия : %s\n", student->surname);
	printf("Инициалы : %s\n", student->initials);
	printf("День рождения : %s\n", student->birthday);
	printf("Дата поступления : %s\n", student->receipt_date);
	printf("Оценка по математике : %d\n", student->math_mark);
	printf("Оценка по физике : %d\n", student->physics_mark);
	printf("Оценка по информатике : %d\n", student->computer_science_mark);
	printf("____________\n");
}

void printSomeAttributes(student_t* student)
{
	printf("Фамилия : %s\n", student->surname);
	printf("Инициалы : %s\n", student->initials);
	printf("День рождения : %s\n", student->birthday);
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

void printAllStudents()
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

void searchStudentBySurname()
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
	scanf_s("%s", se,sizeof(se));

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

void printStudentWithNameStartWithA()
{
	student_t* students = NULL;
	int sch;
	char str2[2] = "А";
	char *istr[100];
	if (!readStudents(&students, &sch))
		return;

	for (int i = 0; i < sch; i++)
	{
		*istr = strstr(students[i].surname, str2);
		if (*istr - students[i].surname + 1 == 1)
		printSomeAttributes(&students[i]);
		char str2[2] = "A";
		*istr = strstr(students[i].surname, str2);
		if (*istr - students[i].surname + 1 == 1)
			printSomeAttributes(&students[i]);
	}
	free(students);
}
