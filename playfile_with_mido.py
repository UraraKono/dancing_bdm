# coding: UTF-8
import mido
from mido import MidiFile
from mido import Message
import time
import rtmidi

msg = Message('note_on', note=60)
print(msg)
ports = mido.get_output_names()
port = mido.open_output(ports[0])
print(port)
filename = "sample.mid"
mid = MidiFile(filename)

#midifile全てのmsgをprint
tempo_original = 500000
with port as outport:
    for msg in mid:
        #print(msg)
        print("tempo:", tempo_original)
        time.sleep(msg.time)
        if not msg.is_meta:
            port.send(msg)
        elif msg.type == "set_tempo":
            print("tempo:", msg.tempo) 
            tempo_original = msg.tempo


