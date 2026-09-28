#include "Controller.h"
#include <cstdio>

using namespace std;

Controller::Controller() : motor(nullptr), timerLeft(0), timerActive(false)
{
}

Controller::Controller(Motor* motor) : motor(motor), timerLeft(0), timerActive(false)
{
}

Controller::~Controller()
{
	cout << "\t[Контролер] відключено." << endl;
}

void Controller::attachMotor(Motor* m)
{
	motor = m;
}

void Controller::powerOn()
{
	if (motor != nullptr)
		motor->start();
}

void Controller::powerOff()
{
	if (motor != nullptr)
		motor->stop();
	cancelTimer();
}

bool Controller::setSpeed(int rpm)
{
	if (motor == nullptr || !motor->setSpeed(rpm))
		return false;
	if (!motor->isRunning())
		motor->start();
	return true;
}

bool Controller::setTimer(int seconds)
{
	if (motor == nullptr || !motor->isRunning())
		return false;
	if (seconds <= 0 || seconds > MAX_TIMER_SECONDS)
		return false;
	timerLeft = seconds;
	timerActive = true;
	return true;
}

void Controller::cancelTimer()
{
	timerLeft = 0;
	timerActive = false;
}

bool Controller::tick(int seconds)
{
	if (!timerActive || seconds <= 0)
		return false;

	timerLeft -= seconds;
	if (timerLeft <= 0)
	{
		if (motor != nullptr)
			motor->stop();
		cancelTimer();
		return true;
	}
	return false;
}

bool Controller::isRunning() const   { return motor != nullptr && motor->isRunning(); }
int  Controller::getSpeed() const    { return motor != nullptr ? motor->getSpeed() : 0; }
int  Controller::getMinSpeed() const { return motor != nullptr ? motor->getMinSpeed() : 0; }
int  Controller::getMaxSpeed() const { return motor != nullptr ? motor->getMaxSpeed() : 0; }
bool Controller::isTimerActive() const { return timerActive; }
int  Controller::getTimeLeft() const   { return timerLeft; }

string Controller::formatTime(int seconds)
{
	char buf[16];
	snprintf(buf, sizeof(buf), "%02d:%02d:%02d", seconds / 3600, (seconds % 3600) / 60, seconds % 60);
	return string(buf);
}

void Controller::show() const
{
	cout << "\t Контролер: ";
	if (timerActive)
		cout << "таймер відключення - залишилось " << formatTime(timerLeft) << endl;
	else
		cout << "таймер відключення не встановлено" << endl;
}
