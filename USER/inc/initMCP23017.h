#ifndef INITMCP23017_H_
#define INITMCP23017_H_

/* ============================================ INCLUDES ===================================================== */

#include "main.h"

/* ============================================ DEFINES ===================================================== */

#define MCP23017_ADDR	0x27

#define MCP23017_PIN_SET		0
#define MCP23017_PIN_RESET	1

#define MCP23017_PIN0	0x01
#define MCP23017_PIN1	0x02
#define MCP23017_PIN2	0x04
#define MCP23017_PIN3	0x08
#define MCP23017_PIN4	0x10
#define MCP23017_PIN5	0x20
#define MCP23017_PIN6	0x40
#define MCP23017_PIN7	0x80

// ONLY IOCON.BANK = 0 !!!

/***************************************************
IODIR – I/O DIRECTION REGISTER
IO7:IO0: These bits control the direction of data I/O <7:0>
1 = Pin is configured as an input.
0 = Pin is configured as an output.
****************************************************/
#define MCP23017_REG_ADDR_IODIRA	0x00
#define MCP23017_REG_ADDR_IODIRB	0x01

#define MCP23017_REG_IODIR_ALL		0xFF
#define MCP23017_REG_IODIR_00			0x01
#define MCP23017_REG_IODIR_01			0x02
#define MCP23017_REG_IODIR_02			0x04
#define MCP23017_REG_IODIR_03			0x08
#define MCP23017_REG_IODIR_04			0x10
#define MCP23017_REG_IODIR_05			0x20
#define MCP23017_REG_IODIR_06			0x40
#define MCP23017_REG_IODIR_07			0x80


/***************************************************
IPOL – INPUT POLARITY PORT REGISTER (ADDR 0x02)
IP7:IP0: These bits control the polarity inversion of the input pins <7:0>
1 = GPIO register bit will reflect the opposite logic state of the input pin.
0 = GPIO register bit will reflect the same logic state of the input pin.
****************************************************/
#define MCP23017_REG_ADDR_IOPOLA	0x02
#define MCP23017_REG_ADDR_IOPOLB 	0x03

#define MCP23017_REG_IOPOL_ALL		0xFF
#define MCP23017_REG_IOPOL_00			0x01
#define MCP23017_REG_IOPOL_01			0x02
#define MCP23017_REG_IOPOL_02			0x04
#define MCP23017_REG_IOPOL_03			0x08
#define MCP23017_REG_IOPOL_04			0x10
#define MCP23017_REG_IOPOL_05			0x20
#define MCP23017_REG_IOPOL_06			0x40
#define MCP23017_REG_IOPOL_07			0x80


/***************************************************
GPINTEN – INTERRUPT-ON-CHANGE PINS (ADDR 0x02)
GPINT7:GPINT0: General purpose I/O interrupt-on-change bits <7:0>
1 = Enable GPIO input pin for interrupt-on-change event.
0 = Disable GPIO input pin for interrupt-on-change event.
****************************************************/
#define MCP23017_REG_ADDR_GPINTENA		0x04
#define MCP23017_REG_ADDR_GPINTENB		0x05

#define MCP23017_REG_GPINTEN_ALL			0xFF
#define MCP23017_REG_GPINTEN_GPINT0		0x01
#define MCP23017_REG_GPINTEN_GPINT1		0x02
#define MCP23017_REG_GPINTEN_GPINT2		0x04
#define MCP23017_REG_GPINTEN_GPINT3		0x08
#define MCP23017_REG_GPINTEN_GPINT4		0x10
#define MCP23017_REG_GPINTEN_GPINT5		0x20
#define MCP23017_REG_GPINTEN_GPINT6		0x40
#define MCP23017_REG_GPINTEN_GPINT7		0x80

/***************************************************
DEFVAL – DEFAULT VALUE REGISTER (ADDR 0x03)
DEF7:DEF0: These bits set the compare value for pins configured 
for interrupt-on-change from defaults <7:0>. Refer to INTCON.
If the associated pin level is the opposite from the register bit, an interrupt occurs.
****************************************************/
#define MCP23017_REG_DEFVALA 				0x06
#define MCP23017_REG_DEFVALB 				0x07

#define MCP23017_REG_DEFVAL_ALL			0xFF
#define MCP23017_REG_DEFVAL_DEF0		0x01
#define MCP23017_REG_DEFVAL_DEF1		0x02
#define MCP23017_REG_DEFVAL_DEF2		0x04
#define MCP23017_REG_DEFVAL_DEF3		0x08
#define MCP23017_REG_DEFVAL_DEF4		0x10
#define MCP23017_REG_DEFVAL_DEF5		0x20
#define MCP23017_REG_DEFVAL_DEF6		0x40
#define MCP23017_REG_DEFVAL_DEF7		0x80



/***************************************************
INTCON – INTERRUPT-ON-CHANGE CONTROL REGISTER
IOC7:IOC0: These bits control how the associated pin 
value is compared for interrupt-on-change <7:0>
1 = Controls how the associated pin value is compared for interrupt-on-change.
0 = Pin value is compared against the previous pin value.
****************************************************/
#define MCP23017_REG_INTCONA 				0x08
#define MCP23017_REG_INTCONB 				0x09

#define MCP23017_REG_INTCON_ALL			0xFF
#define MCP23017_REG_INTCON_IOC0		0x01
#define MCP23017_REG_INTCON_IOC1		0x02
#define MCP23017_REG_INTCON_IOC2		0x04
#define MCP23017_REG_INTCON_IOC3		0x08
#define MCP23017_REG_INTCON_IOC4		0x10
#define MCP23017_REG_INTCON_IOC5		0x20
#define MCP23017_REG_INTCON_IOC6		0x40
#define MCP23017_REG_INTCON_IOC7		0x80



/***************************************************
IOCON – I/O EXPANDER CONFIGURATION REGISTER (ADDR 0x05)

bit 7 BANK: Controls how the registers are addressed
1 = The registers associated with each port are separated into different banks
0 = The registers are in the same bank (addresses are sequential)

bit 6 MIRROR: INT Pins Mirror bit
1 = The INT pins are internally connected
0 = The INT pins are not connected. INTA is associated with PortA and INTB is associated with PortB

bit 5 SEQOP: Sequential Operation mode bit.
1 = Sequential operation disabled, address pointer does not increment.
0 = Sequential operation enabled, address pointer increments.

bit 4 DISSLW: Slew Rate control bit for SDA output.
1 = Slew rate disabled.
0 = Slew rate enabled.

bit 3 HAEN: Hardware Address Enable bit (MCP23S17 only).
Address pins are always enabled on MCP23017.
1 = Enables the MCP23S17 address pins.
0 = Disables the MCP23S17 address pins.

bit 2 ODR: This bit configures the INT pin as an open-drain output.
1 = Open-drain output (overrides the INTPOL bit).
0 = Active driver output (INTPOL bit sets the polarity).

bit 1 INTPOL: This bit sets the polarity of the INT output pin.
1 = Active-high.
0 = Active-low.

bit 0 Unimplemented: Read as ‘0’.
****************************************************/
#define MCP23017_REG_ADDR_IOCONA 		0x0A
#define MCP23017_REG_ADDR_IOCONB 		0x0B

#define MCP23017_REG_IOCON_00				0x01
#define MCP23017_REG_IOCON_INTPOL		0x02
#define MCP23017_REG_IOCON_ODR			0x04
#define MCP23017_REG_IOCON_HAEN			0x08
#define MCP23017_REG_IOCON_DISSLW		0x10
#define MCP23017_REG_IOCON_SEQOP		0x20
#define MCP23017_REG_IOCON_MIRROR		0x40
#define MCP23017_REG_IOCON_BANK			0x80


/***************************************************
GPPU – GPIO PULL-UP RESISTOR REGISTER
PU7:PU0: These bits control the weak pull-up resistors on each pin 
(when configured as an input) <7:0>.
1 = Pull-up enabled.
0 = Pull-up disabled.
****************************************************/
#define MCP23017_REG_ADDR_GPPUA 0x0C
#define MCP23017_REG_ADDR_GPPUB 0x0D

#define MCP23017_REG_GPPU_ALL		0xFF
#define MCP23017_REG_GPPU_PU0		0x01
#define MCP23017_REG_GPPU_PU1		0x02
#define MCP23017_REG_GPPU_PU2		0x04
#define MCP23017_REG_GPPU_PU3		0x08
#define MCP23017_REG_GPPU_PU4		0x10
#define MCP23017_REG_GPPU_PU5		0x20
#define MCP23017_REG_GPPU_PU6		0x40
#define MCP23017_REG_GPPU_PU7		0x80

/***************************************************
INTF – INTERRUPT FLAG REGISTER
INT7:INT0: These bits reflect the interrupt condition on the port. 
Will reflect the change only if interrupts are enabled (GPINTEN) <7:0>.
1 = Pin caused interrupt.
0 = Interrupt not pending.
****************************************************/
#define MCP23017_REG_ADDR_INTFA 	0x0E
#define MCP23017_REG_ADDR_INTFB 	0x0F

#define MCP23017_REG_INTF_ALL			0xFF
#define MCP23017_REG_INTF_INT0		0x01
#define MCP23017_REG_INTF_INT1		0x02
#define MCP23017_REG_INTF_INT2		0x04
#define MCP23017_REG_INTF_INT3		0x08
#define MCP23017_REG_INTF_INT4		0x10
#define MCP23017_REG_INTF_INT5		0x20
#define MCP23017_REG_INTF_INT6		0x40
#define MCP23017_REG_INTF_INT7		0x80



/***************************************************
INTCAP – INTERRUPT CAPTURED VALUE FOR PORT REGISTER
ICP7:ICP0: These bits reflect the logic level on the port pins 
at the time of interrupt due to pin change <7:0>
1 = Logic-high.
0 = Logic-low.
****************************************************/
#define MCP23017_REG_ADDR_INTCAPA 	0x10
#define MCP23017_REG_ADDR_INTCAPB 	0x11

#define MCP23017_REG_INTCAP_ALL			0xFF
#define MCP23017_REG_INTCAP_ICP0		0x01
#define MCP23017_REG_INTCAP_ICP1		0x02
#define MCP23017_REG_INTCAP_ICP2		0x04
#define MCP23017_REG_INTCAP_ICP3		0x08
#define MCP23017_REG_INTCAP_ICP4		0x10
#define MCP23017_REG_INTCAP_ICP5		0x20
#define MCP23017_REG_INTCAP_ICP6		0x40
#define MCP23017_REG_INTCAP_ICP7		0x80



/***************************************************
GPIO – GENERAL PURPOSE I/O PORT REGISTER
GP7:GP0: These bits reflect the logic level on the pins <7:0>
1 = Logic-high.
0 = Logic-low.
****************************************************/
#define MCP23017_REG_ADDR_GPIOA 0x12
#define MCP23017_REG_ADDR_GPIOB 0x13

#define MCP23017_REG_GPIO_ALL		0xFF
#define MCP23017_REG_GPIO_GP0		0x01
#define MCP23017_REG_GPIO_GP1		0x02
#define MCP23017_REG_GPIO_GP2		0x04
#define MCP23017_REG_GPIO_GP3		0x08
#define MCP23017_REG_GPIO_GP4		0x10
#define MCP23017_REG_GPIO_GP5		0x20
#define MCP23017_REG_GPIO_GP6		0x40
#define MCP23017_REG_GPIO_GP7		0x80


/***************************************************
OLAT – OUTPUT LATCH REGISTER 0
OL7:OL0: These bits reflect the logic level on the output latch <7:0>
1 = Logic-high.
0 = Logic-low.
****************************************************/
#define MCP23017_REG_ADDR_OLATA 0x14
#define MCP23017_REG_ADDR_OLATB 0x15

#define MCP23017_REG_OLAT_ALL		0xFF
#define MCP23017_REG_OLAT_OL0		0x01
#define MCP23017_REG_OLAT_OL1		0x02
#define MCP23017_REG_OLAT_OL2		0x04
#define MCP23017_REG_OLAT_OL3		0x08
#define MCP23017_REG_OLAT_OL4		0x10
#define MCP23017_REG_OLAT_OL5		0x20
#define MCP23017_REG_OLAT_OL6		0x40
#define MCP23017_REG_OLAT_OL7		0x80


/* ============================================ FUCTIONS ==================================================== */

void MCP23017_WriteByte(uint8_t _mcp23017_addr, uint8_t _reg_address, uint8_t _data);
uint8_t MCP23017_ReadByte(uint8_t _mcp23017_addr, uint8_t _reg_address);
void MCP23017_Init(void);
uint8_t MCP23017_ReadPin(uint8_t _mcp23017_addr, uint8_t _port, uint8_t _pin);
void MCP23017_WritePin(uint8_t _mcp23017_addr, uint8_t _port, uint8_t _pin, uint8_t _state);

#endif /* INITMCP23017_H_ */
