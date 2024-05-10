#include <avr/io.h>
#include <util/delay.h>

#define PWM_PIN PB0 // PWM pin

// Semi-sine wave lookup table
const uint8_t semi_sine_wave[] = {128, 162, 194, 220, 239, 250, 250, 239, 220, 194, 162, 128, 93, 61, 35, 16, 5, 5, 16, 35, 61, 93};
const uint8_t steps = sizeof(semi_sine_wave);

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
        for (uint8_t i = 0; i < steps; i++) {
            OCR0A = semi_sine_wave[i];
            _delay_ms(1.0/steps); // Delay 1/22 ms for 1 kHz frequency
        }
    }

    return 0;
}
