#include <iostream>
#include <clocale>
#include "Fan.h"
#include "ConsoleIO.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void ShowMenu()
{
	cout << "\n========== ПУЛЬТ КЕРУВАННЯ ВЕНТИЛЯТОРОМ ==========" << endl;
	cout << " 1 - Показати стан вентилятора" << endl;
	cout << " 2 - Увімкнути / вимкнути (кнопка живлення)" << endl;
	cout << " 3 - Обрати режим швидкості (низька / середня / висока)" << endl;
	cout << " 4 - Встановити швидкість обертів вручну" << endl;
	cout << " 5 - Збільшити швидкість (+)" << endl;
	cout << " 6 - Зменшити швидкість (-)" << endl;
	cout << " 7 - Встановити час відключення (хв)" << endl;
	cout << " 8 - Скасувати таймер відключення" << endl;
	cout << " 9 - Імітувати плин часу" << endl;
	cout << " 0 - Вихід" << endl;
}

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif
	setlocale(LC_ALL, "");

	cout << "Налаштування вентилятора." << endl;
	int maxRpm = ConsoleIO::GetInt("Введіть максимальну швидкість двигуна (500-3000 об/хв): ", 500, 3000);
	int power  = ConsoleIO::GetInt("Введіть потужність двигуна (10-200 Вт): ", 10, 200);

	Fan fan("Comfort-1", maxRpm, power);
	RemoteControl& remote = fan.getRemote();

	bool exitFlag = false;
	while (!exitFlag)
	{
		ShowMenu();
		int choice = ConsoleIO::GetInt("Ваш вибір: ", 0, 9);
		cout << endl;

		switch (choice)
		{
		case 1:
			fan.show();
			break;
		case 2:
			remote.pressPower();
			break;
		case 3:
		{
			int lvl = ConsoleIO::GetInt("Режим (1 - низька, 2 - середня, 3 - висока): ", 1, remote.getLevelsCount());
			remote.selectLevel(lvl - 1);
			break;
		}
		case 4:
		{
			int rpm = ConsoleIO::GetInt("Введіть швидкість, об/хв: ", 0, 100000);
			remote.setSpeed(rpm);
			break;
		}
		case 5:
			remote.speedUp();
			break;
		case 6:
			remote.speedDown();
			break;
		case 7:
		{
			int min = ConsoleIO::GetInt("Вимкнути вентилятор через (хв): ", 0, 100000);
			remote.setShutdownTimer(min);
			break;
		}
		case 8:
			remote.cancelShutdownTimer();
			break;
		case 9:
		{
			int sec = ConsoleIO::GetInt("Скільки секунд імітувати (1-43200): ", 1, 43200);
			fan.simulate(sec);
			break;
		}
		case 0:
			exitFlag = true;
			break;
		}
	}

	cout << "\nРоботу завершено." << endl;
	return 0;
}
