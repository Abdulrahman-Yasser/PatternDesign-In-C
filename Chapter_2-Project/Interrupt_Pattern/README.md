
# Pattern 1 : Interrupt Pattern

The Interrupt Pattern is a way of structuring the system to respond appropriately to incoming events. It does require some processor- and compiler-specific services but most embedded compilers, and even some operating systems provide services for just this purpose

## Project Description
The project is nothing but a button and a led. A button got two functions, one should run in a push and the other should run on a release. For that reason i've used Both-Edges flag interrupt.<br>
When the button is pushed, the LED will be HIGH.<br>
When the button is released, the LED will be LOW.<br>
and that's it !!!.<br>
But i've used a ( COOL ) structure just to turn the LED on, i don't know why tf am i soing that. Maybe there is a hidden message (cry for help !!!) in between those lines of codes.<br>

## video : 
[running the code](https://youtu.be/goLU79OLUzw)<br>

ImagePlaceHolder 
i've used the on-Board button (PORTF-0) and the on-board red LED (PORTF-1)



## 🛠 Skills
C, Embedded C, arm architecture

