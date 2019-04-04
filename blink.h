#define LED2_OFF() PORTDbits.RD1 = 0
#define LED2_ON() PORTDbits.RD1 = 1
#define TIMER1_ENABLE() T1CONbits.ON = 1
#define TIMER1_DISABLE() T1CONbits.ON = 0
#define TIMER1_SOURCE_INTERNAL() T1CONbits.TCS = 0 //TCS: Timer Clock Source Select bit
    //define la fuente a usar como reloj el reloj interno del procesador
#define TIMER1_PRESCALE_1_1() T1CONbits.TCKPS = 0x00 // Timer Input Clock Prescale Select bits
    //Los bits TCKPS del registro indican cuánto hay que pre-escalar el temporizador(relacion 1:1, en este caso)
 
//PORTD i can or CLR = 0, SET = 1, INV = from 0 to 1, PORTDINV
// Better to say 
// Put the TRISD as an in

