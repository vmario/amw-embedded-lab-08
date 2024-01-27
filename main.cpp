#include "shifter.hpp"
#include "display.hpp"
#include "timer.hpp"

#include <avr/interrupt.h>
#include <avr/sleep.h>

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
}

/**
 * Inicjalizuje GPIO (włącza przerwanie od przycisku).
 */
void gpioInitialize()
{
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
