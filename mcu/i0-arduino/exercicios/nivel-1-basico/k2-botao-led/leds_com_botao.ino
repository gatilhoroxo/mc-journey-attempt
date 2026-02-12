
//feito no arduino IDE
#define led1 9 //vermelho
#define led2 10 //amarelo
#define led3 11 //verde
#define ledPin 12
#define buttonPin 13

//array com diferentes delays (tempo entre piscadas)
int delays[] = {2000, 1000, 500}; //em milissegundos
int numDelays = sizeof(delays) / sizeof(delays[0]);
int currentDelayIndex = 0;

static bool ledState = LOW;
bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void ledsFadding();
void botaoConfig();
void piscaLed();
void botaoToggle();

void setup() {
  //Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  ledsFadding();
  botaoConfig();
  piscaLed();
  //botaoToggle();
}

void 
ledsFadding(){
  static int brilho = 0;
  static int fadeAmount = 1;
  static unsigned long previousMillis = 0;
  const unsigned long interval = 10; // tempo entre atualizações

  if (millis() - previousMillis >= interval) {
    previousMillis = millis();

    // Atualiza o brilho dos três LEDs
    analogWrite(led1, brilho);
    analogWrite(led2, brilho);
    analogWrite(led3, brilho);

    // Incrementa ou decrementa
    brilho += fadeAmount;

    // Inverte a direção quando chega nos limites
    if (brilho <= 0 || brilho >= 255) {
      fadeAmount = -fadeAmount;
    }
  }
}

void 
botaoConfig(){
  bool reading = digitalRead(buttonPin);
  //detecta mudança de estado com debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    //verifica borda de subida (botão foi pressionado)
    static bool buttonState = LOW; // estado debounced

    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        currentDelayIndex = (currentDelayIndex + 1) % numDelays;
        //Serial.println("botao apertado e solto");
      }
    }
  }
  lastButtonState = reading;
}

void 
piscaLed(){
  static unsigned long lastBlinkTime = 0;
  static bool ledState = LOW;

  //pisca o LED com o delay atual
  if (millis() - lastBlinkTime >= delays[currentDelayIndex]) {
    lastBlinkTime = millis();
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}

void 
botaoToggle() {
  bool reading = digitalRead(buttonPin); //leitura atual do botão

  if (reading != lastButtonState) {
    lastDebounceTime = millis();         //reinicia o tempo de debounce
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    //verifica se houve borda de subida (pressionamento)
    static bool buttonState = LOW; // estado debounced
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ledState = !ledState;              //inverte o estado do LED
        digitalWrite(ledPin, ledState);
      }
    }
  }
  lastButtonState = reading;             // Atualiza o estado do botão
}
