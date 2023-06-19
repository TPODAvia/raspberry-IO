import time
from mpu9250_jmdev.registers import *
from mpu9250_jmdev.mpu_9250 import MPU9250
from smbus2 import SMBus

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

# Initialize I2C bus for barometer
barometer_address = 0x76
bus = SMBus(1)

# Replace the following lines with the appropriate code to read data from your specific barometer sensor.
# You may need to refer to the sensor's documentation or library examples for the correct commands and data processing.
def read_barometer_data():
    # Read raw data from the barometer
    data = bus.read_i2c_block_data(barometer_address, 0, 6)  # Replace 0 and 6 with the correct command and data length

    # Process the raw data and return the result
    pressure = data[0] << 12 | data[1] << 4 | data[2]  # Replace with the correct formula for your sensor
    temperature = data[3] << 12 | data[4] << 4 | data[5]  # Replace with the correct formula for your sensor
    return pressure, temperature

while True:
    print("Accelerometer:", mpu.readAccelerometerMaster())
    print("Gyroscope:", mpu.readGyroscopeMaster())
    print("Magnetometer:", mpu.readMagnetometerMaster())
    print("Temperature:", mpu.readTemperatureMaster())

    pressure, temperature = read_barometer_data()
    print("Barometer Pressure:", pressure)
    print("Barometer Temperature:", temperature)
    print("\n")
    time.sleep(1)
