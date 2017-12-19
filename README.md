# Stats Claw

Arduino Controller for Claw Machine (Built for AP Statistics Carnival)

## Design Ideas

- 2-Axis joystick - 2 analog inputs
- X/Y/Z Limit Switches - 6 digital inputs (min & max for each)
- X/Y linear actuator motors - 2 pwm outs - goes to motor driver/mosfet
- "Drop" button - digital input, runs control sequence to drop claw, close claw, raise claw, home, open claw
- "Start" button - digital input, starts timer countdown (eventually a button to "add credit" and "use credit" to start game, with a credits counter)

Easter eggs inside which contain a note showing $ amount won

Interrupts on limit switches? will probably just complicate the design

# Reference

![Arduino Uno Pinout](http://www.pighixxx.com/test/wp-content/uploads/2017/05/uno.png)

![RPI Pinout](http://raspi.tv/wp-content/uploads/2015/11/Pi-Zero-Portsplus_1500.jpg)

We used the silkscreen on the H-Bridge Driver (designed by Derek) to figure out which pins on the big header go to which inputs on the L298 chips. 

|Motor Port|Input Name|GPIO # (BCM)|Pin #|
|----------|----------|------------|-----|
|Motor 4|Enable A|GPIO 14|Pin ?|
|Motor 4|Input 1|GPIO 18|Pin ?|
|Motor 4|Input 2|GPIO 23|Pin ?|

> NOTE: The silkscreen is wrong - it says Motor 4's Input 4 should be GPIO 10, which doesn't work.
