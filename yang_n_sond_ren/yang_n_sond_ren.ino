int stp = 6;  // 1.motor
int dir = 7;  // 1.motor
int ena = 5; // 1.motor

int stp1 = 3;  // 2.motor
int dir1 = 4;  // 2.motor
int ena1 = 2; // 2.motor

int fan = A0 ;
int sharp_on = A5;
int arka_sensor = A1;

int msaniye = 140;

const int flame0 = 8;
const int flame1 = 9;
const int flame2 = 10;
//const int flame3 = 11;
//const int flame4 = 12;

int x = 3; //DONT CHANGE THIS
int f = 190; //donus acısı 180
int m = 5000;

void setup()
{

  Serial.begin(115200);

  pinMode(arka_sensor, INPUT);

  pinMode(stp, OUTPUT);
  pinMode(stp1, OUTPUT);

  pinMode(dir, OUTPUT);
  pinMode(dir1, OUTPUT);

  pinMode(ena, OUTPUT);
  pinMode(ena1, OUTPUT);

  pinMode(fan, OUTPUT);
  digitalWrite(fan, LOW);

  pinMode(flame0, INPUT);
  pinMode(flame1, INPUT);
  // pinMode(flame2, INPUT);
  //pinMode(flame3, INPUT);
  //pinMode(flame4, INPUT);

  //////////////////////////----------------------------------------////////////////////////////

  while (1) {

   // Serial.println(analogRead(A5));
    int flame0 = digitalRead(8);
    int flame1 = digitalRead(9);
    // int flame2 = digitalRead(10);
    int arka_sensor_state = digitalRead(A1);

    // || flame2 == 1
    if (flame0 == 1 || flame1 == 1 ) {
     
      fan_start();
      motor_dur();

      delay(3000);

    }
    else {
      fan_stop();
      if (arka_sensor_state == 1 ) {                                        //sağ yok

        for (int d = 0; d <= f; d++) {
          tatli_sag();
          delay(1);
        }

        int p = 0;
        while (analogRead(A5) > 50) {
          delay(1);
          motor_ileri();
          p++;

          if (p == 700)
          {
            break;
          }
        }
      }


      else if (arka_sensor_state == 0 && sharp_on_avg(4) < 300 ) {            //sağ var ön yok

        motor_ileri();

      }

      else if (sharp_on_avg(4) > 300) {                                       //önvar

        don_sol();

      }
      else {



      }
    }
  }
}


///////////////////////////////---------------------------------------////////////////////////////////

void loop() {

}

int sharp_on_avg(int n) {
  int avg[n];
  int toplam;
  int sharp_on_val;
  for (int i = 0; i < n; ++i)
  {

    avg[i] = analogRead(sharp_on);

    toplam = toplam + avg[i];

  }

  return toplam / (n + 1);

}

///////////////////////////-----------------------------------------------//////////////////////////

void motor_geri() {

  digitalWrite(ena, LOW);
  digitalWrite(ena1, LOW);

  digitalWrite(dir, LOW);
  digitalWrite(dir1, LOW);

  digitalWrite(stp, HIGH);
  digitalWrite(stp1, HIGH);
  delayMicroseconds(msaniye);

  digitalWrite(stp, LOW);
  digitalWrite(stp1, LOW);
  delayMicroseconds(msaniye);

}

void motor_ileri() {

  digitalWrite(ena, LOW);
  digitalWrite(ena1, LOW);

  digitalWrite(dir, HIGH);
  digitalWrite(dir1, HIGH);

  digitalWrite(stp, HIGH);
  digitalWrite(stp1, HIGH);
  delayMicroseconds(msaniye);

  digitalWrite(stp, LOW);
  digitalWrite(stp1, LOW);
  delayMicroseconds(msaniye);
}

void motor_dur() {

  digitalWrite(ena, HIGH);
  digitalWrite(ena1, HIGH);

}
void fan_start() {

  digitalWrite(fan, LOW);


}


void fan_stop() {

  digitalWrite(fan, HIGH);

}


void don_sol() {

  digitalWrite(ena, LOW);
  digitalWrite(ena1, LOW);

  digitalWrite(dir, LOW);
  digitalWrite(dir1, HIGH);

  digitalWrite(stp, HIGH);
  digitalWrite(stp1, HIGH);
  delayMicroseconds(msaniye);

  digitalWrite(stp, LOW);
  digitalWrite(stp1, LOW);
  delayMicroseconds(msaniye);

}

void tatli_sag() {

  // for (int a = 0; a < 8; a++) {
  for (int i = 0; i < x; i++) {
    digitalWrite(ena, LOW);
    digitalWrite(dir, HIGH);
    digitalWrite(stp, HIGH);
    delayMicroseconds(msaniye);
    digitalWrite(stp, LOW);
    delayMicroseconds(msaniye);
  }
  digitalWrite(ena1, LOW);
  digitalWrite(dir1, HIGH);
  digitalWrite(stp1, HIGH);
  delayMicroseconds(msaniye);
  digitalWrite(stp1, LOW);
  delayMicroseconds(msaniye);

}







