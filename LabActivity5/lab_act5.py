import serial
import time
import os

def clear_screen():
    """Clear the console screen"""
    os.system('cls' if os.name == 'nt' else 'clear')

def display_menu():
    """Display the menu options"""
    print("=" * 40)
    print("   Arduino LED Control System")
    print("=" * 40)
    print("[R] Red ON/OFF")
    print("[G] Green ON/OFF")
    print("[B] Blue ON/OFF")
    print("[A] All ON")
    print("[O] All OFF")
    print("[X] Exit")
    print("=" * 40)

def main():
    # Configure serial port
    PORT = 'COM6'
    BAUD_RATE = 9600
    
    try:
        # Open serial connection
        arduino = serial.Serial(PORT, BAUD_RATE, timeout=1)
        time.sleep(2)  # Wait for Arduino to reset
        
        print(f"Connected to Arduino on {PORT}")
        time.sleep(1)
        
        # Clear initial Arduino messages
        arduino.flushInput()
        
        # Main loop
        while True:
            clear_screen()
            display_menu()
            
            # Get user input
            choice = input("\nEnter your choice: ").strip().upper()
            
            # Validate input
            if not choice:
                continue
            
            # Get first character
            command = choice[0]
            
            # Check for exit
            if command == 'X':
                print("\nClosing connection...")
                arduino.write(b'O')  # Turn off all LEDs before exit
                time.sleep(0.5)
                arduino.close()
                print("Goodbye!")
                break
            
            # Validate command
            if command in ['R', 'G', 'B', 'A', 'O']:
                # Send command to Arduino
                arduino.write(command.encode())
                time.sleep(0.1)
                
                # Read response from Arduino
                if arduino.in_waiting > 0:
                    response = arduino.readline().decode('utf-8').strip()
                    print(f"\nArduino: {response}")
                else:
                    print(f"\nCommand '{command}' sent to Arduino")
                
                time.sleep(1.5)  # Brief pause to see the response
            else:
                print(f"\nERROR: Invalid command '{command}'")
                time.sleep(1.5)
    
    except serial.SerialException as e:
        print(f"\nError: Could not open serial port {PORT}")
        print(f"Details: {e}")
        print("\nPlease check:")
        print("1. Arduino is connected")
        print("2. Correct port is specified")
        print("3. No other program is using the port")
        print("4. pyserial is installed (pip install pyserial)")
    
    except KeyboardInterrupt:
        print("\n\nProgram interrupted by user")
        if 'arduino' in locals() and arduino.is_open:
            arduino.write(b'O')  # Turn off all LEDs
            arduino.close()
        print("Connection closed")
    
    except Exception as e:
        print(f"\nUnexpected error: {e}")
        if 'arduino' in locals() and arduino.is_open:
            arduino.close()

if __name__ == "__main__":
    main()