
# Pattern 1 : Polling Pattern

The Polling Pattern is the simplest way to check for new data or signals from the hardware. Polling can be periodic or opportunistic; periodic polling uses a timer to indicate when the hardware should be sampled whereas opportunistic polling is done when it is convenient for the system, such as between major system functions or at some point in a repeated execution cycle. Opportunistic polling is, by definition, less regular but has less impact on the timeliness of other activities in which the system may be engaged.

## Project Description
I've Used 4 classes. FCTimer, FireCircuitSensor, FireDisplay and FCPeriodicPoller. for sure FC means Fire Circuit.<br>
FCTimer can start and stop the timer, and install the Polling Function that will be called in the periodic timer interrupt.<br>
FireDisplay is nothing but a LED, just to show us a specific reaction over the changing.<br>
FireCircuitSensor is an array of the Sensors that we have in the circuit. It can be increased easly.<br>
FCPeriodicPoller which contains the Poll function along with a handlers for all the last classes.<br>
The project just POLL two analog senosrs.<br>
each sensor has a threshold, the poll gets it's state (whether it's over or below it's threshold) and return false or true.<br>
After getting the state, it make an action on a LED.<br>
The polling happens periodically using a Timer ISR.<br>

## video : 
[running the code](https://youtu.be/goLU79OLUzw)<br>

## UML : 
replace BC with FC <br>
Breathing with Fire
![image](https://user-images.githubusercontent.com/63866803/236702240-b46c9aef-c8f0-42f8-a822-fc7d002ced5e.png)


## 🛠 Skills
C, Embedded C, arm architecture

