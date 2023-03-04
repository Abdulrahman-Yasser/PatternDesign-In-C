
# Pattern 2 : Client-Server Pattern


## Project Description
The project is an implementation of a weather station that reads the data (Light, Smoke, temperature) and publish it to several modules (LCD here).
The project contains the following layers and each layer only access the layer below :

ImagePlaceHolder 

The second alternative approach is to create a “push” implementation in which the responsibility for notifying the clients is given to the WeatherStation_Data_Queue. To implement this, the direction of the associations in the figure below must be applied, and the WeatherStation_Data_Queue must explicitly know about all of its clients to notify them when data become available. The client list would probably be maintained as a list of pointers to clients.

ImagePlaceHolder

## Pattern efficiency
<ul>
<dt> Execution efficiency :</dt>
<dd>the client needs to check frequently if there are a new data, but its kinda better than the classic Client-Server approach because it notify the client when the data comes. (Score = 8)
<dt> Maintainability :</dt>
<dd>The Push approach breaks the classic Client-Server architecture (the server knows about the client).It also will be harder to maintain if we had more clients. (Score = 4)
<dt> Run-time flexibility :</dt>
<dd>in the code I have written you can't link a client in real-time to simplify the code for better explanation</dd></ul>

## 🛠 Skills
C, Embedded C, arm architecture

