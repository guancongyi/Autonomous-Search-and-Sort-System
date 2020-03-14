# Autonomous-Searching-and-Sorting-System
An autonomous system design project, motivated by real world factory scenario.

# Demo
Here is the full description of the project:smiley:: https://youtu.be/dzMtaqMYtxA 

<img src="demo.gif" width="600">


# Description  
This project consists of 3 components:  
* Rovers  
We have two rovers, one is collection rover, the other is transportation rover. The collection rover is responsible for collecting objects in arena, and then the collected objects will be tranferred to the second rover. The transportation rover will then ship the object to the classify area.

* Electric Arms  
Electric Arm wil need to get the information from the server, and grab the object and put it to the designated area.

* Sensors and camera  
Multiple sensors are used to detect the edge of the arena, distance to the object and so on. The camera is used to recognize object's color, and it is also used to measure the distance to the object.

Different communication methods are used in this project: for parts on same rover, we used FreeRTOS message queues to send and recieve messages. Otherwise, we send message to server by using wifly module with TCP protocol, and server will make decision based on messages.  
