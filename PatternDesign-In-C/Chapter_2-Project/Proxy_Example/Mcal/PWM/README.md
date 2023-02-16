
# PWM

This repo will contain PWM(Pulse-Width modulator) Driver,
all you have to do is changing the PWM_Cfg.h and PWM_Lcfg.c for you own configurations as you will see in the example below

## 🔗 Video how to use it Links
Click here to watch a Demo of the PWM Driver
[![youtube](https://img.shields.io/youtube/views/T1rNExItZcU?style=social)](https://youtu.be/-FTmAn_6DzU)


## Screenshots

![Functions API in PWM](https://user-images.githubusercontent.com/63866803/213922537-31e59ced-098f-4b7d-b2f0-585d7f6fb117.png)

![PWM Container](https://user-images.githubusercontent.com/63866803/213921669-1b8f3aa9-4edd-4aa7-a9a2-65bb3be93f42.png)


## 🛠 Skills
C, Embedded C, arm architecture

## Running Tests

To run tests, just change the following variables with your own configurations in two files <br>
MCAL/PWM/Dynamic/inc/PWM.Cfg


```bash
#define PWM_CONFIGURED_NUMBER 1
```
MCAL/PWM/Dynamic/src/PWM.Lcfg

```bash
  const PWM_ConfigType PWM_Container[PWM_CONFIGURED_NUMBER] = {
     {PWM_NUM_0_1, 0, 65534,
      {PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing},
      {PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing, PWM_action_Do_Nothing},
      0, 0, PWM_CONTMODE_DOWN, 55703, 29490}
};
```


## API Reference

#### All the functions you can use in PWM


| Functions | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `pwm_init()` | `void` | `it initialize your PWM with your configuraions`|
| `pwm_update_comparator_a (channel, value)` | `uint8` | `it updates your compare A register for the channel with the value` |
| `pwm_update_comparator_b (channel, value)` | `uint8` | `it updates your compare B register for the channel with the value`
| `pwm_update_comparator_a_percentage (channel, value <= 100)` | `uint8` | `it updates your compare A register for the channel using a built-in method to update it with the percentage with respect to the load, high_threshold and low_threshold values`
| `pwm_update_comparator_b_percentage (channel, value <= 100)` | `uint8` | `it updates your compare A register for the channel using a built-in method to update it with the percentage with respect to the load, high_threshold and low_threshold values` |
| `pwm_update_generation_a (channel, Event, Action)` | `uint8` | `it update the generation Action of a specific Event in a specific Channel Pin_A(0, 2, 4, 6)` |
| `pwm_update_generation_b (channel, Event, Action)` | `uint8` | `it update the generation Action of a specific Event in a specific Channel Pin_A(1, 3, 5, 7)` |
| `PWM_UpdateThresholds (channel, high_threshold, low_threshold)` | `uint8` | `it updates the Channels software threshold, (compare registers will be in range low_threshold : high_threshold)` |
| `pwm_AutomaticDutyCycle (channel, DutyCycle, Pin_A_or_B)` | `uint8` | `it will update your PWM and change it's compare register, event Generation Action and it's counting mode to generate a simple duty cycle PWM` |
| `pwm_update_load (channel, value)` | `uint8` | `it update the load register of the chanel with the value` |
| `pwm_change_mode (channel, Count_Mode)` | `uint8` | `it will change you count mode in the pwm ` |
| `pwm_disable (channel, pins)` | `uint8` | `it will disable the whole PWM channel, not just a pin ` |
| `pwm_stop (channel, pins)` | `uint8` | `it will disable just the chosen pin` |
| `pwm_enable (channel, pins)` | `uint8` | `it will activate the chosen pin to generate the pwm signals` |

#### the only variable you need to change in PWM_Lcfg
| Variables | Type     | Description                       |
| :-------- | :------- | :-------------------------------- |
| `PWM_Container[ PWM_CONFIGURED_NUMBER] `      | `PWM_ConfigType` | `pwm_block (Channel Number)` |
| | |`pwmdiv (the PWM will be divided using that variable (if you don't want to use it make it 0))` |
| | |`load_value (the initial value in load register)` |
| | |`Generates_A (the initial Actions that will be generated in each event pwm(0, 2, 4, 6))` |
| | |`Generates_B (the initial Actions that will be generated in each event pwm(1, 3, 5, 7))` |
| | |`compare_a_value (the initial value in compare A register)` |
| | |`compare_b_value (the initial value in compare B register)` |
| | |`count_mode (whether the PWM will count Up/Down or just Down)` |
| | |`high_threshold (the compare registers will not exceed that value (if you don't want to use it make it 0))` |
| | |`low_threshold (the compare registers will not be lower than that value (if you don't want to use it make it 0))` |

