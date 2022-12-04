#include <stdio.h>
#include <locale.h>
#include <math.h>
//1-2 task
struct CabinetDimensions
{
	int height;
	int depth;
	int width;
};
struct Book
{
	char autor[30];
	char title[30];
	char edition[30];
	int year;
	int numofpages;
	int artiс;
	int width;
	int height;
};
struct BJUK
{
	int protein;
	int fat;
	int carbohydrates;
	float calories;
};
struct FIO
{
	char surname[30];
	char name[30];
	char patronymic[30];
};
struct Notebook
{
	char publisher[30];
	char typeofbook[30];
	int numofpages;
	int sizeofpages;
};
struct Data
{
	int year;
	int month;
	int day;
};
struct Jeans
{
	char firm[30];
	char typeofjeans[30];
	char manorwoman[30];
	int size;
};
struct TV
{
	char firm[30];
	char type[30];
	int diagonal;
	int permission;//разрешение
	int hertz;
	int height;
	int depth;
	int width;
	int weight;
};
struct Body
{
	int weight;
	int shoulders;
	int breast;
	int waist;
	int hip;
	int footsize;
};
struct Worker
{
	struct FIO worker;
	struct Data born;
	float salary;
	int number;
	char jobtitle[30];
};
struct Dish
{
	struct FIO kitchener;
	char season[30];
	char placeofeat[30];
	float timeofcook;
	float calories;
};
struct Student
{
	struct FIO student;
	struct Data born;
	float grants;
	int number;
	int course;
};
struct Patient
{
	struct FIO patient;
	struct Data born;
	int enterdate;
	char hospital[30];
	char disease[30];
	struct FIO doctor;
};

void Input(struct TV* size) {
	printf("Введите ширину телевизора: ");
	scanf_s("%d", &(*size).width);
	printf("Введите высоту телевизора: ");
	scanf_s("%d", &(*size).height);
	printf("Введите высоту телевизора: ");
	scanf_s("%d", &(*size).depth);
}
void diagonal(struct TV* size) {
	int diagonal;
	int height = (*size).height;
	int width = (*size).width;
	diagonal = sqrt(pow(height, 2) + pow(width, 2));
	printf("Диагональ телевизора: %d", diagonal);
}
void square(struct TV* size) {
	int square;
	int height = (*size).height;
	int width = (*size).width;
	square = height * width;
	printf("\nПлощадь экрана: %d", square);
}
void volume(struct TV* size) {
	int volume;
	int height = (*size).height;
	int width = (*size).width;
	int depth = (*size).depth;
	volume = height * width * depth;
	printf("\nОбъем телевизора: %d", volume);
}
void FIOfam(struct FIO* names) {
	printf("Введите фамилию - ");
	getchar((*names).surname);
}
int main()
{
	setlocale(LC_ALL, "russian");
	//3task
	struct CabinetDimensions cabineet = { 50, 50, 50};
	struct FIO ya = { "Межуев", "Максим", "Евгеньевич" };
	struct Data rightnow = { 22, 12,  04};
	printf("Размер шкафа: %d %d %d\n", cabineet.depth, cabineet.height, cabineet.width);
	printf("Мое ФИО: %s %s %s\n", ya.surname, ya.name, ya.patronymic);
	printf("Дата: %d %d %d\n", rightnow.day, rightnow.month, rightnow.year);


	//5 task
	struct TV* size;
	Input(&size);
	diagonal(&size);
	square(&size);
	volume(&size);

	return 0;
}