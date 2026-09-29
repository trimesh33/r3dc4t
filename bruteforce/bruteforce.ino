int n_delay = 100;

volatile bool no = false;
static int prev = 2;

void plus(int n) {
  for(int i = 0; i < n; i++) {
    switch((i+prev)%4) {
      case 0: pinMode(3, 1); break;
      case 1: pinMode(2, 1); break;
      case 2: pinMode(3, 0); break;
      case 3: pinMode(2, 0); break;
    }
    delay(n_delay);
  }
  prev += n;
}

void press() {
  pinMode(4, 1);
  delay(50);
  pinMode(4, 0);
  delay(50);
}

void flush_code(int n) {
  for (int i = 0; i < 4; ++i) {
    plus(n % 10);
    press();
    n /= 10;
  }
}

void bruteforce() {
  for (int i = 0; i < 10000; ++i) {
    reset_a();
    Serial.println(i);
    flush_code(i);
    delay(300);
      
    PCICR = (1 << PCIE2);
    PCMSK2 = (1<<5);

    int32_t timeout = millis();
    while(!no){
      if(millis() - timeout > 1000) {
        Serial.println("<- right");
        break;
      }
    }
    PCICR = 0;
    PCMSK2 = 0;
    
    no = false;  
  }
}

ISR(PCINT2_vect) {
  no = 1;
}

void reset_a() {
  prev = 2;
  pinMode(3, 1);
  pinMode(2, 1);

  pinMode(6, 1);
  delay(n_delay);
  pinMode(6, 0);
  delay(200);
}

void setup() {  
  
  Serial.begin(115200);


  reset_a();

  bruteforce();


void loop() {

}
