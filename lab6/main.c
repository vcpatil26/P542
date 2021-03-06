/* main.c ---
*
* Filename: main.c
* Description:
* Author:
* Maintainer:
* Created: Thu Jan 10 11:23:43 2013
* Last-Updated:
* By:
* Update #: 0
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

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_button.h>
#include <f3d_uart.h>
#include <f3d_sdcard.h>
#include <stm32f30x_rtc.h>
#include <diskio.h>
#include <math.h>

#include <stdio.h>

FATFS Fatfs;	/* File system object */
FIL Fil;	/* File object */
BYTE Buff[128];	/* File read buffer */

int main(void) {
  FRESULT rc;	/* Result code */
  DIR dir;	/* Directory object */
  FILINFO fno;	/* File information object */
  UINT bw, br;
  unsigned int retval;
  int i;
  int n=0;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_led_init();
  f3d_button_init();
  f3d_uart_init();
  f3d_delay_init();
  f3d_systick_init();
  f3d_sdcard_init();
	
  
  /* Provide a delay to allow the SDCARD time to go through it's power
up initialization. */
  for (i=0;i<500;i++) {
    f3d_delay_uS(500);
  }

  printf("Board Reset\n");

  f_mount(0, &Fatfs);	/* Register volume work area (never fails) */
  
  rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if (rc) die(rc);
  
  printf("\nOpen an existing file (message.txt).\n");
    rc = f_open(&Fil, "HELLO.TXT", FA_WRITE);
  if (rc) die(rc);

  n=f_size(&Fil);
  f_lseek(&Fil,n);
  
  printf("\nWrite a text data. *BYAD*\n");
  rc = f_write(&Fil, "bullbullllll\r\n", 16, &bw);
  if (rc) die(rc);
  printf("%u bytes written.\n", bw);
	

  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);

  printf("\nOpen an existing file (message.txt).\n");
  rc = f_open(&Fil, "HELLO.TXT", FA_READ);
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
  
  /*printf("\nCreate a new file (hello.txt).\n");
  rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if (rc) die(rc);*/
  /*
  printf("\nWrite a text data. (Hello world!)\n");
  rc = f_write(&Fil, "Hello world!\r\n", 14, &bw);
  if (rc) die(rc);
  printf("%u bytes written.\n", bw);*/
  /*
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);*/
  
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

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
