#include <Arduino.h>
#include <SevenSeg.h>

#include <Wire.h>
#include <Time.h>


#include <RTCLib.h>

#define TEMPO_ATUALIZACAO 10

// RTC = Real Time Clock
// Conectar SCL (RTC) em A5 (Arduino) e /SDA (RTC) em A4 (Arduino)

// Relógio de Tempo Real
RTC_DS1307 RTC;

// Sete Segmentos 4 digitos
SevenSeg disp(2,3,4,5,6,7,8);

const int numOfDigits=4;
int digitPins[numOfDigits]={10,11,12,13};

// define Pin for Colon
int colonPin = A0;

// Duty Cyle to regulate brightness from 0 to 100%
int dc = 75;  // range 0 to 100

// define witch style of colon we use
char c = ':' ;

// Dados para o Relógio
int dia,mes,ano,hora,minuto,segundo,dia_semana,Tempo;
char semana[][4] = {"DOM","SEG","TER","QUA","QUI","SEX","SAB"};

void setup() {
	Serial.begin(9600);
	Wire.begin();
	RTC.begin();
	// Verifica se o modulo esta funcionando ou nao
	if (!RTC.isrunning())
	{
		Serial.println("O RTC não está executando");
		RTC.adjust(DateTime(__DATE__,__TIME__));
	}

	disp.setDigitPins(numOfDigits, digitPins);

	disp.setDPPin(4);
	disp.setColonPin(colonPin);
	disp.setDutyCycle(dc);
}

void loop() {

   DateTime now = RTC.now();
   dia = now.day();
   mes = now.month();
   ano = now.year();
   hora = now.hour();
   minuto = now.minute();
   segundo = now.second();
   dia_semana = now.dayOfTheWeek();

   if (dia < 10) {
	   Serial.print("0");
   }
   Serial.print(dia);
   Serial.print("/");
   if (mes < 10) {
	   Serial.print("0");
   }
   Serial.print(mes);
   Serial.print("/");
   Serial.println(ano);
   Serial.println(semana[dia_semana]);
   if (hora < 10) {
	   Serial.print("0");
   }
   Serial.print(hora);
   Serial.print(":");
   if (minuto < 10) {
	   Serial.print("0");
   }
   Serial.print(minuto);
   Serial.print(":");
   if (segundo < 10) {
	   Serial.print("0");
   }
   Serial.println(segundo);

   disp.writeClock(hora,minuto,c);
   delay(TEMPO_ATUALIZACAO);
}
