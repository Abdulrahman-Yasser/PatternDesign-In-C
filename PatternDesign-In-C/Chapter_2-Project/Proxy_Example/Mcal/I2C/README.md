
# I2C

This repo will contain I2C(Inter-Integrated Circuit) Driver,
all you have to do is changing the I2C_Cfg.h and I2C_Lcfg.c for you own configurations as you will see in the example below

## 🔗 Video how to use it Links
Click here to watch a Demo of the I2C Driver, It will be added soon
[![youtube](https://img.shields.io/youtube/views/T1rNExItZcU?style=social)]()


## Screenshots



## 🛠 Skills
C, Embedded C, arm architecture

## Running Tests

To run tests, just change the following variables with your own configurations in two files <br>
MCAL/I2C/Dynamic/inc/I2C.Cfg


```bash
#define I2C_CONFIGURED_NUMBER 1
```
MCAL/I2C/Dynamic/src/I2C.Lcfg

```bash
const I2C_ConfigType I2C_Container[I2C_CONFIGURED_NUMBER] = {
    {I2C_NUM_1, I2C_ModeMaster, I2cSpeed_SM_100Kbps, I2C_GlitchSuppression_OFF, I2C_LoopBack_OFF,
     {I2C_MasterISR_None, I2C_MasterISR_None, I2C_MasterISR_None},
     {I2C_SlaveISR_None, I2C_SlaveISR_None, I2C_SlaveISR_None}, 0x00, 0x00, 0x7B, 0xF1
    }
};
```


## API Reference

#### All the functions you can use in I2C


| Functions | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `I2C_init()` | `void` | `it initialize your I2C with your configuraions`|
| `I2C_MasterPoke_to_transmit (channel, value, Slave_memory_Address, Bytes_Cnt)` | `uint8` | `It Start the transmit a Bytes_Cnt via I2C to Slave's Address from the I2C's Queue` |
| `I2C_MasterPoke_to_receive (channel, value, Slave_memory_Address, Bytes_Cnt)` | `uint8` | `It Start receiving a Bytes_Cnt via I2C From Slave's Address from the I2C's Queue` |
| `I2C_Pop_the_Received ( my_I2C , * data )` | `uint8` | `It reads the data that have been received`
| `I2C_Push_to_Transmit ( channel, x, must_be_pushed )` | `uint8` | `It Pushes the data that need to be transmitted, you still need to call I2C_MasterPoke_to_transmit for transmission` |

#### the only variable you need to change in I2C_Lcfg
| Variables | Type     | Description                       |
| :-------- | :------- | :-------------------------------- |
| `I2C_Container[ I2C_CONFIGURED_NUMBER] `      | `I2C_ConfigType` | `I2C_num (Channel Number)` |
| | |`I2C_Mode (I2C's Mode wheter it was Slave or Master)` |
| | |`I2C_Speed (I2C's Speed, 100kbps, 400kbps, 1Mbps or 3.3Mbps)` |
| | |`I2c_GlitchSupression (whether it was ON or OFF)` |
| | |`I2C_LoopBack (whether that feature was ON or OFF)` |
| | |`I2C_MasterISRMode (I2C's ISR if it was Master)` |
| | |`I2C_SlaveISRMode (I2C's ISR if it was Slave)` |
| | |`I2C_Clock_Low_Timeout_Count (uint8 : If > 0, that value will be in the CLKTO Register)` |
| | |`I2C_GlitchFilterPulseWidth (Glitch Filter Register Value)` |
| | |`I2C_SlaveAddress1 (I2C's Address 1 in case it was Slave)` |
| | |`I2C_SlaveAddress2 (I2C's Address 2 in case it was Slave)` |

