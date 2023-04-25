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

bool mensagem(uint32_t data){

	uint8_t info1,info2,info3,info4;
	
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
			mensagem(LED_Display[i][j]);
		}
	}

}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	SPI_0_init();
	SPI_0_enable();
	
	random_matrix();
	
	/* Replace with your application code */
	while (1) {
		sending_matrix();
		_delay_us(50);
	}
		
}