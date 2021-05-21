// spi.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a byte to and from an SPI device
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o spi spi.c -l bcm2835
// sudo ./spi
//
// Or you can test it before installing with:
// gcc -o spi -I ../../src ../../src/bcm2835.c spi.c
// sudo ./spi
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include <bcm2835.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
// Use for testing
//        bcm2835_set_debug(1);

    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
    bcm2835_gpio_fsel(RPI_V2_GPIO_P1_29, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
    
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);                  // The default
    
    // Send a byte to the slave and simultaneously read a byte back from the slave
    // If you tie MISO to MOSI, you should read back what was sent
    
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
    bcm2835_delayMicroseconds(400);
    
    uint8_t send_data7 = 0b01001000;    //Opcode
    uint8_t send_data8 = 0x0A;          //Register
    uint8_t send_data9 = 0b11111110;    //Value
    uint8_t send_data1 = 0b01001000;    //Opcode
    uint8_t send_data2 = 0x10;          //Register
    uint8_t send_data3 = 0b11111111;    //Value
    uint8_t send_data4 = 0b01001001;    //Opcode
    uint8_t send_data5 = 0x19;          //Register
    uint8_t send_data6 = 0x00;          //Value
    uint8_t send_data13 = 0b01001000;    //Opcode
    uint8_t send_data14 = 0x00;          //Register
    uint8_t send_data15 = 0b11111111;    //Value
    uint8_t send_data10 = 0b01001001;    //Opcode
    uint8_t send_data11 = 0x09;          //Register
    uint8_t send_data12 = 0x00;          //Value
    
    uint8_t game_board[8][8];

    
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
    bcm2835_delayMicroseconds(400);
    uint8_t read_data7 = bcm2835_spi_transfer(send_data7);
    uint8_t read_data8 = bcm2835_spi_transfer(send_data8);
    uint8_t read_data9 = bcm2835_spi_transfer(send_data9);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
    bcm2835_delayMicroseconds(400);
    uint8_t read_data1 = bcm2835_spi_transfer(send_data1);
    uint8_t read_data2 = bcm2835_spi_transfer(send_data2);
    uint8_t read_data3 = bcm2835_spi_transfer(send_data3);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
    bcm2835_delayMicroseconds(400);
    uint8_t read_data4 = bcm2835_spi_transfer(send_data4);
    uint8_t read_data5 = bcm2835_spi_transfer(send_data5);
    uint8_t read_data6 = bcm2835_spi_transfer(send_data6);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
    bcm2835_delayMicroseconds(400);
    uint8_t read_data13 = bcm2835_spi_transfer(send_data13);
    uint8_t read_data14 = bcm2835_spi_transfer(send_data14);
    uint8_t read_data15 = bcm2835_spi_transfer(send_data15);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
    bcm2835_delayMicroseconds(400);
    uint8_t read_data10 = bcm2835_spi_transfer(send_data10);
    uint8_t read_data11 = bcm2835_spi_transfer(send_data11);
    uint8_t read_data12 = bcm2835_spi_transfer(send_data12);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);

//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data4, read_data7);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data5, read_data8);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data5, read_data9);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data1, read_data1);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data2, read_data2);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data3, read_data3);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data4, read_data4);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data5, read_data5);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data6, read_data6);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data10, read_data10);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data11, read_data11);
//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data12, read_data12);

    printf("\n8\t7\t6\t5\t4\t3\t2\t1");
    printf("\n%01d\t%01d\t%01d\t%01d\t%01d\t%01d\t%01d\t%01d\n", (read_data12 & 1) != 0, (read_data12 & 2) != 0, (read_data12 & 4) != 0, (read_data12 & 8) != 0, (read_data12 & 16) != 0, (read_data12 & 32) != 0, (read_data12 & 64) != 0, (read_data12 & 128) != 0);
    printf("\n9\t10\t11\t12\t13\t14\t15\t16");
    printf("\n%01d\t%01d\t%01d\t%01d\t%01d\t%01d\t%01d\t%01d\n\n", (read_data6 & 1) != 0, (read_data6 & 2) != 0, (read_data6 & 4) != 0, (read_data6 & 8) != 0, (read_data6 & 16) != 0, (read_data6 & 32) != 0, (read_data6 & 64) != 0, (read_data6 & 128) != 0);

    bcm2835_spi_end();

    bcm2835_close();
    return 0;
}

