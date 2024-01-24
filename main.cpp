#include "shifter.hpp"
#include "display.hpp"
#include "timer.hpp"
#include "adc.hpp"

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

/**
 * Obsługa przerwania pomiaru ADC.
 */
ISR(ADC_vect)
{
	//display.print(adc.temperature(), 2);
}

/**
 * Obsługa przerwania komparatora Timer/Counter0.
 */
ISR(TIMER0_OVF_vect)
{
	static uint16_t counter;
	display.print(counter++);
	display.refresh();
}

/**
 * Obsługa przerwania przepełnienia Timer/Counter1.
 */
ISR(TIMER1_OVF_vect)
{
	//PINB = _BV(5);
}

void shutdown()
{
	shifter.shift(0xff);
	shifter.shift(0x00);
	shifter.latch();
	SMCR = _BV(SM1) | _BV(SE);
	sleep_cpu();
}

ISR(PCINT1_vect)
{
}

void gpioInitialize()
{
	//DDRB |= _BV(5);
	
	PCICR |= _BV(PCIE1);
	PCMSK1 |= _BV(PCINT9);
}

void mainLoop()
{
	_delay_ms(2000);
	shutdown();
}

/**
 * Funkcja główna.
 */
int main()
{
	shifter.initialize();
	timer.initialize();
	//adc.initialize();
	gpioInitialize();

	sei();

	while (true) {
		mainLoop();
	}
}
