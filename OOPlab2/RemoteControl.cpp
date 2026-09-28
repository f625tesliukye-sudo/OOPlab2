#include "RemoteControl.h"

using namespace std;

/*-------------------- SpeedLevel --------------------*/

SpeedLevel::SpeedLevel() : name("Не задано"), rpm(0)
{
}

SpeedLevel::SpeedLevel(const string& name, int rpm) : name(name), rpm(rpm)
{
}

void SpeedLevel::set(const string& n, int r)
{
	name = n;
	rpm = r;
}

string SpeedLevel::getName() const { return name; }
int    SpeedLevel::getRpm() const  { return rpm; }

void SpeedLevel::show() const
{
	cout << name << " (" << rpm << " об/хв)";
}

/*------------------ RemoteControl -------------------*/

RemoteControl::RemoteControl() : controller(nullptr), speedStep(100)
{
}

RemoteControl::RemoteControl(Controller* controller) : controller(controller), speedStep(100)
{
}

RemoteControl::~RemoteControl()
{
	cout << "\t[Пульт] батареї вийнято." << endl;
}

void RemoteControl::attachController(Controller* c)
{
	controller = c;
}

void RemoteControl::setLevel(int index, const string& name, int rpm)
{
	if (index >= 0 && index < LEVELS_COUNT)
		levels[index].set(name, rpm);
}

void RemoteControl::pressPower()
{
	if (controller == nullptr)
		return;

	if (controller->isRunning())
	{
		controller->powerOff();
		cout << "\t[Пульт] Вентилятор ВИМКНЕНО." << endl;
	}
	else
	{
		controller->powerOn();
		cout << "\t[Пульт] Вентилятор УВІМКНЕНО. Швидкість: " << controller->getSpeed() << " об/хв." << endl;
	}
}

bool RemoteControl::selectLevel(int index)
{
	if (controller == nullptr || index < 0 || index >= LEVELS_COUNT)
	{
		cout << "\t[Пульт] Такого режиму не існує." << endl;
		return false;
	}
	return setSpeed(levels[index].getRpm());
}

bool RemoteControl::setSpeed(int rpm)
{
	if (controller == nullptr)
		return false;

	if (!controller->setSpeed(rpm))
	{
		cout << "\t[Пульт] Помилка: швидкість має бути в межах "
		     << controller->getMinSpeed() << " - " << controller->getMaxSpeed() << " об/хв." << endl;
		return false;
	}
	cout << "\t[Пульт] Швидкість встановлено: " << rpm << " об/хв." << endl;
	return true;
}

bool RemoteControl::speedUp()
{
	if (controller == nullptr)
		return false;
	if (!controller->isRunning())
	{
		cout << "\t[Пульт] Вентилятор вимкнено. Спочатку увімкніть його." << endl;
		return false;
	}
	int rpm = controller->getSpeed() + speedStep;
	if (rpm > controller->getMaxSpeed())
		rpm = controller->getMaxSpeed();
	return setSpeed(rpm);
}

bool RemoteControl::speedDown()
{
	if (controller == nullptr)
		return false;
	if (!controller->isRunning())
	{
		cout << "\t[Пульт] Вентилятор вимкнено. Спочатку увімкніть його." << endl;
		return false;
	}
	int rpm = controller->getSpeed() - speedStep;
	if (rpm < controller->getMinSpeed())
		rpm = controller->getMinSpeed();
	return setSpeed(rpm);
}

bool RemoteControl::setShutdownTimer(int minutes)
{
	if (controller == nullptr)
		return false;

	if (!controller->isRunning())
	{
		cout << "\t[Пульт] Вентилятор вимкнено. Таймер можна встановити лише для працюючого вентилятора." << endl;
		return false;
	}
	if (!controller->setTimer(minutes * 60))
	{
		cout << "\t[Пульт] Помилка: час відключення має бути від 1 хв до "
		     << Controller::MAX_TIMER_SECONDS / 60 << " хв." << endl;
		return false;
	}
	cout << "\t[Пульт] Вентилятор вимкнеться через " << minutes << " хв." << endl;
	return true;
}

void RemoteControl::cancelShutdownTimer()
{
	if (controller == nullptr)
		return;
	if (controller->isTimerActive())
	{
		controller->cancelTimer();
		cout << "\t[Пульт] Таймер відключення скасовано." << endl;
	}
	else
		cout << "\t[Пульт] Таймер не було встановлено." << endl;
}

int RemoteControl::getLevelsCount() const
{
	return LEVELS_COUNT;
}

void RemoteControl::show() const
{
	cout << "\t Пульт керування. Режими швидкості:" << endl;
	for (int i = 0; i < LEVELS_COUNT; i++)
	{
		cout << "\t   " << i + 1 << ") ";
		levels[i].show();
		cout << endl;
	}
	cout << "\t   Крок кнопок +/-: " << speedStep << " об/хв" << endl;
}
