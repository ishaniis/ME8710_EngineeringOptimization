/*

Source File
"FlightModels.cpp"

by Cameron J. Turner
Copyright 2020

Version 1.0

*/


/*

	Include Files

*/

#include "FlightModels.h"

double Density(double z, double &P, double &T)
{
	//  Define Variables
	double h = (Re/1000)*(z / 1000)/(Re/1000+z/1000);	//  Convert the altitude to geopotential height (km)
	double rho;											//  Ambient Air Density (kg/m^3)
	double T1, T2, T3, T4, T5, T6, T7;					//  Boundary Temperatures (K)
	double P1, P2, P3, P4, P5, P6, P7;					//	Boundary Pressures (Pa)


	//  Atmospheric Model
	if (h <= 11) {										//  Below 11 km
		T = T0 - 6.5 * h;
		P = P0 * (pow((T0 / T),(34.1632 / -6.5)));
	}
	else if ((h > 11) && (h <= 20)) {					//  11 km to 20 km
		T1 = T0 - 6.5 * 11;
		P1 = P0 * (pow((T0 / T1),(34.1632 / -6.5)));
		T = T1;
		P = P1 * exp(-34.1632 * (h - 11) / T);
	}
	else if ((h > 20) && (h <= 32)) {					//  20 km to 32 km
		T1 = T0 - 6.5 * 11;
		P1 = P0 * (pow((T0 / T1),(34.1632 / -6.5))); 
		T2 = T1;
		P2 = P1 * exp(-34.1632 * (20 - 11) / T1);
		T = T2 +1 * (h-20);
		P = P2 * (pow((T2 / T),(34.1632)));
	}
	else if ((h > 32) && (h <= 47)) {					//  32 km to 47 km
		T1 = T0 - 6.5 * 11;
		P1 = P0 * (pow((T0 / T1),(34.1632 / -6.5)));
		T2 = T1;
		P2 = P1 * exp(-34.1632 * (20 - 11) / T1);
		T3 = T2 + 1 * (32 - 20);
		P3 = P2 * (pow((T2 / T3),(34.1632)));
		T = T3 + 2.8 * (h - 32);
		P = P3 * (pow((T3 / T),(34.1632/2.8)));
	}
	else if ((h > 47) && (h <= 51)) {					//  47 km to 51 km
		T1 = T0 - 6.5 * 11;
		P1 = P0 * (pow((T0 / T1),(34.1632 / -6.5)));
		T2 = T1;
		P2 = P1 * exp(-34.1632 * (20 - 11) / T1);
		T3 = T2 + 1 * (32 - 20);
		P3 = P2 * (pow((T2 / T3),(34.1632)));
		T4 = T3 + 2.8 * (47 - 32);
		P4 = P3 * (pow((T3 / T4),(34.1632 / 2.8)));
		T = T4;
		P = P4 * exp(-34.1632 * (h - 47) / T);
	}
	else if ((h > 51) && (h <= 71)) {					//  51 km to 71 km
		T1 = T0 - 6.5 * 11;
		P1 = P0 * (pow((T0 / T1),(34.1632 / -6.5)));
		T2 = T1;
		P2 = P1 * exp(-34.1632 * (20 - 11) / T1);
		T3 = T2 + 1 * (32 - 20);
		P3 = P2 * (pow((T2 / T3),(34.1632)));
		T4 = T3 + 2.8 * (47 - 32);
		P4 = P3 * (pow((T3 / T4),(34.1632 / 2.8)));
		T5 = T4;
		P5 = P4 * exp(-34.1632 * (51 - 47) / T5);
		T = T5 - 2.8 * (h - 51);
		P = P5 * (pow((T5 / T),(34.1632 / -2.8)));
	}
	else if ((h > 71) && (h <= 86)) {					//  71 km to 86 km
		T1 = T0 - 6.5 * 11;
		P1 = P0 * (pow((T0 / T1),(34.1632 / -6.5)));
		T2 = T1;
		P2 = P1 * exp(-34.1632 * (20 - 11) / T1);
		T3 = T2 + 1 * (32 - 20);
		P3 = P2 * (pow((T2 / T3),(34.1632)));
		T4 = T3 + 2.8 * (47 - 32);
		P4 = P3 * (pow((T3 / T4),(34.1632 / 2.8)));
		T5 = T4;
		P5 = P4 * exp(-34.1632 * (51 - 47) / T5);
		T6 = T5 - 2.8 * (71 - 51);
		P6 = P5 * (pow((T5 / T6),(34.1632 / -2.8)));
		T = T6 - 2.0 * (h - 71);
		P = P6 * (pow((T6 / T),(34.1632 / -2.0)));
	}
	else {												//  86 km to 1000 km
		T1 = T0 - 6.5 * 11;
		P1 = P0 * (pow((T0 / T1),(34.1632 / -6.5)));
		T2 = T1;
		P2 = P1 * exp(-34.1632 * (20 - 11) / T1);
		T3 = T2 + 1 * (32 - 20);
		P3 = P2 * (pow((T2 / T3),(34.1632)));
		T4 = T3 + 2.8 * (47 - 32);
		P4 = P3 * (pow((T3 / T4),(34.1632 / 2.8)));
		T5 = T4;
		P5 = P4 * exp(-34.1632 * (51 - 47) / T5);
		T6 = T5 - 2.8 * (71 - 51);
		P6 = P5 * (pow((T5 / T6),(34.1632 / -2.8)));
		T7 = T6 - 2.0 * (86 - 71);
		P7 = P6 * (pow((T6 / T7),(34.1632 / -2.0)));
		if (h <= 1000) {
			T = T7 + (1000 - T7) * (h - 86) / (1000 - 86);
			P = P7 - P7 * (h - 86) / (1000 - 86);
		}
		else {											//  Above 1000 km
			T = 1000;
			P = 0;
		}
	}


	//  Calculate Density
	rho = (mol * P) / (R * T);

	return rho;
}

double WaveDrag(double v, double T)
{
	//  Define Variables
	double cs = sqrt(1.4 * 287 * T);					//  Speed of Sound at the current temperature
	double MACH = v / cs;								//  Mach Number
	double CD;											//  Effective Drag Coefficient


	//  Determine Wave Drag Coefficient
	if (MACH < 1) {
		CD = CD0 / sqrt(1 - pow(MACH,2));				//  Prandtl-Glauert Rule
	}
	else if(MACH ==1) {
		CD = CD0 / sqrt(1 - pow((MACH-0.001),2));		//  Prandtl-Glauert Rule Modified to Avoid Singularity
	}
	else {
		CD = CD0 / sqrt(pow(MACH,2) - 1);				//  Laitone's Rule
	}

	return CD;
}

double Thrust(double t, dVector<double> &RocketDefinition, dMatrix<double> &RocketData)
{
	//  Define Variables
	double Thrust = 0.0;								//  Local Storage of Thrust Value (N)
	double StagePresent, EngineType, EngineThrust;		//  Local Storage of the Presence of a Stage (0 or 1), Type of Engine, and Engine Thrust
	double Throttle;									//  Throttle Value


	//  Calculate Thrust Due to Boosters
	if (RocketDefinition[1] > 0) {						//  Determine if Boosters are Present
		if(t <= RocketData[RocketDefinition[2]-1][9]) Thrust = Thrust + RocketDefinition[1] * RocketData[RocketDefinition[2]-1][5];
	}


//	cout << "Booster Thrust = " << Thrust << endl;

	//  Calculate Thrust due to Stage
	if ((t >= RocketDefinition[18]) && (t < RocketDefinition[30])) {		//  First Stage Nominal Thrust (N)
		
		//  Define for readability
		StagePresent = RocketDefinition[3];
		EngineType = RocketDefinition[5];
		EngineThrust = RocketData[RocketDefinition[4] - FirstOffset][5];

		
		//  Add Stage Thrust
		Thrust = Thrust + StagePresent*EngineType*EngineThrust;

				
		//  Determine Throttle Setting (First Stage Only)
		Throttle = ThrottleCalc(t, RocketDefinition);


//		cout << "Booster+main Thrust = " << Thrust << endl;
//		cout << "Throttle = " << Throttle << endl;
	

		//  Modify Thrust by Throttle Setting
		Thrust = Thrust * Throttle;


	}
	else if ((t >= RocketDefinition[30]) && (t < RocketDefinition[32])) {	//  Second Stage Nominal Thrust (N)

		if (RocketDefinition[6] > 0) {
			//  Define for readability
			StagePresent = RocketDefinition[6];
			EngineType = RocketDefinition[8];
			EngineThrust = RocketData[RocketDefinition[7] - SecondOffset][5];


			//  Add Stage 2 Thrust
			Thrust = Thrust + StagePresent * EngineType * EngineThrust;
		}
	}
	else if ((t >= RocketDefinition[34]) && (t < RocketDefinition[36])) {	//  Third Stage Nominal Thrust (N)

		if (RocketDefinition[9] > 0) {
			//  Define for readability
			StagePresent = RocketDefinition[9];
			EngineType = RocketDefinition[11];
			EngineThrust = RocketData[RocketDefinition[10] - SecondOffset][5];


			//  Add Stage 3 Thrust
			Thrust = Thrust + StagePresent * EngineType * EngineThrust;
		}
	}
	else if ((t >= RocketDefinition[38]) && (t < RocketDefinition[40])) {	//  Fourth Stage Nominal Thrust (N)

		if (RocketDefinition[12] > 0) {
			//  Define for readability
			StagePresent = RocketDefinition[12];
			EngineType = RocketDefinition[14];
			EngineThrust = RocketData[RocketDefinition[13] - SecondOffset][5];


			//  Add Stage 4 Thrust
			Thrust = Thrust + StagePresent * EngineType * EngineThrust;
		}
	}
	else if ((t >= RocketDefinition[42]) && (t < RocketDefinition[44])) {	//  Fifth Stage Nominal Thrust (N)

		if (RocketDefinition[15]) {
			//  Define for readability
			StagePresent = RocketDefinition[15];
			EngineType = RocketDefinition[17];
			EngineThrust = RocketData[RocketDefinition[16] - SecondOffset][5];


			//  Add Stage 5 Thrust
			Thrust = Thrust + StagePresent * EngineType * EngineThrust;
		}
	}

//	cout << "Thrust = " << Thrust << endl;
	//  Thrust 
	return Thrust;
}

double ThrottleCalc(double t, dVector<double>& RocketDefinition)
{
	//  Define Variables
	double Throttle = 0.0;												//  Throttle Value


	//  Define Throttle Setting
	if (RocketDefinition[0] >= 1) {
		if ((t >= RocketDefinition[18]) && (t < RocketDefinition[28])) {
			//  Define Throttle Equation
			if ((t >= RocketDefinition[18]) && (t <= RocketDefinition[20])) Throttle = 1.0;
			if ((t >= RocketDefinition[20]) && (t <= RocketDefinition[22])) 
				Throttle = 1.0 - (1.0 - RocketDefinition[23]) * (t - RocketDefinition[20]) / (RocketDefinition[22] - RocketDefinition[20]);
			if ((t >= RocketDefinition[22]) && (t <= RocketDefinition[24])) Throttle = RocketDefinition[23];
			if ((t >= RocketDefinition[24]) && (t <= RocketDefinition[26])) 
				Throttle = RocketDefinition[23] + (1.0 - RocketDefinition[23]) * (t - RocketDefinition[24]) / (RocketDefinition[26] - RocketDefinition[24]);
			if ((t >= RocketDefinition[26]) && (t <= RocketDefinition[28])) Throttle = 1.0;
		}
		if ((t >= RocketDefinition[30]) && (t < RocketDefinition[32])) Throttle = 1.0;
		if ((t >= RocketDefinition[34]) && (t < RocketDefinition[36])) Throttle = 1.0;
		if ((t >= RocketDefinition[38]) && (t < RocketDefinition[40])) Throttle = 1.0;
		if ((t >= RocketDefinition[42]) && (t < RocketDefinition[44])) Throttle = 1.0;
	}


	//  Return Throttle Setting
	return Throttle;
}

double GrossVehicleMass(dVector<double> &RocketDefinition, dMatrix<double> &RocketData)
{
	//  Define Variables
	double Mass = 0.0;
	double Temp;


	//  Incorporate Payload + 10% for structure
	Mass = Mass + 1.1 * RocketDefinition[47];
	

	//  Incorporate Boosters
	if (RocketDefinition[1] > 0) {
		Mass = Mass + RocketDefinition[1] * RocketData[RocketDefinition[2] - 1][10];
		RocketDefinition.push_back(RocketDefinition[1] * RocketData[RocketDefinition[2] - 1][10]);
		RocketDefinition.push_back(RocketDefinition[1] * RocketData[RocketDefinition[2] - 1][6]);
		//  Add Booster Gross Mass * Number of Boosters
	}
	else {
		RocketDefinition.push_back(0.0);		//  Null Boosters Stage Wet Mass
		RocketDefinition.push_back(0.0);		//  Null Boosters Stage Dry Mass
	}
//	cout << "Booster Mass = " << Mass << endl;


	//  Incorporate Stage 1 + 8% for structure
	Temp = (RocketDefinition[20] - RocketDefinition[18]) * RocketDefinition[19] 
		+ (RocketDefinition[28] - RocketDefinition[26]) * RocketDefinition[27]
		+ (RocketDefinition[26] - RocketDefinition[20]) * RocketDefinition[25]
		+ 0.5 * ((RocketDefinition[26] - RocketDefinition[24]) 
		+ (RocketDefinition[22] - RocketDefinition[20])) * ((RocketDefinition[19] - RocketDefinition[25]));	
		//  Determine Equivalent Burn Time at Full Thrust
	Temp = RocketDefinition[3] * RocketData[RocketDefinition[4] - FirstOffset][8] * Temp;					
		//  Determine Required Fuel for Burn Time at Full Throttle
	Mass = Mass + RocketDefinition[3] * RocketDefinition[5] * RocketData[RocketDefinition[4] - FirstOffset][6] 
		+ 1.08 * RocketDefinition[5] * Temp;	
	RocketDefinition.push_back(RocketDefinition[3] * RocketDefinition[5] * RocketData[RocketDefinition[4] - FirstOffset][6]
		+ 1.08 * RocketDefinition[5] * Temp);
		//  Add First Stage Engine Mass and Fuel/Structure Mass
	RocketDefinition.push_back(RocketDefinition[3] * RocketDefinition[5] * RocketData[RocketDefinition[4] - FirstOffset][6]
		+ 0.08 * RocketDefinition[5] * Temp);
		//  Store First Stage Dry Mass (kg) w/o Fuel
//	cout << "Booster+Main Mass = " << Mass << endl;


	//  Incorporate Stage 2 + 8% for Structure
	if (RocketDefinition[6] > 0) {
		Temp = (RocketDefinition[32] - RocketDefinition[30]) * RocketData[RocketDefinition[7] - SecondOffset][8] * 1.0;
		//  Determine Required Fuel for Burn Time at Full Throttle
		Mass = Mass + RocketDefinition[8] * RocketData[RocketDefinition[7] - SecondOffset][6]
			+ 1.08 * RocketDefinition[8] * Temp;
		RocketDefinition.push_back(RocketDefinition[8] * RocketData[RocketDefinition[7] - SecondOffset][6]
			+ 1.08 * RocketDefinition[8] * Temp);
		//  Add Second Stage Engine Mass and Fuel/Structure Mass 
		RocketDefinition.push_back(RocketDefinition[8] * RocketData[RocketDefinition[7] - SecondOffset][6]
			+ 0.08 * RocketDefinition[8] * Temp);
		//  Store Second Stage Dry Mass (kg) w/o Fuel 
	}
	else {
		RocketDefinition.push_back(0.0);		//  Null Second Stage Wet Mass
		RocketDefinition.push_back(0.0);		//  Null Second Stage Dry Mass
	}
//	cout << "Booster+Main+2nd Mass = " << Mass << endl;


	//  Incorporate Stage 3 + 8% for Structure
	if (RocketDefinition[9] > 0) {
		Temp = (RocketDefinition[36] - RocketDefinition[34]) * RocketData[RocketDefinition[10] - SecondOffset][8] * 1.0;
		//  Determine Required Fuel for Burn Time at Full Throttle
		Mass = Mass + RocketDefinition[11] * RocketData[RocketDefinition[10] - SecondOffset][6]
			+ 1.08 * RocketDefinition[11] * Temp;
		RocketDefinition.push_back(RocketDefinition[11] * RocketData[RocketDefinition[10] - SecondOffset][6]
			+ 1.08 * RocketDefinition[11] * Temp);
		//  Add Third Stage Engine Mass and Fuel/Structure Mass 
		RocketDefinition.push_back(RocketDefinition[11] * RocketData[RocketDefinition[10] - SecondOffset][6]
			+ 0.08 * RocketDefinition[11] * Temp);
		//  Store Third Stage Dry Mass (kg) w/o Fuel
	}
	else {
		RocketDefinition.push_back(0.0);		//  Null Third Stage Wet Mass
		RocketDefinition.push_back(0.0);		//  Null Third Stage Dry Mass
	}


	//  Incorporate Stage 4 + 8% for Structure
	if (RocketDefinition[12] > 0) {
		Temp = (RocketDefinition[40] - RocketDefinition[38]) * RocketData[RocketDefinition[13] - SecondOffset][8] * 1.0;
		//  Determine Required Fuel for Burn Time at Full Throttle
		Mass = Mass + RocketDefinition[14] * RocketData[RocketDefinition[13] - SecondOffset][6]
			+ 1.08 * RocketDefinition[14] * Temp;
		RocketDefinition.push_back(RocketDefinition[14] * RocketData[RocketDefinition[13] - SecondOffset][6]
			+ 1.08 * RocketDefinition[14] * Temp);
		//  Add Fourth Stage Engine Mass and Fuel/Structure Mass 
		RocketDefinition.push_back(RocketDefinition[14] * RocketData[RocketDefinition[13] - SecondOffset][6]
			+ 0.08 * RocketDefinition[14] * Temp);
		//  Store Fourth Stage Dry Mass (kg) w/o Fuel
	}
	else {
		RocketDefinition.push_back(0.0);		//  Null Fourth Stage Wet Mass
		RocketDefinition.push_back(0.0);		//  Null Fourth Stage Dry Mass
	}


	//  Incorporate Stage 5 + 8% for Structure
	if (RocketDefinition[15] > 0) {
		Temp = (RocketDefinition[44] - RocketDefinition[42]) * RocketData[RocketDefinition[16] - SecondOffset][8] * 1.0;
		//  Determine Required Fuel for Burn Time at Full Throttle
		Mass = Mass + RocketDefinition[17] * RocketData[RocketDefinition[13] - SecondOffset][6]
			+ 1.08 * RocketDefinition[17] * Temp;
		RocketDefinition.push_back(RocketDefinition[17] * RocketData[RocketDefinition[16] - SecondOffset][6]
			+ 1.08 * RocketDefinition[17] * Temp);
		//  Add Fifth Stage Engine Mass and Fuel/Structure Mass 
		RocketDefinition.push_back(RocketDefinition[17] * RocketData[RocketDefinition[16] - SecondOffset][6]
			+ 0.08 * RocketDefinition[17] * Temp);
		//  Store Fifth Stage Dry Mass (kg) w/o Fuel
	}
	else {
		RocketDefinition.push_back(0.0);		//  Null Fifth Stage Wet Mass
		RocketDefinition.push_back(0.0);		//  Null Fifth Stage Dry Mass
	}


	//  Include Stage Seperation Times
	if (RocketDefinition[1] > 0) {				//  Booster Separation Time (sec)
		RocketDefinition.push_back(RocketData[RocketDefinition[2] - 1][9] + 0.5);
	}
	else {
		RocketDefinition.push_back(0);
	}
	if (RocketDefinition[3] > 0) {				//  First Stage Separation Time (sec)
		RocketDefinition.push_back(RocketDefinition[28] + 0.5);
	}
	else {
		RocketDefinition.push_back(0);
	}
	if (RocketDefinition[6] > 0) {				//  Second Stage Separation Time (sec)
		RocketDefinition.push_back(RocketDefinition[32] + 0.5);
	}
	else {
		RocketDefinition.push_back(0);
	}
	if (RocketDefinition[9] > 0) {				//  Third Stage Separation Time (sec)
		RocketDefinition.push_back(RocketDefinition[36] + 0.5);
	}
	else {
		RocketDefinition.push_back(0);
	}
	if (RocketDefinition[12] > 0) {				//  Fourth Stage Separation Time (sec)
		RocketDefinition.push_back(RocketDefinition[40] + 0.5);
	}
	else {
		RocketDefinition.push_back(0);
	}
	if (RocketDefinition[15] > 0) {				//  Fifth Stage Separation Time (sec)
		RocketDefinition.push_back(RocketDefinition[44] + 0.5);
	}
	else {
		RocketDefinition.push_back(0);
	}


	//  Return Resulting Gross Mass
	return Mass;
}

double Fdrag(double rho, double CD, double v, dVector<double>& RocketDefinition, dMatrix<double>& RocketData)
{
	//  Define Variables
	double Drag = 0.0;						//  Resulting Drag Force
	double Area = 0.0;						//  Temporary Area Calculation (m^2)


	//  Calculate Area
	//  Calculate Booster Area
	if (RocketDefinition[1] > 0) Area = 0.25 * pi * RocketDefinition[1] * pow(RocketData[RocketDefinition[2] - 1][7],2);


	//  Calculate Main Core Area
	Area = Area + 0.25 * pi * pow(RocketDefinition[46], 2);


	//  Calculate Drag
	Drag = 0.5 * rho * CD * Area * pow(v, 2);


	//  Assign Sign to Drag
	if (v > 0) Drag = -1.0 * Drag;


	//  Report Resulting Drag Force
	return Drag;
}

double Gravity(double z)
{
	//  Define Constants
	double g;								//  Current acceleration due to gravity


	//  Calculate g
	g = mu / pow(Re + z, 2);


	return g;
}

double MassChange(double t, dVector<double> &RocketDefinition, dMatrix<double> &RocketData)
{
	//  Define Constants
	double dMass = 0.0;						//  Change in mass per second at time t


	//  Change in Booster Mass
	if (RocketDefinition[1] > 0) {
		if (t < RocketData[RocketDefinition[2] - 1][9]) {
			dMass = dMass + RocketData[RocketDefinition[2] - 1][8] * RocketDefinition[1];
		}
	}


	//  Change in First Stage Mass
	if (RocketDefinition[3] > 0) {
		if ((t < RocketDefinition[28]) && (t >= RocketDefinition[18])) {
			dMass = dMass + RocketData[RocketDefinition[4] - FirstOffset][8] * RocketDefinition[5] * ThrottleCalc(t, RocketDefinition);
		}
	}

	
	//  Change in Second Stage Mass
	if (RocketDefinition[6] > 0) {
		if ((t < RocketDefinition[32]) && (t >= RocketDefinition[30])) {
			dMass = dMass + RocketData[RocketDefinition[7] - SecondOffset][8] * RocketDefinition[8] * ThrottleCalc(t, RocketDefinition);
		}
	}


	//  Change in Third Stage Mass
	if (RocketDefinition[9] > 0) {
		if ((t < RocketDefinition[36]) && (t >= RocketDefinition[34])) {
			dMass = dMass + RocketData[RocketDefinition[10] - SecondOffset][8] * RocketDefinition[11] * ThrottleCalc(t, RocketDefinition);
		}
	}


	//  Change in Fourth Stage Mass
	if (RocketDefinition[12] > 0) {
		if ((t < RocketDefinition[40]) && (t >= RocketDefinition[38])){
			dMass = dMass + RocketData[RocketDefinition[13] - SecondOffset][8] * RocketDefinition[14] * ThrottleCalc(t, RocketDefinition);
		}
	}


	//  Change in Fifth Stage Mass
	if (RocketDefinition[15] > 0) {
		if ((t < RocketDefinition[44]) && (t >= RocketDefinition[42])) {
			dMass = dMass + RocketData[RocketDefinition[16] - SecondOffset][8] * RocketDefinition[17] * ThrottleCalc(t, RocketDefinition);
		}
	}


	//  Include Stage Seperation Values
	if ((t >= (RocketDefinition[60] - 0.5 * dt)) && ((t <= RocketDefinition[60] + 0.5 * dt)) && (RocketDefinition[1] > 0)) {
		dMass = dMass + RocketDefinition[49] / dt;		//  Booster Dry Mass
		cout << endl << "Booster Separation" << endl;
	}
	if ((t >= (RocketDefinition[61] - 0.5 * dt)) && (t <= (RocketDefinition[61] + 0.5 * dt)) && (RocketDefinition[3] > 0)) {
		dMass = dMass + RocketDefinition[51] / dt;							//  First Stage Dry Mass
		cout << endl << "First Stage Separation" << endl;
	}
	if ((t >= (RocketDefinition[62] - 0.5 * dt)) && ((t <= RocketDefinition[62] + 0.5 * dt)) && (RocketDefinition[6] > 0)) {
		dMass = dMass + RocketDefinition[53] / dt;							//  Second Stage Dry Mass
		cout << endl << "Second Stage Separation" << endl;
	}
	if ((t >= (RocketDefinition[63] - 0.5 * dt)) && ((t <= RocketDefinition[63] + 0.5 * dt)) && (RocketDefinition[9] > 0)) {
		dMass = dMass + RocketDefinition[55] / dt;						//  Third Stage Dry Mass
		cout << endl << "Third Stage Separation" << endl;
	}
	if ((t >= (RocketDefinition[64] - 0.5 * dt)) && ((t <= RocketDefinition[64] + 0.5 * dt)) && (RocketDefinition[12] > 0)) {
		dMass = dMass + RocketDefinition[57] / dt;						//  Fourth Stage Dry Mass
		cout << endl << "Fourth Stage Separation" << endl;
	}
	if ((t >= (RocketDefinition[65] - 0.5 * dt)) && ((t <= RocketDefinition[65] + 0.5 * dt)) && (RocketDefinition[15] > 0)) {
		dMass = dMass + RocketDefinition[59] / dt;						//  Fifth Stage Dry Mass
		cout << endl << "Fifth Stage Separation" << endl;
	}
	

	//  Return Change in Mass/sec at time t
	return dMass;
}


