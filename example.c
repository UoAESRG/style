// In embedded, use explicit integer sizes
#include <stdint.h>
// That way you know what you are using and where it will overflow
// Includes also come first in any C file

// Headers exist as prototypes to let the compiler know that it WILL be able to do something later on
// So that when you call this function
void function(uint8_t data1[], uint8_t length, uint8_t data2[]);

// It knows it should find this implementation somewhere else
void function(uint8_t data1[], uint8_t length, uint8_t data2[])
{
    // Do things
}
// Prototypes for STATIC functions should be the next thing to appear in the C file

// Code should be separated into modules, following the separation of concerns model
// That is, any module should have one well defined use
// ie. ADC interface, ARRAY functions
void ADC_init();
void ADC_getData();
void ADC_switchChannel();

void ARRAY_multiply();
void ARRAY_get_max();

void UART_put_char(char c);

// Modules should be split header and implementation (.c) files

// Functions in a module are typically named with a leading module name, either caps or lower case
// Followed by the function you would like to execute (either camelCaps or with_underscores, be consistent!)
// ie.
void ADC_init();
uint16_t ADC_read();
void pthread_do_something();

// Check out the linux coding standard for an idea of how things work.

// Functions should be named descriptively
// To be an adequate abstraction (ie. an indirection that you don't need to follow to understand), you need
// to make the operation clear from just the name, (which makes code much more readable).
// Don't be afraid to be verbose.
uint16_t ADC_calculateVoltageFromADCReading(uint16_t reading);
// will always beat:

// Calculate the voltage from the ADC reading
void convertVoltage();

// And that will make your project much more readible

// Any global variables should be declared here, but really
// Global variables are only justifiable for ISRs
// If you need a variable across modules, you can "prototype" it in the header
extern uint8_t my_shared_variable;
// Then declare it in the C file
uint8_t my_shared_variable;

// Magic numbers are bad practice
uint16_t this[42];  // What does 42 even mean?!

#define THAT_SIZE   32
uint16_t that[THAT_SIZE];   //Makes it much more obvious what is going on and why

// Next come the implementations

int main(int argc, char **argv)
{
    // Variable sizes are super important in embedded platforms
    // Remember the bounds of each size, and beware of the implications on your calculations
    //  - division with uint8_t size ints is almost never what you want
    //  - Many processors do not support floating point
    // 	- atomicity of operations is important if using interrupts
    // You can always use python to test what integer maths will do.
    // ie.
    uint8_t a;
    uint8_t b;

    a = b / 127;    // Can (probably) only ever result in 0 or 1
    // Watch out for overflows!

    // Fixed point multiplication allows you to perform more accurate divisions without
    // the stress of floating point operations
    // If it doesn't matter to you the scale, try mV or kV instead of V


    // Enumerations make options far more clear than if(someBoolean) for multiple things
    // This is placed here for convenience, and should be declared at the top of the file above the static definitions
    enum CaptureStateE {
        captureCurrent,
        captureVoltage
    };

    int state = captureCurrent;

    // then
    switch (state) {
    case captureVoltage:
        break;
    case captureCurrent:
        break;
    }
    // becomes far more elegant


    // Reasonable names make program flow much more sensible
    uint16_t adc_val;
    uint16_t voltage;
    unsigned char char_out;

    adc_val = ADC_read();
    voltage = ADC_calculateVoltageFromADCReading(adc_val);
    // Do the other things
    char_out = 'a';
    UART_put_char(char_out);

    return 0;
}

// Should be in the ADC module, perhaps ADC.c
uint16_t ADC_read() {
	return 4;	//!< IEEE vetted random number
}

// Should also be in the ADC module
uint16_t ADC_calculateVoltageFromADCReading(uint16_t reading) {
	return reading * 16;
}

void UART_put_char(char c) {
	// Do the things with the characters
}

// Yes, it compiles.
