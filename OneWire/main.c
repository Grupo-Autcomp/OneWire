#include <atmel_start.h>
#include <util/delay.h>
#define N 30

typedef struct {
	uint32_t R_reg;
	uint32_t G_reg;
	uint32_t B_reg;
} LED;

volatile LED LED_Display[N];
volatile uint32_t RED[N];
volatile uint32_t GRE[N];
volatile uint32_t BLU[N];
uint32_t convert8to32(uint8_t color);
void mensagem(uint32_t red, uint32_t gre, uint32_t blu);
void fill_matrix(LED matrix[N]);


int main(void)
{		
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	SPI_0_init();
	SPI_0_enable();

	fill_matrix(LED_Display);
	
	for (uint8_t i=0; i<30; i++)
	{
		RED[i] = convert8to32(LED_Display[i].R_reg);
		GRE[i] = convert8to32(LED_Display[i].G_reg);
		BLU[i] = convert8to32(LED_Display[i].B_reg);
	}
	
	/* Replace with your application code */
	while (1) {
		for (uint8_t i=0; i<N; i++)
		{	
			mensagem(RED[i], BLU[i], GRE[i]);
		}
		
		//LED0_toggle_level();
		_delay_us(100);
		
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

void mensagem(uint32_t red, uint32_t gre, uint32_t blu){

	uint8_t info_r1;
	uint8_t info_r2;
	uint8_t info_r3;
	uint8_t info_r4;
	
	uint8_t info_g1;
	uint8_t info_g2;
	uint8_t info_g3;
	uint8_t info_g4;
	
	uint8_t info_b1;
	uint8_t info_b2;
	uint8_t info_b3;
	uint8_t info_b4;
	
	info_r1 = (uint8_t) (0xFF & (red >> 24));	
	info_r2 = (uint8_t) (0xFF & (red >> 16));	
	info_r3= (uint8_t) (0xFF & (red >> 8));	
	info_r4= (uint8_t) (0xFF & red);
	
	info_g1 = (uint8_t) (0xFF & (gre >> 24));
	info_g2 = (uint8_t) (0xFF & (gre >> 16));
	info_g3= (uint8_t) (0xFF & (gre >> 8));
	info_g4= (uint8_t) (0xFF & gre);
	
	info_b1 = (uint8_t) (0xFF & (blu >> 24));
	info_b2 = (uint8_t) (0xFF & (blu >> 16));
	info_b3= (uint8_t) (0xFF & (blu >> 8));
	info_b4= (uint8_t) (0xFF & blu);
	
	SPI0.DATA = info_r1;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	SPI0.DATA = info_r2;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	SPI0.DATA = info_r3;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	SPI0.DATA = info_r4;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	
	SPI0.DATA = info_g1;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	SPI0.DATA = info_g2;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	SPI0.DATA = info_g3;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	SPI0.DATA = info_g4;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	
	SPI0.DATA = info_b1;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	SPI0.DATA = info_b2;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	SPI0.DATA = info_b3;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	SPI0.DATA = info_b4;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
}

void fill_matrix(LED matrix[N]){
	uint8_t R;
	uint8_t G;
	uint8_t B;
	
	for(uint8_t i=0; i<N; i++){
		R = rand()%0xFF;
		G = rand()%0xFF;
		B = rand()%0xFF;
		
		matrix[i].R_reg = convert8to32(R);
		matrix[i].G_reg = convert8to32(G);
		matrix[i].B_reg = convert8to32(B);
	}
}
