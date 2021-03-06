/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_button.h>
#include <f3d_gyro.h>
#include <stdio.h>
#include <queue.h>
#define TIMER 20000

void chaluPositive(float n)
{
if(n<20.0)
		f3d_led_all_off();
if(n<115.0 && n>20.0)
	{
		f3d_led_all_off();
		f3d_led_on(1);
	}
if(n>115.0)
	f3d_led_on(2);
if(n>230.0)
	f3d_led_on(3);
if(n>335.0)
	f3d_led_on(4);
if(n>450.0)
	f3d_led_on(5);
}

void chaluNegative(float n)
{
if(n>(-20.0))
	f3d_led_all_off();

	
if(n>(-115.0) && n<(-20.0))
	{
	f3d_led_all_off();
	f3d_led_on(1);
	}
if(n<(-115.0))
	f3d_led_on(0);
if(n<(-230.0))
	f3d_led_on(7);
if(n<(-335.0))
	f3d_led_on(6);
if(n<(-450.0))
	f3d_led_on(5);
}




int main(void) { 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  float pfdata[3];
  f3d_uart_init();
  f3d_led_init();
  f3d_button_init(); 
  f3d_gyro_init();
  int i=0;
  int c;
  int k=0;

  printf("Reset\n");
flush();
  while (1)
   {
 
  f3d_gyro_getdata(pfdata);
  int j = f3d_button_read();
  c=getchar();
     if(c!=0)
  {
   if(c=='y')
   i=1;
   if(c=='z')
   i=2;
   k=1;
  }

  if(j==1 || k==1)
  {
while(1){
    flush();
   j = f3d_button_read();
   
	if(j==0){ 
    
	if(i==0)
 	 {
   	printf("%s","x");
   		while(i==0)
   			{   
    			f3d_gyro_getdata(pfdata);
    //if(pfdata[0]>5.0) 
   
    			if(pfdata[0]>20.0 || pfdata[0]<-20.0){
    			printf("%s","x: ");
    			printf("%f\n",pfdata[0]);
    			}
    		if(pfdata[0]>0)
    		chaluPositive(pfdata[0]);
    		else
    		chaluNegative(pfdata[0]);
    		c=getchar();
     		if(c!=0)
  		{
  		 if(c=='y')
   		i=1;
   		if(c=='z')
   		i=2;
   		k=1;
  		}	
    		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET)
		{i++;
    		break;}
   		}
   
  		} 
	else if(i==1){
  printf("%s","y");
	while(i==1)
{   
f3d_gyro_getdata(pfdata);

   if(pfdata[1]>20.0 || pfdata[1]<-20.0){
   printf("%s","y: ");
   printf("%f\n",pfdata[1]);}
    if(pfdata[1]>0)
    chaluPositive(pfdata[1]);
    else
    chaluNegative(pfdata[1]);
    c=getchar();
     if(c!=0)
  {
   if(c=='x')
   i=0;
   if(c=='z')
   i=2;
   k=1;
  }
if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET)
{i++;
break;}
}
}
else if(i == 2)
{
  printf("%s","z");
while(i==2)
{   
f3d_gyro_getdata(pfdata);
   //if(pfdata[0]>5.0) 
   if(pfdata[2]>20.0 || pfdata[2]<-20.0){
   printf("%f\n",pfdata[2]);}
    if(pfdata[2]>0)
    chaluPositive(pfdata[2]);
    else
    chaluNegative(pfdata[2]);
	c=getchar();
     if(c!=0)
  {
   if(c=='x')
   i=0;
   if(c=='y')
   i=1;
   k=1;
  }
if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET)
{i=0;
break;}
}

}

break;}
  }}
}

}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
printf("%s\n",file);
printf("%d\n",line);
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
