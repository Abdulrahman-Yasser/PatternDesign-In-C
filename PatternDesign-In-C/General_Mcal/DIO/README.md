
# DIO

This repo will contain DIO(Digital Input/Output) Driver,
all you have to do is changing the PORT_Cfg.h and PORT_Lcfg.c for you own configurations as you will see in the example below<br>
That Driver just manipulate the pins on the board, it do not initialize anything<br>
If you want to write, toggle or read a specific pin/port, you will need that driver

## 🔗 Video how to use it Links
Click here to watch a Demo of the DIO Driver<br>
a video will be added soon ...
[![youtube](https://img.shields.io/youtube/views/T1rNExItZcU?style=social)]()


## Screenshots
as you will see there is no inititialization function because the pins are already initialized in PORT.h, all you want to do with the pins is to change the direction, level and maybe the output current. But you will not need anything else "i did not need anything other than that"<br>

![Functions API in DIO](https://user-images.githubusercontent.com/63866803/213947392-0c3c6330-36cc-4aa9-9bf5-d1d5418654dd.png)


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
```bash
int z;
z = Dio_ReadChannel(DIO_Channel0_B);
Dio_WriteChannel(DIO_Channel1_B, DIO_HIGH);
```


## API Reference

#### All the functions you can use in DIO


| Functions | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `Dio_ReadChannel(ChannelId)` | `uint8` | `it reads the pin's digital value`|
| `Dio_WriteChannel (ChannelId, Level)` | `void` | `it writes the pin's digital value` |
| `Dio_ReadPort (PortId)` | `uint8` | `it reads the whole port's digital value`
| `Dio_WritePort (PortId, Level)` | `void` | `it writes the whole port's digital value`
| `Dio_FlipChannel (ChannelId)` | `void` | `it Flips the Pins output (it High make it LOW, and the other way)` |

#### the only variable you need to change in PORT_Lcfg
There is no Complicated types or containers here, because it doesn't initialize the pins.<br>It just manipulate the pins and read it's values
