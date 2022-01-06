# Safety Watch

Created a mesh WiFi network of wearable devices and industrial sensors for the safety of workers in colamines.
Developed with the VIT Summer Research Grant Program, 2018.

## Introduction 

* To incorporate IoT into the safety mechanisms currently used in the bulky and expensive gas level monitoring systems in coalmines.
* A smart watch that is easily portable and gives the workers accurate updates of gas concentrations around them, and also warning them to evacuate the area when the concentrations cross the threshold values of the safety norms.
* The devices connect to mutliple hubs, where the hubs monitor the sensors and transmit the data to be displayed on the screens of the client smart watches.

## Working Principle

* Built a WiFi based mesh network with esp8266 (NodeMCU) microcontrollers. These devices can act as an Access Point, Client or both.
* The hubs/servers are setup as an AP and client. They read and analyze the data from the sensors. Along with regular updates, If the people near the hub are in danger it broadcasts warning to all connected clients. 
* The client recieves the data from the hubs and displays it to the user. It connects to the closest hub to ensure the validity of the data it recieves. The closest hub is determined by calculating approximate distance with the RSSI (recieved signal strength). 

*Block Diagram*
![image](https://user-images.githubusercontent.com/51409005/148349545-3d4125d2-0b57-4c64-9d0d-73d12ab320f7.png)

## Project Structure

The final code for the project is within:
* Client - "Client_Extra_Features"
* Server - "AP_Multiple_Sensors"

The other files were used as checkpoints to test the working of critial features and can be ignored.
