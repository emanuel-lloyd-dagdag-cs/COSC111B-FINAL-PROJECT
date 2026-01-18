from fastapi import FastAPI
import serial
import time

app = FastAPI()

arduino = serial.Serial(
    port='COM5',   # CHANGE IF NEEDED
    baudrate=9600,
    timeout=1
)

time.sleep(2)

# -------- LED CONTROL --------

@app.get("/led/on")
def led_on():
    arduino.write(b'1')
    arduino.write(b'2')
    arduino.write(b'3')
    return {"status": "All LEDs ON"}

@app.get("/led/off")
def led_off():
    arduino.write(b'O')
    return {"status": "All LEDs OFF"}

@app.get("/led/{color}")
def led_color(color: str):
    color = color.lower()

    if color == "red":
        arduino.write(b'1')
    elif color == "green":
        arduino.write(b'2')
    elif color == "blue":
        arduino.write(b'3')
    else:
        return {"error": "Invalid color"}

    return {"status": f"{color} LED toggled"}

# -------- BUTTON STATUS --------

@app.get("/button/status")
def button_status():
    if arduino.in_waiting:
        data = arduino.readline().decode().strip()
        return {"button_event": data}

    return {"button_event": "No button pressed"}
