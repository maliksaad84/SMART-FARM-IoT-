# SMART-FARM-IoT-
This repository includes LORA implementation for Smart Farm

1.	Integration of multiple sensors such as temperature sensor and humidity sensor at same time using scheduling technique with the Lora Gateway.  The development setup is shown below in figure.
 
 
2.	Data is collected at each end node. As shown as an example below:
   
3.	From the Gateway the data is uploaded to Web interface using RESTful API. The web interface shows the graphical user interface (GUI). Showing the values of sensors and interactive plots.
4.	The Gateway sends the data to IoT platform.
The IoT platform and stats are shown below in the figure.
 
5.	Different nodes are identified by assigning unique IDs to them. In code we assigned unique IDs to each node to identify temperature and relay associated to it.
6.	Relay is attached to each node with showing temp. So when the temp exceed beyond certain threshold, user can turn onn the relay remotely. 
7.	Graphical user interface is created on web to display temperature sensor and humidity sensor data.  
 
The above figure shows the data associated with node a8727 and assigned ID is 222.
 
Now the above figure shows the data associated with the node malik and assigned ID is 111.
8.	For the associated android mobile applications following screen shots are shown.
 
 
9.	For the operation of relay, to take action from the web a talk back app is created which sends the command from Gateway to node (i.e downlink) for the operation of relay.

10.	To send command from web, for graphical interface buttons are created.
11.	A unique ID is associated with the each pair of relay and temp/humidity sensor attached to the node.
Following figure shows the gui for buttons that can be operated from the web.

 


