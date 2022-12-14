#include <stdio.h>
#include <locale.h>
struct Dimension 
{	
	int height;
	int depth;
	int width;
};
void Input(struct Dimension* size) {
	printf("Введите высоту шкафа: ");
	scanf_s("%d", &(*size).height);
	printf("Введите ширину шкафа: ");
	scanf_s("%d", &(*size).width);
	printf("Введите толщину шкафа: ");
	scanf_s("%d", &(*size).depth);
}
int calculateSquare(struct Dimension size) {
	int square_board, square_updown, square_front, square;
	square_board = 2 * size.height * size.depth;
	square_updown = 2 * size.width * size.depth;
	square_front = size.height * size.width;
	square = square_board + square_updown + square_front;
	return square;
}
int calculateVolume(struct Dimension size) {
	int Volume = size.height * size.depth * size.width;
	return Volume;
}
float calculateDye(struct Dimension size, float consumption) {
	int square = calculateSquare(size);
	float dye = square * consumption;
	return dye;
}
float calculatePaintingCost(struct Dimension size, float consumption, float workCost, float paintCost) {
	float paintprice = calculateDye(size, consumption) * paintCost;
	float workprice = calculateDye(size, consumption) * workCost;
	float paintcost = paintprice + workprice;
	return paintcost;
}
float calculateCupboardCost(struct Dimension size, float cupboardCost) {
	float costcab = calculateSquare(size) * cupboardCost;
	return costcab;
}
float calculateCabinetMass(struct Dimension size, float weight) {
	float ves_cab = calculateSquare(size) * weight;
	return ves_cab;
}
float LiftCost(struct Dimension size, float weight, int floorsCount, float riseCost) {
	float LiftCost = calculateCabinetMass(size, weight) * floorsCount * riseCost;
	return LiftCost;
}
float calculateCost(struct Dimension size, float cupboardCost, float consumption, float paintCost, float workCost, float weight, int floorsCount, float riseCost, float deliveryCost) {
	float full_price = calculatePaintingCost(size, consumption, workCost, paintCost) + calculateCupboardCost(size, cupboardCost) + LiftCost(size, weight, floorsCount, riseCost) + deliveryCost;
	return full_price;
}
float calculateNalog(struct Dimension size, float cupboardCost, float consumption, float paintCost, float workCost, float weight, int floorsCount, float riseCost, float deliveryCost) {
	float NalogCost = calculateCost(size, cupboardCost, consumption, paintCost, workCost, weight, floorsCount, riseCost, deliveryCost) * 0.13;
	return NalogCost;
}
int main() {
	setlocale(LC_ALL, "russian");
	float paintConsumption = 0.8, paintWorkCost = 35.00, paintCost = 50.00;
	float cupboardCost = 650;
	float weight = 0.9;
	int floorsCount = 5;
	float deliveryCost = 500.00;
	float riseCost = 2.50;
	struct Dimension size;
	printf("Введите параметры шкафа: \n");
	Input(&size);
	float cost, cupboard_cost, painting_cost, delivery_cost, NalogCost;
	cupboard_cost = calculateCupboardCost(size, cupboardCost);
	painting_cost = calculatePaintingCost(size, paintConsumption, paintWorkCost, paintCost);
	delivery_cost = LiftCost(size, weight, floorsCount, riseCost) + deliveryCost;
	NalogCost = calculateNalog(size, cupboardCost, paintConsumption, paintCost, paintWorkCost, weight, floorsCount, riseCost, deliveryCost);
	cost = calculateCost(size, cupboardCost, paintConsumption, paintCost, paintWorkCost, weight, floorsCount, riseCost, deliveryCost) + NalogCost;
	printf("Промежуточный расчет:\n  - Стоимость шкафа: %.2f\n  - Стоимость покраски: %.2f\n  - Стоимость доставки(с подъемом): %.2f\n  - Налог: %.2f\nИтоговая цена: %.2f", cupboard_cost, painting_cost, delivery_cost, NalogCost,  cost);
	return 0;
}