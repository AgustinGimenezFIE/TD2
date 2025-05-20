import serial
import subprocess
import time
from datetime import datetime, timedelta

SERIAL_PORT = '/dev/ttyUSB0'
BAUD_RATE = 115200
CHECK_INTERVAL = 5 * 60
BACKUP_INTERVAL = 6 * 60 * 60

ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
last_backup_time = datetime.min

def hacer_backup():
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    subprocess.run(f"mysqldump -u usuario -p'clave' basededatos > /home/pi/backups/sql_backup_{timestamp}.sql", shell=True)
    subprocess.run(f"lftp -e 'mirror /public_html /home/pi/backups/code_backup_{timestamp} && quit' -u user,pass ftp://ftp.imprenet.ar", shell=True)

def iniciar_xampp():
    subprocess.run("/opt/lampp/lampp start", shell=True)

while True:
    try:
        line = ser.readline().decode().strip()
        now = datetime.now()
        if line == "DOWN":
            hacer_backup()
            iniciar_xampp()
            time.sleep(10 * 60)
        elif line == "OK":
            if (now - last_backup_time).total_seconds() > BACKUP_INTERVAL:
                hacer_backup()
                last_backup_time = now
    except Exception as e:
        print("Error:", e)
    time.sleep(CHECK_INTERVAL)