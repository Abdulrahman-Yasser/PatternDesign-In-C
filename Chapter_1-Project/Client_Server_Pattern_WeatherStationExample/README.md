
# Pattern 1 : classic Client-Server Pattern


## Project Description
The project is an implementation of a weather station that reads the data (Light, Smoke, temperature) and publish it to several modules (LCD here).
The project contains the following layers and each layer only access the layer below :

ImagePlaceHolder 

The code presented above works in a classic client-server approach. The WeatherStation puts data into the queue when it thinks it should and the various clients all individually decide when it is time to pull the data from the queue and do their work. In this case, the WeatherStation_Data_Queue is the server of the data for the clients, and the Display_1, Display_2 and Display_3 are the clients

## Pattern efficiency
<ul>
<dt> Execution efficiency :</dt>
<dd>the client needs to check frequently if there are a new data
<dt> Maintainability :</dt>
<dd>in the code I have written the clients can't invoke the server, all the clients can do is reading the data if available
<dt> Run-time flexibility :</dt>
<dd>in the code I have written you can't link a client in real-time to simplify the code for better explanation</dd></ul>

## 🛠 Skills
C, Embedded C, arm architecture

