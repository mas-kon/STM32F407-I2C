#include "initMCP23017.h"

void MCP23017_WriteByte(uint8_t _mcp23017_addr, uint8_t _reg_address, uint8_t _data){
	
		I2C1->CR1 |= I2C_CR1_START;								// Формируем Start.
		
		while (!(I2C1->SR1 & I2C_SR1_SB)){};     	// Обрабатываем EV5   
		(void) I2C1->SR1;
			
		I2C1->DR = (_mcp23017_addr << 1);					// Передаем адрес slave			
		while (!(I2C1->SR1 & I2C_SR1_ADDR)){};		// Обрабатываем EV6
		(void) I2C1->SR1;
		(void) I2C1->SR2;
		
		I2C1->DR = _reg_address;									// Передаем адрес регистра		
		while (!(I2C1->SR1 & I2C_SR1_TXE)){};			// Ждем освобождения буфера
		
		I2C1->DR = _data;													// Передаем данные для ячейки памяти		
		while (!(I2C1->SR1 & I2C_SR1_BTF)){};			//  Ждем окончания передачи
			
		I2C1->CR1 |= I2C_CR1_STOP;								// Формируем Stop
}

uint8_t MCP23017_ReadByte(uint8_t _mcp23017_addr, uint8_t _reg_address){
	
	uint8_t data;
	uint8_t _mcp23017_opcode_w = 0;
	uint8_t _mcp23017_opcode_r = 0;

	_mcp23017_opcode_w = (_mcp23017_addr << 1) ;
	_mcp23017_opcode_r = (_mcp23017_addr << 1) | 0x1 ;
	
		I2C1->CR1 |= I2C_CR1_START;								// Формируем Start.
		while (!(I2C1->SR1 & I2C_SR1_SB)){};     	// Ждем окончания старта
		(void) I2C1->SR1;													// Обрабатываем EV5   
			
		I2C1->DR = _mcp23017_opcode_w;						// Передаем адрес slave			
		while (!(I2C1->SR1 & I2C_SR1_ADDR)){};		// Ждем обработки адреса
		(void) I2C1->SR1;													// Обрабатываем EV6
		(void) I2C1->SR2;													// Обрабатываем EV6

		I2C1->DR = _reg_address;									// Передаем адрес регистра
		while (!(I2C1->SR1 & I2C_SR1_BTF)){};			// Ждем освобождения буфера

		I2C1->CR1 |= I2C_CR1_START;								// Формируем Restart.
		while (!(I2C1->SR1 & I2C_SR1_SB)){};     	// Ждем окончания старта
		(void) I2C1->SR1;													// Обрабатываем EV5   
			
		I2C1->DR = _mcp23017_opcode_r; 						// Инициируем чтение	
		while (!(I2C1->SR1 & I2C_SR1_ADDR)){};		// Ждем обработки адреса
		(void) I2C1->SR1;													// Обрабатываем EV6
		(void) I2C1->SR2;													// Обрабатываем EV6
		while (!(I2C1->SR1 & I2C_SR1_RXNE)){};
			
		data = I2C1->DR;													// Вычитываем данные из буфера			
			
		I2C1->CR1 |= I2C_CR1_STOP;								// Формируем Stop

		return data;
}

void MCP23017_Init(void){
	MCP23017_WriteByte(MCP23017_ADDR, MCP23017_REG_ADDR_IODIRA, 0x0);		// Выход
	MCP23017_WriteByte(MCP23017_ADDR, MCP23017_REG_ADDR_IODIRB, 0xFF);	// Вход
	MCP23017_WriteByte(MCP23017_ADDR, MCP23017_REG_ADDR_GPIOA, 0xFD);
}

uint8_t MCP23017_ReadPin(uint8_t _mcp23017_addr, uint8_t _port, uint8_t _pin){
	 return ((MCP23017_ReadByte( _mcp23017_addr, _port) & _pin) == 0) ? 0 : 1;
}

void MCP23017_WritePin(uint8_t _mcp23017_addr, uint8_t _port, uint8_t _pin, uint8_t _state){
		uint8_t Port = 0;
		if (_state == SET) Port = MCP23017_ReadByte( _mcp23017_addr, _port) | _pin;
		else Port = MCP23017_ReadByte( _mcp23017_addr, _port) & ~_pin;
		MCP23017_WriteByte( _mcp23017_addr, _port, Port);
}

