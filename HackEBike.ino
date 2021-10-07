
const int analogInPin = A1;  // analog input pin the reed sensor is attached to
const int digitalOutPin = 8; // pin giving signal to bike control unit

int sensorValue = 0;        // value read from the potentiometer
int outputValue = 0;        // value output to bike control unit (PWM, analog out)
long timer = 0;             // time when reed sensor gives signal
int diff = 0;               // difference of last two reed signals
boolean counter = false;    // true => give signal to control unit, false => dont give signal to control
boolean hyst = false;       // true => was fast before and went not slower than lower limit ("Speedmode active") 
			//false = was not fast before or went slower than lower limit("Speedmode not active")
int sum = 0;                //counter for every signal that was skipped


void setup() {
  Serial.begin(9600);		// initialize serial communications at 9600 bps:
}

void loop() {

  pinMode(digitalOutPin, OUTPUT);         // set pin as output

  while (analogRead(analogInPin) > 512) { // wait until reed sensor gives signal 
  }

  timer = millis();                       // get time of signal coming in
  //Serial.println(timer);

  while (analogRead(analogInPin) < 512) { // wait until reed sensor gives second signal
    //Serial.println(millis());

    if (millis()-timer > 8000) {               //enter in case long time between signals => bike is not moving

      for (int i = 0; i < sum; i++) {     //output signals fast that were not given to control unit during riding
        digitalWrite(digitalOutPin, HIGH); //standard on - wait - off of signal to bike control unit
        delay(1);
        digitalWrite(digitalOutPin, LOW);
        delay(10);                  
        //Serial.println("in for loop");
      }
      sum = 0;                             // reset counter
    }
    //Serial.println(millis());
  }
  diff = millis() - timer;               
  //Serial.println(diff);

  if (diff > 310) {                       // loop active when riding slower than 25km/h
    //Serial.println("0-25");
    digitalWrite(digitalOutPin, HIGH);    
    delay(1);                             
    digitalWrite(digitalOutPin, LOW);     
    //delay(50);
    hyst = false;
  }

  else if (310 >= diff && diff >= 250) {  // loop active when riding between 25km/h and 30km/h
    //Serial.println("mittelbereich");

    if (hyst == false) {                  // depending on "history" of ride, here Speedmode is not active
      //Serial.println("25-30, not been fast before");
      digitalWrite(digitalOutPin, HIGH);
      delay(1);
      digitalWrite(digitalOutPin, LOW);
      //delay (50);
    }

    else {                                // Speedmode active
      //Serial.println("25-30, hack active");

      if (counter == true) {              // "pass" signal from reed sensor to control unit
        //Serial.println("pass");
        digitalWrite(digitalOutPin, HIGH);
        delay(1);
        digitalWrite(digitalOutPin, LOW);
        //delay(50);
        
        counter = false;
      }

      else {                              // dont "pass"
        //Serial.println("dont pass");
        //Serial.println("25-30 sum");
        counter = true;                   // change so next time signal will be passed
        sum ++;                           // count each "not pass", to output "lost" signals later when bike is in standstill
        //Serial.println("25-30 sum");
        //delay (50);
      }
    }
  }

  else  {                                 // loop active when riding fast than 30km/h
    //Serial.println("30+");

    if (counter == true) {                // like above
      //Serial.println("pass");
      digitalWrite(digitalOutPin, HIGH);
      delay(1);
      digitalWrite(digitalOutPin, LOW);
      //delay(50);
      counter = false;
    }

    else {
      //Serial.println("dont pass");
      counter = true;
      sum ++;
      //Serial.println("30+ sum");
      //delay (50);
    }
    hyst = true;                          // set, so when going 25-30, speedmode is active
  }
  //Serial.println(sum);

}

