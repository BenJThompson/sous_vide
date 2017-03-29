/* 
 * File:   main.h
 * Author: thompson
 *
 * Created on February 14, 2017, 10:52 AM
 */

#ifndef MAIN_H
#define	MAIN_H

// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = ECIO_EC   // Oscillator Selection bits (EC oscillator, port function on RA6 (ECIO))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 1         // Brown-out Reset Voltage bits (Setting 2 4.33V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)


// Constants

#define    TRIS_OUTPUT 0
#define    TRIS_INPUT 1

#define     VOLTAGE_ADC_CHANNEL = 0
#define     TEMP_ADC_CHANNEL = 1

// Enums

typedef enum {IDLE, OFF, TURN_ON, ON} phase_state_type;
typedef enum {START, IDLE, EDIT_TEMP, EDIT_HOUR, EDIT_MINUTE, RUN} mode_state_type;


// PORT A
//#define  PORTAbits.RA0
//#define  LATAbits.LA0
#define PHASE_TRIS TRISAbits.TRISA0

//#define  PORTAbits.RA1
//#define LATAbits.LA1
#define TEMP_TRIS TRISAbits.TRISA1

//#define  PORTAbits.RA2
//#define LATAbits.LA2
#define GND_REF_TRIS TRISAbits.TRISA2

//#define  PORTAbits.RA3
//#define LATAbits.LA3
#define VREF_TRIS TRISAbits.TRISA3

//#define  PORTAbits.RA4
#define BUZZER LATAbits.LA4
#define BUZZER_TRIS TRISAbits.TRISA4

#define BTN_UP PORTAbits.RA5
//#define  LATAbits.LA5
#define BTN_UP_TRIS TRISAbits.TRISA5

//#define  PORTAbits.RA6
//#define COMM_SEL LATAbits.LA6
#define TRISA6 TRISAbits.TRISA6

    
// PORT B

//#define PORTBbits.RB0
//#define LATBbits.LB0
#define SDA_TRIS TRISBbits.TRISB0

//#define  PORTBbits.RB1
//#define  LATBbits.LB1
#define SCL_TRIS TRISBbits.TRISB1

//#define  PORTBbits.RB2
#define MOTOR LATBbits.LB2
#define MOTOR_TRIS TRISBbits.TRISB2

//#define  PORTBbits.RB3
#define TRIAC LATBbits.LB3
#define TRIAC_TRIS TRISBbits.TRISB3

//#define  PORTBbits.RB4
//#define  LATBbits.LB4
#define TRISB4 TRISBbits.TRISB4

//#define  PORTBbits.RB5
//#define  LATBbits.LB5
#define TRISB5 TRISBbits.TRISB5

//#define  PORTBbits.RB6
//#define  LATBbits.LB6
#define TRISB6 TRISBbits.TRISB6

//#define  PORTBbits.RB7
//#define  LATBbits.LB7
#define TRISB7 TRISBbits.TRISB7



// PORT C
//#define  PORTCbits.RC0
#define LED_1 LATCbits.LC0
#define LED_1_TRIS TRISCbits.TRISC0

//#define  PORTCbits.RC1
#define LED_2 LATCbits.LC1
#define LED_2_TRIS TRISCbits.TRISC1

//#define PORTCbits.RC2
#define LED_3 LATCbits.LC2
#define LED_3_TRIS TRISCbits.TRISC2

//#define  PORTCbits.RC6
#define LED_E LATCbits.LC6
#define LED_E_TRIS TRISCbits.TRISC6

//#define  PORTCbits.RC7
#define LED_F LATCbits.LC7
#define LED_F_TRIS TRISCbits.TRISC7


// PORT D
#define USB_V PORTDbits.RD0
//#define LATDbits.LD0
#define USB_V_TRIS TRISDbits.TRISD0

//#define  PORTDbits.RD1
#define LED_4 LATDbits.LD1
#define LED_4_TRIS TRISDbits.TRISD1

//#define  PORTDbits.RD2
#define LED_D LATDbits.LD2
#define LED_D_TRIS TRISDbits.TRISD2

//#define  PORTDbits.RD3
#define LED_G LATDbits.LD3
#define LED_G_TRIS TRISDbits.TRISD3

//#define  PORTDbits.RD4
#define LED_B LATDbits.LD4
#define LED_B_TRIS TRISDbits.TRISD4

//#define PORTDbits.RD5
#define LED_A LATDbits.LD5
#define LED_A_TRIS TRISDbits.TRISD5

//#define  PORTDbits.RD6
#define LED_C LATDbits.LD6
#define LED_C_TRIS TRISDbits.TRISD6

//#define  PORTDbits.RD7
#define LED_DP LATDbits.LD7
#define LED_DP_TRIS TRISDbits.TRISD7



// PORT E
#define BTN_DOWN PORTEbits.RE0
//define  LATEbits.LE0
#define BTN_DOWN_TRIS TRISEbits.TRISE0

#define BTN_GO PORTEbits.RE1
//#define  LATEbits.LE1
#define BTN_GO_TRIS TRISEbits.TRISE1

#define BTN_STOP PORTEbits.RE2
//#define  LATEbits.LE2
#define BTN_STOP_TRIS TRISEbits.TRISE2


// Function prototypes

void config_osc(void);
void config_io(void);
void config_uart(void);
void config_adc(void);
void config_timer(void);
void config_int(void);
void init_io(void);