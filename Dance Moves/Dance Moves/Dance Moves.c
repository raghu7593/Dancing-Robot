/********************************************************************************
 Platform: ATMEGA1284 servo controller board 
 Experiment:  Longbow locomotion with fast speed on rough terrain 
 Written by: Vinod Desai, NEX Robotics Pvt. Ltd.
 Edited By: Sachitanand Malewar, NEX Robotics Pvt. Ltd.
 Last Modification: 10th Apr 2013
 AVR Studio Version 6 
 
 This application code will make the longbow to move in 3 steps forward, back, 
 clockwise and counterclockwise direction with fast speed on rough terrain. 
 This mode is not recommended mode for long time motion, as it produces much 
 stress on the servo motors and decay the servo motors life.Also take much  more 
 power from the battery. Do not use these motions unless necessary.
 
 Note: 
 
    Make sure that in the configuration options following settings are 
 	done for proper operation of the code

 	Microcontroller: ATMEGA1284P
 	Frequency: 14745600
 	Optimization: O0 

*************************************************************************************************/

/*************************************************************************************************

   Copyright (c) 2013, NEX Robotics Pvt. Ltd.                       -*- c -*-
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the
   distribution.

   * Neither the name of the copyright holders nor the names of
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

   * Source code can be used for academic purpose.
   For commercial use permission form the author needs to be taken.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. 

  Software released under Creative Commence cc by-nc-sa license.
  For legal information refer to: 
  http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode

*********************************************************************************/
//************************************************************************
#include <avr/io.h>                         // already included when you create a project
#include <avr/interrupt.h>
#include <util/delay.h>

#include "longbowLib.h"                     // must include for accessing longbow library functions

#define F_CPU 14745600UL
#include <stdio.h>
int i = 0;
void uart0_init(void)
{
	UCSR0B = 0x00; //disable while setting baud rate
	UCSR0A = 0x00;
	UCSR0C = 0x06;
	UBRR0L = 0x5F; //set baud rate lo
	UBRR0H = 0x00; //set baud rate hi
	UCSR0B = 0x98;
}

void step(char s)
{
	if(i%2 == 0)
	{
		angle_1B(60);
	}
	else
	{
		angle_1B(90);
	}
	_delay_ms(10);
	i++;
}

void hipShake()
{
	angle_1A(45);angle_2A(45);angle_3A(45);angle_4A(135);angle_5A(135);angle_6A(135);
	_delay_ms(500);
	angle_1A(135);angle_2A(135);angle_3A(135);angle_4A(45);angle_5A(45);angle_6A(45);
	_delay_ms(500);
}

void parallelFB1()
{
	angle_1A(75);angle_2A(75);angle_3A(75);angle_4A(105);angle_5A(105);angle_6A(105);	
}

void parallelFB2()
{
	angle_1A(105);angle_2A(105);angle_3A(105);angle_4A(75);angle_5A(75);angle_6A(75);
}


void parallelFB()
{
	angle_1A(75);angle_2A(75);angle_3A(75);angle_4A(105);angle_5A(105);angle_6A(105);
	_delay_ms(500);
	angle_1A(105);angle_2A(105);angle_3A(105);angle_4A(75);angle_5A(75);angle_6A(75);
	_delay_ms(500);
}

void parallelLR1()
{
	angle_1B(130);angle_2B(130);angle_3B(55);angle_4B(55);angle_5B(55);angle_6B(130);
	angle_1C(75);angle_2C(75);angle_3C(105);angle_4C(75);angle_5C(75);angle_6C(105);
}

void parallelLR2()
{
	angle_1C(105);angle_2C(105);angle_3C(75);angle_4C(105);angle_5C(105);angle_6C(75);
	angle_1B(130);angle_2B(130);angle_3B(55);angle_4B(55);angle_5B(55);angle_6B(130);
}

void parallelLR()
{
	angle_1B(130);angle_2B(130);angle_3B(55);angle_4B(55);angle_5B(55);angle_6B(130);
	angle_1C(75);angle_2C(75);angle_3C(105);angle_4C(75);angle_5C(75);angle_6C(105);
	_delay_ms(500);
//	robot_stand_position();
//	_delay_ms(50);
	angle_1C(105);angle_2C(105);angle_3C(75);angle_4C(105);angle_5C(105);angle_6C(75);
	angle_1B(130);angle_2B(130);angle_3B(55);angle_4B(55);angle_5B(55);angle_6B(130);
	_delay_ms(500);
//	robot_stand_position();
//	_delay_ms(50);
}

void angleUD1()
{
	angle_1A(30);angle_2A(90);angle_3A(150);angle_4A(150);angle_5A(90);angle_6A(30);
	angle_1B(145);angle_2B(145);angle_3B(40);angle_4B(40);angle_5B(40);angle_6B(145);
	angle_1C(90);angle_2C(90);angle_3C(90);angle_4C(90);angle_5C(90);angle_6C(90);
}

void angleUD2()
{
	angle_1A(30);angle_2A(90);angle_3A(150);angle_4A(150);angle_5A(90);angle_6A(30);
	angle_1B(125);angle_2B(125);angle_3B(60);angle_4B(60);angle_5B(60);angle_6B(125);
	angle_1C(70);angle_2C(70);angle_3C(110);angle_4C(110);angle_5C(110);angle_6C(70);
}

void angleUD()
{
	angle_1A(30);angle_2A(90);angle_3A(150);angle_4A(150);angle_5A(90);angle_6A(30);

	angle_1B(145);angle_2B(145);angle_3B(40);angle_4B(40);angle_5B(40);angle_6B(145);
	angle_1C(90);angle_2C(90);angle_3C(90);angle_4C(90);angle_5C(90);angle_6C(90);
	_delay_ms(500);
	angle_1B(125);angle_2B(125);angle_3B(60);angle_4B(60);angle_5B(60);angle_6B(125);
	angle_1C(70);angle_2C(70);angle_3C(110);angle_4C(110);angle_5C(110);angle_6C(70);
	_delay_ms(500);
}

void handy1()
{
	angle_1A(0); angle_1B(125); angle_1C(180);
	angle_2A(90); angle_2B(125); angle_2C(90);
	angle_3A(90); angle_3B(55); angle_3C(90);
	angle_4A(90); angle_4B(55); angle_4C(90);
	angle_5A(90); angle_5B(55); angle_5C(90);
	angle_6A(90); angle_6B(125); angle_6C(90);
}

void handy2()
{
	angle_1A(0); angle_1B(90); angle_1C(150);
	angle_2A(90); angle_2B(145); angle_2C(100);
	angle_3A(90); angle_3B(35); angle_3C(80);
	angle_4A(90); angle_4B(75); angle_4C(100);
	angle_5A(90); angle_5B(75); angle_5C(100);
	angle_6A(90); angle_6B(105); angle_6C(80);
}

void handy()
{
	angle_1A(0); angle_1B(125); angle_1C(180); 
	angle_2A(90); angle_2B(125); angle_2C(90);
	angle_3A(90); angle_3B(55); angle_3C(90); 
	angle_4A(90); angle_4B(55); angle_4C(90);
	angle_5A(90); angle_5B(55); angle_5C(90); 
	angle_6A(90); angle_6B(125); angle_6C(90);
	_delay_ms(300);
	angle_1A(0); angle_1B(90); angle_1C(150);
	angle_2A(90); angle_2B(145); angle_2C(100);
	angle_3A(90); angle_3B(35); angle_3C(80); 
	angle_4A(90); angle_4B(75); angle_4C(100);
	angle_5A(90); angle_5B(75); angle_5C(100); 
	angle_6A(90); angle_6B(105); angle_6C(80);
	_delay_ms(300);
	
}


void sideBend()
{
	angle_1C(45);angle_2C(45);angle_3C(135);angle_4C(45);angle_5C(45);angle_6C(135);
	_delay_ms(500);
	angle_1C(135);angle_2C(135);angle_3C(45);angle_4C(135);angle_5C(135);angle_6C(45);
	_delay_ms(500);
}

void sideBend1()
{
	angle_1C(45);angle_2C(45);angle_3C(135);angle_4C(45);angle_5C(45);angle_6C(135);
	angle_1B(80);angle_2B(80);angle_3B(100);angle_4B(80);angle_5B(80);angle_6B(100);
	_delay_ms(600);
	angle_1C(135);angle_2C(135);angle_3C(45);angle_4C(135);angle_5C(135);angle_6C(45);
	angle_1B(100);angle_2B(100);angle_3B(80);angle_4B(100);angle_5B(100);angle_6B(80);
	_delay_ms(600);
}

void hipShakeSideBend()
{
	angle_1A(45);angle_2A(45);angle_3A(45);angle_4A(135);angle_5A(135);angle_6A(135);
	_delay_ms(500);
	angle_1C(45);angle_2C(45);angle_3C(135);angle_4C(45);angle_5C(45);angle_6C(135);
	_delay_ms(500);
	angle_1A(135);angle_2A(135);angle_3A(135);angle_4A(45);angle_5A(45);angle_6A(45);
	_delay_ms(500);
	angle_1C(135);angle_2C(135);angle_3C(45);angle_4C(135);angle_5C(135);angle_6C(45);
	_delay_ms(500);
	robot_stand_position();
	_delay_ms(500);
}

void crouchWithoutDelay()
{
	angle_1A(175); angle_1B(175); angle_1C(5); angle_2A(175); angle_2B(175); angle_2C(5);
	angle_3A(175); angle_3B(5); angle_3C(175); angle_4A(5); angle_4B(5); angle_4C(175);
	angle_5A(5); angle_5B(5); angle_5C(175); angle_6A(5); angle_6B(175); angle_6C(5);
}

void crouchWithoutDelay2()
{
	angle_1A(5); angle_1B(175); angle_1C(5); angle_2A(5); angle_2B(175); angle_2C(5);
	angle_3A(5); angle_3B(5); angle_3C(175); angle_4A(175); angle_4B(5); angle_4C(175);
	angle_5A(175); angle_5B(5); angle_5C(175); angle_6A(175); angle_6B(175); angle_6C(5);
}

void crouch1()
{
	angle_1A(175); angle_1B(175); angle_1C(5); angle_2A(175); angle_2B(175); angle_2C(5);
	angle_3A(175); angle_3B(5); angle_3C(175); angle_4A(5); angle_4B(5); angle_4C(175);
	angle_5A(5); angle_5B(5); angle_5C(175); angle_6A(5); angle_6B(175); angle_6C(5);
	
}

void crouch2()
{
	robot_stand_position();	
}

void crouch3()
{
	angle_1A(5); angle_1B(175); angle_1C(5); angle_2A(5); angle_2B(175); angle_2C(5);
	angle_3A(5); angle_3B(5); angle_3C(175); angle_4A(175); angle_4B(5); angle_4C(175);
	angle_5A(175); angle_5B(5); angle_5C(175); angle_6A(175); angle_6B(175); angle_6C(5);
}

void crouch4()
{
	robot_stand_position();
}



void crouch()
{
	angle_1A(175); angle_1B(175); angle_1C(5); angle_2A(175); angle_2B(175); angle_2C(5);
	angle_3A(175); angle_3B(5); angle_3C(175); angle_4A(5); angle_4B(5); angle_4C(175);
	angle_5A(5); angle_5B(5); angle_5C(175); angle_6A(5); angle_6B(175); angle_6C(5);
	_delay_ms(600);
	robot_stand_position();
	_delay_ms(600);
	
	angle_1A(5); angle_1B(175); angle_1C(5); angle_2A(5); angle_2B(175); angle_2C(5);
	angle_3A(5); angle_3B(5); angle_3C(175); angle_4A(175); angle_4B(5); angle_4C(175);
	angle_5A(175); angle_5B(5); angle_5C(175); angle_6A(175); angle_6B(175); angle_6C(5);
	_delay_ms(600);
	robot_stand_position();
	_delay_ms(600);
}


void chiru1()
{
	angle_2B(5);angle_5B(175);
	
	
	angle_1A(45); angle_2A(135);angle_2C(20);
	angle_3A(45); angle_4A(45);
	angle_5A(135); angle_5C(160);angle_6A(45);
	
}


void chiru2()
{
	angle_2B(5);angle_5B(175);
	
	angle_1A(90); angle_2A(90);angle_2C(90);
	angle_3A(90); angle_4A(90);
	angle_5A(90);angle_5C(90); angle_6A(90);
	
}


void chiru3()
{
	angle_2B(5);angle_5B(175);
	
	angle_1A(135); angle_2A(45);angle_2C(20);
	angle_3A(135); angle_4A(135);
	angle_5A(45);angle_5C(160); angle_6A(135);
	
}


void chiru4()
{
	angle_2B(5);angle_5B(175);
	
	angle_1A(90); angle_2A(90);angle_2C(90);
	angle_3A(90); angle_4A(90);
	angle_5A(90); angle_5C(90);angle_6A(90);
}


void stepTurn()
{
	angle_1B(20);angle_3B(160);angle_5B(160);
	_delay_ms(500);
	angle_1A(120);angle_3A(120);angle_5A(120);
	_delay_ms(500);
	angle_1B(145);angle_2B(145);angle_3B(40);angle_4B(40);angle_5B(40);angle_6B(145);
	angle_1C(120);angle_3C(120);angle_5C(120);
	_delay_ms(500);
	angle_2B(20);angle_4B(160);angle_6B(20);
	_delay_ms(500);
	angle_1A(90);angle_2A(90);angle_3A(90);angle_4A(90);angle_5A(90);angle_6A(90);
	_delay_ms(500);
	robot_stand_position();
}

void chiru()
{
	angle_2B(5);angle_5B(175);
	_delay_ms(400);
	
	angle_1A(45); angle_2A(135);angle_2C(20);
	angle_3A(45); angle_4A(45);
	angle_5A(135); angle_5C(160);angle_6A(45);
	_delay_ms(400);
	//robot_stand_position();
	angle_1A(90); angle_2A(90);angle_2C(90);
	angle_3A(90); angle_4A(90);
	angle_5A(90);angle_5C(90); angle_6A(90);
	_delay_ms(400);
	
	angle_1A(135); angle_2A(45);angle_2C(20);
	angle_3A(135); angle_4A(135);
	angle_5A(45);angle_5C(160); angle_6A(135);
	_delay_ms(400);
	//robot_stand_position();
	angle_1A(90); angle_2A(90);angle_2C(90);
	angle_3A(90); angle_4A(90);
	angle_5A(90); angle_5C(90);angle_6A(90);
	_delay_ms(400);
}

void zeroPosition()
{
	angle_1A(0);angle_2A(0);angle_3A(0);angle_4A(0);angle_5A(0);angle_6A(0);
	angle_1B(0);angle_2B(0);angle_3B(0);angle_4B(0);angle_5B(0);angle_6B(0);
	angle_1C(0);angle_2C(0);angle_3C(0);angle_4C(0);angle_5C(0);angle_6C(0);
}

void upDown()
{
	angle_1B(175);angle_1C(140);
	angle_2B(175);angle_2C(140);
	angle_3B(175);angle_3C(140);
	angle_4B(175);angle_4C(140);
	angle_5B(175);angle_5C(140);
	angle_6B(175);angle_6C(140);
	
	angle_1B(110);
}

void danceMoves()
{
	robot_stand_position();
	int i = 0;
	for(i=0; i<2; i++)
	{
		upDown();
		_delay_ms(100);
	}
	for(i=0; i<2; i++)
	{
		chiru();
	}
	for(i=0; i<2; i++)
	{
		crouch();
	}
	for(i=0; i<2; i++)
	{
		hipShakeSideBend();
	}
	for(i=0; i<2; i++)
	{
		sideBend();
	}
	for(i=0; i<2; i++)
	{
		hipShake();
	}
	robot_stand_position();
}

void danceMovesFinal()
{
	int j = 0;
	robot_stand_position();
	_delay_ms(500);
	for(j=0; j<3; j++)
	{
		parallelFB();
	}
	robot_stand_position();
	_delay_ms(500);
	for(j=0; j<3; j++)
	{
		parallelLR();
	}	
	robot_stand_position();
	_delay_ms(500);
	for(j=0; j<3; j++)
	{
		angleUD();
	}
	robot_stand_position();
	_delay_ms(500);
	for(j=0; j<3; j++)
	{
		handy();
	}
	robot_stand_position();
	_delay_ms(500);
	//for(j=0; j<3; j++)
	//{
	//	hipShakeSideBend();
	//}
	robot_stand_position();
	_delay_ms(500);
	for(j=0; j<3; j++)
	{
		crouch();
	}
	robot_stand_position();
	_delay_ms(500);
	for(j=0; j<3; j++)
	{
		chiru();
	}
	robot_stand_position();
	_delay_ms(500);
}

SIGNAL(USART0_RX_vect)
{
	char ser_data0 = 0x00;
	//uart has received a character in UDR1

	ser_data0 = UDR0;		// receive the data in variable
	if(ser_data0 == 0x72)
	{
		step(ser_data0);
		_delay_ms(100);
		step(ser_data0);
		_delay_ms(100);
		crouch();
		_delay_ms(100);
		step(ser_data0);
		_delay_ms(100);
		step(ser_data0);
	}
	else if(ser_data0 == 'a')
	{
		chiru1();
	}
	else if(ser_data0 == 'b')
	{
		chiru2();
	}
	else if(ser_data0 == 'c')
	{
		chiru3();
	}
	else if(ser_data0 == 'd')
	{
		chiru4();
	}
	else if(ser_data0 == 'e')
	{
		crouch1();	
	}
	else if(ser_data0 == 'f')
	{
		crouch2();
	}
	else if(ser_data0 == 'g')
	{
		crouch3();
	}
	else if(ser_data0 == 'h')
	{
		crouch4();
	}
	else if(ser_data0 == 'i')
	{
		parallelFB1();
	}
	else if(ser_data0 == 'j')
	{
		parallelFB2();
	}
	else if(ser_data0 == 'k')
	{
		angleUD1();
	}
	else if(ser_data0 == 'l')
	{
		angleUD2();
	}
	else if(ser_data0 == 'm')
	{
		parallelLR1();
	}
	else if(ser_data0 == 'n')
	{
		parallelLR2();
	}
	else if(ser_data0 == 'o')
	{
		handy1();
	}
	else if(ser_data0 == 'p')
	{
		handy2();
	}
	else
	{
		robot_stand_position();
	}

	UDR0 = ser_data0;		// echo back received data back to the PC
	
}

void stand()
{
		angle_1A(90);angle_2A(90);angle_3A(90);angle_4A(90);angle_5A(90);angle_6A(90);
		angle_1B(145);angle_2B(145);angle_3B(40);angle_4B(40);angle_5B(40);angle_6B(145);
		angle_1C(90);angle_2C(90);angle_3C(90);angle_4C(90);angle_5C(90);angle_6C(90);
}

void init_devices0()
{
	cli();              //disable all interrupts
	uart0_init();		 //to Rx data from PC to MCU through serial comm
	sei();              //re-enable interrupts
	//all peripherals are now initialized

}

int main(void) 
 {
	init_devices();                     // initializing  Microcontroller 20 servo pins used, timer 1  
	init_devices0();
	
	robot_stand_position();
	_delay_ms(1000);
//	danceMovesFinal();
	robot_stand_position();  	          // must be called as the first instruction after power ON		

/*	int n =10;
	while(n > 0) {
		stepTurn();
		n--;
	}*/
	while(1){}
 }
//***********************************************************************