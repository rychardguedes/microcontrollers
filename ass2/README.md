# Assignment 1

### What to do:
Design a project which uses five 7 segments display and a MAX7219 integrated circtuit to show a number written in a terminal connected to an Arduino.

The program should read a number of 5 characters at max in the virtual terminal and show it on the 7 seg displays. Leftmost 0 must not be displayed.

### How:
There are two `int` variables (`uni` and `ten`), which will control the number to be displayed in each display. Showing the numbers in both displays using just 8 out ports is possible through a multiplex, controlled by pins 2 and 3. The state of pins 14 (A0) and 15 (A1) determines whether the counting is up or down.

### Imporant Notes

- `millis()` should be used instead of `delay()` to avoid pauses during the execution of the program.
- A power terminal is used in transistors' collector due to problems on simulation without it.
- Buttons changes the programs execution only on the rising edge.
- There's a virtual terminal to check when the buttons are pressed.
