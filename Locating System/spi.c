//#include <bcm2835.h>
#include <stdio.h>
#include <math.h>

void initialize_IOs();
int ** poll_gamezone();
void print_board(int board[8][8]);

int main()
{
  int board[8][8];

  for (int i = 0; i<8; i++) {
    for (int j = 0; j<8; j++) {
      board[i][j] = 0;
    }
  }
  board[2][3] = 1;
  print_board(board);


  return 0;
}
 
void print_board(int board[8][8]) {
  printf("\n\n");
  printf("\t┌───┬───┬───┬───┬───┬───┬───┬───┐\n");
  for (int i = 0; i<8; i++) {
    if ((i+1)%2) {
      printf("\t│   │ %d │   │ %d │   │ %d │   │ %d │\n",board[i][1],board[i][3],board[i][5],board[i][7]);
    } else
    {
      printf("\t│ %d │   │ %d │   │ %d │   │ %d │   │\n",board[i][0],board[i][2],board[i][4],board[i][6]);
    }
    if(i != 7) {
      printf("\t├───┼───┼───┼───┼───┼───┼───┼───┤\n");
    }
  }
  printf("\t└───┴───┴───┴───┴───┴───┴───┴───┘\n");
}
/*
int ** poll_gamezone() {

  int board[8][8]; 

  bcm2835_init();
  bcm2835_gpio_fsel(RPI_V2_GPIO_P1_29, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
  bcm2835_spi_begin();
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
  bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);  

  bcm2835_delayMicroseconds(400);
  bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
  bcm2835_delayMicroseconds(400);
  bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
  bcm2835_delayMicroseconds(400);

  for (int i = 0; i<=4; i++) {
    uint8_t address = i + 1;

    uint8_t send_data1 = 0b01000001 | address;    //Opcode
    uint8_t send_data2 = 0x19;                    //GPIO B
    uint8_t send_data3 = 0x00;                    //No data, for reading

    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
    bcm2835_delayMicroseconds(400);
    bcm2835_spi_transfer(send_data1);
    bcm2835_spi_transfer(send_data2);
    uint8_t read_data = bcm2835_spi_transfer(send_data3);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);

    for (int j = 0; j<8; j++) {
      if (j%2) {
        board[j][2*i+0] = (read_data & pow(double(2), double(j))) != 0;
      } else {
        board[j][2*i+1] = (read_data & pow(double(2), double(j))) != 0;
      }
    }
  }

  bcm2835_spi_end();
  bcm2835_close();

  return board;
}

void initialize_IOs() {

  bcm2835_init();
  bcm2835_gpio_fsel(RPI_V2_GPIO_P1_29, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
  bcm2835_spi_begin();
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
  bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);  

  bcm2835_delayMicroseconds(400);
  bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
  bcm2835_delayMicroseconds(400);
  bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
  bcm2835_delayMicroseconds(400);

  for (int i=0; i<=6; i++) {
    uint8_t address = i + 1;

    uint8_t send_data1 = 0b01000000 | address;    //Opcode
    uint8_t send_data2 = 0x0A;                    //IO Config
    uint8_t send_data3 = 0b11111110;              //Value
    uint8_t send_data4 = 0b01000000 | address;    //Opcode
    uint8_t send_data5 = 0x10;                    //IO DIR B
    uint8_t send_data6 = 0b11111111;              //Value
    uint8_t send_data7 = 0b01000000 | address;    //Opcode
    uint8_t send_data8 = 0x00;                    //IO DIR A
    uint8_t send_data9 = 0b11111111;              //Value

    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
    bcm2835_delayMicroseconds(400);
    bcm2835_spi_transfer(send_data1);
    bcm2835_spi_transfer(send_data2);
    bcm2835_spi_transfer(send_data3);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
    bcm2835_delayMicroseconds(400);
    bcm2835_spi_transfer(send_data4);
    bcm2835_spi_transfer(send_data5);
    bcm2835_spi_transfer(send_data6);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, LOW);
    bcm2835_delayMicroseconds(400);
    bcm2835_spi_transfer(send_data7);
    bcm2835_spi_transfer(send_data8);
    bcm2835_spi_transfer(send_data9);
    bcm2835_delayMicroseconds(400);
    bcm2835_gpio_write(RPI_V2_GPIO_P1_29, HIGH);
    bcm2835_delayMicroseconds(400);
  }

  bcm2835_spi_end();
  bcm2835_close();
}
*/