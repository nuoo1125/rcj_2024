from machine import I2C
import time
def init_i2c():
    i2c = I2C(I2C.I2C0, freq=100000, scl=30, sda=31)
    raspberry_pico_address = 0x28

def send_data(data):
    i2c.writeto(raspberry_pico_address, data)
    print(f"Sent: {data}")

def receive_data(num_bytes):
    data = i2c.readfrom(raspberry_pico_address, num_bytes)
    print(f"Received: {data}")
    return data
