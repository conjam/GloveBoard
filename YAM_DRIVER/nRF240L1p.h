#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"


#define PIPE_0 0
#define PIPE_1 1
#define PIPE_2 2
#define PIPE_3 3
#define PIPE_4 4
#define PIPE_5 5

// Commands
#define CMD_R_REGISTER           0x00 // Mask 
#define CMD_W_REGISTER           0x20 // Mask 
#define CMD_R_RX_PAYLOAD         0x61
#define CMD_W_TX_PAYLOAD         0xA0
#define CMD_FLUSH_TX             0xE1
#define CMD_FLUSH_RX             0xE2
#define CMD_REUSE_TX_PL          0xE3
#define CMD_R_RX_PL_WID          0x60
#define CMD_W_ACK_PAYLOAD        0xA8 // Mask
#define CMD_W_TX_PAYLOAD_NO_ACK  0xB0
#define CMD_NOP                  0xFF

// Register offsets
#define REG_CONFIG               0x00
#define REG_EN_AA                0x01
#define REG_EN_RXADDR            0x02
#define REG_SETUP_AW             0x03
#define REG_SETUP_RETR           0x04
#define REG_RF_CH                0x05
#define REG_RF_SETUP             0x06
#define REG_STATUS               0x07
#define REG_OBSERVE_TX           0x08
#define REG_RPD                  0x09
#define REG_RX_ADDR_P0           0x0A
#define REG_RX_ADDR_P1           0x0B
#define REG_RX_ADDR_P2           0x0C
#define REG_RX_ADDR_P3           0x0D
#define REG_RX_ADDR_P4           0x0E
#define REG_RX_ADDR_P5           0x0F
#define REG_TX_ADDR              0x10
#define REG_RX_PW_P0             0x11
#define REG_RX_PW_P1             0x12
#define REG_RX_PW_P2             0x13
#define REG_RX_PW_P3             0x14
#define REG_RX_PW_P4             0x15
#define REG_RX_PW_P5             0x16
#define REG_FIFO_STATUS          0x17
#define REG_DYNPD                0x1C
#define REG_FEATURE              0x1D



void RF24_init(uint8_t channel, uint8_t listen);

void RF24_cleanFifo(uint8_t FIFO);
void ConfigReg(uint8_t reg, value); 
void Rreg(uint8_t reg, uint8_t * data,  uint8_t size);
void Wreg(uint8_t reg, uint8_t * data,  uint8_t size);
uint8_t RF24_TX(uint8_t * data);
uint8_t RF24_RX(uint8_t data);
void RF24_SET_TX_TARGET(uint8_t * addr);
void RF24_GET_TX_TARGET(uint8_t * addr);
void RF_RXFLUSH();
void RF24_setRxAddress(uint8_t pipeId, uint8_t* rxAddr);
void RF24_SET_RX_RECIEVE(uint8_t * addr, uint8_t pipe);
void SEND_PACKET(uint8_t * addr
void SET_PAYLOAD(uint8_t * addr, uint8_t * message); 
