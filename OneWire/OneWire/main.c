#include <atmel_start.h>

typedef struct {
	volatile uint8_t R_reg;
	volatile uint8_t G_reg;
	volatile uint8_t B_reg;
} LED;

LED LED_Display[1] = {
	{ 0x55, 0x00, 0xFF }
};

uint32_t convert8to32(uint8_t color){
	uint8_t data;
	uint8_t i = 7;
	while(i>=0){
		if (color & (1 << i)) {	
			data |= 0x0E << (i*4+3);
		}
		else{
			data |= 0x08 << (i*4+3);
		}
		i--;
	}
	
	return data;
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	/*############################################################################### onde fica o prototipo*/
	uint32_t data_R;
	uint32_t data_G;
	uint32_t data_B;
	
	data_R = convert8to32(LED_Display->R_reg);
	data_G = convert8to32(LED_Display->G_reg);
	data_B = convert8to32(LED_Display->B_reg);
	
	
	/* Replace with your application code */
	while (1) {
		
		SPI_0_write_block(data_R, 32);
		SPI_0_write_block(data_G, 32);
		SPI_0_write_block(data_B, 32);
	}
}


uint32_t convert8to32(uint8_t color);