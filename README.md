USBasp socket pinouts to an IC:
![image1](USBasp.jpg)

Tested WINDOWS software & Driver: `progisp` software & `Zadig (libusb-win32)` driver

Tested Android app: `ZFlasher AVR` app

To getting `rar` archives password, Run `getpass.ipynb`

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

Microcontrollers can be used as oscillator of ELF, VLF, LF, MF and HF analog and digital radio transmitter simply.
