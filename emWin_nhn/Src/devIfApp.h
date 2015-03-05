/* DevIFapp.h --Device Interface application layer function Header file. */

#ifndef __DEVAPPP__
#define __DEVAPPP__


#include <RTL.h> 

#include "nscrtv.h"

#define DEF_DEV_SN "080420-0123"


#define MAX_FANS_PER_UNIT 6
#define MAX_FAN_UNIT 1
#define MAX_FAN_MODULE 1
#define MAX_SM_MODULE 16
#define MAX_PS_MODULE 2	   
#define MAX_PS_MODULE_OUTPUT 4 //C平台就一路输出

#define MAX_OR_INPUT 4
#define MAX_OR_OUTPUT 4

#define MAX_OT_INPUT 2
#define MAX_OT_OUTPUT 2
//+5v,-5v,+24v,+3.3v
#define MAX_SLOT (MAX_SM_MODULE + MAX_PS_MODULE + MAX_FAN_MODULE)



#define MAX_VAR_LENGTH 128
#define MAX_CTRL_LENGTH 128
#define MAX_LIMIT_SIZE 128

#define MAX_PUBLIC_LENGTH 160
#define MAX_CONFIG_LENGTH 16
#define MAX_STATUS_LENGTH 24

#define devID_FRAME 0x03

#define devID_NULL 0
#define devID_UNK 0xFF
#define devID_FRAME 0x03

#define devID_DNOT1 0x01 //1310
#define devID_DNOT2 0x02 //1550
#define devID_UPOT 0x08 //1310


#define devID_DNOR 0x05  //双路切换
#define devID_UPOR 0x07

#define devID_RFAMP 0x09

#define devID_SW 0x0E
#define devID_PS	0x0A
#define devID_EDFA  0x04
#define devID_FAN 0x0F  //应为0x0F
/*entPhysicalId */
#define PHYID_CHASSIS 200
#define PHYID_BACKPLANE 150
#define PHYID_PS 113  //
#define PHYID_FAN 64 //
#define PHYID_MODULE 1 //

#define PHYNAME_CHASSIS	 "Chassis"
#define PHYNAME_BACKPLANE "Backplane"
#define PHYNAME_MODULE	  "Module"
#define PHYNAME_PS		  "Powersupply"
#define PHYNAME_FAN		  "Fan"
#define PHY_MFG_NAME      "TITAN Photonics,INC."
//#define devID_EDFA1  0x04 ///add for edfa
//#define devID_EDFA2  0x14  //two pumps
//#define devID_EDFA3  0x24  //three pumps

#define DEV_NAME_NULL 	"空模块"
#define DEV_NAME_DNOT1 	"正向光发"
#define DEV_NAME_DNOR1 	"单路正向光收"
#define DEV_NAME_DNOR2 	"双路正向光收"
#define DEV_NAME_DNOR3 	"双路切换光收"
#define DEV_NAME_UPOT1 	"单路反向光发"
#define DEV_NAME_UPOT2 	"双路反向光发"
#define DEV_NAME_UPOR1 	"双路独立反向光收"
#define DEV_NAME_UPOR2 	"双路切换反向光收"
#define DEV_NAME_RFAMP1 "射频放大"
#define DEV_NAME_RFSW1  "射频切换开关"
#define DEV_NAME_PS		"电源模块"
#define DEV_NAME_UNK 	"未知模块"
#define DEV_NAME_FRAME	"雷华C型光平台"
#define DEV_NAME_EDFA   "光放大器"		 ///add for edfa

#define DEV_MODEL_DNOT1 "OPFT20"
#define DEV_MODEL_DNOR1 "OPFR20"
#define DEV_MODEL_DNOR2 "OPFR21"
#define DEV_MODEL_DNOR3 "OPFR22"
#define DEV_MODEL_UPOT1 "OPRT20"
#define DEV_MODEL_UPOT2 "OPRT21"
#define DEV_MODEL_UPOR1 "OPRR20"
#define DEV_MODEL_UPOR2 "OPRR21"
#define DEV_MODEL_RFAMP1 "OPFF20"
#define DEV_MODEL_RFSW1 "OPSW30"
#define DEV_MODEL_PS 	"OPPW20"
#define DEV_MODEL_FRAME	"OPPF20"
#define DEV_MODEL_EDFA  "OPFA30"
#define DEV_NAME_NULL_EN 	"Blank"
#define DEV_NAME_UNK_EN 	"Unknow"

//for ver4.2
#define RFAMP_NORFI_TYPE1 "OPFF30-A"
#define RFAMP_NORFI_TYPE2 "OPFF30A"

#define CTRL_OR_ATT1 0x01
#define CTRL_OR_ATT2 0x02
#define CTRL_OR_3STATESW1 0x03
#define CTRL_OR_3STATESW2 0x04
#define CTRL_EDFA_PWR 0x05
#define CTRL_OR_EQ1 0x06
#define CTRL_OR_EQ2 0x07
#define CTRL_AMP_ATT 0x08
#define CTRL_AMP_EQ 0x09
typedef struct {
	int (*qryFuncPtr)(int slot);
	unsigned int waitAckTimeout;
	char retry;
	char spare;
	U16 pollStateBit;
	U16 pollStateRep;
	U16 setLostStatusBit; //写状态
	U16	setUnLostStatusBit;
	U16 setLmtBit;	 //写门限
	U16 setCtrlBit;
} __queryCtrl;

//C平台
//轮询指令
#define POLL_PUB 0x0001
#define POLL_CFG 0x0002
#define POLL_LOST_STATUS 0x0004
#define POLL_UNLOST_STATUS 0x0008
#define POLL_LIMIT 0x0010
#define POLL_VAR 0x0020
#define POLL_PUB_CFG 0x0040
#define POLL_MASK (POLL_PUB_CFG |POLL_LOST_STATUS|POLL_UNLOST_STATUS| POLL_LIMIT|POLL_VAR)
#define POLL_REP (POLL_LOST_STATUS|POLL_UNLOST_STATUS|POLL_LIMIT|POLL_VAR)

//写易失性状态指令
#define WR_BB_LOST_STATE_SETTING 0x01

#define WR_FAN_LOST_STATE_SETTING 0x01
#define WR_FAN_LOST_STATE_INDICATION 0x02

#define WR_PS_LOST_STATE_SETTING 0x01

#define WR_OT_LOST_STATE_SETTING 0x01

#define WR_DNOR_LOST_STATE_SETTING 0x01
#define WR_DNOR_LOST_STATE_RFOUTSW 0x02

#define WR_UPOR_LOST_STATE_SETTING 0x01
#define WR_UPOR_LOST_STATE_RFOUTSW 0x02
#define WR_UPOR_LOST_STATE_TESTPORT 0x04



#define WR_AMP_LOST_STATE_SETTING 0x01

#define WR_SW_LOST_STATE_SETTING 0x01

#define WR_EDFA_LOST_STATE_SETTING 0x01
#define WR_EDFA_LOST_STATE_SWITCH 0x02	 



//写非易失性状态
#define WR_BB_UNLOST_STATE_SETTING 0x01

#define WR_FAN_UNLOST_STATE_SETTING 0x01
#define WR_FAN_UNLOST_STATE_CTRLMODE 0x02
#define WR_FAN_UNLOST_STATE_SPEEDSET 0x04
#define WR_FAN_UNLOST_STATE_CURRENTSET 0x08

#define WR_PS_UNLOST_STATE_SETTING 0x01

#define WR_OT_UNLOST_STATE_SETTING 0x01
#define WR_OT_UNLOST_STATE_GAINTYPE 0x02
#define WR_OT_UNLOST_STATE_ATT 0x04
#define WR_OT_UNLOST_STATE_ANACHN 0x08
#define WR_OT_UNLOST_STATE_DIGCHN 0x10
#define WR_OT_UNLOST_STATE_AMEND1 0x20
#define WR_OT_UNLOST_STATE_AMEND2 0x40

#define WR_DNOR_UNLOST_STATE_SETTING 0x01
#define WR_DNOR_UNLOST_STATE_GAINTYPE 0x02
#define WR_DNOR_UNLOST_STATE_SWSTRATEGY 0x04
#define WR_DNOR_UNLOST_STATE_ATT1 0x08
#define WR_DNOR_UNLOST_STATE_ATT2 0x10
#define WR_DNOR_UNLOST_STATE_EQ1 0x20
#define WR_DNOR_UNLOST_STATE_EQ2 0x40
#define WR_DNOR_UNLOST_STATE_WAVELEN 0x80
#define WR_DNOR_UNLOST_STATE_AMEND1 0x0100
#define WR_DNOR_UNLOST_STATE_AMEND2 0x0200

#define WR_UPOR_UNLOST_STATE_SETTING 0x01
#define WR_UPOR_UNLOST_STATE_GAINTYPE 0x02
#define WR_UPOR_UNLOST_STATE_RFOUTATT1 0x04
#define WR_UPOR_UNLOST_STATE_RFOUTATT2 0x08
#define WR_UPOR_UNLOST_STATE_WAVELEN 0x10
#define WR_UPOR_UNLOST_STATE_AMEND1 0x20
#define WR_UPOR_UNLOST_STATE_AMEND2 0x40


#define WR_AMP_UNLOST_STATE_SETTING 0x01
#define WR_AMP_UNLOST_STATE_GAINTYPE 0x02
#define WR_AMP_UNLOST_STATE_OUTPUTATT1 0x08
#define WR_AMP_UNLOST_STATE_OUTPUTATT2 0x10
#define WR_AMP_UNLOST_STATE_INPUTATT1 0x20
#define WR_AMP_UNLOST_STATE_INPUTATT2 0x40
#define WR_AMP_UNLOST_STATE_EQ1 0x80
#define WR_AMP_UNLOST_STATE_EQ2 0x0100
#define WR_AMP_UNLOST_STATE_AMEND1 0x0200
#define WR_AMP_UNLOST_STATE_AMEND2 0x0400

#define WR_SW_UNLOST_STATE_SETTING 0x01
#define WR_SW_UNLOST_STATE_SWITCHSTRATEGY 0x02
#define WR_SW_UNLOST_STATE_SWITCHDELAY 0x04
#define WR_SW_UNLOST_STATE_SWITCHLEVEL 0x08
#define WR_SW_UNLOST_STATE_OPINAMEND1 0x10
#define WR_SW_UNLOST_STATE_OPINAMEND2 0x20
#define WR_SW_UNLOST_STATE_OPOUTAMEND 0x40
#define WR_SW_UNLOST_STATE_RFINAMEND1 0x80
#define WR_SW_UNLOST_STATE_RFINAMEND2 0x0100
#define WR_SW_UNLOST_STATE_RFOUTAMEND 0x0200

#define WR_EDFA_UNLOST_STATE_SETTING 0x01
#define WR_EDFA_UNLOST_STATE_OUTPUTPOWER 0x02
#define WR_EDFA_UNLOST_STATE_AMEND1 0x04
#define WR_EDFA_UNLOST_STATE_AMEND2 0x08

//写门限指令
#define WR_BBLMT_DEVTEMP 0x01

#define WR_FANLMT_SPEED 0x01
#define WR_FANLMT_CURRENT 0x02

#define WR_PSLMT_INTERNALTEMP 0x01
#define WR_PSLMT_FANSPEED 0x02
#define WR_PSLMT_VOLTAGE 0x04
#define WR_PSLMT_CURRENT 0x08

#define WR_OTLMT_INTERNALTEMP 0x01
#define WR_OTLMT_FANSPEED 0x02
#define WR_OTLMT_OUTPUTPOWER  0x04
#define WR_OTLMT_PUMPBIAS 0x08
#define WR_OTLMT_PUMPTEMP 0x10
#define WR_OTLMT_PUMPTEC 0x20
#define WR_OTLMT_DRIVELEVEL 0x40
#define WR_OTLMT_AGCLEVEL 0x80
#define WR_OTLMT_INPUTLEVEL1 0x0100
#define WR_OTLMT_INPUTLEVEL2 0x0200

#define WR_ORLMT_INTERNALTEMP 0x01
#define WR_ORLMT_FANSPEED 0x02
#define WR_ORLMT_INPUTPOWER 0x04
#define WR_ORLMT_OUTPUTLEVEL 0x08


#define WR_AMPLMT_INTERNALTEMP 0x01
#define WR_AMPLMT_FANSPEED 0x02
#define WR_AMPLMT_OUTPUTLEVEL 0x04
#define WR_AMPLMT_INPUTLEVEL 0x08


#define WR_SWLMT_INTERNALTEMP 0x01
#define WR_SWLMT_FANSPEED 0x02
#define WR_SWLMT_INPUTLEVEL 0x04
#define WR_SWLMT_OUTPUTLEVEL 0x08

#define WR_EDFALMT_INTERNALTEMP 0x01
#define WR_EDFALMT_FANSPEED 0x02
#define WR_EDFALMT_INPUTPOWER 0x04
#define WR_EDFALMT_OUTPUTPOWER 0x08
#define WR_EDFALMT_PUMPPOWER1 0x10
#define WR_EDFALMT_PUMPBIAS1 0x20
#define WR_EDFALMT_PUMPTEMP1 0x40
#define WR_EDFALMT_PUMPTEC1 0x80
#define WR_EDFALMT_PUMPPOWER2 0x0100
#define WR_EDFALMT_PUMPBIAS2 0x0200
#define WR_EDFALMT_PUMPTEMP2 0x0400
#define WR_EDFALMT_PUMPTEC2 0x0800
#define WR_EDFALMT_PUMPPOWER3 0x1000
#define WR_EDFALMT_PUMPBIAS3 0x2000
#define WR_EDFALMT_PUMPTEMP3 0x4000
#define WR_EDFALMT_PUMPTEC3 0x8000
//define for pollStateBit and pollStateRep
#define POLL_CNST	0x01
//#define POLL_VAR	0x02
#define POLL_CTRL 	0x04
//#define POLL_MASK (POLL_CNST | POLL_VAR | POLL_CTRL)
//#define POLL_REP (POLL_VAR | POLL_CTRL)
#define WAIT_ACK	0x80	//pollStateRep 最高位表示该模块是否有效，1 表示等待响应
#define BB_VALID	0x40	//pollStateRep 次高位表示背板是否有效，	 1 表示有效

#define MAX_RETRY_NUM 8//5//3		//轮询失败时，最大重试次数

#define WR_USERFLG 0x01
#define WR_SETTING 0x02

#define WR_BB_TMP 0x04
#define WR_BB_FAN 0x08

#define WR_PS_P05V 0x04
#define WR_PS_N05V 0x08
#define WR_PS_P24V 0x10
#define WR_PS_P3P3V 0x20

#define WR_OT_PWR 0x04
#define WR_OT_LB 0x08
#define WR_OT_LC 0x10
#define WR_OT_LT 0x20
#define WR_OT_RF 0x40
#define WR_OT_DRV 0x80
#define WR_OT_OFS1 0x100
#define WR_OT_OFS2 0x200

#define WR_OR_CONFRFO1 0x04
#define WR_OR_ATT1 0x08
#define WR_OR_OP1 0x10
#define WR_OR_RF1 0x20
#define WR_OR_OFS1 0x40
#define WR_OR_CONFRFO2 0x80
//#define WR_OR_ATT2 0x100
#define WR_OR_OP2 0x200
#define WR_OR_RF2 0x400
#define WR_OR_OFS2 0x800
#define WR_OR_3STAT1 0x1000
#define WR_OR_3STAT2 0x2000
//#define WR_OR_EQ1 0x4000
//#define WR_OR_EQ2 0x8000

#define WR_AMP_ATT1 0x04
#define WR_AMP_RFO 0x08
#define WR_AMP_RFI 0x10
#define WR_AMP_OFS 0x20
#define WR_AMP_EQ 0x40

#define WR_RFSW_THRSHD 0x04
#define WR_RFSW_RF   0x08
#define WR_RFSW_OFS  0x10
#define WR_RFSW_ATT1 0x20
#define WR_RFSW_DLY 0x40

///add for edfa
#define WR_EDFA_OPINSET 0x04
#define WR_EDFA_OPOUTSET 0x08
//#define WR_EDFA_OUTOP 0x10

//C平台基本公共信息定义

/*背板数据结构定义*/
typedef struct{
	union{

	  unsigned char v[MAX_PUBLIC_LENGTH];
	  struct{
		  unsigned char modType;
		  unsigned char subType;
		  char rsv[2];
		  char InternalType[12];
		  char CustomType[16];
		  char Name[16];
		  char SN[16];
		  char HWVer[16];
		  char FWVer[16];
		  char PN[16];
		  char MaterialInfo[16];
		  char OEMInfo[16];
		  char OtherInfo[16];
	  }bb;

	  struct{
		  unsigned char modType;
		  unsigned char subType;
		  char rsv[2];
		  char InternalType[12];
		  char CustomType[16];
		  char Name[16];
		  char SN[16];
		  char HWVer[16];
		  char FWVer[16];
		  char PN[16];
		  char MaterialInfo[16];
		  char OtherInfo[32];
	 }mod;
   }pub;
}__PublicInfo;

typedef struct{
  
   union{
	 unsigned char v[MAX_CONFIG_LENGTH];

     struct{
	   char Color;
       char resv1;
	   char ValidM[2];
	   char ValidL[2];
	   char resv2[26];
	 }bb;

	 struct{
	   char fanNum;
	   char resv1;
	   char ValidM[2];
	   char ValidL[2];
	   char maxSpeed[2];
	   char resv2[24];
	 }fan;
    
     struct{
	   char power[2];
	   char ValidM[2];
	   char ValidL[2];
	   char InputVoltage[2];
	   char OutputVoltage[2];
	   char resv1[4];
	   char fanSpeed[2];
	   char resv2[16];
	 }ps;

	 struct{
	   char power[2];
	   char ValidM[4];
	   char ValidL[4];
	   char wavelength[4];
	   char resv1;
	   char outputNum;
	   char InputLevelA[2];
	   char InputLevelB[2];
	   char resv2[12];
	 }ot;

	 struct{
	   char outputLevel[2];
	   char ValidM[4];
	   char ValidL[4];
	   char OPInNum;
	   char RFOutNum;
	   char OAGCLow[2];
	   char OAGCScope[2];
	   char AttStart[2];
	   char AttScope[2];
	   char EQScope;
	   char resv1;
	   char resv2[10];
	 }dnor;

	 struct{
	   char outputLevel[2];
	   char ValidM[4];
	   char ValidL[4];
	   char OPInNum;
	   char RFOutNum;
	   char OAGCLow[2];
	   char OAGCScope[2];
	   char AttStart[2];
	   char AttScope[2];
	   char resv1[12];
	 }upor;

	 struct{
	   char gain[2];
	   char ValidM[4];
	   char ValidL[4];
	   char outputLevel[2];
	   char RFInNum;
	   char RFOutNum;
	   char resv1[2];
	   char AttStart[2];
	   char AttScope[2];  
	   char EQStart[2];
	   char EQScope[2];
	   char resv[8];
	 }amp;

	 struct{
       char insertionLoss;
	   char resv1;
	   char ValidM[4];
	   char ValidL[4];
	   char OPinLow[2];
	   char OPinHigh[2];
	   char RFinLow[2];
	   char RFinHigh[2];
	   char resv[14];
	 }sw;

	 struct{
       char outputPower[2];
	   char ValidM[4];
	   char ValidL[4];
	   char pumpNum;
	   char outputNum;
	   char workMode;
	   char resv1;
	   char MaxPower[2];
	   char MinPower[2];
	   char resv[14];
	 }EDFA;
   }cfg;
}__ConfigInfo;

typedef struct{
  union{

	  unsigned char v[MAX_STATUS_LENGTH];
	  struct{
	    char setting;
	    char resv[15];
	  }bb;
	  struct{
	    char setting;
		char indication;
		char resv[14];
	  }fan;
	  struct{
	    char setting;
		char resv[15];
	  }ps;
	  struct{
	    char setting;
		char resv[15];
	  }ot;
	
	  struct{
	    char setting;
		char RFOutSW;
		char resv[14];
	  }dnor; 
	  
	  struct{
	    char setting;
		char RFOutSW;
		char testPort;
		char resv1;
		char resv2[12];
	
	  }upor;
	
	  struct{
		char setting;
		char resv1[15];
	  }amp;
	  
	  struct{
	     char setting;
		 char resv1[15];
	  }sw;
	
	  struct{
		 char setting;
		 char OutputSwitch;
		 char resv[14];
	  }edfa;
  }lost_status;
}__Lost_Status;

typedef struct{
  union{

	  unsigned char v[MAX_STATUS_LENGTH];
	  struct{
	    char setting;
	    char resv[15];
	  }bb;
	  struct{
	    char setting;
		char ctrlMode;
		char speedSetting[2];
		char currentSetting[2];
		char resv[10];
	  }fan;
	  struct{
	    char setting;
		char resv[15];
	  }ps;
	  struct{
	    char setting;
		char gainType;
		char resv1[2];
		char inputAtt[2];
		char AnologChn[2];
		char DigitalChn[2];
		char LevelCorrection1[2];
		char LevelCorrection2[2];
		char resv2[2];
	  }ot;
	
	  struct{
	    char setting;
		char gainType;
		char swStrategy;
		char resv1;
		char RFOutAtt1[2];
		char RFOutAtt2[2];
		char EQ1;
		char EQ2;
		char waveLength[4];
		char LevelCorrection1[2];
		char LevelCorrection2[2];
		char resv2[6];
	  }dnor; 
	  
	  struct{
	    char setting;
		char gainType;
		char resv1[2];
		char RFOutAtt1[2];
		char RFOutAtt2[2];
		char waveLength[4];
		char LevelCorrection1[2];
		char LevelCorrection2[2];
		char resv2[8];	
	  }upor;
	
	  struct{
		char setting;
		char gainType;
		char switchStrategy;
		char resv1;
		char RFOutAtt1[2];
		char RFOutAtt2[2];
		char RFInAtt1[2];
		char RFInAtt2[2];
		char EQ1;
		char EQ2;
		char LevelCorrection1[2];
		char LevelCorrection2[2];
		char resv2[6];
	  }amp;
	  
	  struct{
	     char setting;
		 char resv1;
		 char switchStrategy;
		 char switchDelay;
		 char switchPower[2];
		 char switchLevel[2];
		 char OPinCorrection1[2];
		 char OPinCorrection2[2];
		 char OPoutCorrection[2];
		 char RFinCorrection1[2];
		 char RFinCorrection2[2];
		 char RFoutCorrection[2];
		 char resv2[4];
	  }sw;
	
	  struct{
		 char setting;
		 char resv1;
		 char OutputPower[2];
		 char opCorrection1;
		 char opCorrection2;
		 char resv[10];
	  }edfa;
  }unlost_status;
}__UnLost_Status;

typedef struct{	
  union {
    unsigned char v[MAX_VAR_LENGTH];
    struct{
	  char state;
	  char alarmNum;
	  char mod_Online[4];
	  char devTemp[2];
	  char devTemp1[2];
	  char devTemp2[2];
	  char devTemp3[2];
	  char devTemp4[2];
	  char devTemp5[2];
	  char devTemp6[2];
//	  char devTemp7[2];
//	  char devTemp8[2];
	  unsigned int mod_PollRes;
	  unsigned int mod_OnlineChange;
    }bb;
   struct{
	  char state;
	  char alarmNum;
	  char mainWorkState;
	  char resv1;
	  char fanSpeed1[2];
	  char fanSpeed2[2];
	  char fanSpeed3[2];
	  char fanSpeed4[2];
	  char fanSpeed5[2];
	  char fanSpeed6[2];
//	  char fanSpeed7[2];
//	  char fanSpeed8[2];
	  char fanCurrent1[2];
	  char fanCurrent2[2];
	  char fanCurrent3[2];
	  char fanCurrent4[2];
	  char fanCurrent5[2];
	  char fanCurrent6[2];
//	  char fanCurrent7[2];
//	  char fanCurrent8[2];
   }fan;
   
   struct{
	 char state;
	 char alarmNum;
	 char mainWorkState;
	 char resv1;
	 char PSTemp[2];
	 char PSFanSpeed1[2];
	 char PSFanSpeed2[2];
	 char Voltage1[2];
	 char Current1[2];
   }ps;

   struct{
     char state;
	 char alarmNum;
	 char resv1[2];
	 char InternalTemp[2];
	 char resv2[2];
	 char OutputPwr1[2];
	 char LaserBias1[2];
	 char LaserTemp1[2];
	 char TecCurrent1[2];
	 char OutputPwr2[2];
	 char LaserBias2[2];
	 char LaserTemp2[2];
	 char TecCurrent2[2];
	 char DriveLevel1[2];
	 char AgcLevel1[2];
	 char InputLevel1[2];
	 char resv3[2];
	 char DriveLevel2[2];
	 char AgcLevel2[2];
	 char InputLevel2[2];
	 char resv4[2];
   }ot;

   struct{
	 char state;
	 char alarmNum;
	 char resv1[2];
	 char InternalTemp[2];
	 char resv2[2];
	 char InputPwr1A[2];
	 char InputPwr1B[2];
	 char InputPwr2A[2];
	 char InputPwr2B[2];
	 char outputLevel1[2];
	 char outputLevel2[2];
	 char outputLevel3[2];
	 char outputLevel4[2];
   }or;

   struct{
	 char state;
	 char alarmNum;
	 char resv1[2];
	 char InternalTemp[2];
	 char resv2[2];
	 char outputLevel1[2];
	 char outputLevel2[2];
	 char outputLevel3[2];
	 char outputLevel4[2];
   }amp;

   struct{
	 char state;
	 char alarmNum;
	 char resv1[2];
	 char InternalTemp[2];
	 char resv2[2];
	 char InputLevel1[2];
	 char InputLevel2[2];
	 char OutputLevel[2];
	 char resv3[2];	
   }sw;


   struct{
	 char state;
	 char alarmNum;
	 char resv1[2];
	 char InternalTemp[2];
	 char resv2[2];
	 char InputPower1[2];
	 char OutputPower1[2];
	 char OutputPower2[2];

	 char pumpPwr1[2];
	 char pumpBias1[2];
	 char pumpTemp1[2];
	 char pumpTec1[2];
	 char pumpPwr2[2];
	 char pumpBias2[2];
	 char pumpTemp2[2];
	 char pumpTec2[2];
	 char pumpPwr3[2];
	 char pumpBias3[2];
	 char pumpTemp3[2];
	 char pumpTec3[2];
   }edfa;
  }var;
}__Var;


typedef struct{

   union{
	 unsigned char v[MAX_LIMIT_SIZE];
	 struct{
	   char devTempLMT[12];
	 }bb;

	 struct{
	   char FanSpeedLMT[12];
	   char FanCurrentLMT[12];
	 }fan;

	 struct{ 
	   char TempLMT[12];
	   char FanSpeedLMT[12];
	   char Voltage1LMT[12];
	   char Current1LMT[12];
	 }ps;

	 struct{
	   char InternalTempLMT[12];
	   char FanSpeedLMT[12];
	   char OutputPwrLMT[12];
	   char pumpBiasLMT[12];
	   char pumpTempLMT[12];
	   char pumpTECLMT[12];
	   char DriveLevelLMT[12];
       char AgcLevelLMT[12];
	   char InputLevel1LMT[12];
	   char InputLevel2LMT[12];
	 }ot;

	 struct{
	   char InternalTempLMT[12];
	   char FanSpeedLMT[12];
	   char InputPowerLMT[12];
	   char OutputLevelLMT[12];
	 }or;

	 struct{
	   char InternalTempLMT[12];
	   char FanSpeedLMT[12];
	   char OutputLevelLMT[12];
	   char InputLevelLMT[12];
	 }amp;

	 struct{
	   char InternalTempLMT[12];
	   char FanSpeedLMT[12];
	   char InputLevelLMT[12];
	   char OutputLevelLMT[12];
	 }sw;

	 struct{
	   char InternalTempLMT[12];
	   char FanSpeedLmt[12];
	   char InputPowerLMT[12];
	   char OutputPowerLMT[12];
	   char pumpPower1LMT[12];
	   char pumpBias1LMT[12];
	   char pumpTemp1LMT[12];
	   char pumpTEC1LMT[12];
	   char pumpPower2LMT[12];
	   char pumpBias2LMT[12];
	   char pumpTemp2LMT[12];
	   char pumpTEC2LMT[12];
	   char pumpPower3LMT[12];
	   char pumpBias3LMT[12];
	   char pumpTemp3LMT[12];
	   char pumpTEC3LMT[12];

	 }edfa;
   }limit;
}__Limit;

/*
typedef struct {
	char modType;
	char rsv1;
	char modName[16];
	char modTypeInternal[8];
	char modTypeCustom[12];	
	char modSN[16];
	char modPN[16];	
	char modFW[16];
	char modInf[32];
} __moduleConstant;

typedef struct {
	union {
		unsigned char v[MAX_VAR_LENGTH];
  		struct {
		    unsigned char basicStatus;
			unsigned char curAlarmNum;
			unsigned char mod_Online[4];
			char setting;

			char g1fan1Spd[4];
			char g1fan2Spd[4];
			char g2fan1Spd[4];
			char g2fan2Spd[4];
			
			char temp1[4];

			unsigned int mod_PollRes;
			unsigned int mod_OnlineChange;
		} bb;

		struct {
			unsigned char curAlarmNum;
//			char curProtectState;
			char reserved;
//			char enableProtect;
			char setting;

			char P05V[4];
			char N05V[4];
			char P24V[4];
			char P3p3V[4];

		} ps;

 		struct {
			unsigned char curAlarmNum;
			char curProtectState;
			char reserved;
			char enableProtect;
			char setting;

			char otPwr1[4];
			char otLB1[4];
			char otLC1[4];
			char otLT1[4];
			char otRFi1[4];
			char otRFDrv1[4];
			char otPwr2[4];
			char otLB2[4];
			char otLC2[4];
			char otLT2[4];
			char otRFi2[4];
			char otRFDrv2[4];
		} ot;

 		struct {
			unsigned char curAlarmNum;
			char curProtectState;
			char reserved;
			char enableProtect;
			char setting;

			char orOp1[4];
			char orRF1[4];
			char orOp2[4];
			char orRF2[4];
		} or;

 		struct {
			unsigned char curAlarmNum;
			char curProtectState;
			char reserved;
			char enableProtect;
			char setting;

			char ampRFo[4];
			char ampRFi[4];
		} amp;

		struct {
			unsigned char curAlarmNum;
			char curProtectState;
			char reserved;
			char enableProtect;
			char setting;
			
			char rfIn1[4];
			char rfIn2[4];
		} sw;
		///add for edfa
		struct {
		    unsigned char curAlarmNum;
			char curProtectState;
			char otherState;
			char enableProtect;
			char setting;
			char OpOutputPower[4];
			char OpInputPower[4];
			char LaserBias1[4];
			char LaserTEC1[4];
			char PumpTemp1[4];
			char PumpPower1[4];

			char LaserBias2[4];
			char LaserTEC2[4];
			char PumpTemp2[4];
			char PumpPower2[4];

						
			char ModuleTemp[4];
			char debug[4];

		}edfa;				   
	} var;

} __modVarible;


typedef struct {
	union {
		unsigned char v[MAX_CTRL_LENGTH];
		struct {
			unsigned char userFlg;
			unsigned char set;
			
			char TEMPLMT[21];
			char FANSPDLMT[21];
			char FANSPDSET[4][4];
			char FANONOFFCTRL[4];
		} bb;

		struct {
			unsigned char userFlg;
			unsigned char set;

			char P05VLMT[21];
			char N05VLMT[21];
			char P24VLMT[21];
			char P3p3VLMT[21];
		} ps;

 		struct {
			unsigned char userFlg;
			unsigned char set;

			char otPwrLMT[21];
			char otLBLMT[21];
			char otLCLMT[21];
			char otLTLMT[21];
			char otRFiLMT[21];
			char otRFDrvLMT[21];
			signed char RF1Offset;
			signed char RF2Offset;
		} ot;

  		struct {
			unsigned char userFlg;
			unsigned char set;

			char orConfRFO1[4];
			char orAtt1;
			signed char RF1Offset;
			char orOp1LMT[21];
			char orRF1LMT[21];
			char orConfRFO2[4];
			char orAtt2;
			signed char RF2Offset;
			char orOp2LMT[21];			
			char orRF2LMT[21];
			char set3Stat1;
			char set3Stat2;
		} or;



 		struct {
			unsigned char userFlg;
			unsigned char set;

 			signed short ampAtt;
			char ampRFoLMT[21];
			char ampRFiLMT[21];
			signed char RFOffset;
			signed char RFOffsetI;
			signed short eq;
		} amp;

		struct {
			unsigned char userFlg;
			unsigned char set;
			
			char rfswThreshold[4];
			char rfswLMT[21];
			signed char rf1Offset;
			signed char rf2Offset;
			char rfAtt[2];
			char swDelay[2];	//second
//			signed short rfAtt;
			unsigned char rsv[1];
		} sw;

		struct {
			unsigned char userFlg;
			unsigned char set;
			char OpOutSet;	  //输出光功率设置
			char reserved1;	  //
//			char reserved[4];
			char ModTempLMT[21];
			char OpOutLMT[21];
			char OpInLMT[21];

			char LaserBias1LMT[21];
			char LaserTEC1LMT[21];
			char PumpTemp1LMT[21];
            char PumpPwr1LMT[21];            

			char LaserBias2LMT[21];
			char LaserTEC2LMT[21];
			char PumpTemp2LMT[21];
            char PumpPwr2LMT[21];            


		}edfa;
	} ctrl;
} __modCtrl;
*/

typedef struct {
	__queryCtrl queryCtrl;
///	__moduleConstant moduleConstant;
///	__modVarible modVarible; 
///	__modCtrl modCtrl;
	//for C 平台
	__PublicInfo modPub;
	__ConfigInfo modConfig;
	__Lost_Status modLostStatus;
	__UnLost_Status modUnLostStatus;
	__Var modVar;
	__Limit modLimit;

} __module;


typedef struct {
    S16 entPhysicalId;
	S16 heModPhysicalClass;
	S16 heModIsFRU;
	S16 heOpTxUnitOutputStatus;
	S16 heOpTxUnitOnOffControl;

	S16 heOpTxInputIndex[2];
	S16 heOpTxInputRFPower[2];
	S16 heOpTxInputModulatorBias[2];
	S16 heOpTxInputAGCMode[2];
	S16 heOpTxInputModulationMode[2];
	S16 heOpTxInputRFPadLevel[2];
	S16 heOpTxAGCLevel[2];
	S16 heOpTxLaserDriveLevel[2];
	S16 heOpTxConfigurationDriveLevel[2];
	S16 heOpTxConfigurationDriveLevelAtt[2];
	S16 heOpTxRFOffset[2];

	S16 heOpTxLaserIndex[2];
	S16 heOpTxLaserTemp[2];
	S16 heOpTxLaserBiasCurrent[2];
	S16 heOpTxLaserOutputPower[2];
	S16 heOpTxLaserTECCurrent[2];
	S16 heOpTxLaserOutputStatus[2];
	S16 heOpTxLaserOnOffControl[2];
	char heOpTxLaserType[14];	//unisolated FP, isolated FP, uncooled DFB, cooled DFB, ITU
	U32 heOpTxLaserWavelength;
} __heSCTEOT;

typedef struct {
    S16 entPhysicalId;
    S16 heModPhysicalClass;
	S16 heModIsFRU;
	U32 heOpRxInputIndex[4];
	S16 heOpRxInputPower[4];				//0.1 dBm
	U32 heOpRxInputWavelengthControl[4];	//0.01 nm
	S16 heOpRxInputStatus[4];				//normal (1), fault (2)

	U32 heOpRxOutputIndex[4];
	S16 heOpRxOutputControl[4];	//off (1),on (2)
	S16 heOpRxOutputGainType[4];	//constantPower (1), constantGain (2)
	S16 heOpRxOutputPower[4];		//0.1 dBm
	S16 heOpRxConfigurationOutputLevel[4];
	S16 heOpRxOutputRFPadLevel[4];	//0.1 dB
	S16 heOpRxConfigurationOutputRFlevelatt[4];
	S16 heOpRxOutputRFOffset[4];
	char *heOpRxOutputRFName[4];
	S16 heOpRxRFRev3SCtrl[4];
} __heSCTEOR; //same with __heUPOR1



typedef struct {
	S16 heRFAmpGainControlMode;		//none(1), alc(2), asc(3), agc(4), alsc(5)
	S16 heRFAmpAttenuatorControl;	//0.1 dB
	S16 heRFAmpSlopeControl;		//0.1 dB

	S16 heRFAmpOutputIndex;
	char *heRFAmpOutputDescription;
	S16 heRFAmpOutputLevel;				//0.1 dBmV
	S16 heRFAmpOutputAttenuatorControl;	//0.1 dB
	S16 heRFAmpOutputOffset;

	S16 heRFAmpInputIndex;
	char *heRFAmpInputDescription;
	S16 heRFAmpInputLevel;				//0.1 dBmV
	S16 heRFAmpInputOffset;
} __heRFAMP1;

typedef struct {
	S16 heRFSwitchMode;				//automatic(1), manual(2)
	S16 heRFSwitchControl;			//pathA(1), pathB(2), cross(3), bar(4), bothA(5), bothB(6)
	S16 heRFSwitchRevertEnable;		//off(1), on(2), meaningless(3)
	S16 heRFSwitchState;			//pathA(1), pathB(2), cross(3), bar(4), bothA(5), bothB(6)
	S16 heRFSwitchFailoverStatus;	//normal(1),fault(2)
	S16 heRFSwitchBothInputStatus;	//normal(1),fault(2)
	S16 heRFSwitchHysteresis;		
	S16 heRFSwitchWaitToRestoreTime;
	S16 heRFSwitchSensorMode;		//internal(1), external(2)

	S16 heRFSwitchInputIndex[2];
	S16 heRFSwitchInputRFLevel[2];
	S16 heRFSwitchSetInputPowerThreshold[2];				//0.1 dBmV
	S16 heRFSwitchInputStatus[2];		//normal(1),fault(2)
	char *heRFSwitchInputDescription[2];
	S16 heRFSwitchInputExternalControl[2];		//normal(1),fault(2)
	S16 heRFSwitchInputRFOffset[2];

	S16 heRFSwitchOutputIndex;
	char *heRFSwitchOutputDescription;
} __heRFSW1;

typedef struct{
 	unsigned char pumpNum;
	unsigned char workMode;
	unsigned char maxPower;
	unsigned char minPower;
	unsigned char ModVersion;
    //heOpAmpUnitTable - heOpAmpUnitEntry  
	S16 heOpAmpUnitOutputStatus; //光放大单元的输出状态,off(1),on(2)
	S16 heOpAmpUnitOnOffControl; //这个变量控制光放大单元的输出状态,off(1),on(2)

	//heOpAmpInputTable - heOpAmpInputEntry 
	S16 heOpAmpInputIndex; //光放大单元输入端口序号
	S16 heOpAmpInputPower; //输入光功率，单位0.1 dBm

	//heOpAmpLaserTable  - heOpAmpLaserEntry 
	S16 heOpAmpLaserIndex[2]; //激光器序号
	S16 heOpAmpLaserTemp[2];  //激光器的温度，单位0.1 摄氏度
	S16 heOpAmpLaserBiasmandatory[2]; //激光器偏置电流，单位mA	
	S16 heOpAmpLaserOutputPower[2];//激光器输出功率，单位0.1 dBm
	S16 heOpAmpLaserTECmandatory[2]; //激光器致冷电流，单位mA
	char heOpAmpLaserType[32];  //激光器类型
	
	//heOpAmpOutputTable - heOpAmpOutputEntry  
	S16 heOpAmpOutputIndex;	 //光放大单元输出端口序号
	S16 heOpAmpSetOpticalOutputPower;//设置光放大器输出功率，单位0.1 dBm
	S16 heOpAmpGainPerWavelength; //控制单位波长的恒定增益，单位0.1 dBm
	S16 heOpAmpOutputPower;	 //输出光功率，单位0.1 dBm				
	S16 heOpAmpOutputGainType;//控制输出增益类型。可以是恒定功率输出(1)，也可以是恒定增益输出(2)。

    
	
	S16 heModuleTemp; //Module Temp
}__heEDFA;	 ///add for edfa

//C平台背板数据结构定义
typedef struct{
  S16 entPhysicalId;
  S16 heBBIsFRU; //True
  S16 heBBPhysicalClass; 	//backplane
  S16 heBBRelPos;
  S16 devTemp;
  S16 devTemp1;
  S16 devTemp2;
  S16 devTemp3;
  S16 devTemp4;
  S16 devTemp5;
  S16 devTemp6;
	S16 devTemp7;
	S16 devTemp8;
}__insidePlantBB;

//C平台风扇单元描述
typedef struct {
  S16 heFanUnitId;
	S16 entPhysicalId;
  S16 heFanPhysicalClass;	//Fan
  S16 heFANIsFRU; //True
	S16 heFanUnitAlarm;
	S16 heFansStatusId[6];
	S16 heFansStatusCur[6];
	S16 heFansStuatusAlm[6];
	S16 heFanSpeed[8];

	S16 heFanCurrent[8];

} __insidePlantScteFans;

typedef struct {
  S16 entPhysicalId;
  S16 hePSPhysicalClass;	//PS
  S16 hePSIsFRU;
	U32 hePsUnitCurrentIN;
	U32 hePsUnitPowerIN;
	char *hePsUnitDescr;
	S16 hePsInterTemp;
	S16 hePsUnitVoltageIN;
	S16 hePsOutputIndex[MAX_PS_MODULE_OUTPUT];
	U32 hePsOutputCurrent[MAX_PS_MODULE_OUTPUT];
	S16 hePsOutputVoltage[MAX_PS_MODULE_OUTPUT];
	U32 hePsOutputPower[MAX_PS_MODULE_OUTPUT];
	S16 hePsFanSpeed1;
	S16 hePsFanSpeed2;
} __insidePlantSctePs;



void devAppInit(void);
int queryBB(int slot);
int queryPWR(int slot);
int querySLT(int slot);
int queryFAN(int slot);

int floatToInt(char *ft, float ratio);
int floatToIntMSB(char *ft,float ratio);
S16 ByteToShort(char * ft, float ratio);
S16 ByteToShortMSB(char *ft,float ratio);


void fixLenCopyWithTrimRight(char *des, char * src, int len);
void fillAProperty(__aProperty* apPtr, char * ap, float ratio, byte alarmChg, byte TrapEn);
void UpdateThreshold(__aProperty* apPtr, char * ap, float ratio);
///void fillAProperty_mW2dB(__aProperty* apPtr, char * ap, float ratio, byte alarmChg, byte TrapEn);
void fillFParam(char * fPtr, float fVal);
void fillIParam(char * iPtr, int iVal);
void fillLimite(char * lmtPtr, float lmtLL, float lmtL, float lmtH, float lmtHH, float lmtDB, char En);
void filliLimite(char * lmtPtr, int lmtLL, int lmtL, int lmtH, int lmtHH, int lmtDB, char En);

void SetFtParam(char * pPm, float ftVal);
void SetIParam(char * pPm, int iVal);
/**
void devAppBBConst(char *pBuf);
void devAppBBVar(char *pBuf);
void devAppBBCtrl(char *pBuf);
void devAppBBWrRes(char *pBuf);
void devAppPWRConst(int module, char *pBuf);
void devAppPWRVar(int module, char *pBuf);
void devAppPWRCtrl(int module, char *pBuf);
void devAppPWRWrRes(int module, char *pBuf);
void devAppPwrErr(int module, char *pBuf);
void devAppSLTConst(int module, char *pBuf);
//void devAppSLTVar(int module, char *pBuf);
void devAppSLTCtrl(int module, char *pBuf);
void devAppSLTWrRes(int module, char *pBuf);
void devAppSltErr(int module, char *pBuf);	 **/

//C平台命令处理函数
void devAppBBPubCfg(char *pBuf);
void devAppBBPublic(char *pBuf);
void devAppBBConfig(char *pBuf);
void devAppBBLostStatus(char *pBuf);
void devAppBBUnLostStatus(char *pBuf);
void devAppBBLimit(char *pBuf);
void devAppBBVar(char *pBuf);
void devAppBBWrLostStatus(char *pBuf);
void devAppBBWrUnLostStatus(char *pBuf);
void devAppBBWrLimit(char *pBuf);
void devAppBBWrFactory(char *pBuf);
void devAppBBPowerOff(void);

void devAppFanPubCfg(int module, char *pBuf);
void devAppFanPublic(int module, char *pBuf);
void devAppFanConfig(int module, char *pBuf);
void devAppFanLostStatus(int module, char *pBuf);
void devAppFanUnLostStatus(int module, char *pBuf);
void devAppFanLimit(int module, char *pBuf);
void devAppFanVar(int module, char *pBuf);
void devAppFanWrLostStatus(int module, char *pBuf);
void devAppFanWrUnLostStatus(int module, char *pBuf);
void devAppFanWrLimit(int module, char *pBuf);
void devAppFanWrFactory(int module, char *pBuf);
void devAppFanPowerOff(int module);


void devAppFanWrRes(int module, char *pBuf);
void devAppFanErr(int module, char *pBuf);

void devAppPSPubCfg(int module, char *pBuf);
void devAppPSPublic(int module, char *pBuf);
void devAppPSConfig(int module, char *pBuf);
void devAppPSLostStatus(int module, char *pBuf);
void devAppPSUnLostStatus(int module, char *pBuf);
void devAppPSLimit(int module, char *pBuf);
void devAppPSVar(int module, char *pBuf);
void devAppPSWrLostStatus(int module, char *pBuf);
void devAppPSWrUnLostStatus(int module, char *pBuf);
void devAppPSWrLimit(int module, char *pBuf);
void devAppPSWrFactory(int module, char *pBuf);
void devAppPSPowerOff(int module);
void devAppPSWrRes(int module, char *pBuf);
void devAppPSErr(int module, char *pBuf);


void devAppSLTPubCfg(int module, char *pBuf);
void devAppSLTPublic(int module, char *pBuf);
void devAppSLTConfig(int module, char *pBuf);
void devAppSLTLostStatus(int module, char *pBuf);
void devAppSLTUnLostStatus(int module, char *pBuf);
void devAppSLTLimit(int module, char *pBuf);
void devAppSLTVar(int module, char *pBuf);

void devAppSLTWrLostStatus(int module, char *pBuf);
void devAppSLTWrUnLostStatus(int module, char *pBuf);
void devAppSLTWrLimit(int module, char *pBuf);
void devAppSLTWrFactory(int module, char *pBuf);
void devAppSLTPowerOff(int module);
void devAppSLTWrRes(int module, char *pBuf);
void devAppSLTErr(int module, char *pBuf);

void queryDevIF(void);

int devAppHandleQuickKey(char *pBuf);

extern __module * queryModPtr;
extern __module devBB;
//extern __module devPowerSupply[MAX_PS_MODULE];
extern __module slotModule[MAX_SM_MODULE + MAX_PS_MODULE + MAX_FAN_MODULE];
//extern __module * slotModule;
#define BAKUP_BB_CONST		{ (void*)&devBB.moduleConstant, sizeof(__moduleConstant)}
#define BAKUP_BB_CTRL		{ (void*)&devBB.modCtrl, 64}

#endif /* __DEVAPPP__ */
