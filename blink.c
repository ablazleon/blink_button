/* INLCUDES */
#include <xc.h>

/* DEFINES-MACROS*/
#define TOGGLE_LED2() PORTDINV = 0x0002
#define LED2_OFF() PORTDbits.RD1 = 0
#define LED2_ON() PORTDbits.RD1 = 1
#define TIMER1_ENABLE() T1CONbits.ON = 1
#define TIMER1_DISABLE() T1CONbits.ON = 0
#define TIMER1_SOURCE_INTERNAL() T1CONbits.TCS = 0 //TCS: Timer Clock Source Select bit
#define TIMER1_PRESCALE_1_1() T1CONbits.TCKPS = 0x00 // Timer Input Clock Prescale Select bits
//para button_setup()
#define BUT_OFF() PORTDbits.RD0 = 0
#define BUT_ON() PORTDbits.RD0 = 1

/* FUNCTIONS */

/*
 * delay_ms_setup()
 *  * @info: For simulation, divide and truncate PR1 by 1000
 */
vvoid delay_ms_setup() { //TEMPORIZADOR
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

int button(){
    //use flag: IFS0bits.INT0IF
    IFS0bits.INT0IF = 1;    //Activa el flag INTOIF
    if(IFS0bits.INT0IF){    //Si el flag está activado
        return 1;               //Significa que se ha pulsado el button
    }
    return -1;               //No se ha pulsado el button
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
    
    while (button() == 1){       //Condicion de pulsar el interruptor
        delay_ms(300);
        TOGGLE_LED2();
        delay_ms(300);
        TOGGLE_LED2(); 
        delay_ms(300);
        TOGGLE_LED2();
    }
    return 0;
}
