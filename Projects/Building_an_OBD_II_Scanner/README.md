# Overview

Driving a car is great and all, but we all have had to deal with the "Maintenance Required" message on your dashboard even though you're not seeing any funny blinking lights. 

(And with reading an analog odometer becoming a deprecated skill, it gets even more annoying with the message blocks the digital odometer).

Well as it turns out, this message is not actually caused by a tripped sensor in your car, rather, its a timed message that comes up every 5000 miles or so (depending on the car). You can go to any ol' autoshop and get that checked out... but what do they check out.

Autoshops have what is called an "On-Board Diagnostics Tool" or OBD for short. This device connects to your car and communicates with the ICs that are responsible for monitoring things like your engine, transmission, airbags, ABS/traction, body control, instruments, etc.

As it turns out, the car actually communicates with the OBD tool via a standardized communication protocal (similar to SPI, I2C, UART, etc.) called the "Controller Area Network" (CAN)

Why not make our own OBD tool to communicate with the car as a fun project over the course of a week rather than simply go to the automotive store and get it done in 5 minutes? 

(Such is the mindset of a natural born engineer)

# How does the OBD Tool Work?

In essence, the tool can just connect to the OBD port located into your car, then communicated through the CAN protocol. The real challenge is figuring out how the CAN operator works. We know that for any kind of protocol, that there exists a...

1. Tranceiver -> Gets signals from the outside world to send to the controller
2. Controller -> Interprets the signals from the transceiver

We can find out what these componets are and then consult the controller datasheet to get the rundown of how the protocol works!

I have brief overviews of some of the communication protocols. My overview of the CAN protocol can be found [here]().
