#include <avr/io.h>
#include <util/delay.h>

#define PWM_PIN PB0 // PWM pin

int main() {
    // Set PWM pin as output
    DDRB |= (1 << PWM_PIN);

    // Fast PWM mode
    TCCR0A |= (1 << WGM01) | (1 << WGM00);

    // Non-Inverting PWM
    TCCR0A |= (1 << COM0A1);

    // No prescaler
    TCCR0B |= (1 << CS00);

    while(1) {
        // Generate semi-sine wave with a period of 1 ms (1 kHz frequency)
        for (uint8_t i = 0; i < sizeof(semi_sine_wave); i++) {
            OCR0A = semi_sine_wave[i];
            _delay_ms(1); // Delay 1 ms for 1 kHz frequency
        }
    }

    return 0;
}
