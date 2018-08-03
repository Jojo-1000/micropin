# µPin
This C++11 header-only library for AVR microcontrollers is designed to be lightweight and efficient regarding code size and execution speed, but yet bringing you all the features that you need for controlling IO pins.

## Features
* compiletime pin selection (no overhead)
* runtime pin selection (changeable)
* digital in- and output
* PWM
* analog input
* intuitive interface

## Basic usage
### Compiletime pin selection
```c++
#include <Pin.hpp>
// 8 MHz clock speed, required for delay
#define F_CPU 8000000 
#include <util/delay.h>

constexpr MicroPin::StaticDigitalPin<3> pin;

int main()
{
    using namespace MicroPin;
    pin.pinMode(output);

    while(true)
    {
        pin = high;
        delay_ms(500);
        pin = low;
        delay_ms(500);
    }
}
```
### Runtime pin selection
```c++
#include <Pin.hpp>
// 8 MHz clock speed, required for delay
#define F_CPU 8000000
#include <util/delay.h>

MicroPin::DigitalPin pin(3);

int main()
{
    using namespace MicroPin;
    pin.pinMode(output);

    //Some runtime input changes of pin
    pin = DigitalPin(1);

    while(true)
    {
        pin = high;
        delay_ms(500);
        pin = low;
        delay_ms(500);
    }
}
```

## Supported devices
* ATmegaX8 family
  * ATmega48A
  * ATmega48PA
  * ATmega88A
  * ATmega88PA
  * ATmega168A
  * ATmega168PA
  * ATmega328
  * ATmega328P
* ATtinyX5 family
  * ATtiny25
  * ATtiny45
  * ATtiny85
