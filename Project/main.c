#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_button.h>
#include <f3d_uart.h>
#include <stdio.h>
#include <queue.h>
#include <f3d_gyro.h>
#include <f3d_systick.h>
#include <sensor.h>
#include <f3d_timer4.h>
#include <f3d_sdcard.h>
#include <stm32f30x_rtc.h>
#include <diskio.h>
#include <math.h>
#include <string.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <math.h>

FATFS Fatfs;	/* File system object */
FIL Fil;	/* File object */
BYTE Buff[128];	/* File read buffer */


void log243( int xa, int ya, int za,int xm,int ym,int zm)
{	FRESULT rc;	/* Result code */
  DIR dir;	/* Directory object */
  FILINFO fno;	/* File information object */
  UINT bw, br;
  unsigned int retval;
	int n=0;
	int i;
  char as[100];
/* Provide a delay to allow the SDCARD time to go through it's power
up initialization. */
  for (i=0;i<500;i++) {
    f3d_delay_uS(500);
  }
  f_mount(0, &Fatfs);  

   printf("\nOpen an existing file (Data logger).\n");
   rc = f_open(&Fil, "Datalogger.TXT", FA_WRITE | FA_CREATE_ALWAYS);
   if (rc) die(rc);

   n=f_size(&Fil);
   f_lseek(&Fil,n);
   sprintf(as,"%d%s%d%s%d%s%d%s%d%s%d\n",xa,",",ya,",",za,",",xm,",",ym,",",zm);
  
 printf("\nWrite a text data.\n");
   rc = f_write(&Fil,as,strlen(as), &bw);
   if (rc) die(rc);

   printf("\nClose the file.\n");
   rc = f_close(&Fil);
   if (rc) die(rc);

    printf("\nOpen an existing file (message.txt).\n");
  rc = f_open(&Fil, "Datalogger.TXT", FA_READ);
  if (rc) die(rc);
  
  printf("\nType the file content.\n");
  for (;;) {
    rc = f_read(&Fil, Buff, sizeof Buff, &br);	/* Read a chunk of file */
    if (rc || !br) break;	/* Error or end of file */
    for (i = 0; i < br; i++)	/* Type the data */
      putchar(Buff[i]);
  }
  if (rc) die(rc);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);

  
  printf("\nOpen root directory.\n");
  rc = f_opendir(&dir, "");
  if (rc) die(rc);
  
  printf("\nDirectory listing...\n");
  for (;;) {
    rc = f_readdir(&dir, &fno);	/* Read a directory item */
    if (rc || !fno.fname[0]) break;	/* Error or end of dir */
    if (fno.fattrib & AM_DIR)
      printf(" <dir> %s\n", fno.fname);
    else
      printf("%8lu %s\n", fno.fsize, fno.fname);
  }
  if (rc) die(rc);
  printf("\nTest completed.\n");

  rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
  printf("%d %d\n",rc,retval);
  while (1);
}


void main(void) {
  f3d_systick_init();
  f3d_uart_init();
  f3d_i2c1_init();
  f3d_accel_init();
  f3d_mag_init();
  //f3d_led_init();
  f3d_sensor_interface_init();
  f3d_sensor_init();
  f3d_sdcard_init();
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  float accel_data[3];
  float mag_data[3];
  int c;
  //float tilt,utilt;
  //float pitch,roll;
  //float xh,yh;
  float xm,ym,zm;
  float xa,ya,za,xna,yna;
   DIR dir;	/* Directory object */
  FILINFO fno;	/* File information object */
  UINT bw, br;
  unsigned int retval;
	int n=0;
	int i;
  char as[100];
//printf("Hrllo");
/* Provide a delay to allow the SDCARD time to go through it's power
up initialization. */
  /*for (i=0;i<500;i++) {
    f3d_delay_uS(500);
  }*/
  while(1) {
//printf("Hello");
    f3d_accel_read(accel_data);		
    xa=accel_data[0];
    ya=accel_data[1];
    za=accel_data[2];
    //xna=(xa/sqrt((xa*xa)+(ya*ya)+(za*za)));
    //pitch=asin(-xna);
    //yna=(ya/sqrt((xa*xa)+(ya*ya)+(za*za)));
    //roll=asin(yna/cos(pitch));
    //printf("%s%f\n","Pitch : ",pitch*57.2957795);
    //printf("%s%f\n","Roll : ",roll*57.2957795);
    f3d_mag_read(mag_data);
    xm=mag_data[0];
    ym=mag_data[1];
    zm=mag_data[2];	
	while (1)
	{printf("Magnetometer data: %d,%d,%d\n",xm,ym,zm);
	printf("Accelerometer data: %d,%d,%d\n",xa,ya,za);
	log243(xa,ya,za,xm,ym,zm);}   

   
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

