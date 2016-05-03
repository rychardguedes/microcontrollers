# Assignment 1

## What to do:
A counter from 0 to 99 using two 7 segment display and an Arduino. There must be a button to select if it is counting up or down. Also, it should take 1 second between each change in the display.

## How:
There are two `int` variables (`uni` and `ten`), which will control each display. Obviously, when the least significant counts 10, it is decreased to 0 and 1 is incremented to the most significant display. Showing the numbers in both displays using just 8 out ports is possible through a multiplex, controlled by pins 2 and 3.  
