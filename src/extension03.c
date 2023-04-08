// Ex E3.0
//
// In this week's tutorial we used some functions from a library
// "qutyio.h" and from the <stdio.h> library to output data via
// the serial interface. This can be a useful tool for debugging
// your programme. To use the serial interface you first need to
// initialise the required hardware by calling "serial_init()";
// this only needs to be done once at the beginning of your
// programme. After this, you can use the function printf() from
// <stdio.h> to output formatted strings via the serial interface.
//
// You will need to use printf() in few different ways in this
// extension exercise:
//
//   printf("foo") - prints the word 'foo' to the serial output.
//   printf("bar") - prints the word 'bar' to the serial output.
//   printf(" ")   - prints a space to the serial output.
//   printf("%02X", x) - prints the 8-bit integer 'x' to the
//   serial output, formatted as two hexadecimal digits.
//   printf("\n")  - prints a new line to the serial output.
//
// Your task is to write C code to do the following:
//
// 1) Include stdio.h and qutyio.h so that you can access the
//    functions required to write to the serial interface.
// 2) Initialise the qutyio serial inteface by calling serial_init().
// 3) Create a variable "state" to store your student number. You
//    should interpret your student number as a decimal number. Use
//    the smallest standard unsigned integer type in which your student
//    number will fit. (you will need to include the stdint header).
//    e.g. the student number 10000012 would represent the number
//    ten million and twelve.
// 4) Iterate through all the numbers from 0 to 255 in sequence.
//    For each number in the sequence perform the following steps:
//    a) Take the bitwise xor of the number with the variable "state",
//       storing the result back into "state".
//    b) Rotate right the bits in "state" at least one time, and until
//       the LSB of "state" is a zero. If there are no cleared bits in
//       "state" do nothing.
//    c) Print the least significant two bytes of "state" to the serial
//       output as the four hexadecimal digits and a space. No prefix is
//       required.
//    d) Inspect the bits 11-4 of "state" (where bit 0 is the LSB). If the
//       most significant nibble of this byte, represented as a hexadecimal
//       digit, matches the second last digit of your student number,
//       represented decimal digit, print the word "foo" to the serial
//       output. If the least significant nibble of this byte,
//       represented as a hexadecimal digit, matches the final digit
//       of your student number, represented decimal digit, print the
//       word "bar" to the serial output. If both match, print "foobar".
//    e) Print a newline character to the serial output.
// 5) Based on step 4 above, your programme should have printed 256
//    lines to the serial output. After completion of step 4 programme
//    execution should proceed to the infinite loop without producing
//    any further output.
//
// Examples:
//   Assume for all examples below the student number is n12345678
//
//   Assume that after step 4b "state" holds the value 0x11223344
//     The programme should print the line: 3344
//
//   Assume that after step 4b "state" holds the value 0x34567728
//     The programme should print the line: 7728 foo
//
//   Assume that after step 4b "state" holds the value 0x11111780
//     The programme should print the line: 1780 foobar

#include <avr/io.h>
#include <stdio.h>
#include <qutyio.h>
#include <stdint.h>

int main(void)
{
    // Write your code for Ex E3.0 below this line.
    // You will also need to add some preprocessor directives;
    // these would typically go at the top of the file.

    // CONSTANTS
    const uint16_t ITERATIONS = 256;
    const uint32_t LEAST_SIGNIFICANT_BYTES_MASK = 0x0000FFFF;
    const uint8_t STUDENT_NUMBER_2ND_LAST = 1;
    const uint8_t STUDENT_NUMBER_LAST = 2;
    const char FOO[4] = "foo";
    const char BAR[4] = "bar";

    serial_init();

    uint32_t state = 10974512;

    for (uint16_t i = 0; i < ITERATIONS; i++){
        // Perform a bitwise exclusive or (XOR) on state 
        // Store result back into state
        state = i ^ state;

        // Rotate the bits of state right at least one time (do) until 
        // the LSB of state is 0 (while). If all bits are set, do nothing 
        do {
            state = ((state >> 1) | (state << 31));
            if (state == 0xFFFFFFFF) { break; } // Check if all bits are set
        } while ((state & 0b1) != 0);

        // Print the two least significant bytes of state to the serial output
        // as a four digit hexadecimal value
        uint16_t result = (state & LEAST_SIGNIFICANT_BYTES_MASK);
        printf("%04X ", result); 

        // Declare variables to hold bits 11 to 4 and then
        // isolate the most and least significant nibbles
        // of this byte.
        uint8_t bits11To4 = ((state >> 4) & 0xff); 
        uint8_t msNibble = bits11To4 >> 4;
        uint8_t lsNibble = bits11To4 & 0xf;

        // Commit yourself to an mental institution and spend the rest of your days
        // trapped within your own mind until a time comes when this makes sense
        // but it's too late for absolution.
        if (msNibble == STUDENT_NUMBER_2ND_LAST && lsNibble == STUDENT_NUMBER_LAST) {
            printf("%s%s", FOO, BAR);
        } else if (msNibble == STUDENT_NUMBER_2ND_LAST) {
            printf("%s", FOO);
        } else if (lsNibble == STUDENT_NUMBER_LAST) {
            printf("%s", BAR);
        }

        // Print a new line for next iteration
        printf("\n");
    }

    // END OF EXTENSION03 EXERCISES //
    // DO NOT EDIT BELOW THIS LINE //

    while (1)
    {
        // Loop forever
    }
}
