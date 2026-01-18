import serial
import time
import requests

# CONFIGURATION
SERIAL_PORT = 'COM6'
BAUD_RATE = 9600
BASE_URL = "http://172.20.10.3:8000"

try:
    # 1. Connect to Arduino
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Allow Arduino to reset
    print(f"Connected to Arduino on {SERIAL_PORT}")
    print(f"Targeting API: {BASE_URL}")

    while True:
        # 2. Listen for the signal
        if ser.in_waiting > 0:
            try:
                incoming_data = ser.readline().decode('utf-8').strip()

                if incoming_data:
                    print(f"\n[Button Pressed] Signal: {incoming_data}")

                    # 3. Extract the Number (e.g., "GROUP_4" -> "4")
                    # This ensures the URL format matches the exam requirement: /led/group/<number>/toggle
                    group_num = "".join(filter(str.isdigit, incoming_data))

                    if group_num:
                        endpoint = f"{BASE_URL}/led/group/{group_num}/toggle"
                        print(f"[API] Sending request to: {endpoint}")

                        try:
                            # 4. SEND THE HTTP REQUEST
                            response = requests.get(endpoint, timeout=2)

                            # 5. Print Server Response
                            if response.status_code == 200:
                                print(f">> SUCCESS: Server toggled the remote LED.")
                            else:
                                print(f">> FAILED: Server returned code {response.status_code}")
                                print(f"   Message: {response.text}")

                        except requests.exceptions.RequestException as e:
                            print(f">> NETWORK ERROR: Is the server running at {BASE_URL}?")
                            print(f"   Details: {e}")
                    else:
                        print(">> ERROR: Could not parse group number from signal.")

            except UnicodeDecodeError:
                pass  # Ignore serial noise

except serial.SerialException:
    print(f"Error: Could not open {SERIAL_PORT}. Is the Arduino plugged in?")
except KeyboardInterrupt:
    if 'ser' in locals() and ser.is_open:
        ser.close()
    print("\nDisconnected.")