#include <xc.h>
#include "avr/io.h"
#define P_LCD PORTC

void LCD_pulso_E ( ) {
	PORTD = PORTD | 0x10 ;// Nivel alto en la terminal E
	PORTD = PORTD & 0xEF ;// Nivel bajo en la terminal E
}

void LCD_write_4 ( uint8_t inst) {
	P_LCD = inst & 0x0F ; // Rs = 0
	LCD_pulso_E ( ) ;
}

void LCD_write_8 (uint8_t inst) {
	uint8_t temp ;
	temp = ( inst & 0xF0) >> 4;
	LCD_write_4 (temp) ; // Primero el nibble alto
	temp = inst & 0x0F ;
	LCD_write_4 ( temp ) ; // Después el nibble bajo
	_delay_us ( 4 0 ) ;
}

void LCD_clear( ) {
	LCD_write_8 (0x01) ;
	_delay_ms( 2 ) ;
}

void LCD_write_data (uint8_t data_8) {
	uint8_t temp ;
	temp = ( data_8 & 0xF0 ) >> 4 ; // PARTE ALTA
	P_LCD = temp | 0x20 ; // RS = 1
	LCD_pulso_E ( ) ;
	temp = data_8 & 0x0F ; // PARTE BAJA
	P_LCD = temp | 0x20 ; // RS = 1
	LCD_pulso_E( ) ;
	_delay_us(40) ;
}

void LCD_reset ( ) {
	_delay_ms(15) ;
	LCD_write_4 (0x03 ) ; // Configura la función del display
	
	_delay_ms(4.1) ;
	LCD_write_4 (0x03 ) ; // Configura la función del display
						  // La interfaz aun es de 8 b i t s
	_delay_us(100) ;
	LCD_write_4 (0x03) ; // Configura la función del display
	_delay_us(40) ; // La interfaz aun es de 8 bits
	LCD_write_4 (0x02 ) ; // Configura la función del display
	_delay_us(40) ; // Define l a i n t e r f a z de 4 b i t s
	LCD_write_8 (0x28 ) ; // Configura la función del Display
						// Dos líneas y 5x7 puntos
	LCD_write_8 (0x0C) ; // Encendido del Display
	LCD clear ( ) ; // Limpieza del Display
	LCD_write_8 (0x06) ; // Ajuste de entrada de datos
						// Autoincremento del contador
						// y sin desplazamiento
}

void LCD_cursor( uint8_t pos ) {
	uint8_t col ;
	col = pos & 0x0F ;
	if (( pos & 0xF0 ) == 0) {
		col = col | 0x80 ; // DB7 = 1
		LCD_write_8 (col) ;
	}
	else {
		col = col | 0xC0 ; // DB7 = 1 y dirección = 0x40
		LCD_write_8 (col) ;
	}
}		

void LCD_write_cad( char cad [ ] , uint8_t tam) {
	uint8_t i ;
	LCD clear ( ) ;
	for ( i=0; i<tam ; i++) {
		LCD_write_data(uint8_t) cad [ i ] ) ;
		if ( i==15)
		LCD_cursor(0X10) ;
	}

}				
