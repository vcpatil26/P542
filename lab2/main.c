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
#include <stm32f30x.h>
#include <f3d_led.h>
#include <f3d_button.h>
#include <f3d_uart.h>
#include<stdio.h>
#include<queue.h>
#include<f3d_systick.h>
// Simple looping delay function

int delay(int l)
{ 
  int c;
  int i = 2000000;
  while (i-- > 0) 
  {
    asm("nop");/* This stops it optimising code out*/ 
  }
	f3d_button_read();
        c=getchar();
           if(c!=0)
           {
              if(c=='p')
	      {
		if(l==0)
		printf("%s","NW\n");
		if(l==1)
                printf("%s","N\n"); 
		if(l==2)
                printf("%s","NE\n"); 
		if(l==3)
                printf("%s","E\n"); 
		if(l==4)
                printf("%s","SE\n"); 
		if(l==5)
                printf("%s","S\n"); 
		if(l==6)
                printf("%s","SW\n"); 
		if(l==7)
                printf("%s","W\n"); 
		if(l==8)
                printf("%s","ALL ON\n"); 
		if(l==9)
                printf("%s","ALL OFF\n"); 	
                while(1==1)
		{
		   if(getchar()=='r')
		   return;
		}
	      }
           }
	return;
}

int main(void) 
{
setvbuf(stdin, NULL, _IONBF, 0);
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);
f3d_led_init();
f3d_button_init();
f3d_uart_init();

while(1)
{
flush();
f3d_led_on(1);
delay(1);

f3d_led_off(1);
f3d_led_on(2);
delay(2);

f3d_led_off(2);
f3d_led_on(3);
delay(3);

f3d_led_off(3);
f3d_led_on(4);
delay(4);

f3d_led_off(4);
f3d_led_on(5);
delay(5);

f3d_led_off(5);
f3d_led_on(6);
delay(6);

f3d_led_off(6);
f3d_led_on(7);
delay(7);

f3d_led_off(7);
f3d_led_on(0);
delay(0);

f3d_led_off(8);
f3d_led_all_on();
delay(0);

f3d_led_all_off();
delay(9);
flush();		
}
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  /* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
