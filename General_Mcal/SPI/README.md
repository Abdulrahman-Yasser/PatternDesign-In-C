
# SPI

This repo will contain SPI Driver.
This is a task for Reusable firmware development book.

## 🔗 Video how to use it Links
Click here to watch a Demo of the SPI Driver
[![youtube]()


## Screenshots


## 🛠 Skills
C, Embedded C, arm architecture

## Running Tests

To run tests, just change the following variables with your own configurations in two files <br>
General_Mcal/PWM/Dynamic/inc/SPI.Cfg


```bash
#define SSI_CONFIGURED_NUMBER 1
```
General_Mcal/PWM/Dynamic/src/PWM.Lcfg

```bash
static SsiConfig_t Ssi_Container[SSI_CONFIGURED_NUMBER] = {
            {.BaudRate = 1000, .ClkSrc = SSI_SysClk, .ClockPolarity = E_FALSE,
            .DMA_State = SSI_DMA_NotAvailable, .DataSize = 8, .Interrupt = SSI_HALF_FIFO,
            .SlaveOrMaster = SSI_Master, .channelNumber = SSI_Channel_2, .protocolMode = SSI_Protocol_SPI
            }
};
```


