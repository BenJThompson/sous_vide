/*
 * File:   main.c
 * Author: thompson
 *
 * Created on February 13, 2017, 4:46 PM
 */

/*
 * TODO
 * 
 * - WDT
 * - Phase State Machine
 * - UI State Machine
 * - Display Update
 * - Temperature Update
 * - Phase Interrupt - Determine TAD times and checking frequency
 * - Dynamic phase max-voltage level and period ranging to determine phase
 * -  
 * 
 */




#include <xc.h>
#include <stdbool.h>
#include "main.h"

volatile unsigned int tick = 0;
volatile phase_state_type phase_state = IDLE;
volatile double voltage_adc_value;
volatile bool voltage_adc_updated;
volatile double temp_adc_value;

void main(void) {
    double mains_max_v;
    double mains_period;
    
    config_osc();
    config_adc();
    config_io();
    //config_uart();
    config_timer();
    config_int();
    init_io();

    get_mains_info(&mains_max_v, &mains_period);
    
}

void interrupt low_priority low_isr(void) {
    tick += 1;
    INTCONbits.TMR0IF = 0;
}

void interrupt high_priority isr(void) {    
    // Trigger the temperature ADC after the peak of the of phase has been found
    //      and there is some time before we need to check it again.
    //      Make an averaged temperature
    //      Ensure that the temperature variable is volatile
    
    // TODO Add interrupt for turning off the triac trigger
    if (PIR1bits.TMR1IF){
        update_phase_state();
        PIR1bits.TMR1IF = 0;
    }
    if(PIR1bits.ADIF){
        update_adc_value();
        PIR1bits.ADIF = 0;
    }
}

void update_phase_state(void){
    // TODO
}

void update_adc_value(void){
    if (ADCON0bits.CHS0 == VOLTAGE_ADC_CHANNEL){
        voltage_adc_value = (double)(ADRESH << 8 + ADRESL) / 0x400;
        voltage_adc_updated = true;
    } else {
        // TODO temp_adc_value = ?
    }
}

void config_int() {
    
    /* Timer 0 - Tick timer */
    INTCON2bits.TMR0IP = 0; // 0 = low priority
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    /* Timer 1 - Process timer */
    IPR1bits.TMR1IP = 1; // 1 = high priority
    PIR1bits.TMR1IF = 0; 
    PIE1bits.TMR1IE = 1;
    /* ADC */ 
    IPR1bits.ADIP = 1; 
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;    
            
    INTCONbits.GIEH = 1; // 1 = Enables all high-priority interrupts
    INTCONbits.GIEL = 1; // 1 = Enables all low-priority peripheral interrupts (if GIE/GIEH = 1)
}

void config_timer() {
    /* Tick timer */
    // f = ((1Mhz / 4) / 250) = 1 kHz
    TMR0L = 0xFF - 250 - 2;
    INTCONbits.TMR0IF = 0; // 0 = TMR0 register did not overflow
    // T0CON<7> 1 = starts Timer0
    // T0CON<6> 1 = Timer0 is configured as a 8-bit timer/counter
    // T0CON<5> 0 = Internal instruction cycle clock (CLKO)
    // T0CON<4> N/A
    // T0CON<3> 1 = Timer0 prescaler is not assigned.
    // T0CON<2:0>  N/A
    T0CON = 0b11001000;
    
    /* Process timer */
    // (1e-6s*4) * 65535 = 0.26s; typical mains period = 0.02s to 0.016s
    // T1CON<7> 1 = Enables register read/write of Timer1 in one 16-bit operation
    // T1CON<6> 0 = Device clock is derived from another source
    // T1CON<5:4> 00 = 1:1 Prescale value
    // T1CON<3> 0 = Timer1 oscillator is shut off
    // T1CON<2> This bit is ignored.
    // T1CON<1> 0 = Internal clock (F OSC /4)
    // T1CON<0> 0 = disables Timer1
    T1CON = 0b10000000;
    
    /* Mains Period Timer */
    // T3CON<7> 1 = Enables register read/write of Timer3 in one 16-bit operation
    // T3CON<6> 1 = Timer3 is the capture/compare clock source for both CCP modules
    // T3CON<5:4> 00 = 1:1 Prescale value
    // T3CON<3> This bit is ignored.
    // T3CON<2> This bit is ignored.
    // T3CON<1> 0 = Internal clock (F OSC /4)
    // T3CON<0> 0 = Stops Timer3
    T3CON = 0b11000000;
}

void config_osc(void) {
    // Should be called before all other config functions

    // Most of osc configuration occurs in PRAGMAS in header file

    // Config for INTIO
    /* Internal Oscillator used as Microcontroller Clock Source, EC
    Oscillator used as USB Clock Source, Digital I/O on RA6*/

    // OSCCON<7> (IDLEN) 1 = Device enters Idle mode on SLEEP instruction
    // OSCCON<6:4> (IRCF2:IRCF0) 100 = 1 MHz
    // OSCCON<3:2> Read only 
    // OSCCON<1:0> (SCS1:SCS0) 1x = Internal oscillator
    OSCCON = 0b11000011;

    // 31 kHz device clock derived directly from INTRC internal oscillator
    // Center frequency. Oscillator module is running at the calibrated frequency.
    OSCTUNE = 0b00000000;
}

void config_io(void) {
    
    // PORT A
    PHASE_TRIS = TRIS_INPUT;
    TEMP_TRIS = TRIS_INPUT;
    GND_REF_TRIS = TRIS_INPUT;
    VREF_TRIS = TRIS_INPUT;
    BUZZER_TRIS = TRIS_OUTPUT;
    BTN_UP_TRIS = TRIS_INPUT;
    TRISA6 = TRIS_INPUT;

    // PORT B
    SDA_TRIS = TRIS_INPUT;
    SCL_TRIS = TRIS_INPUT;
    MOTOR_TRIS = TRIS_OUTPUT;
    TRIAC_TRIS = TRIS_OUTPUT;
    TRISB4 = TRIS_INPUT;
    TRISB5 = TRIS_INPUT;
    TRISB6 = TRIS_INPUT;
    TRISB7 = TRIS_INPUT;
    
    // PORT C
    LED_1_TRIS = TRIS_OUTPUT;
    LED_2_TRIS = TRIS_OUTPUT;
    LED_3_TRIS = TRIS_OUTPUT;
    LED_E_TRIS = TRIS_OUTPUT;
    LED_F_TRIS = TRIS_OUTPUT;

    // PORT D
    USB_V_TRIS = TRIS_INPUT;
    LED_4_TRIS = TRIS_OUTPUT;
    LED_D_TRIS = TRIS_OUTPUT;
    LED_G_TRIS = TRIS_OUTPUT;
    LED_B_TRIS = TRIS_OUTPUT;
    LED_A_TRIS = TRIS_OUTPUT;
    LED_C_TRIS = TRIS_OUTPUT;
    LED_DP_TRIS = TRIS_OUTPUT;

    // PORT E
    BTN_DOWN_TRIS = TRIS_INPUT;
    BTN_GO_TRIS = TRIS_INPUT;
    BTN_STOP_TRIS = TRIS_INPUT;
}

void init_io(void) {
    
    // PORT A

    // PORT B
    MOTOR = 0;
    TRIAC = 0;
    
    // PORT C
    LED_1 = 0;
    LED_2 = 0;
    LED_3 = 0;
    LED_E = 0;
    LED_F = 0;

    // PORT D
    LED_4 = 0;
    LED_D = 0;
    LED_G = 0;
    LED_B = 0;
    LED_A = 0;
    LED_C = 0;
    LED_DP = 0;

    // PORT E
}

void config_adc(void){
    
    // ADCON0<7:6> Unimplemented
    // ADCON0<5:2> 0000 = Channel 0 (AN0)
    // ADCON0<1> When ADON = 1, 0 = A/D Idle
    // ADCON0<0> 1 = A/D converter module is enabled
    ADCON0 = 0b00000001;
    
    // ADCON0<7:6> Unimplemented
    // ADCON0<5> 1 = V REF - (AN2)
    // ADCON0<4> 1 = V REF + (AN3)
    // ADCON0<3:0> 1101 = AN0 through AN3 analog; the remainder digital
    ADCON1 = 0b00111101;
    
    // ADCON0<7> 1 = Right justified
    // ADCON0<6> Unimplemented
    // ADCON0<5:3> 001 = 2 T_AD --> 2 * 2us = 4us (min = 1.1us)
    // ADCON0<2:0> 000 = F OSC/2 --> T_AD = (1/(1 Mhz/2)) = 2us
    ADCON2 = 0b10001000;
}

void get_mains_info(double *mains_max_v, double *mains_period){
    double voltage_sum = 0.0;
    double voltage_max = 0.0;
    double voltage_max_approx = 0.0;
    double inst_voltage;
    unsigned long voltage_sample_count = 0;
    unsigned int halfperiod_count = 0;
    unsigned int halfperiod_state = 0;
    
    // Find approx peak value (approx due to noise)
    // @4us/sample will sample a min of 5 periods, actual will be more
    while(voltage_sample_count < 400000){ 
        inst_voltage = get_voltage_adc_blocking();
        if (inst_voltage > voltage_max_approx){
            voltage_max_approx = inst_voltage;
        }
    }        
    
    // Wait for zero crossing
    bool zero_crossed = false;
    while(zero_crossed == false){
        inst_voltage = get_voltage_adc_blocking();
        if (inst_voltage < (voltage_max_approx * 0.05)){
            zero_crossed = true;
        }
    }
    
    // Find half period
    while(halfperiod_count < 100){
        while (halfperiod_state == 0){
            inst_voltage = get_voltage_adc_blocking();
            if (voltage_adc_value < (voltage_max_approx * 0.05)){
                zero_crossed = true;
            }
        }
    }
        
    // Find peak and avg values
    // @4us/sample will sample a min of 10 periods
    while(voltage_sample_count < 800000){ 
        if (start_adc(VOLTAGE_ADC_CHANNEL)){
            while(voltage_adc_updated == false){}
            voltage_sum += voltage_adc_value;
            if (voltage_adc_value > voltage_max){
                voltage_max = voltage_adc_value;
            }
            voltage_sample_count += 1;
            voltage_adc_updated = false;
        }
        mains_average = voltage_sum / voltage; 
         
   }
}

double get_voltage_adc_blocking(void){
    bool success = false;
    while (success == false){
        success = start_adc(VOLTAGE_ADC_CHANNEL);
    }
    while(voltage_adc_updated == false){}
    voltage_adc_updated = false;
    return voltage_adc_value;
}

bool start_adc(int channel){
    bool success = false;
    if (0 == ADCON0bits.GO_DONE){
        ADCON0bits.CHS0 = channel;
        ADCON0bits.GO_DONE = 1;
        success = true;
    }
    return success;
}