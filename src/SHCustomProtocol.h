#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

// #ifndef MAIN_APP
// #define MAIN_APP
// #include <import_utils.h>
#include <Arduino.h>
#include <ui.h>
#include "SHCustomProtocol.h"
#include <Ticker.h>

Ticker ticker;

class SHCustomProtocol {
private:

public:

	/*
	CUSTOM PROTOCOL CLASS
	SEE https://github.com/zegreatclan/SimHub/wiki/Custom-Arduino-hardware-support

	GENERAL RULES :
		- ALWAYS BACKUP THIS FILE, reinstalling/updating SimHub would overwrite it with the default version.
		- Read data AS FAST AS POSSIBLE in the read function
		- NEVER block the arduino (using delay for instance)
		- Make sure the data read in "read()" function READS ALL THE DATA from the serial port matching the custom protocol definition
		- Idle function is called hundreds of times per second, never use it for slow code, arduino performances would fall
		- If you use library suspending interrupts make sure to use it only in the "read" function when ALL data has been read from the serial port.
			It is the only interrupt safe place

	COMMON FUNCTIONS :
		- FlowSerialReadStringUntil('\n')
			Read the incoming data up to the end (\n) won't be included
		- FlowSerialReadStringUntil(';')
			Read the incoming data up to the separator (;) separator won't be included
		- FlowSerialDebugPrintLn(string)
			Send a debug message to simhub which will display in the log panel and log file (only use it when debugging, it would slow down arduino in run conditions)
	*/

	// Global variables

	#define IMAGE_BUF_SIZE 2048

	uint32_t deltaTime = 0; // Time since last timer call
	uint32_t nextCall = 0;  // Time until next timer call
	uint32_t lastTime = 0;  // Last recorded time

	// bool gameRunning = false;

	// Called when starting the arduino (setup method in main sketch)
	void setup()
	{
		lastTime = millis();
		smartdisplay_init();
		smartdisplay_lcd_set_backlight(1);
		ui_init();
	}

	void set_ui_value(char * value, String serialRead)
	{
		strcpy(value, serialRead.c_str());
	}

	/**
	 *
	 *
	    format(isnull([DataCorePlugin.GameData.NewData.SpeedKmh],0),'0') + ';' +
		isnull([DataCorePlugin.GameData.NewData.Gear],'N') + ';' +
		format(isnull([Rpms],0),'0') + ';' +
		left(isnull([CurrentLapTime],'00:00:00'),3,8) + ';' +
		left(isnull([LastLapTime],'00:00:00'),3,8) + ';' +
		left(isnull([BestLapTime],'00:00:00'),3,8) + ';' +
		format(isnull([PersistantTrackerPlugin.SessionBestLiveDeltaSeconds],0),'0.000') + ';' +
		abs(format(isnull([BrakeBias], 0), '00.0')) + ';' +
		format(isnull([ERSPercent], 0),'0') + ';' +
		format(isnull([GameRawData.Tyre.TempFrontLeft],0), '00.0') + ';' +
		format(isnull([GameRawData.Tyre.TempFrontRight],0), '00.0') + ';' +
		format(isnull([GameRawData.Tyre.TempRearLeft],0), '00.0') + ';' +
		format(isnull([GameRawData.Tyre.TempRearRight],0), '00.0') + ';' +
		format(isnull([GameRawData.Tyre.WearFrontLeft],0), '00.0') + ';' +
		format(isnull([GameRawData.Tyre.WearFrontRight],0), '00.0') + ';' +
		format(isnull([GameRawData.Tyre.WearRearLeft],0), '00.0') + ';' +
		format(isnull([GameRawData.Tyre.WearRearRight],0), '00.0') + ';' +
		IF(isnull([GameData.NewData.FrontWingLeftDamage],0) > 0 || isnull([GameData.NewData.FrontWingRightDamage],0) > 0, '1', '0') + ';' +
		IF(isnull([GameData.NewData.RearWingDamage],0) > 0, '1', '0') + ';' +
		IF(isnull([GameData.NewData.TyreWearFrontLeft],0) > 50 || isnull([GameData.NewData.TyreWearFrontRight],0) > 50 || isnull([GameData.NewData.TyreWearRearLeft],0) > 50 || isnull([GameData.NewData.TyreWearRearRight],0) > 50, '1', '0') + ';' +
		isnull([GameRawData.Physics.EngineBrake], '0') + ';' +
		isnull([GameRawData.Physics.ErsHeatCharging], '0') + ';' +
		isnull([GameRawData.Physics.ErsRecoveryLevel], '0') + ';' +
		isnull([GameRawData.Physics.ErsPowerLevel], '0') + ';' +
		isnull([Flag_Yellow]) + ';' +
		isnull([DataCorePlugin.GameRunning]) + ';'

	 */

	// Called when new data is coming from computer
	void read()
	{
		// speed
		strcpy(speed, FlowSerialReadStringUntil(';').c_str());

		// gear
		strcpy(gear, FlowSerialReadStringUntil(';').c_str());

		// rpms
		strcpy(rpmsValue, FlowSerialReadStringUntil(';').c_str());

		// lap time current
		strcpy(currentLapTime, FlowSerialReadStringUntil(';').c_str());

		// last lap time
		strcpy(lastLapTime, FlowSerialReadStringUntil(';').c_str());

		// best lap time
		strcpy(bestLapTime, FlowSerialReadStringUntil(';').c_str());

		// delta time
		strcpy(sessionBestLiveDeltaSeconds, FlowSerialReadStringUntil(';').c_str());

		// brake bias
		strcpy(brakeBias, FlowSerialReadStringUntil(';').c_str());

		//  ERS percent stored
		strcpy(ersPercent, FlowSerialReadStringUntil(';').c_str());

		// tyre temps
		strcpy(tyreTempFrontLeft, FlowSerialReadStringUntil(';').c_str());
		strcpy(tyreTempFrontRight, FlowSerialReadStringUntil(';').c_str());
		strcpy(tyreTempRearLeft, FlowSerialReadStringUntil(';').c_str());
		strcpy(tyreTempRearRight, FlowSerialReadStringUntil(';').c_str());

		// tyre wear
		strcpy(tyreWearFrontLeft, FlowSerialReadStringUntil(';').c_str());
		strcpy(tyreWearFrontRight, FlowSerialReadStringUntil(';').c_str());
		strcpy(tyreWearRearLeft, FlowSerialReadStringUntil(';').c_str());
		strcpy(tyreWearRearRight, FlowSerialReadStringUntil(';').c_str());

		// Front Wing DMG
		strcpy(frontWingDamage, FlowSerialReadStringUntil(';').c_str());

		// rear wing dmg
		strcpy(rearWingDamage, FlowSerialReadStringUntil(';').c_str());

		// tyre overwear / dmg
		// strcpy(tyreDamage, FlowSerialReadStringUntil(';').c_str());
		FlowSerialReadStringUntil(';');
		
		// Engine Brake
		strcpy(engBrake, FlowSerialReadStringUntil(';').c_str());

		// MGU-H Mode / ErsHeatCharging (Battery (1) / motor (0) )
		strcpy(mgu_h_mode, FlowSerialReadStringUntil(';').c_str());

		// MGU-K recovery (ERS Recovery level)
		strcpy(mgu_k_recovery, FlowSerialReadStringUntil(';').c_str());

		// MGU-K delivery (ERS Power Level)
		strcpy(mgu_k_delivery, FlowSerialReadStringUntil(';').c_str());

		// Yellow Flag Active
		strcpy(flagWarning, FlowSerialReadStringUntil(';').c_str());

		// strcpy(tcLevel, FlowSerialReadStringUntil(';').c_str());
		// strcpy(tcActive, FlowSerialReadStringUntil(';').c_str());
		// strcpy(absLevel, FlowSerialReadStringUntil(';').c_str());
		// strcpy(absActive, FlowSerialReadStringUntil(';').c_str());
		// strcpy(isTCCutNull, FlowSerialReadStringUntil(';').c_str());
		// strcpy(tcTcCut, FlowSerialReadStringUntil(';').c_str());
		// strcpy(lapInvalidated, FlowSerialReadStringUntil(';').c_str());

		// Is game running?
		strcpy(gameRunning, FlowSerialReadStringUntil('\n').c_str());


		
		// strcpy(differential, FlowSerialReadStringUntil(';').c_str());
		
	}
	// Called once per arduino loop, timing can't be predicted, 
	// but it's called between each command sent to the arduino
	/**
	 * Colors
	 * DRS Available: (bg_color: D0EA85, 255), (text_color: 000000, 255)
	 * DRS Enabled: (bg_color: 79F86F,255), (text_color:ffffff, 255)
	 * Red flag: (bg_color: ED3636, 255)
	 * Yellow Flag: (bg_color: D0EA85, 255)
	 */

	#define SCR_IDLE 0
	#define SCR_LOAD 1
	#define SCR_RUNNING 2

	void loop()
	{
		uint32_t currentTime = millis();
		deltaTime = currentTime - lastTime;

		if (atoi(gameRunning) == 1) {
			if (current_screen() == SCR_IDLE) {
				FlowSerialDebugPrintLn("Game Running Found, Changing to Load Screen->Running");
				set_loading_scr();

				nextCall = lv_timer_handler(); // Assume lv_timer_handler returns the time until the next call
				lastTime = currentTime;

				ticker.once(2, set_running_scr);
			}
			if (deltaTime >= nextCall && current_screen() == SCR_RUNNING)
			{
				// update
				updateUI();

				nextCall = lv_timer_handler(); // Assume lv_timer_handler returns the time until the next call
				lastTime = currentTime;		   // Reset deltaTime by updating lastTime to the current time
			}
		} 
		
		else 
		{
			if (current_screen() == SCR_RUNNING) {
				FlowSerialDebugPrintLn("Game stopped Running, Changing to idle");
				set_idle_scr();
			}

			nextCall = lv_timer_handler(); // Assume lv_timer_handler returns the time until the next call
			lastTime = currentTime;	
		}
		
	}

	// Called once between each byte read on arduino,
	// THIS IS A CRITICAL PATH :
	// AVOID ANY TIME CONSUMING ROUTINES !!!
	// PREFER READ OR LOOP METHOS AS MUCH AS POSSIBLE
	// AVOID ANY INTERRUPTS DISABLE (serial data would be lost!!!)
	void idle() {
	}
};

#endif