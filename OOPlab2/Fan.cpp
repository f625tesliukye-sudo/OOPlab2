#include "Fan.h"
#include <thread>
#include <chrono>

using namespace std;

Fan::Fan() : model("Standard"), motor(), controller(&motor), remote(&controller)
{
	configureRemote();
}

Fan::Fan(const string& model, int maxRpm, int power)
	: model(model), motor(maxRpm, power), controller(&motor), remote(&controller)
{
	configureRemote();
}

Fan::~Fan()
{
	cout << "\t[Вентилятор \"" << model << "\"] розібрано." << endl;
}

void Fan::configureRemote()
{
	int lo  = motor.getMinSpeed();
	int hi  = motor.getMaxSpeed();
	int mid = (lo + hi) / 2;
	remote.setLevel(0, "Низька",  lo);
	remote.setLevel(1, "Середня", mid);
	remote.setLevel(2, "Висока",  hi);
}

void Fan::setModel(const string& value) { model = value; }
string Fan::getModel() const            { return model; }
RemoteControl& Fan::getRemote()         { return remote; }

void Fan::simulate(int seconds)
{
	if (!controller.isTimerActive())
	{
		cout << "\t Таймер відключення не активний - імітувати нічого." << endl;
		return;
	}

	int printEvery = seconds / 10;
	if (printEvery < 1)
		printEvery = 1;

	cout << "\n\t --- Імітація: минає " << seconds << " с ---" << endl;
	for (int t = 1; t <= seconds; t++)
	{
		bool switchedOff = controller.tick(1);

		if (t % printEvery == 0 || switchedOff)
		{
			cout << "\t +" << Controller::formatTime(t) << "  швидкість: " << motor.getSpeed() << " об/хв";
			if (controller.isTimerActive())
				cout << ",  до відключення: " << Controller::formatTime(controller.getTimeLeft());
			cout << endl;
			this_thread::sleep_for(chrono::milliseconds(30));
		}

		if (switchedOff)
		{
			cout << "\t [Контролер] Час вичерпано - вентилятор автоматично ВІДКЛЮЧЕНО." << endl;
			return;
		}
	}
	cout << "\t --- Імітацію завершено, вентилятор ще працює ---" << endl;
}

void Fan::show() const
{
	cout << "\n\t==== Вентилятор \"" << model << "\" ====" << endl;
	motor.show();
	controller.show();
	remote.show();
	cout << "\t=================================" << endl;
}
