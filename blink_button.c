/**
 * 1. button_setup():cofg GPIO como entrada haciendo uso macros [COMO EN EL EJEMPLO DEL LED]
 * 2. Localizar el pin al que está conectado el boton de la placa, y el puerto  *[pin 46]*
 * 3. polling para leer el flag del interruptor asociado(IFS0bits.INT0IF) ¿  ?
 * 4. Poner #includes y #defines en blink.h *OK!*
 */
#include <xc.h>
#include "blink.h"

void delay_ms_setup() { //TEMPORIZADOR
    //Configure Timer1 for 1us count with 8 MHz clock for simulator
    //Configure Timer1 for 1ms count with 8 MHz clock for loading

    // T1CON to control multiplexers of the TIMER1 BLOCK DIAGRAM
    TIMER1_DISABLE();     // TIMER1 OFF
    TIMER1_SOURCE_INTERNAL(); // Configure clock as PBCLK (Peripheral Bus Clock) 
    TIMER1_PRESCALE_1_1(); // Prescaler 1:1

    //PR1 = 7999; 
    PR1 = 7999; // 32 bits register (16 available) to compare with TMR1    
}
void delay_ms (int ms){
    //Use Timer1 interrupt flag
    TMR1 = 0; //??
    TIMER1_ENABLE();
    
    while(ms--){
        IFS0bits.T1IF = 0;        //Desactiva el flag T1IF
        while(!IFS0bits.T1IF){    //Si el flag no se ha activado
            _nop();                     //No hace nada
        }
    }
    TIMER1_DISABLE();
}  

void led_setup() {
    // Configure PORT registers' for LED2
    TRISDbits.TRISD1 = 0;   //configura un pin como salida
}

void button_setup(){    //User button with name BUT, connected to PIC32MX440F256H pin 46 
    TRISDbits.TRISD0 = 1;   //configura el pin como entrada
}

int main() {
    delay_ms_setup();
    led_setup();
    button_setup();
    while(1){
    while (IFS0bits.INT0IF){  //Condicion de pulsar el interruptor
        LED2_ON();
        delay_ms(300);
        LED2_OFF();
        delay_ms(300);
        
        LED2_ON();
        delay_ms(300);    
        LED2_OFF();
        delay_ms(300);
        
        LED2_ON();
        delay_ms(300);
        LED2_OFF();
        delay_ms(300);
    }
    }
    return 0;
}