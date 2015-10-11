#include <Wire.h>

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

long int cpt = 0;

/*Function:I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
 *This function read Nbytes bytes from I2C device at address Address.
 *Put read bytes starting at register Register in the Data array.
 */

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  // Read Nbytes
  Wire.requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (Wire.available())
    Data[index++] = Wire.read();
}

/*Function:I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
 *Write a byte (Data) in device (Address) at register (Register)
 */

void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}


// Initializations
void setupIMU()
{
  // Arduino initializations
  Wire.begin();                        //Set up I2C buss

  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);
  // Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);

  // Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01);
}

// Main loop, read and display data
void Gyro_Read(_Robot *Bagger)
{
  static int16_t gyro_dT;
  static int16_t gyro_LastIntTime;
  static int16_t gyro_Int;
  static int16_t gyro_Angle;
  
  // Read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

  // Gyroscope
  int16_t gx = Buf[8] << 8 | Buf[9];
  int16_t gy = Buf[10] << 8 | Buf[11];
  int16_t gz = Buf[12] << 8 | Buf[13];

  // Integrate

  gyro_dT = millis() - gyro_LastIntTime;
  gyro_LastIntTime = millis();
  gyro_Int += gz * (gyro_dT / 1000);
  gyro_Angle     = -gyro_Int / 131;

  // Gyroscope
  Serial.print("Angle to home: ");
  Serial.print (gyro_Angle, DEC);
  Serial.println ("\t");
//  Serial.print("gy: ");
//  Serial.print (gy, DEC);
//  Serial.print ("\t");
//  Serial.print("gz: ");
//  Serial.print (gz, DEC);
//  Serial.print ("\t");
}
