
# PORT

This repo will contain PORT Driver.<br>
That driver is responsible of initializing all the hardware pins in the board for it's desired function.<br>
all you have to do is changing the PORT_Cfg.h and PORT_Lcfg.c for you own configurations as you will see in the example below<br>

## 🔗 Video how to use it Links
Click here to watch a Demo of the PORT Driver
A video will be added soon
[![youtube](https://img.shields.io/youtube/views/T1rNExItZcU?style=social)]()


## Screenshots
![Functions API in PORT](https://user-images.githubusercontent.com/63866803/213946488-f6be8bfa-8807-4408-b5ed-d7cd633a3cd6.png)

![PORT Container](https://user-images.githubusercontent.com/63866803/213946308-f6d79388-6d19-42c6-8509-105ebcb7ca82.png)

## 🛠 Skills
C, Embedded C, arm architecture

## Running Tests

To run tests, just change the following variables with your own configurations in two files <br>
General_Mcal/PORT/Dynamic/inc/PORT.Cfg


```bash
#define configured_pins 2
```
General_Mcal/PORT/Dynamic/src/PORT.Lcfg

```bash
const Port_ConfigType ConfigPtr[configured_pins] =
{
  {Port_Pin_B0, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_DIO, Port_PinInternal_HW, Port_PinOutputCurrent_2ma},
  {Port_Pin_B1, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_DIO, Port_PinInternal_OpenDrain, Port_PinOutputCurrent_2ma},
  {Port_Pin_B4, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_M0PWMn, Port_PinInternal_HW, Port_PinOutputCurrent_2ma},  // SCL
  {Port_Pin_B5, Port_PinLevel_HIGH, Port_PinDir_OUT, Port_PinMode_M0PWMn, Port_PinInternal_OpenDrain, Port_PinOutputCurrent_2ma}  // SDA
};
```


## API Reference

#### All the functions you can use in PORT


| Functions | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `Port_Init()` | `void` | `it initialize your Pins with your configuraions, all the pins must be configured here even if it's used later in the program`|

#### the only variable you need to change in PORT_Lcfg
| Variables | Type     | Description                       |
| :-------- | :------- | :-------------------------------- |
| `ConfigPtr[configured_pins] `      | `Port_ConfigType` | `PinNum (Pin Number)` |
| | |`PinInitialLevel (The initial Pin's Digital level in the beginning of the program (HIGH/LOW))` |
| | |`PinInitialDirection (The initial Pin's Direction in the beginning of the program (OUTPUT/INPUT))` |
| | |`PinMode (The initial mode the pin will be in (the value will be written in PCTL register for it's alternative function))` |
| | |`PinInternalAttach (the initial pin's internal PullUp/PullDown register or open drain)` |
| | |`PinCurrent (the initial pin's current value that the pin will generate (2ma, 4ma or 8ma))` |


