/*

Source File
"RocketSim.cpp"

by Cameron J. Turner
Copyright 2020

Version 1.0

*/


/*

	Include Files

*/

//#pragma once
#include "RocketSim.h"


int main() 
{
	// Initialize Files as blank
	ofstream logout("log.txt", ios::out);			//  Log File for the Simulation
	logout.close();
	ofstream Rocketout("Rocket.txt", ios::out);		//  Data about the Rocket Configuration
	Rocketout.close();
	ofstream Telemetry("Telemetry.txt", ios::out);	//  Flight Telemetry
	Telemetry.close();

	ifstream Batch("Batch.txt", ios::in);			//  Open Batch Run File



	//	Variable Definitions
	dVector<double> RocketDefinition;				//	Defines the Parameters of the Rocket
	dVector<double> RocketPerformance;				
		RocketPerformance.resize(nRocketPerfRows);	//	Defines the Performance of the Rocket at a Timestep
	dMatrix<double> RocketData;						//  Loads Data from Existing Rocket Systems
	unsigned long long int N;						//	Confirms the number of cells defined in {RocketDefinition}
	double Temp;									//  Temporary Storage of Data
	double P = 0.0;									//  Temporary Storage of current Pressure (Pa)
	double T = 0.0;									//  Temporary Storage of current Temperature (K)
	double dMass;									//  Change in Mass of the vehicle during a time dt (kg)
	double time = 0.0;								//  Current time of the simulation (sec)
	dVector<double> BatchFile;						//  Defines the values of a Batch Run File
	int iBatch = 0;									//  iBatch serves as a counter to the Batch File


	//  Read Batch Run File
	do {
		Batch >> Temp;
		BatchFile.push_back(Temp);
	//	cout << BatchFile.size() << " " << BatchFile[BatchFile.size() - 1] << endl;
	} while (!Batch.eof());

	//	Run Menu to Generate Data
	if(BatchFile[0] == 0) N = RocketMenu(RocketDefinition);


	//  Load Rocket Data
	ifstream RocketIn("RocketData.txt", ios::in);
	RocketData.resize(nRocketRows, nRocketCols);
	for (int i = 0; i < nRocketRows; i++) {
		for (int j = 0; j < nRocketCols; j++) {
			RocketIn >> Temp;
			RocketData[i][j] = Temp;
		}
	}
	RocketIn.close();

	
	//	Simulate the Rocket Launch
	do {

		//  Open Files to Write Results
		logout.open("log.txt", ios::app);
		Telemetry.open("Telemetry.txt", ios::app);
		Rocketout.open("Rocket.txt", ios::app);


		//  Initiate Launch
		cout << "Begin Launch of Rocket " << iBatch + 1 << endl;


		//  Transfer Batch File to {RocketPerformance}
		if (BatchFile[0] != 0) {
			RocketDefinition.resize(BatchLength);
			for (int jBatch = 0; jBatch < BatchLength; jBatch++)
				RocketDefinition[jBatch] = BatchFile[iBatch * BatchSize + jBatch + 1];
			logout << "Running a Batch File - Rocket Design " << iBatch + 1 << endl << endl;
		}


		//  Set Initial Simulation Conditions	
		time = 0.0;												//  Set Initial Time in Simulation
		RocketPerformance[0] = time;							//  Simulation starts at time, t = 0 sec (Liftoff)
		RocketPerformance[1] = Thrust(0, RocketDefinition, RocketData);
																//  Initial Thrust at time, t = 0 sec (Liftoff)
		RocketPerformance[2] = GrossVehicleMass(RocketDefinition, RocketData);
																//  Initial Gross Mass at time, t = 0 sec (Liftoff)
		RocketPerformance[3] = z0;								//  Altitude of the Launch Pad at time, t = 0 sec (Liftoff)
		RocketPerformance[4] = 0.0;								//  Velocity of the rocket at time, t = 0 sec (Liftoff)
		RocketPerformance[6] = Density(RocketPerformance[3], P, T);
																//  Atmospheric Density at altitude at time, t = 0 sec (Liftoff)
		RocketPerformance[7] = P;								//  Atmospheric Pressure at altitude at time, t = 0 sec (Liftoff)
		RocketPerformance[8] = T;								//  Atmospheric Temperature at altitude at time, t = 0 sec (Liftoff)
		RocketPerformance[9] = WaveDrag(RocketPerformance[4], T);
																//  Current Coefficient of Drag using the WaveDrag Analysis at time, t = 0 sec (Liftoff)
		RocketPerformance[10] = Fdrag(RocketPerformance[6], RocketPerformance[9], RocketPerformance[4], RocketDefinition, RocketData);
																//  Current Drag Force at time, t = 0 sec (Liftoff)
		RocketPerformance[11] = Gravity(RocketPerformance[3]);
																//  Current Gravitational Acceleration at time, t = 0 sec (Liftoff)
		RocketPerformance[12] = 0.5 * RocketPerformance[6] * pow(RocketPerformance[4], 2);
																//  Dynamic Pressure on the rocket at time, t = 0 sec (Liftoff)
		RocketPerformance[13] = RocketPerformance[4] / sqrt(1.4 * 287 * RocketPerformance[8]);
																//  Mach Number of the rocket at time, t = 0 sec (Liftoff)
		RocketPerformance[5]  = (RocketPerformance[1] / RocketPerformance[2]) - RocketPerformance[11];
																//  Acceleration of the rocket at time, t = 0 sec (Liftoff)
		RocketPerformance[14] = pow(RocketPerformance[4], 2) / (Re + RocketPerformance[3]) - RocketPerformance[11] + LaunchTangentialVel;
																//  Necessary Centrifugal Acceleration to maintain orbit (Positive Value = Yes, Negative Value = no)
		RocketPerformance[15] = 0.0;							//  Change in Mass since Prior Step (kg)
		RocketPerformance[16] = RocketPerformance[3] / 1000;	//  Altitude (km)
		


		//  Print {RocketDefinition} to Log File
		logout << "{RocketDefintion} = {" << endl;
		for (unsigned long long int i = 0; i < RocketDefinition.size(); i++) {
			logout << RocketDefinition[i] << endl;
			Rocketout << RocketDefinition[i] << endl;
		}
		logout << " }" << endl << endl;


		//  Print Initial Rocket Launch Conditions to log.txt and telemetry.txt	
		//	logout << "Time(sec) Thrust(N) Mass(kg) Altitude(m) Velocity(m/s) Acceleration(m/s^2) AtmosphericDensity(kg/m^3)"
		//		<< " Pressure(Pa) Temperature(K) CD(-) Fdrag(N) g(m/s^2) DynamicPressure(Pa) MachNumber(-)" 
		//		<< " OrbitalAccelerationBalance(m/s^2) dMass(kg) Altitude(km)" << endl;
		Telemetry << "Time(sec) Thrust(N) Mass(kg) Altitude(m) Velocity(m/s) Acceleration(m/s^2) AtmosphericDensity(kg/m^3)"
			<< " Pressure(Pa) Temperature(K) CD(-) Fdrag(N) g(m/s^2) DynamicPressure(Pa) MachNumber(-)"
			<< " OrbitalAccelerationBalance(m/s^2) dMass(kg) Altitude(km)" << endl;

		for (int i = 0; i < nRocketPerfRows; i++) {
			//	logout << RocketPerformance[i] << " ";
			Telemetry << RocketPerformance[i] << " ";
		}
		//	logout << endl;
		Telemetry << endl;

		do {																			//  Calculate Rocket Conditions during Flight every dt sec
			time += dt;
			RocketPerformance[0] = time;												//  Update Time (sec)
			RocketPerformance[1] = Thrust(RocketPerformance[0], RocketDefinition, RocketData);
																						//  Update Thrust (N)
			dMass = MassChange(time, RocketDefinition, RocketData) * dt;
			RocketPerformance[2] -= dMass;												//  Update Mass (kg)
			RocketPerformance[3] = RocketPerformance[3] + RocketPerformance[4] * dt + 0.5 * RocketPerformance[5] * pow(dt, 2);
																						//  Update Altitude (m)
			RocketPerformance[4] = RocketPerformance[4] + RocketPerformance[5] * dt;	//  Update Velocity (m/s)
			RocketPerformance[6] = Density(RocketPerformance[3], P, T);					//  Update Atmospheric Density (kg/m^3) at Altitude
			RocketPerformance[7] = P;													//  Update Atmospheric Pressure (Pa) at Altitude
			RocketPerformance[8] = T;													//  Update Atmospheric Temperature (K) at Altitude
			RocketPerformance[9] = WaveDrag(RocketPerformance[4], T);					//  Determine Drag Coefficient with Wave Drag Model	
			RocketPerformance[10] = Fdrag(RocketPerformance[6], RocketPerformance[9], RocketPerformance[4], RocketDefinition, RocketData);
																						//  Update Drag Force (N)
			RocketPerformance[11] = Gravity(RocketPerformance[3]);						//  Update Acceleration due to gravity (m/s^2) at Altitude
			RocketPerformance[12] = 0.5 * RocketPerformance[6] * pow(RocketPerformance[4], 2);
																						//  Update Dynamic Pressure (Pa) on the Rocket
			if (RocketPerformance[8] > 0)
				RocketPerformance[13] = RocketPerformance[4] / sqrt(1.4 * 287 * RocketPerformance[8]);
																						//  Update the Mach Number of the Rocket
			if (RocketPerformance[2] > 0)
				RocketPerformance[5] = ((RocketPerformance[1] + RocketPerformance[10]) / RocketPerformance[2]) - RocketPerformance[11];
																						//  Update the Acceleration of the Rocket (m/s^2)
			RocketPerformance[14] = pow(RocketPerformance[4], 2) / (Re + RocketPerformance[3]) - RocketPerformance[11] + LaunchTangentialVel;
																						//  Necessary Centrifugal Acceleration to maintain orbit 
																						//		(Positive Value = Yes, Negative Value = no)
			RocketPerformance[15] = dMass;												//  Change in Mass since Prior Step (kg)
			RocketPerformance[16] = RocketPerformance[3] / 1000;						//  Altitude (km)

			//	Print Rocket Conditions to log.txt and telemetry.txt
			for (int i = 0; i < nRocketPerfRows; i++) {
				//				logout << RocketPerformance[i] << " ";
				Telemetry << RocketPerformance[i] << " ";
			}

			//	logout << endl;
			Telemetry << endl;


			//  Failure Modes
			if (RocketPerformance[2] < 0) {
				logout << "Rocket runs out of Mass!" << endl << endl;
				cout << "Rocket runs out of Mass!" << endl << endl;
				break;										//  Stop if Mass is Less than 0 kg (i.e. Rocket is out of mass)
			}
			if (RocketPerformance[3] < 0) {
				logout << "Rocket Crashes into the Ground!" << endl << endl;
				cout << "Rocket Crashes into the Ground!" << endl << endl;
				break;										//  Stop if Altitude is Less than 0 m (i.e. Crash!)
			}


		} while (time <= tmax + RocketDefinition[44]);


		//  Wrap up flight
		logout << endl << "Rocket Flight Complete!" << endl << endl;
		cout << endl << "Rocket Flight Complete!" << endl << endl;
		iBatch++;


		// Close Files
		Rocketout.close();
		logout.close();
		Telemetry.close();

	}while (iBatch < BatchFile[0]);

	system("PAUSE");
	return 0;
}