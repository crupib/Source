
#include "stdafx.h"
#include "Main.h"
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
/*
//***** These are comments from the original code.
'///////////////////////////////////////////////////////////////////////////////
'///////////////////////////////////////////////////////////////////////////////
'
'
'PROGRAM FOR THE CONTROL PID OF two Motors WITH hp ENCODER HEDS-5540 100 line resolution
'date 05-28-2007 'version BASCOM 1.8.11.3
'the serial port in this version does not interfere with the timer 0-1 '
'transmission of the position performed at the end of the cycle, PID at beginning of the cycle 'MAIN Loop
'**************************************************f*********************************************************
'
'
' Input Format Command:
' Command [par1] [par2] [par3] Cr
'
' Out Format Command:
' [MtrNum] [command], [par1]
'
' Input Commands From Windows Terminal [ 115200 , 8 , N , 1 ]
' Not Case Sentitive
'.................................................................................................................
' Rstf                                   RESET CPU WITH WATCHDOG START
' Made                                   WHO WROTE PROGRAMM
' Ver                                    VERSION OF PROGRAMM
' Skp  [MtrNum] [kp Value]               SET PROPORZIONAL PID 0-1000 MAX
' Ski  [MtrNum] [ki Value]               SET INTEGRAL     PID 0-100  MAX
' Skd  [MtrNum] [kd Value]               SET DERIVATIVE   PID 0-1000 MAX
' Vmax [MtrNum] [vmax Value]             SET MAX VELOCITY IN PROPORZIONAL VELOCITY PROFILE 0-255
' Svm  [MtrNum] [svm Value]              SET MAX VELOCITY IN TRAPEZOIDAL MODE 0-255
' Spid [MtrNum] [kp] [ki] [kd]           SET PID MOTOR KP KI KD
' Stime[stime Value]                     SET PID EXECUTION TIME 0-10msec/default=3.5 + .5 lt=4msec
' Smode[MtrNum] [mode]                   SET SINGLE MODE FOR ONE MOTOR
' Svel [MtrNum] [svel Value]             SET MOTOR WITH INTEGRAL VELOCITY PROFILE AND MOVE 0-255
' Velo [vel 1] [vel 2]                   SET TWO INDEPENDENT SPEED FOR MOTORS 0-255 & 0-255
' Spwm [MtrNum] [spwm Value]             SET MAX PWM OUT FOR TORQUE LIMIT 0-255
' Sacc [MtrNum] [acc Value]              SET ACCELERATION DEGREE 1-89 DEGREES
' Sang [MtrNum] [angular Factor]         SET ANGULAR FACTOR FOR VELOCITY PROFILE 1-100
' Go   [MtrNum] [position Value]         GO TO POSITION IN POSITION MODE CONTROL +- 23 BITS
' Pos  [MtrNum] [position Value] [speed] SET POSITION IN TRAPEZOIDAL PROFILE 0-255
' Move [position 1] [position 2]         MOVE BOTH MOTORS TO POS 1 & POS 2  +-23 BITS TRAPEZOIDAL MODE
' Velp [position 1] [position 2]         MOVE CONTINUOS POSITION WITH VARIBLE PROPORZIONAL VELOCITY
' Start is Start_move                    START MOVE IF START_MOVE = FALSE
' Stop is Mode_idle                      STOP MOVE AND POWER DOWN MOTORS
' Gmax [MtrNum]                          GET MAX VELOCITY IN VELOCITY PROFILE MODE
' Gvm [MtrNum]                           GET MAX VELOCITY IN TRAPEZOIDAL MODE
' Gve [MtrNum]                           GET ABSOLUTE SPEED FROM ENCODER
' Enc [MtrNum]                           READ ABSOLUTE ENCODER POSITION
' Gpid [MtrNum]                          GET PID MOTOR VALUES
' Gtime                                  GET PID EXECUTION TIME
' Szp [MtrNum]                           SET ZERO POSITION
' Idle [MtrNum]                          POWER OFF MOTOR
' Gsm [MtrNum]                           GET Motor STATE 0=STOP 1=MOVE
' Mode [mode]                            SET MODE PROFILE FOR 2 Motor 0,1,2,3,4
' Gmode                                  GET PROFILE MODE SETTING
' Gpwm [MtrNum]                          GET MAX PWM OUT
' Rpwm [MtrNum]                          READ REAL PWM OUT TO CONTROL MAX CURRENT
' Gacc [MtrNum]                          GET ACCELERATION PROFILE IN DEGREE 1-89
' Gang [MtrNum]                          GET ANGULAR FACTOR
' Rst [MtrNum]                           RESET ENCODER
'.............................................................................................................

//**** Was commented out in basic code
'$prog &HFF , &H6F , &HD7 , &H00       'FUSE BITS
'$regfile = "m128def.dat"
'$crystal = 20000000 '18432000 'over clocked CPU
'$baud = 115200
'$hwstack = 64
'$swstack = 64
'$framesize = 64


'-------------------------------------------------------------------------------
*/
/*------------------ - ALIAS---------------------------------------------------- -
M1_pwm Alias Pwm1a : M1_pwm = 0       'pwm out Motor x
M2_pwm Alias Pwm1b : M2_pwm = 0       'pwm out Motor y
Ddrd.2 = 0 : Portd.2 = 1       'pullup x int 0
Ddrd.3 = 0 : Portd.3 = 1       'pullup x int 1
Limit_1 Alias Pinb.0 : Ddrb.0 = 0       'limit 1 - Interrupt 1
Limit_2 Alias Pinb.1 : Ddrb.1 = 0       'limit 2 - Interupt 2
Aux_0 Alias Pinb.2 : Ddrb.2 = 0 : Portb.2 = 1       '*pullup aux 0 *CHANGE-to (X)&(Y)*
Aux_1 Alias Pinb.3 : Ddrb.3 = 0 : Portb.3 = 1       '*pullup aux 1 *encoder overflow *
Stop1_bit Alias Portb.4 : Ddrb.4 = 1       '*status Motor 1 *CHANGE-to encoder(X)&(Y)*
Stop2_bit Alias Portc.6 : Ddrc.6 = 1       '*status Motor 2 *direction.*
M1dir_bit Alias Portd.6 : Ddrd.6 = 1       'direction Motor x
M2dir_bit Alias Portd.7 : Ddrd.7 = 1       'direction Motor y
Motor_led Alias Portc.7 : Ddrc.7 = 1       'led test
Test1_led Alias Portf.7 : Ddrf.7 = 1       'KJL Added
Hctl_xy Alias Portc.0 : Ddrc.0 = 1       'selection xy hctl2032
Hctl_sel1 Alias Portc.1 : Ddrc.1 = 1       'selection byte bit 0
Hctl_sel2 Alias Portc.2 : Ddrc.2 = 1       'selection byte bit 1
Hctl_oe Alias Portc.3 : Ddrc.3 = 1       'selecion oe hctl data
Hctl_rst_1 Alias Portc.4 : Ddrc.4 = 1       'reset encoder x
Hctl_rst_2 Alias Portc.5 : Ddrc.5 = 1       'reset encoder y
Hctl_data Alias Pina : Ddra = &H00       'porta input data encoder
'-------------------------------------------------------------------------------
*/
//-------------------------------------------------------------------------------------
//Registers to be filled in per board


#define PINA   0x02 
#define PINB   0x05
#define PINC   0x08
#define PIND   0x0b

#define DDRC   0x07
#define DDRB   0x04
#define DDRA   0x01
#define DDRD   0x0a
#define DDRF   0x0e

#define PORTA  0x00  
#define PORTC  0x06
#define PORTB  0x03
#define PORTF  0x10
#define PORTD  0x09

#define UDR    0x0c
#define USR    0x0d

#define Deg2rad(angle) ((angle) / 180.0 * M_PI)
byte ports[40] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,3 };

/*
$regfile = "m128def.dat"       ' specify the used micro
$crystal = 20000000 ' used crystal frequency
$baud = 19200       ' use baud rate
$hwstack = 64       ' default use 32 for the hardware stack
$swstack = 64       '10       ' default use 10 for the SW stack
$framesize = 64     '40     ' default use 40 for the frame space
*/
static const char regfile[] = "m128def.dat"; //      ' specify the used micro
int  crystal = 20000000; //' used crystal frequency - Obsolete
int  baud = 19200;       //' use baud rate
int  hwstack = 64;       //' default use 32 for the hardware stack
int  swstack = 64;       //'10       ' default use 10 for the SW stack
int  framesize = 64;     //'40     ' default use 40 for the frame space
/*
Const Si = 1
Const No = 0
Const Vb6 = No      'change to 'YES' to use serial port comm with Visual basic 6
'                    NO = WINDOWS terminal
*/
#define Si = 1
#define No = 0
#define Vb6 = "No"
/*
'---------------------------- CONSTANTS -----------------------------------------
Const Mode_pos = 0
Const Mode_vel = 1
Const Mode_trp = 2
Const Mode_velp = 3
Const Mode_idle = 4
Const True = 1
Const False = 0
*/
const byte Mode_pos = 0;
const byte Mode_vel = 1;
const byte Mode_trp = 2;
const byte Mode_velp = 3;
const byte Mode_idle = 4;
/*
'-------------------------------------------------------------------------------
'------------------- SUBROUTINE ------------------------------------------------
'-------------------------------------------------------------------------------
Declare Sub Hctl_2032(byval Mtrnum As Byte)
Declare Sub Exe_pid(byval Mtrnum As Byte, Byval Pid_setpoint As Long, Byval Pid_actual As Long)
Declare Sub Configure_pid(byval M As Byte, Byval Mtrnum_kp As Long, Byval Mtrnum_ki As Long, Byval Mtrnum_kd As Long)
Declare Sub Init_parameter(byval M As Byte)
Declare Sub Calc_trapez(byval M As Byte)
Declare Sub Print_com(byval Mt As Byte, Byval Stringa As String, Byval Value As Long)
Declare Sub Set_mode(byval Mode_control As Byte)
Declare Function Max_minl(byval I As Long) As Long       ' keep between -255 to 255
*/
void Hctl_2032(byte Mtrnum);
void Exe_pid(byte * Mtrnum, long * Pid_setpoint, long * Pid_actual);
void Configure_pid(byte mtr, long Mtrnum_kp, long Mtrnum_ki, long Mtrnum_kd);
void Init_parameter(byte M);
void Calc_trapez(byte M);
void Print_com(byte Mt, char * Stringa, long Value);
void Set_mode(byte Mode_control);
long Max_minl(long I);

void main(void)
{
	/*------------------ - ALIAS---------------------------------------------------- -
	M1_pwm Alias Pwm1a : M1_pwm = 0       'pwm out Motor x
	M2_pwm Alias Pwm1b : M2_pwm = 0       'pwm out Motor y
	Ddrd.2 = 0 : Portd.2 = 1       'pullup x int 0
	Ddrd.3 = 0 : Portd.3 = 1       'pullup x int 1
	Limit_1 Alias Pinb.0 : Ddrb.0 = 0       'limit 1 - Interrupt 1
	Limit_2 Alias Pinb.1 : Ddrb.1 = 0       'limit 2 - Interupt 2
	Aux_0 Alias Pinb.2 : Ddrb.2 = 0 : Portb.2 = 1       '*pullup aux 0 *CHANGE-to (X)&(Y)*
	Aux_1 Alias Pinb.3 : Ddrb.3 = 0 : Portb.3 = 1       '*pullup aux 1 *encoder overflow *
	Stop1_bit Alias Portb.4 : Ddrb.4 = 1       '*status Motor 1 *CHANGE-to encoder(X)&(Y)*
	Stop2_bit Alias Portc.6 : Ddrc.6 = 1       '*status Motor 2 *direction.*
	M1dir_bit Alias Portd.6 : Ddrd.6 = 1       'direction Motor x
	M2dir_bit Alias Portd.7 : Ddrd.7 = 1       'direction Motor y
	Motor_led Alias Portc.7 : Ddrc.7 = 1       'led test
	Test1_led Alias Portf.7 : Ddrf.7 = 1       'KJL Added
	Hctl_xy Alias Portc.0 : Ddrc.0 = 1       'selection xy hctl2032
	Hctl_sel1 Alias Portc.1 : Ddrc.1 = 1       'selection byte bit 0
	Hctl_sel2 Alias Portc.2 : Ddrc.2 = 1       'selection byte bit 1
	Hctl_oe Alias Portc.3 : Ddrc.3 = 1       'selecion oe hctl data
	Hctl_rst_1 Alias Portc.4 : Ddrc.4 = 1       'reset encoder x
	Hctl_rst_2 Alias Portc.5 : Ddrc.5 = 1       'reset encoder y
	Hctl_data Alias Pina : Ddra = &H00       'porta input data encoder
	'-------------------------------------------------------------------------------
	*/
	byte  F = ports[PORTF];
	byte  Ddrd = ports[DDRD];
	byte C = ports[PORTC];
	byte D = ports[PORTD];
	byte pina = ports[PINA];
	
	Test1_led.Test1_led = F & 00000001;
	Motor_led.Motor_led = C & 00000001;
	Hctl_rst_1.Hctl_rst_1 = C & 00001000;
	Hctl_rst_2.Hctl_rst_2 = C & 00010000;
	M1_dir_bit.M1_dir_bit = D & 00100000;
	M2_dir_bit.M2_dir_bit = D & 01000000;
	Hctl_xy.Hctl_xy = C & 00000100;
	Hctl_oe.Hctl_oe = C & 00000100;
	Hctl_data.Hctl_data = ports[PINA];
	Ddrd = 0;
	M1_pwm = 0;
	M2_pwm = 0;
	
	void(*foo)(void);

	/*'------------------- CONFIGURATION --------------------------------------------
	'-------------------------------------------------------------------------------
	'confiqure the timer1 for pwm set to 8 bit,
	'set freq = 39.0625 Khz with xtal=20mhz and prescale = 1
	'we have (20000000/256 = 78.125 Khz) (78.125 K / presc = 78.125 Khz) (78.125/2 pwm = 39.0625 Khz)
	'-------------------------------------------------------------------------------
	Config Watchdog = 16
	Stop Watchdog
	Config Int0 = Falling
	Config Int1 = Falling
	Config Timer1 = Pwm, Pwm = 8, Compare A Pwm = Clear Down, Compare B Pwm = Clear Down, Prescale = 1       '39.0622Khz pwm
	Config Timer0 = Timer, Prescale = 64       '20000000 clk / 64 presc = 312.5 Khz Timer Clock
	On Timer0 Timer_0   ' Update PID    '312.5 Khz / 256 (8bit counter overflow) = 1.2207 Khz interrupt
	On Int0 Int_0       '  Int for limit switch 1 @ Port D.2
	On Int1 Int_1       '  Int for limit switch 2 @ Port D.3
	On Urxc Rs232       '  @ Port
	Enable Timer0       ' Serial Port Handler
	Enable Urxc         '  enable serial port interrupt
	Enable Int0         '  enable interrupt for Motor 1 limit switch @ Port D.2
	Enable Int1         '  enable interrupt for Motor 2 limit switch @ Port D.3
	Enable Interrupts   ' enable all interrupts
	*/
	Config_Watchdog(16);
	Watchdog(STOP);
	Config_intx(FALLING,0);
	Config_intx(FALLING,1);
	Config_timer1(PWM, NONE,
		0, 0, CLEAR_DOWN,
		NOTUSED, 
		8, CLEAR_DOWN,
		CLEAR_DOWN,
		"Timer1", 1);
	Config_timer0(TIMER, NONE,  0, "Timer0", 64);
	On_interrupt("Timer01", &Timer_01);
	On_interrupt("Timer0", &Timer_0);
	On_interrupt("Int0", &Int_0);
	On_interrupt("Int0", &Int_1);
	On_interrupt("Urxc", &Rs232);
	Enable_interrupt("Urxc");
	Enable_interrupt("Timer0");
	Enable_interrupt("Int0");
	Enable_interrupt("Int1");
	Enable_all_interrupts();
	foo = &Int_0;
	(*foo)();
	foo = &Int_1;
	(*foo)();
	/*
	Call Init_parameter(1)
	Call Init_parameter(2)
	Call Configure_pid(1, 500, 100, 500)       ''configure Motor 1 - pid initialize
	Call Configure_pid(2, 500, 100, 500)       'configure Motor 2 - pid initialize
	'...................P....I......D
	Print "(0 Motor Control, 0)"
	*/
	Init_parameter(1);
	Init_parameter(2);
	Configure_pid(1, 500, 100, 500);
	Configure_pid(2, 500, 100, 500);
	printf("0 Motor Control, 0\n");
	//Test code
	//Tx_enable.Tx_enable = 1;//Test code
	Rs232();
	
	/*
	'-------------------------------------------------------------------------------
	'---------------------- MAIN PROGRAM -------------------------------------------
	'-------------------------------------------------------------------------------
	Main:
		Test1_led = True
		Motor_led = True

		Do

		Test1_led = True

		If Tx_enable = 1 Then       'allow transmission
		Tx_enable = 0
		Print Str_tx_1       'transmit the string
		End If

		Test1_led = False


		'..... here we monitor the 2 Motors
		Loop
		'-------------------------------------------------------------------------------
		End
	*/
	
	Test1_led.Test1_led = True;
	Motor_led.Motor_led = True;

	while (true)
	{

		Test1_led.Test1_led = True;
		if (Tx_enable.Tx_enable == 1)
		{
			Tx_enable.Tx_enable = 0;
			printf("%s\n", Str_tx_1);
		}
		Test1_led.Test1_led = False;
	}
}
/*
'-------------------------------------------------------------------------------
'---------------------- Configure pid -------------------------------------
'-------------------------------------------------------------------------------
Sub Configure_pid(mtr, Mtrnum_kp, Mtrnum_ki, Mtrnum_kd)

Pid_kp(mtr) = Mtrnum_kp
Pid_ki(mtr) = Mtrnum_ki
Pid_kd(mtr) = Mtrnum_kd
Pid_scale(mtr) = 100

End Sub
*/
void Configure_pid(byte mtr, long Mtrnum_kp, long Mtrnum_ki, long Mtrnum_kd)
{
	Pid_kp[mtr] = Mtrnum_kp;
	Pid_ki[mtr] = Mtrnum_ki;
	Pid_kd[mtr] = Mtrnum_kd;
	Pid_scale[mtr] = 100;
}
/*
Rs232:
#if Vb6
Input Ucommand Noecho       'using vb6
#else
Char(1) = Inkey()       'using window's terminal program
Char(1) = Ucase(char(1))
If Char(1) = Chr(13) Then
Print
#endif
'...........................................................................
If Ucommand = "" Then Ucommand = Ucommand_old       'user pressed return key, repeat old command
N_cmd = Split(ucommand, Cmd_ar(1), " ")
Mtr = Val(cmd_ar(2))
'............................................................
*/
void Rs232(void)
{	
	int i, count,n_cmd;
	char *p;
	char *cmd_array[5]; 
    command command_entered;
	int cmdnum = 0;
	count = i = 0;
	Serial_input(); 
	byte Mtrnum = 1;
	long Setpoint = 2;
	long * Pid_setpoint = &Setpoint;
	long actual = 2;
	long * Pid_actual = &actual;

	Exe_pid(&Mtrnum, Pid_setpoint, Pid_actual);

	printf("ucommand = %s\n", ucommand);
	strupr(ucommand);
	printf("ucommand = %s\n", ucommand);	
	p = strtok(ucommand, " ");
	while (p != NULL)
	{
		cmd_array[i++] = p;
		p = strtok(NULL, " ");
		count++;
	}

	for (i = 0; i<count; ++i)
		printf("%s\n", cmd_array[i]);
	if (strcmp(ucommand, "")==0)
		strcpy(ucommand, ucommand_old);
	n_cmd = count;
	Mtr = (byte)atoi(cmd_array[1]); 
	cmdnum = searchforcommand(cmd_array[0]);
	command_entered = (command)cmdnum;
	/*
	Select Case Cmd_ar(1)
		Case "RSTF"       'Rstf  RESET CPU WITH WATCHDOG START
		Print "(0 RST Program, 0)"
		'Start Watchdog
		'..........................................................
	*/
	switch (command_entered)
	{
	case RSTF:
			printf("0 RST Program, 0\n");
			Watchdog(START);
			break;
			/* Next 6 commands
			Case "MADE"       'Made WHO WROTE PROGRAMM
				Print "(5-28-07, 0)"
				'..........................................................
				Case "VER"       'Ver VERSION OF PROGRAMM
				Print "(Version 2.0, 0)"
				'..........................................................
				Case "SKP"       'Skp[MtrNum] [kp Value] SET PROPORZIONAL PID 0-1000
				Pid_kp(mtr) = Val(cmd_ar(3))
				Print "("; Mtr; " SKP, "; Pid_kp(mtr); ")"
				'..........................................................
				Case "SKI"       'Ski[MtrNum][ki Value] SET INTEGRAL PID 0-100
				Pid_ki(mtr) = Val(cmd_ar(3))
				Print "("; Mtr; " SKI, "; Pid_ki(mtr); ")"
				'..........................................................
				Case "SKD"       'Skd[MtrNum][kd Value] SET DERIVATIVE PID 0-1000
				Pid_kd(mtr) = Val(cmd_ar(3))
				Print "("; Mtr; " SKD, "; Pid_kd(mtr); ")"
				'..........................................................
				Case "GO"       'Go[MtrNum][position Value] GO TO POSITION IN POSITION MODE CONTROL +- 23 BITS
				If Mode_ctrl <> Mode_pos Then       'if mode <> position mode
				Call Set_mode(mode_pos)       'set the position
				End If
				Mtr = Val(cmd_ar(2))
				Pos_final(mtr) = Val(cmd_ar(3))
				Print "("; Mtr; " GO, "; Pos_final(mtr); ")"
				'..........................................................
	*/
	case MADE:
			printf("09-02-2014\n");
			break;
	case VER:
			printf("Version 3.0, 0\n");
			break;
	case SKP:
			Pid_kp[Mtr] = atoi(cmd_array[2]);
			printf("; Mtr; SKP %i\n", Pid_kp[Mtr]);
			break;
	case SKI:
			Pid_ki[Mtr] = atoi(cmd_array[2]);
			printf("; Mtr; SKI %i\n", Pid_ki[Mtr]);
			break;
	case SKD:
			Pid_kd[Mtr] = atoi(cmd_array[2]);
			printf("; Mtr; SKD %i\n", Pid_kd[Mtr]);
			break;
	case GO:
			if (Mode_ctrl != Mode_pos)
				Set_mode(Mode_pos);
			Mtr = atoi(cmd_array[1]);
			Pos_final[Mtr] = atoi(cmd_array[2]);
			printf("; Mtr; GO %i\n", Pos_final[Mtr]);
			break;
			/* Next 10 commands
			Case "VMAX"       'Vmax[MtrNum][vmax Value] SET MAX VELOCITY IN PROPORZIONAL VELOCITY PROFILE 0-255
				Vmax_pos(mtr) = Val(cmd_ar(3))
				Vmax_neg(mtr) = -vmax_pos(mtr)
				Print "("; Mtr; " VMAX, "; Vmax_pos(mtr); ")"

			Case "GMAX"       'Gmax[MtrNum] GET MAX VELOCITY IN VELOCITY PROFILE MODE
				Print "("; Mtr; " GMAX, "; Vmax_pos(mtr); ")"

			Case "SVM"       'Svm[MtrNum][svm Value] SET MAX VELOCITY IN TRAPEZOIDAL MODE 0-255
				Vel_pos(mtr) = Val(cmd_ar(3))
				Vel_last(mtr) = Vel_pos(mtr)
				Vel_neg(mtr) = -vel_pos(mtr)
				Print "("; Mtr; " SVM, "; Vel_pos(mtr); ")"
				'..........................................................
			Case "GVM"       'Gvm[MtrNum] GET MAX VELOCITY IN TRAPEZOIDAL MODE
			Print "("; Mtr; " GVM, "; Vel_pos(mtr); ")"
			'..........................................................
			Case "GVE"       'Gve[MtrNum] GET ABSOLUTE SPEED FROM ENCODER
			Tx_enable = 1
			Call Print_com(mtr, Cmd_ar(1), Act_speed(mtr))
			'..........................................................
			Case "ENC"       'Enc[MtrNum] READ ABSOLUTE ENCODER POSITION
			Tx_enable = 1
			Call Print_com(mtr, Cmd_ar(1), Pos_encoder(mtr))
			'..........................................................
			Case "SPID"       'Spid[MtrNum][kp][ki][kd] SET PID MOTOR KP KI KD
					Pid_kp(mtr) = Val(cmd_ar(3))
					Pid_ki(mtr) = Val(cmd_ar(4))
					Pid_kd(mtr) = Val(cmd_ar(5))
					Print "("; Mtr; " SPID, "; Pid_kp(mtr); " "; Pid_ki(mtr); " "; Pid_kd(mtr); ")"
					'..........................................................
			Case "GPID"       'Gpid[MtrNum] GET PID MOTOR VALUES
			Print "("; Mtr; " GPID, "; Pid_kp(mtr); " "; Pid_ki(mtr); " "; Pid_kd(mtr); ")"
			'..........................................................
			Case "STIME"       'Stime[stime Value] SET PID EXECUTION TIME 0-10msec/default=3.5 + .5 lt=4msec
			Pid_time = Val(cmd_ar(2))
			Print "("; 0; " STIME, "; Pid_time; ")"
			'..........................................................
			Case "GTIME"       'Gtime GET PID EXECUTION TIME
			Print "("; 0; " GTIME, "; Pid_time; ")"
			'..........................................................
*/
	case VMAX:
			Vmax_pos[Mtr] = atoi(cmd_array[2]);
			Vmax_neg[Mtr] = -Vmax_pos[Mtr];
			printf("; Mtr; VMAX %i\n", Vmax_pos[Mtr]);
			break;
	case GMAX:
			printf("; Mtr; GMAX %i\n", Vmax_pos[Mtr]);
			break;
	case SVM:
			Vel_pos[Mtr] = atoi(cmd_array[2]);
			Vel_last[Mtr] = Vel_pos[Mtr];
			Vel_neg[Mtr] = -Vel_pos[Mtr];
			printf("; Mtr; SVM %i\n", Vel_pos[Mtr]);
			break;
	case GVM:
			printf("; Mtr; GVM %i\n", Vel_pos[Mtr]);
			break;
	case GVE:
			Tx_enable.Tx_enable = 1;
			Print_com(Mtr, cmd_array[0], Act_speed[Mtr]);
			break;
	case ENC:
			Tx_enable.Tx_enable = 1;
			Print_com(Mtr, cmd_array[0], Pos_encoder[Mtr]);
			break;
	case SPID:
			Pid_kp[Mtr] = atoi(cmd_array[2]);
			Pid_ki[Mtr] = atoi(cmd_array[3]);
			Pid_kd[Mtr] = atoi(cmd_array[4]);
			printf("Mtr, SPID, kp %i ki %i kd %i", Pid_kp[Mtr], Pid_ki[Mtr], Pid_kd[Mtr]);
			break;
	case GPID:
			printf("Mtr, GPID, kp %i ki %i kd %i", Pid_kp[Mtr], Pid_ki[Mtr], Pid_kd[Mtr]);
			break;
	case STIME:
			Pid_time = atoi(cmd_array[1]);
			printf("; Mtr; STIME %i\n", Pid_time);
			break;
	case GTIME:
			printf("; Mtr; GTIME %i\n", Pid_time);
			break;
			/* 2 commands
			Case "SZP"       'Szp [MtrNum] SET ZERO POSITION
					Select Case Mtr       '  NEED to work on this one!!
						Case 1       '            maybe stop motor first!!
						Hctl_rst_1 = 0       ' reset mtr1 encoder counter = 0
						Waitms 1       '      wait 1 ms? is that length needed?
						Hctl_rst_1 = 1
						Case 2
						Hctl_rst_2 = 0       ' reset mtr2 encoder counter = 0
						Waitms 1
						Hctl_rst_2 = 1
					End Select

					Pos_encoder(mtr) = 0
					Old_encoder(mtr) = 0
					Motor_setpoint(mtr) = 0
					Pos_final(mtr) = 0
					New_speed(mtr) = 0
					Call Hctl_2032(mtr)
					Print "("; Mtr; " SZP, "; Pos_encoder(mtr); ")"
					'..........................................................
				Case "IDLE"       'Idle [MtrNum] POWER OFF MOTOR
					Call Configure_pid(mtr, 0, 0, 0)
					Print "("; Mtr; " IDLE, )"
					'..........................................................
				Case "GSM"       'Gsm [MtrNum] GET MOTOR STATE 0=STOP 1=MOVE
					If Act_speed(mtr) > 3 Or Act_speed(mtr) < -3 Then       'Motor in Motion
					Tx_enable = 1
					Call Print_com(mtr, Cmd_ar(mtr), 1)
					Else       'Motor stopped
					Tx_enable = 1
					Call Print_com(mtr, Cmd_ar(mtr), 0)
					End If
					'..........................................................*/
	case SZP:
			switch (Mtr)
			{
			case 1:
				Hctl_rst_1.Hctl_rst_1 = 0;
				Sleep(1);
				Hctl_rst_1.Hctl_rst_1 = 1;
				break;
			case 2:
				Hctl_rst_2.Hctl_rst_2 = 0;
				Sleep(1);
				Hctl_rst_2.Hctl_rst_2 = 1;
				break;
			}
			Pos_encoder[Mtr] = 0;
			Old_encoder[Mtr] = 0;
			Motor_setpoint[Mtr] = 0;
			Pos_final[Mtr] = 0;
			New_speed[Mtr] = 0;
			Hctl_2032(Mtr);
			printf("; Mtr; SZP %i\n", Pos_encoder[Mtr]);
			break;
	case IDLE:
			Configure_pid(Mtr, 0, 0, 0);
			printf("Mtr IDLE\n");
			break;

	case GSM:
			if ((Act_speed[Mtr] > 3) || (Act_speed[Mtr] < -3))
			{
				Tx_enable.Tx_enable = 1;
				Print_com(Mtr, cmd_array[Mtr], 0);
			}
			else
			{
				Tx_enable.Tx_enable = 1;
				Print_com(Mtr, cmd_array[Mtr], 0);
			}
			break;
			/*
			Case "SMODE"       'Smode[MtrNum][mode] SET SINGLE MODE FOR ONE MOTOR
			Mode_ctrl = Val(cmd_ar(3))
			Select Case Mode_ctrl
			Case Mode_pos
			Call Configure_pid(mtr, 200, 0, 200)       ' POSITION Mode = 0
			Motor_setpoint(mtr) = Pos_encoder(mtr)
			Case Mode_vel
			Call Configure_pid(mtr, 700, 100, 700)       'VELOCITY Mode = 1
			Case Mode_trp
			Call Configure_pid(mtr, 500, 100, 500)       'TRAPEZOIDALE Mode = 2
			Pos_final(mtr) = Pos_encoder(mtr)
			Case Mode_velp
			Call Configure_pid(mtr, 100, 10, 100)       'VELOCITY proportional = 3
			Case Mode_idle
			Call Configure_pid(mtr, 0, 0, 0)       'IDLE 4
			End Select
			Print "(0 MODE, "; Mode_ctrl; ")"
			'..........................................................
			Case "MODE"       'Mode[mode] SET MODE PROFILE FOR both Motors 0,1,2,3,4
			Mode_ctrl = Val(cmd_ar(2))       'Set control mode
			Call Set_mode(mode_ctrl)
			Print "(0 MODE, "; Mode_ctrl; ")"
			'..........................................................
			Case "GMODE"       'GET MODE PROFILE FOR both Motors 0,1,2,3,4
			Print "(0 GMODE, "; Mode_ctrl; ")"
			'..........................................................
			*/
	case SMODE:
			Mode_ctrl = atoi(cmd_array[2]);
			switch (Mode_ctrl)
			{
			case Mode_pos:
				Configure_pid(Mtr, 200, 0, 200);
				Motor_setpoint[Mtr] = Pos_encoder[Mtr];
				break;
			case Mode_vel:
				Configure_pid(Mtr, 700, 100, 700);
				break;
			case Mode_trp:
				Configure_pid(Mtr, 500, 100, 500);
				Pos_final[Mtr] = Pos_encoder[Mtr];
				break;
			case Mode_velp:
				Configure_pid(Mtr, 100, 10, 100);
				break;
			case Mode_idle:
				Configure_pid(Mtr, 0, 0, 0);
				break;
			}
			printf("0 MODE %i\n", Mode_ctrl);
			break;
	case MODE:
			Mode_ctrl = atoi(cmd_array[1]);
			Set_mode(Mode_ctrl);
			printf("0 MODE %i\n", Mode_ctrl);
			break;
	case GMODE:
			printf("0 GMODE %i\n", Mode_ctrl);
			break;
			/*
			Case "SVEL"       'Svel[MtrNum][svel Value] SET MOTOR WITH INTEGRAL VELOCITY PROFILE AND MOVE 0-255
			If Mode_ctrl <> Mode_vel Then       'mode <> vel mode - if mode trapezoidal
			Call Set_mode(mode_vel)
			End If
			Motor_setpoint(mtr) = Val(cmd_ar(3))       'values  -127  +127
			Print "("; Mtr; " SVEL, "; Motor_setpoint(mtr); ")"
			'..........................................................
			Case "VELO"       'Velo[vel 1][vel 2] SET TWO INDEPENDENT SPEED FOR MOTORS 0-255 & 0-255
			If Mode_ctrl <> Mode_vel Then       'mode <> vel mode - if mode trapezoidal
			Call Set_mode(mode_vel)
			End If
			Motor_setpoint(1) = Val(cmd_ar(2))       'value  -127  +127
			Motor_setpoint(2) = Val(cmd_ar(3))
			'..........................................................
			Case "SPWM"       'Spwm[MtrNum][spwm Value] SET MAX PWM OUT FOR TORQUE LIMIT 0-255
			Max_pwm(mtr) = Val(cmd_ar(3))
			Print "("; Mtr; " SPWM, "; Max_pwm(mtr); ")"
			'..........................................................
			Case "GPWM"       'Gpwm[MtrNum] GET MAX PWM OUT
			Print "("; Mtr; " GPWM, "; Max_pwm(mtr); ")"
			'..........................................................
			Case "RPWM"       'Rpwm [MtrNum] READ REAL PWM OUT TO CONTROL MAX CURRENT
			Print "("; Mtr; " RPWM, "; Rpwm(mtr); ")"
			'..........................................................
			Case "SACC"       'Sacc[MtrNum][acc Value] SET ACCELERATION DEGREE 1-89 DEGREES
			Deg(mtr) = Val(cmd_ar(3))
			Rad(mtr) = Deg2rad(deg(mtr))
			Rad(mtr) = Tan(rad(mtr))
			Vel_max(mtr) = Vel_pos(mtr) * 10
			Point_p1(mtr) = Vel_max(mtr) / Rad(mtr)
			Point_p1(mtr) = Point_p1(mtr) * 10
			Print "("; Mtr; " SACC, "; Deg(mtr); ")"
			'...  Print "P1: " ; Point_p1(mtr )
			'..........................................................
			Case "GACC"       'Gacc[MtrNum] GET ACCELERATION PROFILE IN DEGREE 1-89
			Print "("; Mtr; " GACC, "; Deg(mtr); ")"
			'..........................................................
			Case "SANG"       'Sang[MtrNum][angular Factor] SET ANGULAR FACTOR FOR VELOCITY PROFILE 1-100
			Factor_acc(mtr) = Val(cmd_ar(3))
			Print "("; Mtr; " SANG, "; Factor_acc(mtr); ")"
			'..........................................................
			Case "GANG"       'Gang [MtrNum] GET ANGULAR FACTOR
			Print "("; Mtr; " GANG, "; Factor_acc(mtr); ")"
			'..........................................................
			Case "POS"       'Pos[MtrNum][position Value][speed] SET POSITION AND SPEED IN TRAPEZOIDAL PROFILE
			If Mode_ctrl <> Mode_trp Then       'if not trapezoidale - set to trap mode
			Call Set_mode(mode_trp)
			End If
			Pos_final(mtr) = Val(cmd_ar(3))
			Vel_pos(mtr) = Val(cmd_ar(4))
			Call Calc_trapez(mtr)
			Start_move = True
			'..........................................................
			Case "MOVE"       'Move[position 1][position 2][speed] MOVE BOTH MOTORS TO POS 1 & POS 2  +-23 BITS TRAPEZOIDAL MODE
			If Mode_ctrl <> Mode_trp Then       'if not trapezoidale - set to trap mode
			Call Set_mode(mode_trp)
			End If
			Pos_final(1) = Val(cmd_ar(2))
			Pos_final(2) = Val(cmd_ar(3))
			Vel_pos(1) = Val(cmd_ar(4))
			Vel_pos(2) = Val(cmd_ar(4))
			Call Calc_trapez(1)
			Call Calc_trapez(2)
			Print "(0 MOVE, "; Pos_final(1); " "; Pos_final(2); ")"
			'Start_move = False                    'set Start_Move = false to
			'..........................................................
			Case "VELP"       'Velp[position 1][position 2] MOVE CONTINUOS POSITION WITH VARIBLE PROPORZIONAL VELOCITY
			If Mode_ctrl <> Mode_velp Then       'if not valocity mode set to velocity mode
			Call Set_mode(mode_velp)
			End If
			Acc_speed_p(1) = Vmax_pos(1)
			Acc_speed_p(2) = Vmax_pos(2)
			Acc_speed_n(1) = Vmax_neg(1)
			Acc_speed_n(2) = Vmax_neg(2)
			Factor_ang(1) = Factor_acc(1)
			Factor_ang(2) = Factor_acc(2)
			Pos_final(1) = Val(cmd_ar(2))
			Pos_final(2) = Val(cmd_ar(3))
			'..........................................................
			Case "SUM"       '?? Sum1 is added to Pos_final see CASE ELSE below
			Sum1 = Val(cmd_ar(2))
			'..........................................................
			Case "START"       'Start is Start_move START MOVE IF START_MOVE = FALSE
			Start_move = True
			Print "(0 START, 0)"
			'..........................................................
			Case "STOP "       'Stop is Mode_idle STOP MOVE AND POWER DOWN MOTORS
			Mode_ctrl = Mode_idle
			Print "(0 STOP, 0)"
			'..........................................................
			Case "RST"       'Rst [MtrNum] RESET ENCODER
			If Mtr = 1 Then       'NEED SOME WORK HERE!
			Hctl_rst_1 = 0
			Waitms 1
			Hctl_rst_1 = 1
			End If
			If Mtr = 2 Then
			Hctl_rst_2 = 0
			Waitms 1
			Hctl_rst_2 = 1
			End If
			Call Hctl_2032(mtr)
			Print "("; Mtr; " RST, "; Pos_encoder(mtr); ")"
			'..........................................................
			'Case Else       'CASE ELSE - WHAT THE HELL!!NEED SOME WORK HERE!!
			'    If Mode_ctrl <> Mode_velp Then       'set mode to velocity mode if not in velocity mode
			'       Call Set_mode(mode_velp)
			'    End If
			'    Pos_final(1) = Pos_final(1) + Sum1       'inc motor 1 target by user Sum1
			'    Pos_final(2) = Pos_final(2) + Sum1       'inc motor 2 target by user Sum2
			'..........................................................
			End Select
			*/
	case SVEL:
			if (Mode_ctrl != Mode_vel)
				Set_mode(Mode_vel);
			Motor_setpoint[Mtr] = atoi(cmd_array[2]);
			printf("Mtr SVEL %i\n", Motor_setpoint[Mtr]);
			break;
	case VELO:
			if (Mode_ctrl != Mode_trp)
				Set_mode(Mode_vel);
			Motor_setpoint[1] = atoi(cmd_array[1]);
			Motor_setpoint[2] = atoi(cmd_array[2]);
			break;
	case SPWM:
			Max_pwm[Mtr] = atoi(cmd_array[2]);
			printf("Mtr %i SPWM %i\n", Mtr, Max_pwm[Mtr]);
			break;
	case GPWM:
			printf("Mtr GPWM %i\n", Max_pwm[Mtr]);
			break;
	case RPWM:
			printf("Mtr RPWM %i\n", Rpwm[Mtr]);
			break;
	case SACC:
			Deg[Mtr] = (float)atof(cmd_array[2]);
			Rad[Mtr] = (float)Deg2rad(Deg[Mtr]);
			Rad[Mtr] = tan(Rad[Mtr]);
			Vel_max[Mtr] = (float)Vel_pos[Mtr]*10;
			Point_p1[Mtr] = (long) (Vel_max[Mtr] / Rad[Mtr]);
			Point_p1[Mtr] = Point_p1[Mtr] * 10;
			printf("Mtr %i SACC %i\n",Mtr, Deg[Mtr]);
			break;
	case GACC:
			printf("Mtr %i GACC %f\n",Mtr, Deg[Mtr]);
			break;
	case SANG:
			Factor_acc[Mtr] = atoi(cmd_array[2]);
			printf("Mtr %i SANG %i\n", Mtr, Factor_acc[Mtr]);
			break;
	case GANG:
			printf("Mtr %i GANG %f\n",Mtr ,Factor_acc[Mtr]);
			break;
	case POS:
			if (Mode_ctrl != Mode_trp)
				Set_mode(Mode_trp);
			Pos_final[Mtr] = atoi(cmd_array[2]);
			Vel_pos[Mtr] = atoi(cmd_array[3]);
			Calc_trapez(Mtr);
			Start_move.Start_move = True;
			break;
	case MOVE:
			if (Mode_ctrl != Mode_trp)
				Set_mode(Mode_trp);
			Pos_final[1] = atoi(cmd_array[1]);
			Pos_final[2] = atoi(cmd_array[2]);
			Vel_pos[1] = atoi(cmd_array[3]);
			Vel_pos[2] = atoi(cmd_array[3]);
			Calc_trapez(1);
			Calc_trapez(2);
			printf("0 Move %i %i\n", Pos_final[1], Pos_final[2]);
			break;
	case VELP:
			if (Mode_ctrl != Mode_velp)
				Set_mode(Mode_velp);
			Acc_speed_p[1] = Vmax_pos[1];
			Acc_speed_p[2] = Vmax_pos[2];
			Acc_speed_n[1] = Vmax_neg[1];
			Acc_speed_n[2] = Vmax_neg[2];
			Factor_ang[1] = Factor_acc[1];
			Factor_ang[2] = Factor_acc[2];
			Pos_final[1] = atoi(cmd_array[1]);
			Pos_final[2] = atoi(cmd_array[2]);
			break;
	case SUM:
			Sum1 = atoi(cmd_array[1]);
			break;
	case STARTC:
			Start_move.Start_move = True;
			printf("0 START, 0\n");
			break;
	case STOPC:
			Mode_ctrl = Mode_idle;
			printf("0 STOP, 0\n");
			break;
	case RST:
			if (Mtr == 1)
			{
				Hctl_rst_1.Hctl_rst_1= 0;
				Sleep(1);
				Hctl_rst_1.Hctl_rst_1= 1;
			}
			if (Mtr == 2)
			{
				Hctl_rst_2.Hctl_rst_2 = 0;
				Sleep(1);
				Hctl_rst_2.Hctl_rst_2 = 1;
			}
			Hctl_2032(Mtr);
			printf("Mtr %i RST %i\n\r", Mtr, Pos_encoder[Mtr]);
			break;
	default:
			printf("What the hell!\n");
	}
	/*
	Ucommand_old = Ucommand
	Ucommand = ""
	'......................................................................
	#if Vb6
	#else
	Else
	Ucommand = Ucommand + Chr(char(1))
	Print Ucommand; Chr(13);
	End If
	#endif
	Return
*/
	strcpy(Ucommand_old, Ucommand);
	strcpy(Ucommand, "");
}
/*
'-------------------------------------------------------------------------------
'----------------------- Read HCTL 2032 -------------------------------------
'-------------------------------------------------------------------------------
Sub Hctl_2032(mtr_num)

Temp_enc = Varptr(pos_encoder(mtr_num))

If Mtr_num = 1 Then
Hctl_xy = 0
Else             'Mtr_num = 2
Hctl_xy = 1
End If

Hctl_oe = 0      'oe - enable output

Hctl_sel1 = 0 : Hctl_sel2 = 1 : Poke Temp_enc + 3, Hctl_data       'msb
Hctl_sel1 = 1 : Hctl_sel2 = 1 : Poke Temp_enc + 2, Hctl_data       'byte #3
Hctl_sel1 = 0 : Hctl_sel2 = 0 : Poke Temp_enc + 1, Hctl_data       'byte #2
Hctl_sel1 = 1 : Hctl_sel2 = 0 : Poke Temp_enc, Hctl_data       '   'lsb

Hctl_oe = 1      'oe - disable output

End Sub
*/
void Hctl_2032(byte Mtr_num)
{
	Temp_enc = &Pos_encoder[Mtr_num];
	if (Mtr_num == 1)
		Hctl_xy.Hctl_xy= 0;
	else
		Hctl_xy.Hctl_xy= 1;
	Hctl_oe.Hctl_oe = 0;

	Hctl_sel1.Hctl_sel1 = 0;
	Hctl_sel2.Hctl_sel2 = 0;
	Hctl_data.Hctl_data = Temp_enc[3];

	Hctl_sel1.Hctl_sel1 = 1;
	Hctl_sel2.Hctl_sel2 = 1;
	Hctl_data.Hctl_data = Temp_enc[2];

	Hctl_sel1.Hctl_sel1 = 0;
	Hctl_sel2.Hctl_sel2 = 0;
	Hctl_data.Hctl_data = Temp_enc[1];

	Hctl_sel1.Hctl_sel1 = 1;
	Hctl_sel2.Hctl_sel2 = 0;
	Hctl_data.Hctl_data = Temp_enc[0];
	Hctl_oe.Hctl_oe = 1;
}
/*
'-------------------------------------------------------------------------------
'------------------------- Calculation of Trapezioidale Profile -------------------
'-------------------------------------------------------------------------------
Sub Calc_trapez(mtr)

If Vel_pos(mtr) = 0 Then Vel_pos(mtr) = Vel_last(mtr)

Rad(mtr) = Deg2rad(deg(mtr))       'trasforms slope degrees to radians
Rad(mtr) = Tan(rad(mtr))       'calculate angle tangent
Vel_max(mtr) = Vel_pos(mtr) * 10       'calculate max velocity to point 1
Point_p1(mtr) = Vel_max(mtr) / Rad(mtr)
Point_p1(mtr) = Point_p1(mtr) * 10

Vel_neg(mtr) = -vel_pos(mtr)
Vel_last(mtr) = Vel_pos(mtr)

Call Hctl_2032(mtr)

Diff_position(mtr) = Pos_final(mtr) - Pos_encoder(mtr)
Diff_position(mtr) = Abs(diff_position(mtr))

Factor_acc(mtr) = Point_p1(mtr) / Vel_pos(mtr)       'calculate accel factor
'...............................................added with accel command
Diff_2(mtr) = Diff_position(mtr) / 2

If Point_p1(mtr) > Diff_2(mtr) Then
Point_p1(mtr) = Diff_2(mtr) / 2
End If
'..........................................................
If Pos_final(mtr) = > Pos_encoder(mtr) Then
Dir_diff(mtr) = True       '--->
Trapez_1(mtr) = Pos_encoder(mtr) + Point_p1(mtr)
Trapez_2(mtr) = Pos_final(mtr) - Point_p1(mtr)
Else
Dir_diff(mtr) = False       '<---
Trapez_1(mtr) = Pos_encoder(mtr) - Point_p1(mtr)
Trapez_2(mtr) = Pos_final(mtr) + Point_p1(mtr)
End If

'..........................................................
Print "("; Mtr; " POS, "; Pos_final(mtr); ")"
'...Print "Trapeziod: " ; Trapez_1(mtr ) ; ", " ; Trapez_2(mtr )
'...Print "Fator ang: " ; Factor_acc(mtr )

End Sub
*/
void Calc_trapez(byte M)
{
	//needs to be implemented
	if (Vel_pos[M] == 0) Vel_pos[M] = Vel_last[M];
	Rad[M] =(float)Deg2rad(Deg[Mtr]);
	Rad[M] = tan(Rad[M]);
	Vel_max[M] = (float) Vel_pos[M] * 10;
	Point_p1[M] = (long) (Vel_max[M] / Rad[M]);
	Point_p1[M] = Point_p1[M] * 10;

	Vel_neg[M] = -Vel_pos[M];
	Vel_last[M] = Vel_pos[M];
	Hctl_2032(M);
	Diff_position[M] = Pos_final[M] - Pos_encoder[M];
	Diff_position[M] = abs(Diff_position[M]);
	Factor_acc[M] = Point_p1[M]/ Vel_pos[M];
	Diff_2[M] = Diff_position[M] / 2;
	if (Point_p1[M] > Diff_2[M]) Point_p1[M] = Diff_2[M] / 2;
	if (Pos_final[M] >= Pos_encoder[M])
	{
		Dir_diff[M] = True;
		Trapez_1[M] = Pos_encoder[M] + Point_p1[M];
		Trapez_2[M] = Pos_final[M] - Point_p1[M];
	}
	else
	{
		Dir_diff[M] = False;
		Trapez_1[M] = Pos_encoder[M] - Point_p1[M];
		Trapez_2[M] = Pos_final[M] + Point_p1[M];
	}
	printf("MTR %i POS %i", M, Pos_final[M]);
}
/*
'-------------------------------------------------------------------------------
'----------------------- Execute PID ----------------------------------------
'-------------------------------------------------------------------------------
'the following routine updates PID for the two Motors in 460 uSec (.46 msec)
'resulting in a PID update freq of 305.18 hz' the period of the PID is ~3.28 msec set with(timer_pid = 4)
'1.2207khz/4(timer_pid = 4)=305.18/sec*.46 msec = 140.3828/1000 msec = 14% processor time; 86% remaining
Timer_0:

If Timer_pid = Pid_time Then
Timer_pid = 0
For Mtr_num = 1 To 2
Motor_led = True
Call Hctl_2032(mtr_num)       'load the encoder position
Act_speed(mtr_num) = Pos_encoder(mtr_num) - Old_encoder(mtr_num)       'speed in counts per PID period (~3.5 msec)
Old_encoder(mtr_num) = Pos_encoder(mtr_num)       'update current encoder position to old_encoder
New_speed(mtr_num) = Pos_final(mtr_num) - Pos_encoder(mtr_num)       'Difference per sample
Difference(mtr_num) = New_speed(mtr_num)       ' = Pos_final(Mtr_num)-Pos_encoder(Mtr_num)'Diff.between position & final position
'------------------------------------------------------------------------
' if it is changed before you remove velocity then it accelerates 'if it is changed before of sign you remove speed and then it accelerates
'------------------------------------------------------------------------
If Flag_velocity = True Then       '= Velocity Profile Mode
If Pos_final(mtr_num) = > Pos_encoder(mtr_num) Then       'current motor position is => desired position
Dir_diff(mtr_num) = True       '---> position is greater than
If Difference(mtr_num) <= 10000 Then Acc_speed_p(mtr_num) = New_speed(mtr_num) / Factor_acc(mtr_num)       '99/100= 0 = decellerate
If Acc_speed_p(mtr_num) < 1 Then Acc_speed_p(mtr_num) = 1
If New_speed(mtr_num) > Vmax_pos(mtr_num) Then New_speed(mtr_num) = Vmax_pos(mtr_num)
If New_speed(mtr_num) > Acc_speed_p(mtr_num) Then New_speed(mtr_num) = Acc_speed_p(mtr_num)
Else  '................................'current motor position is < desired position '99 / 100 = 0
Dir_diff(mtr_num) = False       '<--- position is less than
If Difference(mtr_num) = > -10000 Then Acc_speed_n(mtr_num) = New_speed(mtr_num) / Factor_acc(mtr_num)       'decellerate
If Acc_speed_n(mtr_num) > -1 Then Acc_speed_n(mtr_num) = -1
If New_speed(mtr_num) < Vmax_neg(mtr_num) Then New_speed(mtr_num) = Vmax_neg(mtr_num)
If New_speed(mtr_num) < Acc_speed_n(mtr_num) Then New_speed(mtr_num) = Acc_speed_n(mtr_num)
End If       'ELSE Flag_velocity = False; mode =  Position, Velocity, Trapizoidal or Idle.
Else     '*CHECK-"If Dir_diff(mtr_num)=True" is determined once per move in subroutine Calc_trapez(mtr)-What!!
If Dir_diff(mtr_num) = True Then       'Pos_final(mtr ) => Pos_encoder(mtr ) - see subroutine ' Calc_trapez(mtr)'
New_encoder(mtr_num) = Trapez_1(mtr_num) - Pos_encoder(mtr_num)       '30000 - 10000 = 20000
New_encoder(mtr_num) = Point_p1(mtr_num) - New_encoder(mtr_num)       '20000 - 20000 = 0
If Pos_encoder(mtr_num) < Trapez_1(mtr_num) Then Acc_speed(mtr_num) = New_encoder(mtr_num) / Factor_acc(mtr_num)       'acceleration before Trapez_1 -->
If Pos_encoder(mtr_num) = > Trapez_2(mtr_num) Then Acc_speed(mtr_num) = New_speed(mtr_num) / Factor_acc(mtr_num)       'deceleration after trap 2-->
If Acc_speed(mtr_num) < 1 Then Acc_speed(mtr_num) = 1
If New_speed(mtr_num) > Vel_pos(mtr_num) Then New_speed(mtr_num) = Vel_pos(mtr_num)       '     positive speed - keep within set maximum speed
If New_speed(mtr_num) > Acc_speed(mtr_num) Then New_speed(mtr_num) = Acc_speed(mtr_num)       ' reduce the speed  'reduced  acceleration
Else  'Dir_diff(mtr_num) = False        'Pos_final(mtr) < Pos_encoder(mtr)
New_encoder(mtr_num) = Trapez_1(mtr_num) - Pos_encoder(mtr_num)       '80000 - 99000    = -20000
New_encoder(mtr_num) = New_encoder(mtr_num) + Point_p1(mtr_num)       '21000 -  20000)   =  -1000
New_encoder(mtr_num) = -new_encoder(mtr_num)       'invert sign of encoder counts
If Pos_encoder(mtr_num) = > Trapez_1(mtr_num) Then Acc_speed(mtr_num) = New_encoder(mtr_num) / Factor_acc(mtr_num)       'acceleration Before Trapez_1 < - -
If Pos_encoder(mtr_num) < Trapez_2(mtr_num) Then Acc_speed(mtr_num) = New_speed(mtr_num) / Factor_acc(mtr_num)       'deceleration after Trapez_2 <--
If Acc_speed(mtr_num) > -1 Then Acc_speed(mtr_num) = -1
If New_speed(mtr_num) < Vel_neg(mtr_num) Then New_speed(mtr_num) = Vel_neg(mtr_num)       'negative speed - keep within set maximum speed
If New_speed(mtr_num) < Acc_speed(mtr_num) Then New_speed(mtr_num) = Acc_speed(mtr_num)       'reduce the speed
End If
End If

Select Case Mode_ctrl
Case Mode_pos       'position mode
Call Exe_pid(mtr_num, Pos_final(mtr_num), Pos_encoder(mtr_num))
Case Mode_vel       'velocity mode - raw pwm value
Call Exe_pid(mtr_num, Motor_setpoint(mtr_num), Act_speed(mtr_num))
Case Mode_trp       'trapizoidal mode
Motor_setpoint(mtr_num) = New_speed(mtr_num)
If Start_move = 0 Then Motor_setpoint(mtr_num) = 0
Call Exe_pid(mtr_num, Motor_setpoint(mtr_num), Act_speed(mtr_num))
Case Mode_velp       'velocity profile mode - position control with static velocity
Motor_setpoint(mtr_num) = New_speed(mtr_num)
Call Exe_pid(mtr_num, Motor_setpoint(mtr_num), Act_speed(mtr_num))
Case Mode_idle       'stop motor
Call Configure_pid(mtr_num, 0, 0, 0)
'..Pos_encoder(Mtr_num) = 0
'..Old_encoder(Mtr_num) = 0
'..Motor_setpoint(Mtr_num) = 0
'..Pos_final(Mtr_num) = 0
'..New_speed(Mtr_num) = 0
If Mtr_num = 1 Then M1_pwm = 0
If Mtr_num = 2 Then M2_pwm = 0
End Select

'***************************************************************************
'Code below controls motion flag output pin
'based on motor stop period > 150 cts = 0 or moving = 1
'151 cts * 4 msec loop time  = 596 msec of no motion
If Abs(act_speed(mtr_num)) > 2 Then       ' motion = true
Mstop_ctr(mtr_num) = 0       '          ' reset stop counter = 0
Elseif Mstop_ctr(mtr_num) < 200 Then       'motion = false
Incr Mstop_ctr(mtr_num)       '         ' increment stop counter
End If

If Mstop_ctr(mtr_num) > 150 Then       '..no motion for > 150 PID cycles
Temp_bit = 0       '....................clear bit
Else     '                             ...no motion for <= 150 PID cycles
Temp_bit = 1       '................... set bit
End If

If Mtr_num = 1 Then
Stop1_bit = Temp_bit       'Stop1_bit = B.4 pin
Else
Stop2_bit = Temp_bit       'Stop2_bit = C.6 pin
End If
'Code above controls motion flag output pin
'******************************************************************************
Next Mtr_num
End If          'PID above resets Timer_pid to 0, next timer int = 2..3..4

Incr Timer_pid  'PID consumes .5 msec,+ 3 more timer int = 3.5 msec total

Motor_led = False

Return

*/
void Timer_0(void)
{
	printf("Timer_01\n");
	if (Timer_pid == Pid_time)
	{
		Timer_pid = 0;
		for (Mtr_num = 1; Mtr_num < 3; Mtr_num++)
		{
			Motor_led.Motor_led = True;
			Hctl_2032(Mtr_num);
			Act_speed[Mtr_num] = Pos_encoder[Mtr_num] - Old_encoder[Mtr_num];
			Old_encoder[Mtr_num] = Pos_encoder[Mtr_num];
			New_speed[Mtr_num] = Pos_final[Mtr_num] - Pos_encoder[Mtr_num]; 
			Difference[Mtr_num] = New_speed[Mtr_num];
			if (Flag_velocity.Flag_velocity == True)
			{
				if (Pos_final[Mtr_num] >= Pos_encoder[Mtr_num])
					Dir_diff[Mtr_num] = True;
				if (Difference[Mtr_num] < 10000)
				{
					Acc_speed_p[Mtr_num] = New_speed[Mtr_num] / Factor_acc[Mtr_num];
					if (Acc_speed_p[Mtr_num] < 1)
						Acc_speed_p[Mtr_num] = 1;
					if (New_speed[Mtr_num] > Vmax_pos[Mtr_num])
						New_speed[Mtr_num] = Vmax_pos[Mtr_num];
					if (New_speed[Mtr_num] > Acc_speed_p[Mtr_num])
						New_speed[Mtr_num] = Acc_speed_p[Mtr_num];
				}
				else
				{
					Dir_diff[Mtr_num] = False;
					if (Difference[Mtr_num] >= -10000)
						Acc_speed_n[Mtr_num] = New_speed[Mtr_num] / Factor_acc[Mtr_num];
					if (Acc_speed_n[Mtr_num] > -1)
						Acc_speed_n[Mtr_num] = -1;
					if (New_speed[Mtr_num] < Vmax_neg[Mtr_num])
						New_speed[Mtr_num] = Vmax_neg[Mtr_num];
					if (New_speed[Mtr_num] < Acc_speed_n[Mtr_num])
						New_speed[Mtr_num] = Acc_speed_n[Mtr_num];
				}
			}
			else
			{
				if (Dir_diff[Mtr] = True)
				{
					New_encoder[Mtr_num] = Trapez_1[Mtr_num] - Pos_encoder[Mtr_num];
					New_encoder[Mtr_num] = Point_p1[Mtr_num] - New_encoder[Mtr_num];;
					if (Pos_encoder[Mtr_num]< Trapez_1[Mtr_num])  Acc_speed[Mtr_num] = New_encoder[Mtr_num] / Factor_acc[Mtr_num];      
					if (Pos_encoder[Mtr_num] >= Trapez_2[Mtr_num]) Acc_speed[Mtr_num] = New_speed[Mtr_num] / Factor_acc[Mtr_num];
					if (Acc_speed[Mtr_num] < 1) Acc_speed[Mtr_num] = 1;
					if (New_speed[Mtr_num] > Vel_pos[Mtr_num])  New_speed[Mtr_num] = Vel_pos[Mtr_num];
					if (New_speed[Mtr_num] > Acc_speed[Mtr_num]) New_speed[Mtr_num] = Acc_speed[Mtr_num];
				}
				else
				{
					New_encoder[Mtr_num] = Trapez_1[Mtr_num] - Pos_encoder[Mtr_num];
					New_encoder[Mtr_num] = New_encoder[Mtr_num] + Point_p1[Mtr_num];
					New_encoder[Mtr_num] = -New_encoder[Mtr_num];
					if (Pos_encoder[Mtr_num] >= Trapez_1[Mtr_num])  Acc_speed[Mtr_num] = New_encoder[Mtr_num] / Factor_acc[Mtr_num];
					if (Pos_encoder[Mtr_num] < Trapez_2[Mtr_num]) Acc_speed[Mtr_num] = New_speed[Mtr_num] / Factor_acc[Mtr_num];
					if (Acc_speed[Mtr_num] > -1) Acc_speed[Mtr_num] = -1;
					if (New_speed[Mtr_num] < Vel_neg[Mtr_num])  New_speed[Mtr_num] = Vel_neg[Mtr_num];
					if (New_speed[Mtr_num] < Acc_speed[Mtr_num]) New_speed[Mtr_num] = Acc_speed[Mtr_num];
				}
			}
			switch (Mode_ctrl)
			{
			case Mode_pos:
				Exe_pid(&Mtr, &Pos_final[Mtr_num], &Pos_encoder[Mtr_num]);
				break;
			case Mode_vel:
				Exe_pid(&Mtr_num, &Motor_setpoint[Mtr_num], &Act_speed[Mtr_num]);
				break;
			case Mode_trp:			
				Motor_setpoint[Mtr_num] = New_speed[Mtr];
				if (Start_move.Start_move == 0) Motor_setpoint[Mtr_num] = 0;
				Exe_pid(&Mtr_num, &Motor_setpoint[Mtr_num], &Act_speed[Mtr_num]);
				break;

			case Mode_velp:
				Configure_pid(Mtr_num, 0, 0, 0);
				if (Mtr_num == 1) M1_pwm = 0;
				if (Mtr_num == 2) M2_pwm = 0;
				break;
			}
			if (abs(Act_speed[Mtr_num]) > 2)
				Mstop_ctr[Mtr_num] = 0;
			else if (Mstop_ctr[Mtr_num] < 200){
				Mstop_ctr[Mtr_num]++;
			}
			if (Mstop_ctr[Mtr_num] > 150)
				Temp_bit.Temp_bit= 0;
			else
				Temp_bit.Temp_bit= 1;
			if (Mtr_num = 1)
				Stop1_bit.Stop1_bit= 0;
			else
				Stop2_bit.Stop2_bit = 1;
		}
	}
	Timer_pid++;
	Motor_led.Motor_led = False;
}
/*
'KJL Function's

Function Max_minl(byval I As Long) As Long       'keep value between -255 to 255

If I > 255 Then
I = 255
Elseif I < 255 Then
I = -255
End If

Max_minl = I

End Function
*/
long Max_minl(long I)
{
	if (I > 255)
		I = 255;
	else if (I < 255)
		I = -255;
	return (long)I;
}

/*
'-------------------------------------------------------------------------------
'----------------------- CALCULATE  PID ---------------------------------------
'----------------------- time PER PID = 90 uSecond ---------------------------
'-------------------------------------------------------------------------------
Sub Exe_pid(mtr_num, Pid_setpoint, Pid_actual)       '90 microsecond

'.. Motor_led = True
Pid_error(mtr_num) = Pid_setpoint - Pid_actual
Pid_out(mtr_num) = Pid_error(mtr_num) * Pid_kp(mtr_num)

Ptemp(mtr_num) = Pid_error(mtr_num) - Pid_prev_error(mtr_num)
Ptemp(mtr_num) = Ptemp(mtr_num) * Pid_kd(mtr_num)

Pid_prev_error(mtr_num) = Pid_error(mtr_num)

Pid_out(mtr_num) = Pid_out(mtr_num) + Ptemp(mtr_num)

Ptemp(mtr_num) = Pid_integral_error(mtr_num) * Pid_ki(mtr_num)
Pid_out(mtr_num) = Pid_out(mtr_num) + Ptemp(mtr_num)
Pid_out(mtr_num) = Max_minl(pid_out(mtr_num) / Pid_scale(mtr_num))       '+/-255 limit

Pwm_temp = Abs(pid_out(mtr_num))       'calculate the absolute value

If Pwm_temp < 255 Then       'add Pid_integral to Pid_error if < 255
Pid_error(mtr_num) = Max_minl(pid_error(mtr_num) + Pid_integral_error(mtr_num))
Pid_integral_error(mtr_num) = Pid_error(mtr_num)
End If

If Pid_out(mtr_num) = > 0 Then       'set motor direction
Dir_temp = 0
Else
Dir_temp = 1
End If

'keep < user max PWM limit
If Pwm_temp = > Max_pwm(mtr_num) Then Pwm_temp = Max_pwm(mtr_num)

Rpwm(mtr_num) = Pwm_temp       'pwm rate

If Mtr_num = 1 Then       'apply to specific motor
M1dir_bit = Dir_temp
M1_pwm = Pwm_temp
Else
M2dir_bit = Dir_temp
M2_pwm = Pwm_temp
End If

'.. Motor_led = False

End Sub
*/

void Exe_pid(byte * Mtrnum, long *Pid_setpoint, long * Pid_actual)
{
	printf("exe_pid %d\n", *Pid_setpoint);
	Pid_error[*Mtrnum] = *Pid_setpoint - *Pid_actual;
	Pid_out[*Mtrnum] = Pid_error[*Mtrnum] * Pid_kp[*Mtrnum];
	Ptemp[*Mtrnum] = Pid_error[*Mtrnum] - Pid_prev_error[*Mtrnum];
	Ptemp[*Mtrnum] = Ptemp[*Mtrnum] * Pid_kd[*Mtrnum];
	Pid_prev_error[*Mtrnum] = Pid_error[*Mtrnum];
	Pid_out[*Mtrnum] = Pid_out[*Mtrnum] + Ptemp[*Mtrnum];
	Ptemp[*Mtrnum] = Pid_integral_error[*Mtrnum] * Pid_ki[*Mtrnum];
	Pid_out[*Mtrnum] = Pid_out[*Mtrnum] + Ptemp[*Mtrnum];
	Pid_out[*Mtrnum] = Max_minl(Pid_out[*Mtrnum] / Pid_scale[*Mtrnum]);
	Pwm_temp = (byte)abs(Pid_out[*Mtrnum]);
	if (Pwm_temp < 255) {
		Pid_error[*Mtrnum] = Max_minl(Pid_out[*Mtrnum]) + Pid_integral_error[*Mtrnum];
		Pid_integral_error[*Mtrnum] = Pid_error[*Mtrnum];
	}
	if (Pid_out[*Mtrnum] >= 0)
		Dir_temp = 0;
	else
		Dir_temp = 1;
	if (Pwm_temp >= Max_pwm[*Mtrnum])
		Pwm_temp = Max_pwm[*Mtrnum];
	Rpwm[*Mtrnum] = Pwm_temp;
	if (*Mtrnum == 1)
	{
		M1_dir_bit.M1_dir_bit = Dir_temp;
		M1_pwm = Pwm_temp;
	}
	else
	{
		M2_dir_bit.M2_dir_bit = Dir_temp;
		M2_pwm = Pwm_temp;
	}
}
/*
Sub Set_mode(mode_control)

Select Case Mode_control

Case Mode_pos       'POSITION 0

Flag_velocity = False
Call Configure_pid(1, 200, 0, 200)
Call Configure_pid(2, 200, 0, 200)
Pos_final(1) = Pos_encoder(1)
Pos_final(2) = Pos_encoder(2)

Case Mode_vel       'VELOCITY  1

Flag_velocity = False
Call Configure_pid(1, 700, 100, 700)
Call Configure_pid(2, 700, 100, 700)
Motor_setpoint(1) = 0
Motor_setpoint(2) = 0

Case Mode_trp       'TRAPEZOIDALE 2

Flag_velocity = False
Call Configure_pid(1, 500, 100, 500)
Call Configure_pid(2, 500, 100, 500)
Pos_final(1) = Pos_encoder(1)
Pos_final(2) = Pos_encoder(2)

Case Mode_velp       'VELOCITY PID 3

Flag_velocity = True
Call Configure_pid(1, 400, 100, 400)
Call Configure_pid(2, 400, 100, 400)
Pos_final(1) = Pos_encoder(1)
Pos_final(2) = Pos_encoder(2)

Case Mode_idle       'IDLE  4

Flag_velocity = False
Call Configure_pid(1, 0, 0, 0)
Call Configure_pid(2, 0, 0, 0)
End Select

Mode_ctrl = Mode_control

End Sub


*/
void Set_mode(byte mode_control)
{
	switch (mode_control)
	{
	case Mode_pos:
		Flag_velocity.Flag_velocity = False;
		Configure_pid(1, 200, 0, 200);
		Configure_pid(2, 200, 0, 200);
		Pos_final[1] = Pos_encoder[1];
		Pos_final[2] = Pos_encoder[2];
		break;
	case Mode_vel:
		Flag_velocity.Flag_velocity = False;
		Configure_pid(1, 700, 100, 700);
		Configure_pid(2, 700, 100, 700);
		Motor_setpoint[1] = 0;
		Motor_setpoint[2] = 0;
		break;
	case Mode_trp:
		Flag_velocity.Flag_velocity = False;
		Configure_pid(1, 500, 100, 500);
		Configure_pid(2, 500, 100, 500);
		Pos_final[1] = Pos_encoder[1];
		Pos_final[2] = Pos_encoder[2];
		break;
	case Mode_velp:
		Flag_velocity.Flag_velocity = True;
		Configure_pid(1, 400, 100, 400);
		Configure_pid(2, 400, 100, 400);
		Pos_final[1] = Pos_encoder[1];
		Pos_final[2] = Pos_encoder[2];
		break;
	case Mode_idle:
		Flag_velocity.Flag_velocity = False;
		Configure_pid(1, 0, 0, 0);
		Configure_pid(2, 0, 0, 0);
		break;
	default:
		break;
	}
	Mode_ctrl = mode_control;

}
