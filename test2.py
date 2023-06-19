import time
import board
import busio
import adafruit_bmp280
from mpu9250_jmdev.registers import *
from mpu9250_jmdev.mpu_9250 import MPU9250

# Initialize MPU9250
mpu = MPU9250(
    address_ak=AK8963_ADDRESS,
    address_mpu_master=MPU9050_ADDRESS_68,
    bus=1,
    gfs=GFS_1000,
    afs=AFS_8G,
    mfs=AK8963_BIT_16,
    mode=AK8963_MODE_C100HZ
)

mpu.configure()  # Apply the settings to the registers.

# Initialize BMP280
i2c = busio.I2C(board.SCL, board.SDA)
bmp280 = adafruit_bmp280.Adafruit_BMP280_I2C(i2c, address=0x76)
bmp280.sea_level_pressure = 1013.25

while True:
    print("Accelerometer:", mpu.readAccelerometerMaster())
    print("Gyroscope:", mpu.readGyroscopeMaster())
    print("Magnetometer:", mpu.readMagnetometerMaster())
    print("Temperature:", mpu.readTemperatureMaster())

    print("BMP280 Pressure:", bmp280.pressure)
    print("BMP280 Temperature:", bmp280.temperature)
    print("BMP280 Altitude:", bmp280.altitude)
    print("\n")
    time.sleep(1)
