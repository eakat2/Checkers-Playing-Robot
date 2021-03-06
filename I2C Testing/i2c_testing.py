import smbus
import time

bus = smbus.SMBus(1)

bus.write_byte_data(0x20, 0x00, 0x00)
bus.write_byte_data(0x20, 0x01, 0x00)

counter = 0

try:
    while 1:
        for counter = range(0, 255):
            bus.write_byte_data(0x20, 0x12, counter)
            bus.write_byte_data(0x20, 0x13, counter)
            time.sleep(0.5)
except KeyboardInterrupt:
    bus.write_byte_data(0x20, 0x12, 0x00)
    bus.write_byte_data(0x20, 0x13, 0x00)
    print("Program Exited Cleanly")