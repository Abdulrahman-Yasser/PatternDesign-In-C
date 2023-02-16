
# GPT

This repo will contain GPT(General-purpose Timer) Driver,
all you have to do is changing the GPT_Cfg.h and GPT_Lcfg.c for you own configurations as you will see in the example below

## 🔗 Video how to use it Links
Click here to watch a Demo of the UART Driver, It will be added soon
[![youtube](https://img.shields.io/youtube/views/T1rNExItZcU?style=social)]()


## Screenshots
![Functions API in UART](https://user-images.githubusercontent.com/63866803/214153223-7cb6dadd-87b0-49d5-83e8-e3b709005387.png)
![UART Container](https://user-images.githubusercontent.com/63866803/214155090-dfd6b58d-d447-4393-b1b2-660a43e092fc.png)


## 🛠 Skills
C, Embedded C, arm architecture

## Running Tests

To run tests, just change the following variables with your own configurations in two files <br>
MCAL/UART/Dynamic/inc/UART.Cfg


```bash
#define TIMERS_NUMBERS      11

#define MY_TIMER0_CHANNEL               (Gpt_ChannelType)Gpt_Channel_Normal_0
#define MY_TIMER0_FREQUENCY             (uint32)15       //15us
#define MY_TIMER0_PRESCALING_TYPE       Gpt_Prescale_Hardware
#define MY_TIMER0_WAIT_PERIOD           (Gpt_ValueType)60000
#define MY_TIMER0_MODE                  (Gpt_ModeType)Gpt_Mode_Periodic_A
#define MY_TIMER0_INTERRUPT             ((1 << Gpt_InterruptOverFlow))
#define MY_TIMER0_ISR_CALLBACK          App_Function

#define MY_DEFAULT_CHANNEL              Gpt_Channel_Normal_0
#define MY_DEFAULT_FREQUENCY            0
#define MY_DEFAULT_PRESCALING_TYPE      Gpt_Prescale_NotUsed
#define MY_DEFAULT_WAIT_PERIOD          0
#define MY_DEFAULT_MODE                 Gpt_Mode_NotUsed
#define MY_DEFAULT_INTERRUPT            Gpt_Interrupt_NotUsed
#define MY_DEFAULT_ISR_CALLBACK         Default_Function

extern const Gpt_ConfigType GPT_ConfigPtr_Container[TIMERS_NUMBERS];
```
MCAL/UART/Dynamic/src/UART_Lcfg

```bash
const Gpt_ConfigType GPT_ConfigPtr_Container[TIMERS_NUMBERS] =
{
 {MY_TIMER0_CHANNEL, MY_TIMER0_PRESCALING_TYPE, MY_TIMER0_FREQUENCY, MY_TIMER0_WAIT_PERIOD, MY_TIMER0_MODE, MY_TIMER0_INTERRUPT, MY_TIMER0_ISR_CALLBACK, MY_DEFAULT_ISR_CALLBACK },
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
 {MY_DEFAULT_CHANNEL, MY_DEFAULT_PRESCALING_TYPE, MY_DEFAULT_FREQUENCY, MY_DEFAULT_WAIT_PERIOD, MY_DEFAULT_MODE, MY_DEFAULT_INTERRUPT, MY_DEFAULT_ISR_CALLBACK , MY_DEFAULT_ISR_CALLBACK},
};
```


## API Reference

#### All the functions you can use in timer


| Functions | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `Gpt_Init()` | `void` | `it initialize your TIMER with your configuraions`|
| `Gpt_DisableNotification (channel)` | `void` | `The function Disable all ISRs in a timer Channel` |
| `Gpt_EnableNotification (channel)` | `void` | `The function Enables all the ISRs in a timer Channel`
| `Gpt_StartTimer (channel, value)` | `void` | `The function Start the timer and load it with a specific value`
| `Gpt_StopTimer (channel)` | `void` | `The function Stops the timer and Reload it with zero` |
| `Gpt_GetTimeElapsed (channel)` | `Gpt_ValueType` | `The function Returns the Elapsed time of the timer` |
| `Gpt_GetTimeRemaining (channel)` | `Gpt_ValueType` | `The function Returns the Remaining time of the timer` |
| `Gpt_GetPredefTimerValue (PredefTimer, TimeValuePtr)` | `Gpt_ValueType` | `The function Returns the Elapsed time of the timer` |

#### the only variable you need to change in GPT_Lcfg
| Variables | Type     | Description                       |
| :-------- | :------- | :-------------------------------- |
| `GPT_ConfigPtr_Container[TIMERS_NUMBERS] `      | `Gpt_ConfigType` | `GptChannelId (Channel Number)` |
| | |`PreScalingType (if it was Gpt_Prescale_Software, then the prescaling will be through the software, which means that every time the timer will overflow that variable will decreament once, untill it goes zero, just after that it will generate the overflow function. Otherwise it will be a normal preScaler using the hardware register)` |
| | |`GptChannelTickFrequency (it got the prescale vaue)` |
| | |`GptChannelTickValueMax (it got the load value that the GPTM will not exceed)` |
| | |`ChannelMode (the timer mode whether it will be periodic, oneShot, RTC, EdgeCount or EdgeTime)` |
| | |`Interrupt_Type (that value goes as it is to the IM register to activate the ISR, so please check the DataSheet before filling it)` |
| | |`void (*GptNotificationCallBack_OverFlowEvent) (a Call-back function passed through the initialization, that function will be called when an overflow occurs)` |
| | |`void (*GptNotificationCallBack_Match) (a Call-back function passed through the initialization, that function will be called when a Matching occurs)` |
