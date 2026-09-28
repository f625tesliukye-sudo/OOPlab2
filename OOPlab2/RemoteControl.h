#pragma once
#include <iostream>
#include <string>
#include "Controller.h"

/*------------------------------------------------
Клас, що описує один режим швидкості на пульті
(елемент масиву об'єктів)
------------------------------------------------*/
class SpeedLevel
{
private:
	std::string name;   // назва режиму
	int         rpm;    // швидкість, об/хв

public:
	SpeedLevel();
	SpeedLevel(const std::string& name, int rpm);

	void        set(const std::string& name, int rpm);
	std::string getName() const;
	int         getRpm() const;
	void        show() const;
};

/*------------------------------------------------
Клас ПУЛЬТ КЕРУВАННЯ: користувач працює лише з ним,
а він передає команди контролеру
------------------------------------------------*/
class RemoteControl
{
private:
	static const int LEVELS_COUNT = 3;

	Controller* controller;
	SpeedLevel  levels[LEVELS_COUNT];   // масив об'єктів: 3 режими швидкості
	int         speedStep;              // крок кнопок "+" / "-", об/хв

public:
	RemoteControl();
	explicit RemoteControl(Controller* controller);
	~RemoteControl();

	void attachController(Controller* c);
	void setLevel(int index, const std::string& name, int rpm);

	// кнопки пульта
	void pressPower();                    // вмикає/вимикає вентилятор
	bool selectLevel(int index);          // вибір режиму (0..2)
	bool setSpeed(int rpm);               // точне налаштування швидкості
	bool speedUp();                       // кнопка "+"
	bool speedDown();                     // кнопка "-"
	bool setShutdownTimer(int minutes);   // час відключення, хв
	void cancelShutdownTimer();           // скасувати відключення

	int  getLevelsCount() const;
	void show() const;
};
