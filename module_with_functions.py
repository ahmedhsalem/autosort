# Python module with definitions of variables, functions, and classes
import serial

# Setting up the pyserial module

ser = serial.Serial(
                    port='/dev/ttyACM0',
                    baudrate=9600,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    timeout=5
)
