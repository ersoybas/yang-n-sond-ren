int stp = 6;  // 1.motor
int dir = 7;  // 1.motor
int ena = 5; // 1.motor

int stp1 = 3;  // 2.motor
int dir1 = 4;  // 2.motor
int ena1 = 2; // 2.motor

int fan = A0 ;

int sharp_on = A5; // nor:60-90 //don : 160-190
//int sharp_arka= A5;// nor:160-180

int msaniye = 140;


const int flame0 = 8;
const int flame1 = 9;
const int flame2 = 10;
const int flame3 = 11;
const int flame4 = 12;

int x = 3; //DONT CHANGE THIS
int f = 260; //donus acısı 180
int arka_sensor = A1;

void setup()
{

  Serial.begin(115200);
  pinMode(stp, OUTPUT);
  pinMode(stp1, OUTPUT);

  pinMode(dir, OUTPUT);
  pinMode(dir1, OUTPUT);

  pinMode(ena, OUTPUT);
  pinMode(ena1, OUTPUT);
  pinMode(fan, OUTPUT);
  digitalWrite(fan, HIGH);

  pinMode(flame0, INPUT);
  pinMode(flame1, INPUT);
  pinMode(flame2, INPUT);
  pinMode(flame3, INPUT);
  pinMode(flame4, INPUT);

  pinMode(arka_sensor, INPUT);
  while (1) {
  //Serial.println(analogRead(A5));

    int arka_sensor_state = digitalRead(A1);

    if (arka_sensor_state == 1 ) { //sağ yok

      for (int d = 0; d <= f; d++) {
      tatli_sag();
      delay(1);
        } 
        
        int p = 0;
        while (analogRead(A5) > 85) {
          delay(1);
          motor_ileri();
          p++;
            if (p == 625) 
            {
               break;
                }

      }


    }


    else if (arka_sensor_state == 0 && sharp_on_avg(4) < 300 ) { //sağ var ön yok
      motor_ileri();
    }

    else if (sharp_on_avg(4) > 300) { //sağ var önvar
      don_sol();

    }
    else {
      motor_dur();
    }
    //  else {
    //     motor_dur;
    //        fan_start();

    //   }


  }


}




void loop() {
  // read the input pin:
  int sensorState1 = digitalRead(A0);
  int sensorState2 = digitalRead(A1);
  int sensorState3 = digitalRead(A2);
  int sensorState4 = digitalRead(A3);
  int sensorState5 = digitalRead(A4);



}
/*int sharp_arka_avg(int n){
  int avg[n];
  int toplam;
 int sharp_arka_val;
  for (int i = 0; i < n; ++i)
  {
     avg[i]=analogRead(sharp_arka);

     toplam =toplam + avg[i];

  }

  return toplam/(n+1);

}
*/
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

int flameSensors(int n) {
  int avg0[n];
  int avg1[n];
  int avg2[n];
  int avg3[n];
  int avg4[n];
  int toplam;
  int flame_sensors_val;
  for (int i = 0; i < n; ++i)
  {
    avg0[i] = digitalRead(flame0);
    avg1[i] = digitalRead(flame0);
    avg2[i] = digitalRead(flame0);
    avg3[i] = digitalRead(flame0);
    avg4[i] = digitalRead(flame0);
    toplam = avg0[i] + avg1[i] + avg2[i] + avg3[i] + avg4[i];

  }

  return toplam / (n + 1);

}


void motor_geri() {

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

void motor_ileri() {

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
    digitalWrite(ena1, LOW);
    digitalWrite(dir1, LOW);
    digitalWrite(stp1, HIGH);
    delayMicroseconds(msaniye);
    digitalWrite(stp1, LOW);
    delayMicroseconds(msaniye);            
  }
  digitalWrite(ena, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(stp, HIGH);
  delayMicroseconds(msaniye);
  digitalWrite(stp, LOW);
  delayMicroseconds(msaniye);
  
}







