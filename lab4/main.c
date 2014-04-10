#include <stm32f30x.h>
#include <f3d_led.h>
#include <f3d_button.h>
#include <f3d_uart.h>
#include<stdio.h>
#include<queue.h>
#include<f3d_gyro.h>
#include<f3d_systick.h>
#include <sensor.h>

int main(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    uint8_t ctrl1=0x00;
    f3d_led_init();
    f3d_button_init();
    f3d_uart_init();
    f3d_gyro_init();   
    f3d_sensor_interface_init();
    f3d_sensor_init();
    int j=0;
    while(1){
	j=f3d_button_read();
	if(j==1)
	{
	f3d_systick_init();
	j=f3d_button_read();
	if(j==0)
	{
	while(1){	
	j=f3d_button_read();
	if(j==1)
	printy();}}}
    /*int z=0;
    int j=f3d_button_read();
    if(j==1){
    while(f3d_button_read());
    j=0;
    while(j!=1 && z<20)
    {
	z=z+1;
	j=f3d_button_read();
	//if(j==0){
        uint8_t ctrl1 = 0x00;
        ctrl1 = 0x01;
        f3d_sensor_write(&ctrl1, 0x21, 1);
        int16_t temperature;
        uint8_t pu8[3] ={0};
        f3d_sensor_read(pu8, 0x2B, 2);//READING TEMPERATURE
        temperature = ((uint16_t) pu8[1]<<8) | pu8[0];
        float Temperature_DegC = 42.5 + temperature / (120*4);
        printf("Temperature is:%f\n",Temperature_DegC);
        f3d_sensor_read(pu8, 0x28, 3);//READING PRESSURE
        uint32_t pressure = ((uint32_t)pu8[2]<<16)|((uint32_t)pu8[1]<<8)|pu8[0]; // make a unsigned 32 bit variable
        float pressure1 = pressure / 4096;
        printf("Pressure is:%f mb\n",pressure1);
        float Altitude_ft = (1-pow(pressure1/1013.25,0.190284))*145366.45;
        printf("Altitude is:%f Ft\n",Altitude_ft);  }while(f3d_button_read());}*/
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{

printf("Assert Called!");

/* Infinite loop */
/* Use GDB to find out why we're here */
    while (1);

}
#endif
