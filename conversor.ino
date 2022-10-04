
//Definição das portas
int ledAzul = 13; 
int ledAmarelo = 12; 
int buttonUnidade = 9;
int buttonDezena = 10;
int buttonCentena = 11;
int buttonConverter = 8;
int buttonReset = 7;

//Variáveis
int unidade = 0;
int dezena = 0;
int centena = 0;
int decimal = 0;

//Vetores
int binario[9];
int Pinos[] = {A0, A1, A2, A3, A4, A5, 6, 5, 4, 3}; 
int aux;
int PinoArdu = 0;

//Função que reseta
void (*funcReset)() = 0;

void setup() {
    Serial.begin(9600);
  
    pinMode(ledAzul, OUTPUT);
    pinMode(buttonUnidade, INPUT_PULLUP); 
    pinMode(buttonDezena, INPUT_PULLUP);
    pinMode(buttonCentena, INPUT_PULLUP);
    pinMode(buttonConverter, INPUT_PULLUP);
  	pinMode(buttonReset, INPUT_PULLUP);
  	
  	//Define os espaços dos leds como OUTPUT
    for (int PinoArdu = 0; PinoArdu <= 9; PinoArdu++) {
        pinMode(Pinos[PinoArdu], OUTPUT);
    }
}

void loop(){
  	
    digitalWrite(ledAzul, HIGH);
  	//TESTE LEDS
    /*digitalWrite(ledAmarelo, LOW);
  	digitalWrite(Pinos[0], HIGH);
  	digitalWrite(Pinos[1], HIGH);
  	digitalWrite(Pinos[2], HIGH);
    digitalWrite(Pinos[3], HIGH);
    digitalWrite(Pinos[4], HIGH);
    digitalWrite(Pinos[5], HIGH);
    digitalWrite(Pinos[6], HIGH);
    digitalWrite(Pinos[7], HIGH);
  	digitalWrite(Pinos[8], HIGH);
  	digitalWrite(Pinos[9], HIGH);
  	digitalWrite(Pinos[10], HIGH);*/
  
    //UNIDADE
    if (digitalRead(buttonUnidade) == LOW){
    digitalWrite(ledAmarelo, HIGH);
    unidade++;
    while (digitalRead(buttonUnidade) == LOW);
    delay(100);
    }
  
    //DEZENA
    if (digitalRead(buttonDezena) == LOW){
        digitalWrite(ledAmarelo, HIGH);
        dezena += 10;
        while (digitalRead(buttonDezena) == LOW);
        delay(100);
    }
  
    //CENTENA
    if (digitalRead(buttonCentena) == LOW){
        digitalWrite(ledAmarelo, HIGH);
        centena += 100;
        while (digitalRead(buttonCentena) == LOW);
        delay(100);
    }
  	
  	//Verificação dos valores no serial
    decimal = unidade + dezena + centena;
    Serial.println(decimal);
  	delay(200);
    
    //Começa a conversão
    if (digitalRead(buttonConverter) == LOW){ //Quando o botão é apertado
        Serial.println("INICIANDO A CONVERSÃO");
        for(int aux = 9; aux >= 0; aux--){
            if(decimal % 2 == 0){
                binario[aux] = 0;
            }else{
                binario[aux] = 1;
            }
            decimal = decimal / 2;
        }
      	//Acende os leds de acordo com o vetor binario
        for(int aux = 0; aux <= 9; aux++){
          	if(binario[aux] == 1){
  				digitalWrite(Pinos[aux], HIGH);
            }
    	}
    }
  	//Apaga os leds e reseta a memória quando apertado o botão reset
  	if (digitalRead(buttonReset) == LOW){
      	for(int aux = 0; aux <= 9; aux++){
  			digitalWrite(Pinos[aux], LOW);
    	}
      	digitalWrite(ledAzul, LOW);
     	delay(50);
        funcReset();	
    }
}