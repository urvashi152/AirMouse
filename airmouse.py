import serial
import time
import pyautogui
import keyboard

# ==== Serial Setup ====
arduino_port = 'COM3'  # Change this to your Arduino COM port
baud_rate = 9600
ser = serial.Serial(arduino_port, baud_rate)
time.sleep(2)  # Allow time for serial connection to establish

# ==== Constants ====
SENSITIVITY_X = 500
SENSITIVITY_Y = 500
DEAD_ZONE = 10          
VOLUME_STEP = 10        # For volume up/down simulation
ALPHA = 0.7             # Smoothing factor (0-1, higher = smoother)

# ==== Smoothing Variables ====
prev_move_x = 0
prev_move_y = 0

# For volume control (via potentiometer or mapped angle)
prev_map_pot_value = 50  # Assume middle value (0–100 scale)

print("Python air mouse started. Move your hand to control cursor.")

while True:
    try:
        line = ser.readline().decode('latin1').strip()
        if not line:
            continue

        # Expected format: "ax,ay,clickL,clickR,scrollU,scrollD,pot"
        parts = line.split(',')
        if len(parts) < 7:
            continue

        ax = int(parts[0])
        ay = int(parts[1])
        clickL = int(parts[2])
        clickR = int(parts[3])
        scrollU = int(parts[4])
        scrollD = int(parts[5])
        potVal = int(parts[6])

        # ==== Cursor Movement ====
        move_x = ax / SENSITIVITY_X
        move_y = -ay / SENSITIVITY_Y  # Invert Y-axis if needed

        # Apply smoothing
        smooth_x = ALPHA * prev_move_x + (1 - ALPHA) * move_x
        smooth_y = ALPHA * prev_move_y + (1 - ALPHA) * move_y

        # Apply dead zone
        if abs(smooth_x) > DEAD_ZONE or abs(smooth_y) > DEAD_ZONE:
            pyautogui.moveRel(smooth_x, smooth_y)

        prev_move_x = smooth_x
        prev_move_y = smooth_y

        # ==== Click Handling ====
        if clickL:
            pyautogui.mouseDown(button='left')
        else:
            pyautogui.mouseUp(button='left')

        if clickR:
            pyautogui.mouseDown(button='right')
        else:
            pyautogui.mouseUp(button='right')

        # ==== Scroll Handling ====
        if scrollU:
            pyautogui.scroll(1)
        if scrollD:
            pyautogui.scroll(-1)

        # ==== Volume Control (based on potentiometer) ====
        mapped_pot = int((potVal / 1023.0) * 100)  # Scale to 0–100
        if mapped_pot - prev_map_pot_value > 10:
            keyboard.send("volume up")
            prev_map_pot_value = mapped_pot
        elif prev_map_pot_value - mapped_pot > 10:
            keyboard.send("volume down")
            prev_map_pot_value = mapped_pot

    except Exception as e:
        print(f"Error: {e}")
