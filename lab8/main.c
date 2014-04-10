#include <stm32f30x.h>
#include <f3d_uart.h>
#include <f3d_uart2.h>
#include <stdio.h>
// Simple looping delay function
int main(void)
{
  char b=5;
  int c;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  f3d_uart_init();
  f3d_uart2_init();
  f3d_systick_init();
  printf("Reset\n");
  
  while(1)
    {
	c = 3;
        printf("scam");
        //putchar2(getchar());
        //putchar(getchar2());
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


