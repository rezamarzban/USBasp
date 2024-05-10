USBasp socket pinouts to an IC:
![image1](USBasp.jpg)

Tested WINDOWS software & Driver: `progisp` software & `Zadig (libusb-win32)` driver

Tested Android app: `ZFlasher AVR` app

To getting `rar` archives password, Run `getpass.ipynb`

#### AVR IC programming guide:

1- Write an `AVR` program in `C` programming language or other programing languages (`Python`, `Assembly`, ...).

2- Compile written `C` language `AVR` program with `avr-gcc`.

3- Build `hex` file with `avr-objcopy` from compiled `C` code.

4- Choose a programmer hardware among `Arduino uno`, `USBasp` and so on, Then Connect programmer pins to `AVR` IC pins according to provided user manuals and datasheets.

5- Install programmer software (`AVRDUDE`, `Arduino IDE`, `progisp`, `Zflasher AVR`, ...) and driver (`Zadiag`, ...) according to your OS. Then launch programmer software.

6- Upload `hex` file to `AVR` IC flash.

#### Build `hex`:

```
avr-gcc -g -Os -mmcu=see_docs -o main.elf main.c
```

```
avr-objcopy -j .text -j .data -O ihex main.elf main.hex
```

`-mmcu` option docs: `https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html`

Sample LED blinking `main.c` code:

```
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
```

#### An idea:

Microcontrollers can be used as oscillator of ELF, VLF, LF, MF and HF analog and digital radio transmitters simply. Here is an example code to generating semi sinewave signal with PWM module at an `AVR` IC:

```
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
```
