
# UART

This repo will contain UART(Universal asynchronous receiver-transmitter) Driver,
all you have to do is changing the UART_Cfg.h and UART_Lcfg.c for you own configurations as you will see in the example below

## 🔗 Video how to use it Links
Click here to watch a Demo of the UART Driver, It will be added soon
[![youtube](https://img.shields.io/youtube/views/T1rNExItZcU?style=social)]()


## Screenshots
![Functions API in UART](https://user-images.githubusercontent.com/63866803/214109685-59d73945-756e-4083-97cd-64e7453e70ed.png)
![UART Container](https://user-images.githubusercontent.com/63866803/214115066-524ffcdf-0596-48aa-8ad1-f2bf35443aeb.png)

## 🛠 Skills
C, Embedded C, arm architecture

## Running Tests

To run tests, just change the following variables with your own configurations in two files <br>
MCAL_Layer/UART/Dynamic/inc/UART.Cfg


```bash
#define UART_CONFIGURED_NUMBER 2
```
MCAL_Layer/UART/Dynamic/src/UART.Lcfg

```bash
const UART_ConfigType UART_Container[UART_CONFIGURED_NUMBER] = {
    {
    .uart_n = UART_NUM_5,.Uart_Mode = UARTMode_Transmit_Receive,
    .Data_Size = UARTSize_EIGHT_BITS, .parity = UARTParity_NO_PARITY,
    .StopBits_Num = UARTSTOPBIT_ONE,
    .Uart_ISRMode = {UARTISRMode_Transmit,UARTISRMode_Receive,UARTISRMode_None,UARTISRMode_None},
    .BaudRate = 9600,.endOfTransmission = 1,
    .fifo_size_rx = UART_FIFO_NOTUSED,.fifo_size_tx = UART_FIFO_NOTUSED
    },
    {
    .uart_n = UART_NUM_7,.Uart_Mode = UARTMode_Transmit_Receive,
    .Data_Size = UARTSize_EIGHT_BITS, .parity = UARTParity_NO_PARITY,
    .StopBits_Num = UARTSTOPBIT_ONE,
    .Uart_ISRMode = {UARTISRMode_Transmit,UARTISRMode_Receive,UARTISRMode_None,UARTISRMode_None},
    .BaudRate = 9600,.endOfTransmission = 0,
    .fifo_size_rx = UART_FIFO_NOTUSED,.fifo_size_tx = UART_FIFO_7_8
    }
};
```


## API Reference

#### All the functions you can use in UART


| Functions | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `uart_init()` | `void` | `it initialize your UART with your configuraions`|
| `UART_Poke_to_transmit (my_uart, Bytes_Cnt)` | `void` | `it starts the transmission via my_uart channel id, if the Bytes_Cnt is 0 : it will transmit all of the queue, else it will tranmit the number of the bytes` |
| `UART_Poke_to_receive (my_uart, Bytes_Cnt)` | `void` | `it starts the receiving via my_uart channel id, if the Bytes_Cnt is 0 : it will receive untill the queue is full, else it will receive the number of the bytes`
| `UART_Push_to_Transmit (my_uart, x , must_be_pushed)` | `void` | `It inserts data in your pre-initialized uart-Queue, it does not transmit it. it just push the data in the queue. you still need to call UART_Poke_to_transmit`
| `UART_Pop_the_Received (my_uart, *data)` | `void` | `It receive the data here after your calling to the function UART_Poke_to_receive or when it automatically receive in the ISR` |

#### the only variable you need to change in UART_Lcfg
| Variables | Type     | Description                       |
| :-------- | :------- | :-------------------------------- |
| `UART_Container[UART_CONFIGURED_NUMBER] `      | `UART_ConfigType` | `uart_n (Channel Number)` |
| | |`Uart_Mode (the UART's Mode whether it was receive, transmit or both)` |
| | |`Data_Size (UART Data size 5-Bits : 8-Bits)` |
| | |`parity (The parity of the UART if exist)` |
| | |`StopBits_Num (the UART's Stop bits that will be transmitted)` |
| | |`Uart_ISRMode (the UART got a static array that contain a number of ISR)` |
| | |`BaudRate (the UART's Baud rate, whatever the desired rate it will be generated)` |
| | |`endOfTransmission (a Flag that represent the EOF flag in the UART, if 1 it will generate a flag whenever it finishes a transmit)` |
| | |`fifo_size_rx (a Pointer to a pre-initialized Queue that is initialized with the UART's ID initialization. that Queue is used in receiving data)` |
| | |`fifo_size_tx (a Pointer to a pre-initialized Queue that is initialized with the UART's ID initialization. that Queue is used in transmitting data)` |

