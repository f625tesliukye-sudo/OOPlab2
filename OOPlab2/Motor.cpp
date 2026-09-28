#include "Motor.h"

using namespace std;

Motor::Motor() : minRpm(200), maxRpm(1500), currentRpm(0), lastRpm(200), power(45), running(false)
{
}

Motor::Motor(int maxRpm, int power) : minRpm(200), maxRpm(maxRpm), currentRpm(0), lastRpm(200), power(power), running(false)
{
	if (this->maxRpm < minRpm)
		this->maxRpm = minRpm;
	if (this->power < 1)
		this->power = 1;
}

Motor::~Motor()
{
	cout << "\t[Двигун] знеструмлено та демонтовано." << endl;
}

void Motor::start()
{
	running = true;
	currentRpm = lastRpm;
}

void Motor::stop()
{
	if (running)
		lastRpm = currentRpm;   // запам'ятовуємо швидкість для наступного вмикання
	currentRpm = 0;
	running = false;
}

bool Motor::setSpeed(int rpm)
{
	if (rpm < minRpm || rpm > maxRpm)
		return false;
	lastRpm = rpm;
	if (running)
		currentRpm = rpm;
	return true;
}

int  Motor::getSpeed() const    { return currentRpm; }
int  Motor::getMinSpeed() const { return minRpm; }
int  Motor::getMaxSpeed() const { return maxRpm; }
void Motor::setPower(int value) { if (value > 0) power = value; }
int  Motor::getPower() const    { return power; }
bool Motor::isRunning() const   { return running; }

void Motor::show() const
{
	cout << "\t Двигун: " << (running ? "ПРАЦЮЄ" : "зупинено") << endl;
	cout << "\t   Поточна швидкість: " << currentRpm << " об/хв" << endl;
	cout << "\t   Діапазон швидкостей: " << minRpm << " - " << maxRpm << " об/хв" << endl;
	cout << "\t   Потужність: " << power << " Вт" << endl;
}
