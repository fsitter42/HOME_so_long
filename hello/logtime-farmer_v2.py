#!/usr/bin/env python
import time
import os
from datetime import datetime
from pynput.mouse import Controller as MouseController
from pynput.keyboard import Key, Controller as KeyboardController, Listener
from random import randint
import subprocess

mouse = MouseController()
keyboard = KeyboardController()

def intro():
    print(" __ ____ _________________ _______ _______ ___ __ ____________")
    print(" / / / __ \/ ___/_ __/ _/ |/ / __/ / __/ _ | / _ \/ |/ / __/ _ / ")
    print(" / /__/ /_/ / (_ / / / _/ // /|_/ / _/ / _// __ |/ , _/ /|_/ / _// , _/")
    print("/____/\____/\___/ /_/ /___/_/ /_/___/ /_/ /_/ |_/_/|_/_/ /_/___/_/|_| ")
    print("\n\n")

def get_now_timestamp():
    now = datetime.now()
    return now.strftime("%H:%M:%S")

def infoBanner(number):
    print(get_now_timestamp(), "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
    print(get_now_timestamp(), "X Prepare for farming. X")
    print(get_now_timestamp(), "X Beginning in 5 seconds.. X")
    print(get_now_timestamp(), "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n")
    print(get_now_timestamp(), f"You're going to farm {number} hours.\n")
    print(get_now_timestamp(), "Beginning in 5 seconds..")
    time.sleep(5)
    print("Startiiiiing")

lastSavePosition = (0, 0)

def lock_screen():
    os.system('gnome-session-quit --no-prompt')

def open_fullscreen_image():
    image_path = "./black.png"
    if not os.path.exists(image_path):
        print(f"{get_now_timestamp()} Warning: Image file not found: {image_path}")
        print(f"{get_now_timestamp()} Continuing without opening the image.")
        return
    
    # Use Eye of GNOME (eog), the default GNOME image viewer on Ubuntu
    # --fullscreen opens it in fullscreen mode
    # Detached with & so the script continues immediately
    subprocess.Popen(['eog', '--fullscreen', image_path])

def on_press(key):
    # Any keyboard press (except ESC) triggers screen lock
    # ESC exits the program cleanly
    if key == Key.esc:
        print(f"\n{get_now_timestamp()} ESC pressed - exiting program.")
        os._exit(0)  # Force exit
    else:
        lock_screen()

def move_mouse():
    global lastSavePosition
    x = randint(1, 1000)
    y = randint(1, 1000)
    lastSavePosition = (x, y)
    mouse.position = lastSavePosition

def mouse_detect(timetofarm):
    global lastSavePosition
    lastSavePosition = mouse.position
    
    # Open the fullscreen black image immediately after starting farming
    open_fullscreen_image()
    
    start_time = time.time()
    last_move_time = start_time
    
    while True:
        elapsed = time.time() - start_time
        if elapsed >= timetofarm:
            print(f"\n{get_now_timestamp()} Farming time completed!")
            break
        
        # Move mouse every 20 minutes
        if time.time() - last_move_time > 20 * 60:
            move_mouse()
            last_move_time = time.time()
        
        # Detect manual mouse movement
        currentPosition = mouse.position
        if currentPosition != lastSavePosition:
            lock_screen()
        
        time.sleep(0.1)

def main():
    intro()
    while True:
        print(get_now_timestamp(), 'How many hours do you wanna farm?')
        farming_input = input('> ')
        try:
            number = int(farming_input)
            if number > 0:
                break
            else:
                print("Please enter a positive integer.")
        except ValueError:
            print("Invalid input - please enter a whole number.")
    
    infoBanner(number)
    timetofarm = number * 3600
    
    # Start global keyboard listener
    listener = Listener(on_press=on_press)
    listener.start()
    
    try:
        mouse_detect(timetofarm)
    finally:
        listener.stop()

if __name__ == "__main__":
    main()
