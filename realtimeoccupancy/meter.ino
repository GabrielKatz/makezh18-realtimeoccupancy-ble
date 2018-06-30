#define accelX A0 // X pin connected to Analog 0
#define accelY A1 // Y pin connected to Analog 1
#define accelZ A2 // Z pin connected to Analog 2
//Accelerometer limits
int xMin; //Minimum x Value
int xMax; //Maximum x Value
int xVal; //Current x Value

int yMin; //Minimum y Value
int yMax; //Maximum y Value
int yVal; //Current y Value

int zMin; //Minimum z Value
int zMax; //Maximum z Value
int zVal; //Current z Value

#define tolerance 20

// Function used to calibrate the Accelerometer
void calibrateAccel() {

  //initialise x,y,z variables
  xVal = analogRead(accelX);
  xMin = xVal;
  xMax = xVal;
  
  yVal = analogRead(accelY);
  yMin = yVal;
  yMax = yVal;
  
  zVal = analogRead(accelZ);
  zMin = zVal;
  zMax = zVal;
  
  
  //calibrate the Accelerometer (should take about 0.5 seconds)
  for (int i=0; i<50; i++){
  // Calibrate X Values
  xVal = analogRead(accelX);
  if(xVal>xMax){
  xMax=xVal;
  }else if (xVal < xMin){
  xMin=xVal;
  }
  
  // Calibrate Y Values
  yVal = analogRead(accelY);
  if(yVal>yMax){
  yMax=yVal;
  }else if (yVal < yMin){
  yMin=yVal;
  }
  
  // Calibrate Z Values
  zVal = analogRead(accelZ);
  if(zVal>zMax){
  zMax=zVal;
  }else if (zVal < zMin){
  zMin=zVal;
  }
  
  //Delay 10msec between readings
  delay(10);
  }
  printValues(); //Only useful when connected to computer- using serial monitor.
}

void printValues(){
  Serial.print("xMin=");
  Serial.print(xMin);
  Serial.print(", xMax=");
  Serial.print(xMax);
  Serial.println();
  
  Serial.print("yMin=");
  Serial.print(yMin);
  Serial.print(", yMax=");
  Serial.print(yMax);
  Serial.println();
  
  Serial.print("zMin=");
  Serial.print(zMin);
  Serial.print(", zMax=");
  Serial.print(zMax);
  Serial.println();
  
  Serial.println("------------------------");
}

boolean checkMotion(){
  boolean tempB=false;
  xVal = analogRead(accelX);
  yVal = analogRead(accelY);
  zVal = analogRead(accelZ);
  
  if(xVal >(xMax+tolerance)||xVal < (xMin-tolerance)){
  tempB=true;
  Serial.print("X Failed = ");
  Serial.println(xVal);
  }
  
  if(yVal >(yMax+tolerance)||yVal < (yMin-tolerance)){
  tempB=true;
  Serial.print("Y Failed = ");
  Serial.println(yVal);
  }
  
  if(zVal >(zMax+tolerance)||zVal < (zMin-tolerance)){
  tempB=true;
  Serial.print("Z Failed = ");
  Serial.println(zVal);
  }
  if(!tempB) {
    Serial.println("Accelerometer check succeeded!");
  }
  return tempB;
 }
