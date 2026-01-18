Laboratory Finals Practical Exam

This code establishes a physical remote control for a web-connected LED system.

The Arduino sketch monitors a button presss and sends the specific identifier "GROUP_4" to the computer via USB. The accompanying Python script listens for this serial message and acts as a bridge; once it detects the signal, it sends an HTTP web request to a remote server to toggle the LED associated with Group 4. This setup demonstrates how to use a simple physical switch to trigger a network-based API command.
