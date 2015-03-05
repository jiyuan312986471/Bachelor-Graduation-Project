#include "devIfApp.h"

__insidePlantBB chassisData;
__insidePlantScteFans fanData;
__insidePlantSctePs   ps1Data;
__insidePlantSctePs   ps2Data;
__heSCTEOR orData;
void InitChassisData()
{
	//S16 entPhysicalId;
  //S16 heBBIsFRU; //True
  //S16 heBBPhysicalClass; 	//backplane
  //S16 heBBRelPos;
  chassisData.devTemp = 10;
  chassisData.devTemp1 = 12;
  chassisData.devTemp2 = 13;
  chassisData.devTemp3 = 14;
  chassisData.devTemp4 = 15;
  chassisData.devTemp5 = 16;
  chassisData.devTemp6 = 17;
	chassisData.devTemp7 = 18;
	chassisData.devTemp8 = 19;
}

void InitPSData()
{
	int i;
	for(i=0;i<MAX_PS_MODULE_OUTPUT;i++)
	{
		ps1Data.hePsOutputCurrent[i] = 10+i;
		ps2Data.hePsOutputCurrent[i] = 12+i;
		
		ps1Data.hePsOutputVoltage[i] = 45+i;
		ps2Data.hePsOutputVoltage[i] = 50+i;
		
		ps1Data.hePsOutputPower[i] = 50+i;
		ps2Data.hePsOutputPower[i] = 60-i;
	}

  ps1Data.hePsInterTemp = 200;
	ps2Data.hePsInterTemp = 300;
	ps1Data.hePsFanSpeed1 = 1200;
	ps2Data.hePsFanSpeed1 = 1200;
	
	ps1Data.hePsFanSpeed2 = 1500;
	ps2Data.hePsFanSpeed2 = 1500;

}

void InitFanData()
{
//	fanData.heFanUnitId;
	//fanData.entPhysicalId;
  //fanData.heFanPhysicalClass;	//Fan
  //fanData.heFANIsFRU; //True
	//fanData.heFanUnitAlarm;
	//fanData.heFansStatusId[6];
	//fanData.heFansStatusCur[6];
	//fanData.heFansStuatusAlm[6];
	int i;
	for(i=0;i<8;i++)
	{
		fanData.heFanSpeed[i] = 1200;
		fanData.heFanCurrent[i] = 10;
	}

}

void InitORData()
{
	int i;
  for(i=0;i<4;i++)
	{
		orData.heOpRxInputIndex[i] = i+1;
		orData.heOpRxInputPower[i] = 10;
		orData.heOpRxInputWavelengthControl[i] = 1310;
		orData.heOpRxOutputIndex[i] = i+1;
		orData.heOpRxOutputControl[i] = 2;
		orData.heOpRxOutputGainType[i] = 1;
		orData.heOpRxOutputPower[i] = 5;
		orData.heOpRxOutputRFPadLevel[i] = 1;
		orData.heOpRxOutputRFOffset[i] = 1;
		orData.heOpRxRFRev3SCtrl[i] = 0;
	
	}

}
