
# Pattern 1 : classic Client-Server Pattern

Code Works fine <br>
Running the code -->  [![YouTube](https://img.shields.io/badge/-YouTube-red?style=flat&logo=YouTube&logoColor=white&link=https://www.youtube.com/@ElectroEngage)](https://youtu.be/pPjvWL2Ylyg)<br>

## Project Description
The project is an implementation of a weather station that reads the data (Light, Smoke, temperature) and publish it to several modules (LCD here).
The project contains the following layers and each layer only access the layer below :

![aaae](https://github.com/Abdulrahman-Yasser/PatternDesign-In-C/assets/63866803/053834d2-40cb-4806-a55f-fe1a6bbe69be)

The code presented above works in a classic client-server approach. The WeatherStation puts data into the queue when it thinks it should and the various clients all individually decide when it is time to pull the data from the queue and do their work. In this case, the WeatherStation_Data_Queue is the server of the data for the clients, and the Display_1, Display_2 and Display_3 are the clients

## Pattern efficiency
<dl>
<dt> Execution efficiency :</dt>
<dd>the client needs to check frequently if there are a new data</dd>
<dd>Elements in the Queue can't be deleted because it doesn't know if there is a client who still didn't read an element</dd>
<dt> Maintainability :</dt>
<dd>in the code I have written the clients can't invoke the server, all the clients can do is reading the data if available</dd>
<dt> Run-time flexibility :</dt>
<dd>in the code I have written you can't link a client in real-time to simplify the code for better explanation</dd></dl>

## 🛠 Skills
C, Embedded C, arm architecture

