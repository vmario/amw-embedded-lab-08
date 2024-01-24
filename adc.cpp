#include "adc.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

const Adc adc;

void Adc::initialize() const
{
	TCCR1B = _BV(CS11);
	TIMSK1 = _BV(TOIE1);

	ADMUX = _BV(REFS1) | _BV(REFS0);
	ADCSRA = _BV(ADSC) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

	ADCSRB = _BV(ADTS2) | _BV(ADTS1);
}

double Adc::temperature() const
{
	constexpr auto REFERENCE_VOLTAGE{1.1};
	constexpr auto RESOLUTION{1024};
	constexpr auto SCALE{10000};

	uint16_t value = ADCL;
	value += ADCH << 8;

	return REFERENCE_VOLTAGE / RESOLUTION * SCALE * value;
}
