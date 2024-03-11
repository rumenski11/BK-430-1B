#include <msp430x14x.h>  

long adcValue;

void Init_ADC()   
{   
    P6SEL |= BIT1;                                // port 6 Selection bit 1 (p6.1)
    ADC12CTL0 = ADC12ON+SHT0_8+MSC;             // ADC12 Control 0 = Enable + Multiple SampleConversion   
    ADC12CTL1 = SHP+CONSEQ_1;                   // ADC12 Sample/Hold Pulse Mode + conversion mode
       
    ADC12MCTL0 = INCH_1;                        //ADC12 Memory Control 0 = ADC12 Input Channel Select Bit 1

    ADC12IE = BIT7;                             // Interrupt Enable = bit7
    ADC12CTL0 |= ENC;                           //ADC12 Control 0 Enable Conversion
}   


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 //Stop watchdog timer
  
  Init_ADC();
  
  P5DIR |=0XFF; 
  P5OUT |=0XFF;
  
  while (1)   
    {          
        ADC12CTL0 |= ADC12SC;               //Start conversion
        adcValue = ADC12MEM0;
        
        if(adcValue >= 0X800)
        {
          P5OUT=0XF7;
        }else
        { 
          P5OUT=0XFE;
        }
    }
}
//end