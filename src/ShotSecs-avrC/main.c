//Counter for espresso machine shot time.
//Fuses (L H E): E3 DA FD

#define F_CPU	4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"


#define SegOne   0x20 //Activates digit 1
#define SegTwo   0x10 //activates digit 2

void main() {
    int debug=0; //set to 0 to disable debug msgs
	if (debug) USART_init(); // Initialize USART
	char seg_code[]={0x3f,0x6,0x5b,0x4f,0x66,0x6d,0x7c,0x7,0x7f,0x67}; //array of hex representations of decimal digits
    char seg_codeDP[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfc,0x87,0xff,0xe7}; //array of hex representations of decimal digits, plus decimal point active
    int cnt,i;
	char String[4];
	cnt=0;
    
    
    /* Configure the ports as output */
    DDRB = 0xff; // Data lines
    DDRC = 0xff; // Control signal PORTC4-PORTC5
    DDRD = 0x00; // Input for motor
    PORTD = (1 << 3); //Enable pull-up


	void display(int counter) //Display the counter on the 7-segment display 
	{
		int time = 0;
		int seg1,seg2 = 0;
		if (counter<100) time = 10; else time=102; //time to keep tenths and wholes in display
		
		for (i = 0; i < time; i++) //loop to keep same digit displayed for a while
		{
			PORTC = SegOne; //segment one
			if (counter<100) 
			{
				seg1 = counter / 10;
				PORTB = seg_codeDP[seg1];
			}
			else
			{
				seg1 = (counter-100) / 10;
				PORTB = seg_code[seg1]; 
			}	
			_delay_ms(10);

			PORTC = SegTwo; //segment two
			if (counter<100) 
			{
				seg2 = counter % 10;
				PORTB = seg_code[seg2];
			}
			else
			{
				seg2 = (counter-100) % 10;
				PORTB = seg_code[seg2]; 
			}	
			_delay_ms(10);
		}
		if (debug) {
					USART_putstring(", Seg1: ");
					itoa(seg1, String, 10);
					USART_putstring(String);
					USART_putstring(", Seg2: ");
					itoa(seg2, String, 10);
					USART_putstring(String);
					USART_putstring("\n");
				}
	}
    
    
    
    
    while (1)
    {
		while(!(PIND & (1<<PD3)))
		{
    		for (cnt = 0; cnt <= 99; cnt++) // loop 0-999 tenth seconds
        	{
        		if (debug) {
					USART_putstring("cnt: ");
					itoa(cnt, String, 10);
					USART_putstring(String);
					USART_putstring("\n");    	// Pass the string to the USART_putstring function and sends it over the serial
				}
				if (PIND & (1<<PD3)) break;
        		display(cnt);
        		//if (PIND & (1<<PD3)) break;
        	}
			if (PIND & (1<<PD3)) break;
    		for (cnt = 110; cnt <= 199; cnt++) // loop 0-999 tenth seconds
        	{
        		if (debug) {
					USART_putstring("cnt: ");
					itoa(cnt, String, 10);
					USART_putstring(String);
					USART_putstring("\n");    	// Pass the string to the USART_putstring function and sends it over the serial
				}
				if (PIND & (1<<PD3)) break;
        		display(cnt);
        		if (PIND & (1<<PD3)) break;
        	}

		}    
		display(cnt);
}
}