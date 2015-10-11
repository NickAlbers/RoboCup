//// Set initial input parameters
//enum Mscale {
//  MFS_14BITS = 0, // 0.6 mG per LSB
//  MFS_16BITS      // 0.15 mG per LSB
//};
//
//
//// Specify sensor full scale
//uint8_t Mscale = MFS_16BITS; // Choose either 14-bit or 16-bit magnetometer resolution
//uint8_t Mmode = 0x02;        // 2 for 8 Hz, 6 for 100 Hz continuous magnetometer data read
//float aRes, gRes, mRes;      // scale resolutions per LSB for the sensors
//
//
//int16_t magCount[3];    // Stores the 16-bit signed magnetometer sensor output
//float magCalibration[3] = {0, 0, 0}, magbias[3] = {0, 0, 0};  // Factory mag calibration and mag bias
//
//float mx, my, mz; // variables to hold latest sensor data values
//
//float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};    // vector to hold quaternion
//
//void setupMagenometer()
//{
//  Wire.begin();
//  //  TWBR = 12;  // 400 kbit/sec I2C speed
//  //  Serial.begin(38400);
//
//  // Set up the interrupt pin, its set as active high, push-pull
//  pinMode(intPin, INPUT);
//  digitalWrite(intPin, LOW);
//  pinMode(myLed, OUTPUT);
//  digitalWrite(myLed, HIGH);
//
//  // Read the WHO_AM_I register, this is a good test of communication
//  Serial.println("I AM");
//  Serial.println(c, HEX);
//  Serial.print("I Should Be");
//  Serial.println(0x71, HEX);
//
//  if (c == 0x71) // WHO_AM_I should always be 0x68
//  {
//    Serial.println("MPU9250 is online...");
//
//    initMPU9250();
//    Serial.println("MPU9250 initialized for active data mode...."); // Initialize device for active mode read of acclerometer, gyroscope, and temperature
//
//    // Read the WHO_AM_I register of the magnetometer, this is a good test of communication
//    byte d = readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);  // Read WHO_AM_I register for AK8963
//    Serial.print("AK8963 "); Serial.print("I AM "); Serial.print(d, HEX); Serial.print(" I should be "); Serial.println(0x48, HEX);
//
//    // Get magnetometer calibration from AK8963 ROM
//    initAK8963(magCalibration); Serial.println("AK8963 initialized for active data mode...."); // Initialize device for active mode read of magnetometer
//
//    if (SerialDebug) {
//      //  Serial.println("Calibration values: ");
//      Serial.print("X-Axis sensitivity adjustment value "); Serial.println(magCalibration[0], 2);
//      Serial.print("Y-Axis sensitivity adjustment value "); Serial.println(magCalibration[1], 2);
//      Serial.print("Z-Axis sensitivity adjustment value "); Serial.println(magCalibration[2], 2);
//    }
//  }
//
//  else
//  {
//    Serial.print("Could not connect to MPU9250: 0x");
//    Serial.println(c, HEX);
//    while (1) ; // Loop forever if communication doesn't happen
//  }
//}
//
//void readMag()
//{
//  // If intPin goes high, all data registers have new data
//  if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {  // On interrupt, check if data ready interrupt
//    readAccelData(accelCount);  // Read the x/y/z adc values
//    getAres();
//
//    readMagData(magCount);  // Read the x/y/z adc values
//
//    getMres();
//    magbias[0] = +470.;  // User environmental x-axis correction in milliGauss, should be automatically calculated
//    magbias[1] = +120.;  // User environmental x-axis correction in milliGauss
//    magbias[2] = +125.;  // User environmental x-axis correction in milliGauss
//
//    // Calculate the magnetometer values in milliGauss
//    // Include factory calibration per data sheet and user environmental corrections
//    mx = (float)magCount[0] * mRes * magCalibration[0] - magbias[0]; // get actual magnetometer value, this depends on scale being set
//    my = (float)magCount[1] * mRes * magCalibration[1] - magbias[1];
//    mz = (float)magCount[2] * mRes * magCalibration[2] - magbias[2];
//  }
//  
//  Now = micros();
//  deltat = ((Now - lastUpdate) / 1000000.0f); // set integration time by time elapsed since last filter update
//  lastUpdate = Now;
//
//  sum += deltat; // sum for averaging filter update rate
//  sumCount++;
//  
////  MahonyQuaternionUpdate(ax, ay, az, gx * PI / 180.0f, gy * PI / 180.0f, gz * PI / 180.0f, my, mx, mz);
//
//
//  if (!AHRS) {
//    delt_t = millis() - count;
//    if (delt_t > 500) {
//
//      if (SerialDebug) {
//
//        // Print mag values in degree/sec
//        Serial.print("X-mag field: "); Serial.print(mx); Serial.print(" mG ");
//        Serial.print("Y-mag field: "); Serial.print(my); Serial.print(" mG ");
//        Serial.print("Z-mag field: "); Serial.print(mz); Serial.println(" mG");
//      }
//
//      count = millis();
//    }
//  }
//  else {
//    // Serial print and/or display at 0.5 s rate independent of data rates
//    delt_t = millis() - count;
//    if (delt_t > 500) { // update LCD once per half-second independent of read rate
//
//      if (SerialDebug) {
//        Serial.print("mx = "); Serial.print( (int)mx );
//        Serial.print(" my = "); Serial.print( (int)my );
//        Serial.print(" mz = "); Serial.print( (int)mz ); Serial.println(" mG");
//        
//        Serial.print("q0 = "); Serial.print(q[0]);
//        Serial.print(" qx = "); Serial.print(q[1]);
//        Serial.print(" qy = "); Serial.print(q[2]);
//        Serial.print(" qz = "); Serial.println(q[3]);
//}
//
//

