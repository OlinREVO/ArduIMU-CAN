#include "mcp_can.h"
#include <SPI.h>
#include <stdio.h>
#define INT8U unsigned char

unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];

void setup()
{
  delay(5000);
  Serial.begin(9600);
  if(CAN.begin(CAN_500KBPS) ==CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");
  attachInterrupt(0, MCP2515_ISR, FALLING);  // interrupt indicates when message is available
}

void MCP2515_ISR()
{
     Flag_Recv = 1;
}

void loop()
{
    if(Flag_Recv)
    {
      Flag_Recv = 0;
      CAN.readMsgBuf(&len, buf);
      Serial.print("CAN message length = ");
      Serial.print(len, DEC);
      Serial.print(" CAN message = ");
      for (int i = 0; i < 8; i = i + 1)
      {
        Serial.print(buf[i], DEC);
      }
      Serial.println();
    }
}
