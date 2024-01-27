#include "shifter.hpp"
#include "display.hpp"
#include "timer.hpp"

#include <avr/interrupt.h>
#include <avr/sleep.h>

#if 1
#include <util/delay.h>
#endif

/**
 * Obsługa przerwania komparatora Timer/Counter0.
 *
 * Odświeża wyświetlacz i inkrementuje licznik.
 */
ISR(TIMER0_OVF_vect)
{
	static uint16_t counter;
	display.print(counter++);
	display.refresh();
}

/**
 * Przełącza mikrokontroler w stan uśpienia.
 */
void shutdown()
{
#if 1
#if 1
	_delay_ms(2000);
	shifter.shift(0xff);
	shifter.shift(0x00);
	shifter.latch();
#endif
	SMCR = _BV(SM1) | _BV(SE);
	sleep_cpu();
#endif
}

#if 1
ISR(PCINT1_vect)
{
}
#endif

/**
 * Inicjalizuje GPIO (włącza przerwanie od przycisku).
 */
void gpioInitialize()
{
#if 1
	PCICR |= _BV(PCIE1);
	PCMSK1 |= _BV(PCINT9);
#endif
}

/**
 * Funkcja główna.
 */
int main()
{
	shifter.initialize();
	timer.initialize();
	gpioInitialize();

	sei();

	while (true) {
		shutdown();
	}
}
