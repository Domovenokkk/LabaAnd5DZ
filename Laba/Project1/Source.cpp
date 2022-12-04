#include <iostream>
#include <string>
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
	int arti�;
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
	int permission;//����������
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
	printf("������� ������ ����������: ");
	scanf_s("%d", &(*size).width);
	printf("������� ������ ����������: ");
	scanf_s("%d", &(*size).height);
	printf("������� ������ ����������: ");
	scanf_s("%d", &(*size).depth);
}
float diagonal(struct TV size) {
	float diagonal;
	diagonal = sqrt(pow((size).width, 2) + pow((size).height, 2));
	return diagonal;
}
int square(struct TV size) {
	int square;
	square = (size).height * (size).width;
	return square;
}
int volume(struct TV size) {
	int volume;
	volume = (size).depth * (size).width * (size).height;
	return volume;
}

int main()
{
	setlocale(LC_ALL, "russian");
	//3task
	struct CabinetDimensions cabineet = { 50, 50, 50 };
	struct FIO ya = { "������", "������", "����������" };
	struct Data rightnow = { 22, 12,  04 };
	printf("������ �����: %d %d %d\n", cabineet.depth, cabineet.height, cabineet.width);
	printf("��� ���: %s %s %s\n", ya.surname, ya.name, ya.patronymic);
	printf("����: %d %d %d\n", rightnow.day, rightnow.month, rightnow.year);

	struct FIO* famnames;
	famnames = new struct FIO[3];

	//5 task
	struct TV* size;
	Input(size);
	diagonal(*size);
	square(*size);
	volume(*size);

	return 0;
}