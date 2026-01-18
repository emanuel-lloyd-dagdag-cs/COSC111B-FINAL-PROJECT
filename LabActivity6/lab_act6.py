import serial
import time
import os

# ===== CONFIG =====
PORT = "COM5"       # change if needed
BAUD_RATE = 9600
CLEAR_TIME = 5      # seconds

last_activity = time.time()

# ===== FUNCTIONS =====
def clear_console():
    os.system("cls")   # Windows only (simplified)

def print_menu():
    print("Press Arduino button:")
    print("Button1 -> Toggle RED LED")
    print("Button2 -> Toggle GREEN LED")
    print("Button3 -> Toggle BLUE LED")
    print("Ctrl+C to exit\n")

# ===== MAIN =====
try:
    arduino = serial.Serial(PORT, BAUD_RATE, timeout=1)
    time.sleep(2)
    arduino.reset_input_buffer()

    clear_console()
    print_menu()

    while True:
        # Clear after inactivity
        if time.time() - last_activity >= CLEAR_TIME:
            clear_console()
            print_menu()
            last_activity = time.time()

        if arduino.in_waiting > 0:
            clear_console()
            print_menu()

            data = arduino.readline().decode().strip().upper()
            last_activity = time.time()

            if data == "R":
                print("Red toggled")
                arduino.write(b"1")
            elif data == "G":
                print("Green toggled")
                arduino.write(b"2")
            elif data == "B":
                print("Blue toggled")
                arduino.write(b"3")

        time.sleep(0.05)

except KeyboardInterrupt:
    pass

finally:
    arduino.close()
    clear_console()
    print("Program terminated.")    