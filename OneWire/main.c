#include <atmel_start.h>
#include <util/delay.h>

typedef struct {
	volatile uint8_t R_reg;
	volatile uint8_t G_reg;
	volatile uint8_t B_reg;
} LED;

volatile LED LED_Display[1] = {
	{0x00, 0x00, 0xFF}
};

uint32_t convert8to32(uint8_t color);
bool mensagem(uint32_t data);

volatile uint32_t data_R;
volatile uint32_t data_G;
volatile uint32_t data_B;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	SPI_0_init();
	SPI_0_enable();

	
	data_R = convert8to32(LED_Display->R_reg);
	data_G = convert8to32(LED_Display->G_reg);
	data_B = convert8to32(LED_Display->B_reg);
	
	/* Replace with your application code */
	while (1) {
		for (uint8_t i=0; i<=30; i++)
		{
			mensagem(data_R);
			mensagem(data_G);
			mensagem(data_B);
		}
		
		//LED0_toggle_level();
		_delay_us(50);
		
	}
}

uint32_t convert8to32(uint8_t color){
	
	uint32_t data = 0x00000000;
	int8_t i = 7;
	
	while(i>=0){
		if (color & (1 << i)) {
			data |= (uint32_t) 0x00000008 << (i*4);
		}
		else{
			data |= (uint32_t) 0x0000000E << (i*4);
		}
		i--;
	}
	
	return data;
}

bool mensagem(uint32_t data){

	uint8_t info1;
	uint8_t info2;
	uint8_t info3;
	uint8_t info4;
	
	info1= (uint8_t) (0xFF & (data >> 24));
	SPI0.DATA = info1;
	while (SPI_0_status_busy() & SPI_0_status_done());
	
	info2= (uint8_t) (0xFF & (data >> 16));
	SPI0.DATA = info2;
	while (SPI_0_status_busy() & SPI_0_status_done());
	
	info3= (uint8_t) (0xFF & (data >> 8));
	SPI0.DATA = info3;
	while (SPI_0_status_busy() & SPI_0_status_done());
	
	info4= (uint8_t) (0xFF & data);
	SPI0.DATA = info4;
	while (SPI_0_status_busy() & SPI_0_status_done());
	
	return SPI_0_status_done();
}