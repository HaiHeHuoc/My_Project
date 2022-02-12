#include <main.h>

void main()
{
   setup_adc_ports(sAN0, VSS_VREF);
   setup_adc(ADC_CLOCK_DIV_16);
   set_adc_channel(0);

   setup_timer_2(T2_DIV_BY_16,255,1);  //100 us overflow, 100 us interrupt

   setup_ccp1(CCP_PWM);
   
   int Val;
   
   while(TRUE)
   {
      Val=read_adc();
      set_pwm1_duty(Val);
      delay_ms(100);
      
   
   //TODO: User Code
   }

}
