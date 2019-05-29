import keyboard
import serial
import sys


comPort : str = sys.argv[1]
ser = serial.Serial()

# space -> '%'
# enter -> '#'
# backspace -> '['
# shift -> '$'
# ctrl -> '|'
# alt -> '@'
# alt_gr -> '~'
symDict = {'%':'space', '#':'enter', '[':'backspace', '$':'shift', '|':'ctrl', '@':'alt', '~':'altGr', '{':'left_arrow', '}':'right_arrow', '^':'up_arrow', '_':'down_arrow'}
symPress = {i:False for i in symDict.values()}

def setup():
    ser.port = comPort
    ser.timeout = 0
    ser.baudrate = 9600
    ser.open()

def loop():
    data = ''
    if ser.inWaiting() > 0:
        data = str(ser.read(),encoding='ascii')
        print('EVENT : ' + data)
    if len(data) > 0:
        if data in symDict.keys():
            data = symDict[data]
            if symPress[data]:
                keyboard.release(data)
                symPress[data] = False
            else:
                keyboard.press(data)
                symPress[data] = True
        elif data.islower():
            keyboard.press(data)
        else:
            keyboard.release(data)

if __name__ == "__main__":
    setup()
    try:
        while(True):
            loop()
    except KeyboardInterrupt:
        ser.close()
        print('Bye')
    ser.close()
        


