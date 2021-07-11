/*

Header File
"Menu.h"

by Cameron J. Turner
Copyright 2020

Version 1.0

*/


/*

	Defined Variables

*/

constexpr auto nRocketRows = 118;	  //  Number of Rows of Data about Rocket Engines;
constexpr auto nRocketCols = 12;      //  Number of Columns of Data about Rocket Engines;
									  //	Column 1  - Menu ID Number
									  //	Column 2  - Stage ID (0 - booster, 1 - First Stage, 2 - Second and higher stages)
									  //	Column 3  - Fuel Type (1 - HTPB, 2 - RP1/LOX, 3 - PBAN, 4 - N2O4/UDMH, 5 - LH2/LOX, 6 - CH4/LOX, 7 - N2O4/MMH
									  //	Column 4  - Oxidizer/Fuel Ratio (Solid Fuels have a Ratio of 1)
									  //    Column 5  - Specific Impulse, ISP (sec)
									  //    Column 6  - Thrust (N)
									  //    Column 7  - Dry Mass (kg) - 0 when burn time is undefined for solid booster
								  	  //    Column 8  - Diameter (m)
									  //    Column 9  - Fuel Consumption (kg/sec)
									  //    Column 10 - Burn Time (sec) - defined as 0 when burn time is undefined
									  //    Column 11 - Gross Mass (kg) - defined as 0 when burn time is undefined
									  //    Column 12 - Rocket Type (0 - Solid, 1 - Liquid)
constexpr auto G = 0.00000000006673;  //  Gravitational Constant G (Nm^2/kg^2)
constexpr auto mu = 398600000000000;  //  Mass of the Earth (kg) * G (Nm^2/kg)
constexpr auto mol = 0.029;			  //  Molar mass of air
constexpr auto R = 8.314;			  //  Ideal Gas Constant
constexpr auto Re = 6378137;		  //  Radius of the Earth (m)
constexpr auto P0 = 101325;			  //  Standard Pressure at Sea Level (Pa)
constexpr auto T0 = 298;			  //  Standard Temperature at Sea Level or 25C (K)
constexpr auto go = 9.80665;		  //  Gravitational Acceleration at Sea Level (m/s^2) 
constexpr auto pi = 3.14159;		  //  Mathematical Constant Pi
constexpr auto z0 = 3;				  //  Initial Launch Elevation
constexpr auto CD0 = 0.75;			  //  Coefficient of Drag (typical of a rocket)
constexpr auto T_Coast = 300;		  //  Number of seconds of coast time in the simulation (after final stace Cut-Off
constexpr auto nRocketPerfRows = 17;  //  Number of Rows in the Rocket Performance Vector
									  //    Row 1  - Time (sec)
									  //    Row 2  - Thrust (N)
									  //    Row 3  - Rocket Mass (kg)
									  //    Row 4  - Altitude, z (m)
									  //    Row 5  - Velocity, v (m/s)
									  //    Row 6  - Acceleration, a (m/s^2)
									  //    Row 7  - Air Density, f(z), (kg/m^3)
									  //    Row 8  - Pressure, f(z), (Pa)
									  //    Row 9  - Temperature, f(z), (K)
									  //    Row 10 - Coefficient of Drag ( - )
									  //    Row 11 - Drag Force, (N)
									  //    Row 12 - Updated Gravitational Constant, f(z), (m/s^2)
									  //    Row 13 - Dynamic Pressure (Pa)
									  //    Row 14 - Centrifugal Acceleration - Gravitational Acceleration (m/s^2)
									  //		Positive Value means orbit obtained
									  //		Negative Value means orbit not obtained
									  //    Row 15 - Change in Mass (kg)
									  //    Row 16 - Altitde (km)
constexpr auto FirstOffset = 69;	  //  Offset of Menu Numbers for First Stage Choices versus Row in [RocketData]
constexpr auto SecondOffset = 123;	  //  Offset of Menu Numbers for Upper Stage Choices versus Row in [RocketData]
constexpr auto dt = 0.1;			  //  Defined Simulation Time Step (sec)
constexpr auto tmax = 15;			  //  Time the simulation runs past final stage cutoff (sec)
constexpr auto BatchLength = 48;	  //  Length of a Rocket Definition without Masses and Separation Times
constexpr auto BatchSize = 66;		  //  Length of a FULL Rocket Definition
constexpr auto LaunchTangentialVel = 0.026195;
									  //  Centrifugal Acceleration due to Tangential Acceleration at KSC (v = 408.75 m/s)

/*

	Include Files

*/

#pragma once
#include <iostream>		//  Included Header File for Console I/O
#include "Cmatrix.h"	//  Included Header File for Basic Vectors and Matrices
#include <string>		//  Included Header File for Strings
#include <fstream>		//  Included Header File for File I/O
#include <cstdlib>		//  Included Header File for rand() and srand() 
#include <ctime>		//  Included Header File for Time Functions #pragma once
#include <math.h>		//  Mathmatical Functions



