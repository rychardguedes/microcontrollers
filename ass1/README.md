# Assignment 1

### What to do:
A counter from 0 to 99 using two 7 segment display and an Arduino. There must be a button to select if it is counting up or down. Also, it should take 1 second between each change in the display.

### How:
There are two `int` variables (`uni` and `ten`), which will control the number to be displayed in each display. Showing the numbers in both displays using just 8 out ports is possible through a multiplex, controlled by pins 2 and 3. The state of pin 4 determines whether the counting is up or down.

### Imporant Notes

- `millis()` should be used instead of `delay()` to avoid pauses during the execution of the program. However, I still use a delay of 5 milliseconds for multiplexing the numbers. As this delay is so short, it won't affect the result.
- A power terminal is used in transistors' collector due to problems on simulation without it.
