#include <atmel_start.h>
#include <stdlib.h.>

//LEMBRAR DE ORDEM BGR

uint32_t LED_Display [30][3];


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

void random_matrix(){
	//Esse codigo cria uma matrix aleatoria e ja converte para 32 bits
	//Ele é void pois está alterando a variavel global
	for (uint8_t i =0; i<=0x30;i++){
		for(uint8_t j=0;j<=3;j++){
			LED_Display[i][j]=rand() % 0xFF;
			LED_Display[i][j]=convert8to32(LED_Display[i][j]);
		}
	}
	
}

void sending_matrix(){
	//Este codigo envia a matrix que está declarada como global
	for (uint8_t i = 0; i<=30;i++){
		for (uint8_t j=0; j<=3;j++){
			SPI_0_write_block(LED_Display[i][j],32);
		}
	}

}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	/*############################################################################### onde fica o prototipo*/
	
	random_matrix();
	
	/* Replace with your application code */
	while (1) {
		sending_matrix();
	}
		
}