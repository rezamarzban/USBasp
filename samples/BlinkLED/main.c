#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB4

int main(void) {

  // Configure LED_PIN (PB4) as output
  DDRB |= (1 << LED_PIN);

  while (1) {
    PORTB |= (1 << LED_PIN);
    _delay_ms(500);
    PORTB &= ~(1 << LED_PIN);
    _delay_ms(500);
  }

  return 0;
}
