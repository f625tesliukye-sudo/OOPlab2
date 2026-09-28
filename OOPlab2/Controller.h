#pragma once
#include <iostream>
#include <string>
#include "Motor.h"

class Controller
{
private:
	Motor* motor;       
	int    timerLeft;    
	bool   timerActive;  

public:
	static const int MAX_TIMER_SECONDS = 12 * 60 * 60;  

	Controller();
	explicit Controller(Motor* motor);
	~Controller();

	void attachMotor(Motor* m);

	void powerOn();                  
	void powerOff();                 
	bool setSpeed(int rpm);          

	bool setTimer(int seconds);     
	void cancelTimer();              
	bool tick(int seconds);          

	bool isRunning() const;
	int  getSpeed() const;
	int  getMinSpeed() const;
	int  getMaxSpeed() const;
	bool isTimerActive() const;
	int  getTimeLeft() const;

	static std::string formatTime(int seconds);  

	void show() const;
};
