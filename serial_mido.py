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
print("please input the filename")
filename = input()
mid = MidiFile(filename)
tempo_original = 500000 #us 元のテンポ設定
bpm_changed = 120
ser = serial.Serial("/dev/cu.usbserial-14110", 9600, timeout=None) 
not_used = ser.readline()

with port as outport:
    for i, msg in enumerate(mid):
        if ser.inWaiting() > 0:
            val_arduino = ser.readline()
            print("tempo:", val_arduino.decode())
            bpm_changed = int(val_arduino.decode())
        tempo_changed = mido.bpm2tempo(bpm_changed)
        x = msg.time * tempo_changed / tempo_original
        time.sleep(x)
        if not msg.is_meta:
            port.send(msg)
        elif msg.type == "set_tempo":
            print("original tempo:", mido.tempo2bpm(msg.tempo))
            tempo_original = msg.tempo

ser.close()