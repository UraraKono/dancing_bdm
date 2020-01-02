# coding: UTF-8
import mido
from mido import MidiFile, Message, MetaMessage
import time
import rtmidi
import math
import serial
import time

ports = mido.get_output_names()
port = mido.open_output(ports[0])
print("port:", port)
print("please input the usbserial number (14110)")
num = input()
sername = "/dev/cu.wchusbserial" + num
ser = serial.Serial(sername, 9600, timeout=None) 

print("please input the filename")
filename = input()
mid = MidiFile(filename)
tempo_original = 500000 #us 元のテンポ設定
bpm_changed = 120

not_used = ser.readline()
print(not_used.decode())#MMA8452Q Basic Reading Code!
not_used = ser.readline()
print(not_used.decode())#ready

with port as outport:
    for i, msg in enumerate(mid):
        if ser.inWaiting() > 0:
            val_arduino = ser.readline()
            print("tempo:", int(val_arduino.decode()) * 1.5)
            bpm_changed = int(val_arduino.decode()) * 1.5
        tempo_changed = mido.bpm2tempo(bpm_changed)
        x = msg.time * tempo_changed / tempo_original
        time.sleep(x)
        print(msg)
        if not msg.is_meta:
            port.send(msg)
        elif msg.type == "set_tempo":
            print("original tempo:", mido.tempo2bpm(msg.tempo))
            tempo_original = msg.tempo

ser.close()