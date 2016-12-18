import serial
import json
from Adafruit_IO import *

aio = Client("2a9bddbbfe6543f2b567f6094e87cb13")


comunicacaoSerial = serial.Serial('/dev/ttyUSB0', 9600)

while 1:
	try:
		sensorMsg = comunicacaoSerial.readline()
		msg = json.loads(sensorMsg)
		aio.send("casa-temperatura-externa", msg["temperature"])
		aio.send("casa-humidade-externa", msg["humidity"])
		aio.send("casa-luz-natural", msg["photocell"])
		print msg
	except ValueError:
		print "Ops! That was no valid json message. Try again..."

