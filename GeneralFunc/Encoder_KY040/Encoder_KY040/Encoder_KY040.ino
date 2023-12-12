#define ENCODER_CLK 25
#define ENCODER_DT 32
#define ENCODER_SW 33

int counter = 0;
bool clkw = false; /* counter-clockwise direction*/
uint8_t lastStateCLK;
uint8_t currentStateCLK;
unsigned long lastPush = 0;
unsigned long buttonPushCounter = 0;
int upper_limit = 250;
void cLK_ISR()
{
  if(digitalRead(ENCODER_DT) == LOW)
  {
    clkw = true;
    if(++counter > upper_limit) counter = upper_limit;
  }
  else
  {
    clkw = false;
    if(--counter < 0) counter = 0;
  }
  Serial.print("counter: "); Serial.println(counter);
}

void buttonPush(unsigned long* buttonPushCounter)
{
  uint8_t btnState = digitalRead(ENCODER_SW);
  if(btnState == LOW)
  {
    if(millis() - lastPush < 500)
    {
      return;
    }
    lastPush = millis();
    (*buttonPushCounter)++;
    Serial.println("button is pushed!");
  } 
}

void setup() {
  Serial.begin(115200);
  Serial.println("Test ...");
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  attachInterrupt(ENCODER_CLK, cLK_ISR, RISING);
}

void loop() {
  buttonPush(&buttonPushCounter);
}
