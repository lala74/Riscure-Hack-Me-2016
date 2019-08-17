#define MOLE_NUM_PIN      13
#define TIME_OUT          55

volatile bool is_game_starting = true;
volatile bool show_one = false;
volatile bool flag_hit_mole = false;
volatile int num_serial_available = 0;

String str = "";
volatile int currState = 0;
volatile int oldState = 0;
volatile int mole_num = 0;
volatile int time_between_2_pics = 0;
volatile int a = 0;

volatile int index = 0;

volatile bool mole_correct[7] = {false, false, false, false, false, false, false};
volatile int num_mole_try[7] = {2,2,2,2,2,2,2};

void hit_mole(int mole_number) {
  digitalWrite(mole_number, HIGH);
  delay(50);
  digitalWrite(mole_number, LOW);
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(19200);
  Serial.setTimeout(20);
  pinMode(MOLE_NUM_PIN, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
 
  if (Serial.available() > 0){
    if (num_serial_available == 0) {
      str = Serial.readString();
      index = str.indexOf("<Enter>");
      if(index > 0) {
        Serial.print("\n\r");
        is_game_starting = true;
        flag_hit_mole = false;
        if (mole_correct[mole_num] == false) {
          if (num_mole_try[mole_num] == 12) {
            num_mole_try[mole_num] = 2;
          } else {
            num_mole_try[mole_num]++;
          }
        }
      } else {
        flag_hit_mole = true;
        mole_correct[mole_num] = true;
      }
      mole_num = 0;
    }
    if (flag_hit_mole == false) {
      num_serial_available++;
    }
    if (num_serial_available == 3) {
      num_serial_available = 0;
    }
  }
  
  if (is_game_starting == true) {
    currState = digitalRead(MOLE_NUM_PIN);
    if(currState != oldState) {
    // There is a change of state pin
      oldState = currState;
      time_between_2_pics = 0;
      show_one = false;
      if (currState == 0) {
      // The change from 1 -> 0
        mole_num++;
      }
    }
    if (time_between_2_pics > TIME_OUT) {
      if (show_one == false) {
        switch (mole_num)
        {
          case 1:
          {
            hit_mole(num_mole_try[1]);
          }
            break;
          case 2:
          {
            hit_mole(num_mole_try[2]);
          }
            break;
          case 3:
          {
            hit_mole(num_mole_try[3]);
          }
            break;
          case 4:
          {
            hit_mole(num_mole_try[4]);
          }
            break;
          case 5:
          {
            hit_mole(num_mole_try[5]);
          }
            break;
          case 6:
          {
            hit_mole(num_mole_try[6]);
          }
            break;          
        }
        show_one = true;
      }
    }
    time_between_2_pics++;
  }
  delay(1);
}
