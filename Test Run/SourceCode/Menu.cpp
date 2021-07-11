/*

Source File
"Menu.cpp"

by Cameron J. Turner
Copyright 2020

Version 1.0

*/


/*

	Include Files

*/

#include "Menu.h"


unsigned long long int RocketMenu(dVector<double> &RocketDefinition)
{
	//	Define Local Variables
	unsigned long long int temp;
	double Temp;
	bool ok = false;

	//	Open the Log File
	ofstream logout("log.txt", ios::app);

	//	Open Rocket File (Batch Runs)
	ofstream Rocketout("Rocket.txt", ios::app);

	//	Determine the Number of Stages in the Rocket
	do {
		cout << "Enter the number of stages in the Rocket (>0 and <=5): " << endl;
		cin >> temp;
		cout << endl;
		if ((temp > 0) && (temp <= 5)) ok = true;
	} while (ok == false);

	logout << "Enter the number of stages in the Rocket (>0 and <=5): " << temp << endl << endl;
	RocketDefinition.push_back(1.0 * temp);
	ok = false;

	//	Determine the Number of Boosters with the first stage of the Rocket
	do {
		cout << "Enter the number of boosters attached to the first stage of the Rocket (>=0): " << endl;
		cin >> temp;
		cout << endl;
		if (temp >= 0) ok = true;
	} while (ok == false);

	logout << "Enter the number of boosters attached to the first stage of the Rocket (>=0): " << temp << endl << endl;
	RocketDefinition.push_back(1.0 * temp);
	ok = false;

	//	Booster Modeling

	if (temp > 0) {

		//	Determine the Booster Type for the first stage of the Rocket
		do {
			cout << "Select the type of Booster Rocket from the list: " << endl
				<< " 1)   Aerojet AJ-60A         17)  Northrup Castor-4A-XL" << endl
				<< " 2)   Airbus CBC             18)  Northrup GEM" << endl
				<< " 3)   Airbus EAP-238         19)  Northrup GEM40" << endl
				<< " 4)   Airbus EAP-P241        20)  Northrup GEM46" << endl
				<< " 5)   Airbus EPC-H158        21)  Northrup GEM60" << endl
				<< " 6)   Airbus EPC-H173        22)  Northrup GEM63" << endl
				<< " 7)   Avio P120C             23)  Northrup GEM63XL" << endl
				<< " 8)   Avio P230              24)  Orbital SLS-SRB" << endl
				<< " 9)   Avio P80               25)  Orbital STS-SRB" << endl
				<< " 10)  Godrej & Boyce SLV-1   26)  SDSC PSLV-DL" << endl
				<< " 11)  Hercules SRMU          27)  SDSC PSLV-G" << endl
				<< " 12)  JAXA H2A-SRB-A         28)  SDSC PSLV-QL" << endl
				<< " 13)  JAXA SRB-A3            29)  SDSC PSLV-XL" << endl
				<< " 14)  Lockheed MA-5A         30)  SDSC S139" << endl
				<< " 15)  Northrup Castor 120    31)  SDSC S200" << endl
				<< " 16)  Northrup Castor IVA    32)  UTC UA1207" << endl;
			cin >> temp;
			cout << endl;
			if ((temp > 0) && (temp <= 32)) ok = true;
		} while (ok == false);

		logout << "Select the type of Booster Rocket from the list: " << endl;
		switch (temp) {
			case 1: logout << " 1)   Aerojet AJ-60A "; break;
			case 2: logout << " 2)   Airbus CBC "; break;
			case 3: logout << " 3)   Airbus EA-238 "; break;
			case 4: logout << " 4)   Airbus EAP-P241 "; break;
			case 5: logout << " 5)   Airbus EPC-H158 "; break;
			case 6: logout << " 6)   Airbus EPC-H173 "; break;
			case 7: logout << " 7)   Avio P120C "; break;
			case 8: logout << " 8)   Avio P230 "; break;
			case 9: logout << " 9)   Avio P80 "; break;
			case 10: logout << " 10)  Godrej & Boyce SLV-1 "; break;
			case 11: logout << " 11)  Hercules SRMU "; break;
			case 12: logout << " 12)  JAXA H2A-SRB - A "; break;
			case 13: logout << " 13)  JAXA SRB-A3 "; break;
			case 14: logout << " 14)  Lockheed MA-5A "; break;
			case 15: logout << " 15)  Northrup Castor 120 "; break;
			case 16: logout << " 16)  Northrup Castor IVA "; break;
			case 17: logout << " 17)  Northrup Castor-4A-XL "; break;
			case 18: logout << " 18)  Northrup GEM "; break;
			case 19: logout << " 19)  Northrup GEM40 "; break;
			case 20: logout << " 20)  Northrup GEM46 "; break;
			case 21: logout << " 21)  Northrup GEM60 "; break;
			case 22: logout << " 22)  Northrup GEM63 "; break;
			case 23: logout << " 23)  Northrup GEM63XL "; break;
			case 24: logout << " 24)  Orbital SLS-SRB "; break;
			case 25: logout << " 25)  Orbital STS-SRB "; break;
			case 26: logout << " 26)  SDSC PSLV-DL "; break;
			case 27: logout << " 27)  SDSC PSLV-G "; break;
			case 28: logout << " 28)  SDSC PSLV-QL "; break;
			case 29: logout << " 29)  SDSC PSLV-XL "; break;
			case 30: logout << " 30)  SDSC S139 "; break;
			case 31: logout << " 31)  SDSC S200 "; break;
			case 32: logout << " 32)  UTC UA1207 "; break;
		}
		logout << endl << endl;

		RocketDefinition.push_back(1.0 * temp);
		ok = false;

	}
	else {
		RocketDefinition.push_back(0.0);
	}

	//	Stage Modeling
	for (int i = 0; i < 5; i++) {
		if (i <= RocketDefinition[0] - 1.0) {
			
			//	Stage Engine Type Selection

			//	Differentiate between Stage 1 and Upper Stages (>2)

			if (i == 0) {	//	For Stage 1

				RocketDefinition.push_back(1.0);
				do {
					cout << "Select the type of Rocket Engine for Stage " << i + 1 << " from the list: " << endl
						<< " 101)  AALPT YF-100         117)  Godrej & Boyce SLV-1     132)  Orbital SLS-SRB" << endl
						<< " 102)  AALPT YF-100A        118)  JAXA SRB-A3              133)  Pivdenne RD-801" << endl
						<< " 103)  AALPT YF-130         119)  JSC AJ26-62              134)  Pivdenne RD-810" << endl
						<< " 104)  AALPT YF-21B         120)  Landspace TQ-12          135)  Pivdenne RD-870" << endl
						<< " 105)  AALPT YF-21C         121)  Launcher Engine2         136)  PLD TEPREL" << endl
						<< " 106)  AALPT YF-25          122)  Mitsubishi LE-7A         137)  Relativity Aeon1" << endl
						<< " 107)  AALPT YF-77          123)  Northrup GEM63           138)  RocketDyne RS-25" << endl
						<< " 108)  Aerojet AJ-60A       124)  Northrup GEM63XL         139)  RocketDyne RS-68A" << endl
						<< " 109)  Aerojet AR1          125)  NPO RD-107A              140)  RocketLab Rutherford" << endl
						<< " 110)  Astra Delphin        126)  NPO RD-171M              141)  SDSC S139" << endl
						<< " 111)  Avio P120C           127)  NPO RD-180               142)  SDSC S200" << endl
						<< " 112)  Avio P230            128)  NPO RD-181               143)  Snecma Vulcain2" << endl
						<< " 113)  Avio P80             129)  NPO RD-191               144)  SpaceX Merlin 1D" << endl
						<< " 114)  Blue Origin BE-3     130)  NPO RD-193               145)  SpaceX Raptor" << endl
						<< " 115)  Blue Origin BE-4     131)  NPO RD-276               146)  Virgin Galactic Newton3" << endl
						<< " 116)  Firefly Reaver1" << endl;

					cin >> temp;
					cout << endl;
					if ((temp > 100) && (temp <= 146)) ok = true;
				} while (ok == false);

				logout << "Select the type of Rocket Engine for Stage " << i + 1 << " from the list: " << endl;
				switch (temp) {
					case 101: logout << " 101)  AALPT YF-100 "; break;
					case 102: logout << " 102)  AALPT YF-100A "; break;
					case 103: logout << " 103)  AALPT YF-130 "; break;
					case 104: logout << " 104)  AALPT YF-21B "; break;
					case 105: logout << " 105)  AALPT YF-21C "; break;
					case 106: logout << " 106)  AALPT YF-25 "; break;
					case 107: logout << " 107)  AALPT YF-77 "; break;
					case 108: logout << " 108)  Aerojet AJ-60A "; break;
					case 109: logout << " 109)  Aerojet AR1 "; break;
					case 110: logout << " 110)  Astra Delphin "; break;
					case 111: logout << " 111)  Avio P120C "; break;
					case 112: logout << " 112)  Avio P230 "; break;
					case 113: logout << " 113)  Avio P80 "; break;
					case 114: logout << " 114)  Blue Origin BE-3 "; break;
					case 115: logout << " 115)  Blue Origin BE-4 "; break;
					case 116: logout << " 116)  Firefly Reaver1 "; break;
					case 117: logout << " 117)  Godrej & Boyce SLV-1 "; break;
					case 118: logout << " 118)  JAXA SRB-A3 "; break;
					case 119: logout << " 119)  JSC AJ26-62 "; break;
					case 120: logout << " 120)  Landspace TQ-12 "; break;
					case 121: logout << " 121)  Launcher Engine2 "; break;
					case 122: logout << " 122)  Mitsubishi LE-7A "; break;
					case 123: logout << " 123)  Northrup GEM63 "; break;
					case 124: logout << " 124)  Northrup GEM63XL "; break;
					case 125: logout << " 125)  NPO RD-107A "; break;
					case 126: logout << " 126)  NPO RD-171M "; break;
					case 127: logout << " 127)  NPO RD-180 "; break;
					case 128: logout << " 128)  NPO RD-181 "; break;
					case 129: logout << " 129)  NPO RD-191 "; break;
					case 130: logout << " 130)  NPO RD-193 "; break;
					case 131: logout << " 131)  NPO RD-276 "; break;
					case 132: logout << " 132)  Orbital SLS-SRB "; break;
					case 133: logout << " 133)  Pivdenne RD-801 "; break;
					case 134: logout << " 134)  Pivdenne RD-810 "; break;
					case 135: logout << " 135)  Pivdenne RD-870 "; break;
					case 136: logout << " 136)  PLD	TEPREL "; break;
					case 137: logout << " 137)  Relativity Aeon1 "; break;
					case 138: logout << " 138)  RocketDyne RS-25 "; break;
					case 139: logout << " 139)  RocketDyne RS-68A "; break;
					case 140: logout << " 140)  RocketLab Rutherford "; break;
					case 141: logout << " 141)  SDSC S139 "; break;
					case 142: logout << " 142)  SDSC S200 "; break;
					case 143: logout << " 143)  Snecma Vulcain2 "; break;
					case 144: logout << " 144)  SpaceX Merlin 1D "; break;
					case 145: logout << " 145)  SpaceX Raptor "; break;
					case 146: logout << " 146)  Virgin Galactic Newton3 "; break;
				}
				logout << endl << endl;

			}
			else {		// For Stages 2+

				RocketDefinition.push_back(1.0);
				do {
					cout << "Select the type of Rocket Engine for Stage " << i + 1 << " from the list: " << endl
						<< " 201)  AALPT YF-115         215)  Aerojet RL-10C         228)  Mitsubishi LE-5B" << endl
						<< " 202)  AALPT YF-22B         216)  Avio Mira LM10         229)  NPO RD-108A" << endl
						<< " 203)  AALPT YF-22C         217)  Avio Zefiro23          230)  Pivdenne RD-8" << endl
						<< " 204)  AALPT YF-22D         218)  Avio Zefiro9A          231)  Pivdenne RD-809K" << endl
						<< " 205)  AALPT YF-22E         219)  Blue Origin BE-3U      232)  Pivdenne RD-843" << endl
						<< " 206)  AALPT YF-40          220)  Firefly Lightning1     233)  Pivdenne RD-861K" << endl
						<< " 207)  AALPT YF-50D         221)  KBKhA RD-0124          234)  Relativity Aeon1V" << endl
						<< " 208)  AALPT YF-73          222)  KBKhA RD-0146D         235)  RocketLab RutherfordV" << endl
						<< " 209)  AALPT YF-75          223)  Launcher Engine2V      236)  Snecma HM7B" << endl
						<< " 210)  AALPT YF-75D         224)  LPSC CE-20             237)  Snecma Vinci" << endl
						<< " 211)  AALPT YF-90          225)  LPSC CE-7.5            238)  SpaceX Merlin 1DV" << endl
						<< " 212)  Aerojet AJ10-190     226)  LPSC SCE-200           239)  SpaceX RaptorV" << endl
						<< " 213)  Aerojet RL-10A       227)  LPSC Vikas             240)  Virgin Galactic Newton4" << endl
						<< " 214)  Aerojet RL-10B" << endl;
					cin >> temp;
					cout << endl;
					if ((temp > 200) && (temp <= 240)) ok = true;
				} while (ok == false);

				logout << "Select the type of Rocket Engine for Stage " << i + 1 << " from the list: " << endl;
				switch (temp) {
					case 201: logout << " 201)  AALPT YF-115 "; break;
					case 202: logout << " 202)  AALPT YF-22B "; break;
					case 203: logout << " 203)  AALPT YF-22C "; break;
					case 204: logout << " 204)  AALPT YF-22D "; break;
					case 205: logout << " 205)  AALPT YF-22E "; break;
					case 206: logout << " 206)  AALPT YF-40 "; break;
					case 207: logout << " 207)  AALPT YF-50D "; break;
					case 208: logout << " 208)  AALPT YF-73 "; break;
					case 209: logout << " 209)  AALPT YF-75 "; break;
					case 210: logout << " 210)  AALPT YF-75D "; break;
					case 211: logout << " 211)  AALPT YF-90 "; break;
					case 212: logout << " 212)  Aerojet AJ10-190 "; break;
					case 213: logout << " 213)  Aerojet RL-10A "; break;
					case 214: logout << " 214)  Aerojet RL-10B "; break;
					case 215: logout << " 215)  Aerojet RL-10C "; break;
					case 216: logout << " 216)  Avio Mira LM10 "; break;
					case 217: logout << " 217)  Avio Zefiro23 "; break;
					case 218: logout << " 218)  Avio Zefiro9A "; break;
					case 219: logout << " 219)  Blue Origin BE-3U "; break;
					case 220: logout << " 220)  Firefly Lightning1 "; break;
					case 221: logout << " 221)  KBKhA RD-0124 "; break;
					case 222: logout << " 222)  KBKhA RD-0146D "; break;
					case 223: logout << " 223)  Launcher Engine2V3 "; break;
					case 224: logout << " 224)  LPSC CE-20 "; break;
					case 225: logout << " 225)  LPSC CE-7.5 "; break;
					case 226: logout << " 226)  LPSC SCE-200 "; break;
					case 227: logout << " 227)  LPSC Vikas "; break;
					case 228: logout << " 228)  Mitsubishi LE-5B "; break;
					case 229: logout << " 229)  NPO RD-108A "; break;
					case 230: logout << " 230)  Pivdenne RD-8 "; break;
					case 231: logout << " 231)  Pivdenne RD-809K "; break;
					case 232: logout << " 232)  Pivdenne RD-843 "; break;
					case 233: logout << " 233)  Pivdenne RD-861K "; break;
					case 234: logout << " 234)  Relativity Aeon1V "; break;
					case 235: logout << " 235)  RocketLab RutherfordV "; break;
					case 236: logout << " 236)  Snecma HM7BL "; break;
					case 237: logout << " 237)  Snecma Vinci "; break;
					case 238: logout << " 238)  SpaceX Merlin 1DV "; break;
					case 239: logout << " 239)  SpaceX RaptorV "; break;
					case 240: logout << " 240)  Virgin Galactic Newton4 "; break;
				}
				logout << endl << endl;
			}

			RocketDefinition.push_back(1.0 * temp);
			ok = false;

			//	Determine the Number of Engines on the stage of the Rocket
			do {
				cout << "Enter the number of Rocket Engines for Stage " << i + 1 << " of the Rocket (>=0 and <= 50): " << endl;
				cin >> temp;
				cout << endl;
				if ((temp >= 0) && (temp <= 50)) ok = true;
			} while (ok == false);

			logout << "Enter the number of Rocket Engines for Stage " << i + 1 << " of the Rocket (>=0 and <= 50): " << temp << endl << endl;

			RocketDefinition.push_back(1.0 * temp);
			ok = false;
		}
		else {
			for (int j = 0; j < 3; j++) RocketDefinition.push_back(0.0);
		}

	}

	
	//	Build Thrust Profile
	//	Start with Ignition
	cout << "At Time, T = 0 sec, the first stage engines are started at full throttle (100% or throttle = 1)." << endl << endl;
	RocketDefinition.push_back(0.0);
	RocketDefinition.push_back(1.0);

	//	Define Throttle Down Time (T_tD)
	do {
		cout << "Enter the Throttle Down Time, T_tD where T_tD > 0 sec: " << endl;
		cin >> Temp;
		cout << endl;
		if (Temp > 0) ok = true;
	} while (ok == false);

	logout << "Enter the Throttle Down Time, T_tD where T_tD > 0 sec: " << Temp << " sec." << endl << endl;

	RocketDefinition.push_back(Temp);
	RocketDefinition.push_back(1.0);
	ok = false;

	//	Define Throttle Down Complete Time (T_tDC)
	do {
		cout << "Enter the Throttle Down Complete Time, T_tDC where T_tDC > " << RocketDefinition[RocketDefinition.size()-2] << " sec: " << endl;
		cin >> Temp;
		cout << endl;
		if (Temp > RocketDefinition[RocketDefinition.size() - 2]) ok = true;
	} while (ok == false);

	logout << "Enter the Throttle Down Complete Time, T_tDC where T_tDC > " << RocketDefinition[RocketDefinition.size() - 2] << " sec: " << Temp << " sec." << endl << endl;

	RocketDefinition.push_back(Temp);
	ok = false;

	//	Define Throttle Down Level (T_tDL)
	do {
		cout << "Enter the Throttle Down Level, T_tDL where 0.0 <= T_tDL < 1.0: " << endl;
		cin >> Temp;
		cout << endl;
		if ((Temp < 1.0) && (Temp >= 0.0)) ok = true;
	} while (ok == false);

	logout << "Enter the Throttle Down Level, T_tDL where 0.0 <= T_tDL < 1.0: " << Temp << endl << endl;

	RocketDefinition.push_back(Temp);
	ok = false;

	//	Define Throttle Down Up Time (T_tU)
	do {
		cout << "Enter the Throttle Up Time, T_tU where T_tU > " << RocketDefinition[RocketDefinition.size() - 2] << " sec: " << endl;
		cin >> Temp;
		cout << endl;
		if (Temp > RocketDefinition[RocketDefinition.size() - 2]) ok = true;
	} while (ok == false);

	logout << "Enter the Throttle Up Time, T_tU where T_tU > " << RocketDefinition[RocketDefinition.size() - 2] << " sec: " << Temp << " sec." << endl << endl;

	RocketDefinition.push_back(Temp);
	RocketDefinition.push_back(RocketDefinition[RocketDefinition.size() - 2]);
	ok = false;

	//	Define Throttle Up Complete tine (T_tUC)
	do {
		cout << "Enter the Throttle Up Complete time, T_tUC where T_tUC > " << RocketDefinition[RocketDefinition.size() - 2] << " sec: " << endl;
		cin >> Temp;
		cout << endl;
		if (Temp > RocketDefinition[RocketDefinition.size() - 2]) ok = true;
	} while (ok == false);

	logout << "Enter the Throttle Up Complete time, T_tUC where T_tUC > " << RocketDefinition[RocketDefinition.size() - 2] << " sec: " << Temp << endl << endl;

	RocketDefinition.push_back(Temp);
	RocketDefinition.push_back(1.0);
	ok = false;
	
	//	Define MECO tine (T_meco)
	do {
		cout << "Enter the MECO time (Main Engine Cut Off), T_meco where T_meco > " << RocketDefinition[RocketDefinition.size() - 2] << " sec: " << endl;
		cin >> Temp;
		cout << endl;
		if (Temp > RocketDefinition[RocketDefinition.size() - 2]) ok = true;
	} while (ok == false);

	logout << "Enter the MECO time (Main Engine Cut Off), T_meco where T_meco > " << RocketDefinition[RocketDefinition.size() - 2] << " sec: " << Temp << endl << endl;

	RocketDefinition.push_back(Temp);
	RocketDefinition.push_back(0.0);
	ok = false;

	//	Determine Stage Ignition and Burn Times
	for (int j = 2; j <= 5; j++) {
		if (RocketDefinition[0] >= j){

			//  Define Stage Ignition (Throttle is 100%)
			do {
				cout << "Enter the Stage " << j << " Ignition time (" << j << "SI), T_" << j <<"SI > " << RocketDefinition[RocketDefinition.size() - 2]+1.0 << " sec: " << endl;
				cin >> Temp;
				cout << endl;
				if (Temp > RocketDefinition[RocketDefinition.size() - 2] + 1.0) ok = true;
			} while (ok == false);

			logout << "Enter the Stage " << j << " Ignition time (" << j << "SI), T_" << j << "SI > " << RocketDefinition[RocketDefinition.size() - 2] + 1.0 << " sec: " << Temp << endl << endl;

			RocketDefinition.push_back(Temp);
			RocketDefinition.push_back(1.0);
			ok = false;

			//  Define Stage Cut-Off (Throttle is 0%)
			do {
				cout << "Enter the Stage " << j << " Cut-Off time (" << j << "SCO), T_" << j << "SCO > " << RocketDefinition[RocketDefinition.size() - 2] + 1.0 << " sec: " << endl;
				cin >> Temp;
				cout << endl;
				if (Temp > RocketDefinition[RocketDefinition.size() - 2] + 1.0) ok = true;
			} while (ok == false);

			logout << "Enter the Stage " << j << " Cut-Off time (" << j << "SCO), T_" << j << "SCO > " << RocketDefinition[RocketDefinition.size() - 2] + 1.0 << " sec: " << Temp << endl << endl;

			RocketDefinition.push_back(Temp);
			RocketDefinition.push_back(0.0);
			ok = false;

		}
		else {
			RocketDefinition.push_back(RocketDefinition[RocketDefinition.size() - 2] + 1.0);
			RocketDefinition.push_back(0.0);
			RocketDefinition.push_back(RocketDefinition[RocketDefinition.size() - 2] + 1.0);
			RocketDefinition.push_back(0.0);
		}
	}

	//  Determine Diameter of Main Stage
	do {
		cout << "Determine the Main Stage Diameter which should be sufficent to account for the diameters of all rocket nozzles used on the main stage." << endl
			<< "Booster Engines are not included in this calculation. Enter the Diameter in meters of the main stage: " << endl;
		cin >> Temp;
		cout << endl;
		if (Temp > 0.0) ok = true;
	} while (ok == false);

	logout << "Determine the Main Stage Diameter which should be sufficent to account for the diameters of all rocket nozzles used on the main stage." << endl
		<< "Booster Engines are not included in this calculation. Enter the Diameter in meters of the main stage: " << Temp << endl << endl;

	RocketDefinition.push_back(Temp);
	ok = false;


	//  Determine Payload 
	do {
		cout << "Specify the mass of the payload to be launched in kg: " << endl;
		cin >> Temp;
		cout << endl;
		if (Temp > 0.0) ok = true;
	} while (ok == false);

	logout << "Specify the mass of the payload to be launched in kg: " << Temp << endl << endl;

	RocketDefinition.push_back(Temp);
	ok = false;

	
	//	Close Files
	logout.close();
	Rocketout.close();
		
	temp = RocketDefinition.size();
	return temp;
}
