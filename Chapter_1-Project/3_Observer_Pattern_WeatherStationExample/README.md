
# Pattern 2 : observer pattern (my Eddition)

Running the code -->  [![YouTube](https://img.shields.io/badge/-YouTube-red?style=flat&logo=YouTube&logoColor=white&link=https://www.youtube.com/@ElectroEngage)]([https://youtu.be/jEViYmZrtyM))<br>
Article --> [![Linkedin](https://img.shields.io/badge/LinkedIn-%20-blue?logo=Linkedin&logoColor=blue&labelColor=black)](https://www.linkedin.com/pulse/observer-pattern-embedded-systems-abdulrahman-yasser-uerkf%3FtrackingId=88TioHn5TVqwjmQ%252FpXZN5g%253D%253D/?trackingId=88TioHn5TVqwjmQ%2FpXZN5g%3D%3D)
> Observer is a behavioral design pattern that lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they’re observing. according to Refactoring.Guru.

> The observer pattern is a software design pattern in which an object, called the subject, maintains a list of its dependents, called observers, and notifies them automatically of state changes. according to angular.
This pattern is a good choice when we need the clients to be served once the data arrives. which will consume time depending on each notification function for each client and the number of those clients and functions however, We can control the number of the clients to solve that problem. But still, it consumes time depending on the called functions.



## Project Description
The project is nothing but 
- A server (Observable) which publishes a button state.
- A clients (Observer) which subscripe to the button state, [Buzzer, RED led, BLUE led, GREEN led].
- Each client attach a specific function when it subscripes to the server.
- The server then reads the data, run each client's function and passes the published data in it.



## Pattern efficiency

<dl>
<dt> Execution efficiency :</dt>
<dd> the client needs to check frequently if there are a new data, but its kinda better than the classic Client-Server approach because it notify the client when the data comes. (Score = 8) </dd>
<dt> Maintainability :</dt>
<dd> The Push approach breaks the classic Client-Server architecture (the server knows about the client).It also will be harder to maintain if we had more clients. (Score = 4) </dd>
<dt> Run-time flexibility :</dt>
<dd> we can easily subscripe and unsubscripe to the server </dd> </dl>

## 🛠 Skills
C, Embedded C, arm architecture
