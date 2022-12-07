#include <iostream>
#include <string>
using namespace std;
//4
struct Time {
	int hour;
	int minute;
	int second;
};
struct FIO {
	string surname;
	string name;
	string patronymic;
};
struct Data {
	int day;
	int month;
	int year;
};
struct Food
{
	Time time_of_eating;
	string name;
	int num_calories;
	string place;
};
struct Fam {
	string chlen_of_fam;
	FIO fam;
	Data born;
	int year_old;

};

void main() {
	// 4
	struct Food* racion_of_food = new struct Food[3];
	racion_of_food[0] = { {8,8,8} ,"Breakfast", 200, "Kithcen"};
	racion_of_food[1] = { {14,14,14} ,"Lunch", 500, "Bathroom"};
	racion_of_food[2] = { {18,43,23} ,"Dinner", 1000, "Toilet"};

	struct Fam* fam = new struct Fam[3];
	fam[0] = { "Father", {"Дальченко", "Олег", "Васильевич"}, {12, 10, 1983}, 40 };
	fam[1] = { "Mother" , {"Дальченко", "Олеся", "Викторовна"}, {07, 12, 1986}, 38 };
	fam[2] = { "Son" , {"Дальченко", "Максим", "Евгеньевич"}, {12, 11, 2000} , 22};
}