#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_button.h>
#include <f3d_uart.h>
#include <stdio.h>
#include<queue.h>
#include<f3d_gyro.h>
#include<f3d_systick.h>
#include <sensor.h>
#include <f3d_timer4.h>
#include <f3d_sdcard.h>
#include <stm32f30x_rtc.h>
#include <diskio.h>
#include <math.h>
#include<string.h>
#include<f3d_accel.h>
#include<f3d_mag.h>
#include<math.h>


void bijli(int n) {
  f3d_led_all_off();
  if(n==0)
    f3d_led_on(0);
  if(n==1)
    f3d_led_on(1);
  if(n==2)
    f3d_led_on(2);
  if(n==3)
    f3d_led_on(3);
  if(n==4)
    f3d_led_on(4);
  if(n==5)
    f3d_led_on(5);
  if(n==6)
    f3d_led_on(6);
  if(n==7)
    f3d_led_on(7);
}



void main(void) {
  f3d_systick_init();
  f3d_uart2_init();
  f3d_i2c1_init();
  f3d_accel_init();
  f3d_mag_init();
  f3d_led_init();
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  float accel_data[3];
  float mag_data[3];
  int c;
  float tilt,utilt;
  float pitch,roll;
  float xh,yh;
  float xm,ym,zm;
  float xa,ya,za,xna,yna;
  while(1) {
    f3d_accel_read(accel_data);		
    xa=accel_data[0];
    ya=accel_data[1];
    za=accel_data[2];
    xna=(xa/sqrt((xa*xa)+(ya*ya)+(za*za)));
    pitch=asin(-xna);
    yna=(ya/sqrt((xa*xa)+(ya*ya)+(za*za)));
    roll=asin(yna/cos(pitch));
    printf("%s%f\n","Pitch : ",pitch*57.2957795);
    printf("%s%f\n","Roll : ",roll*57.2957795);
    f3d_mag_read(mag_data);
    xm=mag_data[0];
    ym=mag_data[1];
    zm=mag_data[2];
    xh= xm*cos(pitch)+zm*sin(pitch);
    yh= (xm*sin(roll)*sin(pitch)) + (ym*cos(roll))-(zm*sin(roll)*cos(pitch));			
    utilt=atan(ym/xm)*57.2957795;						//Uncompensated heading
    tilt=atan(yh/xh)*57.2957795;						//tilt compensated heading
    printf("%s%f\n","Uncompensated heading: ",utilt);
    printf("%s%f\n\n\n","Tilt compensated heading: ",tilt);
    if(yh<=0 && xh<=0) {
      if(tilt<22.5)
        bijli(1);
      else if(tilt<67.5)
        bijli(2);
      else
        bijli(3);
    }
    else if(yh>0 && xh<0) {
      if(tilt<-67.5)
        bijli(7);
      else if(tilt<-22)
        bijli(0);
      else
        bijli(1);
    }
    else if(yh>0 && xh>0) {
      if(tilt<22.5)
        bijli(5);
      else if(tilt=67.5)
        bijli(6);
      else
        bijli(7);
    }
    else if(yh<0 && xh>0) {
      if(tilt<-67.5)
        bijli(3);
      else if(tilt<-22.5)
        bijli(4);
      else
        bijli(5);
    }
  }  
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  printf("Assertion: %s %d\n",file, line);
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

