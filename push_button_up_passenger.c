#include "push_button_up_passenger.h"


#define GPIO_PORTD_PRIORITY_MASK      0x1FFFFFFF
#define GPIO_PORTD_PRIORITY_BITS_POS  29
#define GPIO_PORTD_INTERRUPT_PRIORITY 5


void push_button_up_passenger_init(void)
{
		SYSCTL_RCGCGPIO_R|= 0x08;
	while((SYSCTL_PRGPIO_R & 0x08)!= 0x08);
	GPIO_PORTD_LOCK_R = 0x4C4F434B;
	GPIO_PORTD_AMSEL_R &= ~(1<<2);
	GPIO_PORTD_DIR_R &=~ (1<<2);
	GPIO_PORTD_DEN_R |= (1<<2);
	GPIO_PORTD_PUR_R   |= (1<<2);
	GPIO_PORTD_IS_R    &= ~(1<<2);      /* PD2 detect edges */
  GPIO_PORTD_IBE_R   &= ~(1<<2);      /* PD2 will detect a certain edge */
  GPIO_PORTD_IEV_R   &= ~(1<<2);      /* PD2 will detect a falling edge */
  GPIO_PORTD_ICR_R   |= (1<<2);       /* Clear Trigger flag for PD2 (Interupt Flag) */
  GPIO_PORTD_IM_R    |= (1<<2);       /* Enable Interrupt on PD2 pin */
  /* Set GPIO PORTF priotiy as 2 by set Bit number 29, 30 and 31c with value 2 */
  NVIC_PRI0_R = (NVIC_PRI0_R & GPIO_PORTD_PRIORITY_MASK) | (GPIO_PORTD_INTERRUPT_PRIORITY<<GPIO_PORTD_PRIORITY_BITS_POS); 
  NVIC_EN0_R         |= 0x00000008;   /* Enable NVIC Interrupt for GPIO PORTD by set bit number 3 in EN0 Register */
	
}


boolean push_button_up_passenger_pressed(void)
{
	return !(GPIO_PORTD_DATA_R & 0x04);
	
}

