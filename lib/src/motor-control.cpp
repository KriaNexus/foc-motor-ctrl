/*
 * Copyright (C) 2023 Advanced Micro Devices, Inc.
 * SPDX-License-Identifier: MIT
 */

//#include "logging.hpp"
#include "motor-control/motor-control.hpp"
/* TODO: implement
#include "adchub.hpp"
#include "foc.hpp"
#include "sensors/sensor.hpp"
#include "pwm.hpp"
#include "mc_driver.hpp"
*/

/** TODO List:
 *   - Move fucntion definitions out of the class
 *   - Use smart pointers if make sense
 *   - populate InitConfig structure
 *	- If possible group the drivers specific init as sub strutures defined
 *	in respective drivers
 *   - Check Naming convention and use '_' after the specifier if required.
 */

using namespace std;

struct InitCofig {
	int foc_RampRate;
};

class MotorControlImpl : public MotorControl {
public:

	MotorControlImpl(int sessionId = 0, string configPath = DEFAULT_CONFIG_PATH):
		mSessionId(sessionId),
		mConfigPath(configPath)
		{
			parseConfig();
			// init all the driving classes
		}

	int getSpeed() override {

		return 0;
	}

	int getPosition() override {
		return 0;
	}

	int getTorque() override {
		return 0;
	}

	int getCurrent(ElectricalData type) override {
		return 0;
	}

	int getVoltage(ElectricalData type) override {
		return 0;
	}

	bool getFaultStatus(FaultType type) override {
		return false;
	}

	FocData getFocCalc() override {
		FocData data = {0};
		return data;
	}

	void SetSpeed(int speed) override {

	}

	void SetTorque(int torque) override {

	}

	void SetPosition(int position) override {

	}

	void SetGain(GainType gainController, int k_p, int k_i) override {

	}

	void SetGain(GainType gainController, int k_p, int k_i, int k_d) override {

	}


	void clearFaults() override {

	}

	void clearFaults(FaultCategory category) override {

	}

	int getSessionId () {
		return mSessionId;
	}

	~MotorControlImpl() {
		mSessionId =-1;
	}

private:
	int mSessionId;
	string mConfigPath;
	InitCofig mConfig;

	/* TODO: implement
	Sensor *mpSensor;
	FOCImpl *mpFoc;		// implement ramp_rate
	ADCHub *mpAdcHub;
	PWMImpl *mpPwm;
	*/

	/*
	 * Member functions
	 */
	void parseConfig() {
		// parse the config using mConfigPath
		// and fillup mCofig structure
	}

};

// Initialize the static member variable of the MotorControl class
MotorControl *MotorControl::mspInstance = nullptr;

MotorControl::~MotorControl()
{
	if (mspInstance) { /* sanity check, though not needed */
		delete mspInstance;
		mspInstance = nullptr;
	}
}

MotorControl *MotorControl::getMotorControlInstance(int sessionId,
						    string configPath)
{
	MotorControl *ptr = nullptr;
	if (mspInstance) {
		MotorControlImpl *impl_ptr = dynamic_cast<MotorControlImpl *>(mspInstance);
		if (impl_ptr->getSessionId() == sessionId) {
			// Check if it is called for same sessionId
			// TODO: Implement restriction for subsequent calls
			// here.
			ptr = mspInstance;
		}
	} else {
		mspInstance = new MotorControlImpl(sessionId, configPath);
		ptr = mspInstance;
	}
	return ptr;
}

