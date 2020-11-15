#include <stdio.h>
#include <conio.h>
#include "min.h"
#include "max.h"
#include "diff.h"
#include "sum.h"

int main() {
	int command;
	int array[100];
	int size = 0;
	scanf_s("%d", &command);
	while (getchar() != '\n') {
		scanf_s("%d", &array[size]);
		size++;
	}
	switch (command) {
	case 0:
		printf("%d\n", max(array, size));
		break;
	case 1:
		printf("%d\n", min(array, size));
		break;
	case 2:
		printf("%d\n", diff(array, size));
		break;
	case 3:
		printf("%d\n", sum(array, size));
		break;
	default:
		printf("������ �����������\n");
		break;
	}
	_getch();
	return 0;
}