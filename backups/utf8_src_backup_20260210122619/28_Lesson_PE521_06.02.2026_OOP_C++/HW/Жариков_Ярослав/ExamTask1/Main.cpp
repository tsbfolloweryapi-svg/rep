#include "pch.h"
#include "Utils.h"
#include "App.h"
#include "Palette.h"


int main() {
	// настройка вывода в консоль
	init(L"Экзамен задание_1");
	ostringstream oss;

	// Объект класса приложения для обработок по заданию
	App* app = new App();

	try {
		cout << color(mainColor) << cls;
		showNavBarMessage(
			hintColor, acctColor,
			"  Вектор вещественных чисел (STL, алгоритмы)  |  ~Esc~ ~F10~ Выход"
		);

		app->doTask1();
	}
	catch (exception& ex) {
		// заливка экрана базовым цветом, вывод строки навигации с сообщением
		cout << color(mainColor) << cls;
		showNavBarMessage(hintColor, "  Ошибка в приложении, нажмите любую клавишу для продолжения");

		int width = 72;

		oss.str("");
		oss << endlm(4) << left
			<< "\t" << setw(width) << " " << "\n"
			<< "\t" << setw(width) << "    [Ошибка]" << "\n"
			<< "\t    " << left << setw(width - 4) << ex.what() << right << "\n"
			<< "\t" << setw(width) << " " << "\n"
			<< "\t" << setw(width) << " " << "\n"
			<< endlm(4)
			<< right;
		showMessage(oss.str(), errColor, mainColor);
	} // try-catch

	getKey("    Нажмите любую клавишу для завершения...");
	delete app;
	cls();
	return 0;
} // main
