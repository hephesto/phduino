from jabberbot import JabberBot
import datetime
import serial

class SystemInfoJabberBot(JabberBot):

	def init_serial(self):
		self.ser = serial.Serial(serial_port, baud_rate, timeout=5)
		return

	def close_serial(self):
		self.ser.close()
		return

	def bot_cmd (self, mess, args):
		"""Send a command to the pHduino. Type cmd help for a help."""
		self.ser.write(str(mess.getBody()))
		print str(mess.getBody())
		return

	def idle_proc(self):
		"""Callback function that read strings from serial port and send to a recipient by a jabber connection."""
		if self.ser.inWaiting():
			line = self.ser.readline()
			line = line.strip()
			self.send(recipient, line)
		return

username = 'pHduino xmmp account'
password = 'pHduino xmpp password'
recipient = 'Your xmpp account'
#serial_port = '/dev/ttyUSB0' # for linux
serial_port = 'COM9' # for Windows
baud_rate = 115200

print('Starting pHduino-Jabberbot...')
print('To close the phduino_jabberbot.py, press Ctrl-C.')
print('To list the pHduino commands, send cmd help from your IM account to pHduino-Jabberbot IM account.')

bot = SystemInfoJabberBot(username, password)
bot.init_serial()
bot.serve_forever()
bot.close_serial()

print('Bye')
