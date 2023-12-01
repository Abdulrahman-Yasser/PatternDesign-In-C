
# Pattern 2 : observer pattern


## Project Description
The project is an implementation of a weather station that reads the data (Light, Smoke, temperature) and publish it to several modules (LCD here).
The project contains the following layers and each layer only access the layer below :

ImagePlaceHolder 

The observer pattern addresses the concern of dynamically adding and removing clients of data or services, as well as optimizing the processing associated with updating those clients in a timely way

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

