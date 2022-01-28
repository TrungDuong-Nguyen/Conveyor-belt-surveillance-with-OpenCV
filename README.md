In recent years, computer vision has been a fast-growing field in which many innovative applications have been developing in various sectors like medical, autonomous vehicle, robotic, agriculture, sport, etc. One of the promising applications of computer vision technology is video surveillance.

This 5-months research project in realized during my final year at the University of Technology of Ho Chi Minh City. The primary objectives of the project and its principal tasks are intially stated in [this document](/Project-Objectives-and-Principal-Tasks.md).  


## Project name
Supervise the objects on a conveyor using computer vision.

## Project outline
In the industrial environment, the counting of products on a conveyor is carried out with the help of specialized electronic sensors. Generally, these sensors will then connect to a human-machine interface for monitoring purposes or a programmable logic controller to trigger commands to the corresponding actuators. 

In this project, I develop a system that performs product counting by processing in real-time the video stream captured by a camera installed in a running conveyor. In addition, data related to the counting process such as the video flow, time, and product image is saved on the computer. For experimenting with my vision system, I also assembled a model of conveyor controlled by an inverter. 

Considering the system's functioning, I distinguish three scenarios in which the system could operate, and write C++ code for each of these three modes. The programs are based on two computer vision libraries: OpenCV and cvBlobsLib. To monitor the counting process and facilitate the data extraction, I build a simple user interface using MFC library. The experiments show that the system's accuracy is around 90% depending on the testing contexts. Also, the counting method that relied on computer vision technology proves its simplicity and flexibility compared to the traditional one.

<br>

***

For more details, please glance over [the presentation slides](/Presentation-slide/Presentation-slide.pdf) (in French). 