/*--------------------------------------------------------------------------------------
Konfigurasi Pin
PIN PZEM <=> STM32
RX - A2
TX - A3

PIN DMD <=> STM32
A - B11
B - B12
CLK - B13
SCLK - B10
R - B15
OE - B1
--------------------------------------------------------------------------------------*/
#include <DMD_STM32.h>
#include <PZEM004Tv30_STM32.h>
#include "st_fonts/SystemFont5x7.h"
#include "st_fonts/Arial_black_16.h"
#include "st_fonts/Arial_Black_16_ISO_8859_1.h"

// Pakai SPI 2   
SPIClass dmd_spi(2);
PZEM004Tv30_STM32 pzem(&Serial2);

// Pakai 3 DMD
#define DISPLAYS_ACROSS 3
#define DISPLAYS_DOWN 1

#define DMD_PIN_A PB11
#define DMD_PIN_B PB12
#define DMD_PIN_nOE PB1
#define DMD_PIN_SCLK PB10
DMD dmd(DMD_PIN_A, DMD_PIN_B, DMD_PIN_nOE, DMD_PIN_SCLK, DISPLAYS_ACROSS, DISPLAYS_DOWN, dmd_spi );

DMD_Standard_Font Arial_F(Arial_Black_16);

void setup(void)
{
  Serial2.begin(9600);
  Serial.begin(9600);
  dmd.init();
  dmd.clearScreen( true );
  dmd.setBrightness(80);
}

void loop(void)
{
  dmd.selectFont(&Arial_F);
 //dmd.clearScreen( true );
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();

  char tegangan[10];
  char arus[10];
  char arus2[10];
  char daya[10];

  dtostrf(voltage, 6, 4, tegangan);
  dtostrf(current, 6, 4, arus);
  dtostrf(power, 6, 4, daya);

  dmd.drawString(3, 1, tegangan, 3, GRAPHICS_NORMAL );
  
  //menyesuaikan jumlah digit manual

  if (current>=0.000 && current< 0.099){
      String arus1 = String(current);
      arus1.remove(0,1);
      arus1.toCharArray(arus2, 5);
      dmd.drawString(38, 1, arus2, 4, GRAPHICS_NORMAL );
    }else if (current>=0.100 && current < 9.999){
    dmd.drawString(39, 1, arus, 3, GRAPHICS_NORMAL );
    }else{
    dmd.drawString(38, 1, "OC", 2, GRAPHICS_NORMAL );
    Serial.println(arus);
    }

  if (power>=0.0 && power<10.0){
    dmd.drawString(69, 1, daya, 3, GRAPHICS_NORMAL );
    }else if (power>=10.0 && power<99.9){
    dmd.drawString(69, 1, daya, 3, GRAPHICS_NORMAL );
    }else{
    dmd.drawString(67, 1, daya, 3, GRAPHICS_NORMAL );
    }
  
  dmd.drawBox(  0,  0, 31, 15, GRAPHICS_NORMAL );
  dmd.drawBox(  32,  0, 63, 15, GRAPHICS_NORMAL );
  dmd.drawBox(  64,  0, 95, 15, GRAPHICS_NORMAL );
  delay(500);
}
