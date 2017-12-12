# Stats Claw

Arduino Controller for Claw Machine (Built for AP Statistics Carnival)

## Design Ideas

2-Axis joystick - 2 analog inputs
X/Y/Z Limit Switches - 6 digital inputs (min & max for each)
X/Y linear actuator motors - 2 pwm outs - goes to motor driver/mosfet
"Drop" button - digital input, runs control sequence to drop claw, close claw, raise claw, home, open claw
"Start" button - digital input, starts timer countdown (eventually a button to "add credit" and "use credit" to start game, with a credits counter)

Easter eggs inside which contain a note showing $ amount won

Interrupts on limit switches? will probably just complicate the design
