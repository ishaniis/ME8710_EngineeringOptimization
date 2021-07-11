/*

Header File
"FlightModels.h"

by Cameron J. Turner
Copyright 2020

Version 1.0

*/


/*

	Include Files

*/

#pragma once
#include "Constants.h"	// Defines constants for the program

/*

	Function Definitions Files

*/


double Density(double z, double &P, double &T);
//	FUNCTION Density() - Determines the Density, Pressure and Temperature of the atmosphere as a function of altitude, z given in (m)

double WaveDrag(double v, double T);
//	FUNCTION WaveDrag() - Determines the Coefficient of Drag due to the Wave Drag Analysis

double Thrust(double t, dVector<double> &RocketDefinition, dMatrix<double> &RocketData);
//	FUNCTION Thrust() - Determines the Thrust of the Rocket at a time, t

double ThrottleCalc(double t, dVector<double>& RocketDefinition);
//  FUNCTION ThrottleCalc() - Determines the Throttle Setting of the Rocket at a time, t

double GrossVehicleMass(dVector<double> &RocketDefinition, dMatrix<double> &RocketData);
//	FUNCTION GrossVehicleMass() - Determines the Mass of the Rocket at a time, t = 0

double Fdrag(double rho, double CD, double v, dVector<double> &RocketDefinition, dMatrix<double> &RocketData);
//	FUNCTION Fdrag() - Determines the Drag on the Rocket

double Gravity(double z);
//  FUNCTION Gravity() - Determines the gravitational acceleration at an altitude z

double MassChange(double t, dVector<double>& RocketDefinition, dMatrix<double>& RocketData);
//  FUNCTION MassChange() - Determines the change in mass of the rocket at a time t
