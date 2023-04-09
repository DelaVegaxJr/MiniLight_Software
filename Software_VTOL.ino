#include <SPI.h>
#include <SD.h>
#include "ABlocks_DHT.h"

double CalidadAire;
double Gases;
double alcohol;
double contador;
double temperatura;
double humedad;
File sd_file;
DHT dht26(26,DHT11);

void fnc_sd_print_esp32ks(String _f, String _t, boolean _nl){
	sd_file = SD.open(String("/")+_f, FILE_APPEND);
	if(sd_file){
		if(_nl)sd_file.println(_t);
		else sd_file.print(_t);
		sd_file.close();
	}
}

void setup()
{
  	pinMode(4, INPUT);
	pinMode(2, INPUT);
	pinMode(35, INPUT);
	pinMode(26, INPUT);

	Serial.begin(9600);
	Serial.flush();
	while(Serial.available()>0)Serial.read();

	SPIClass *spi_hspiSD = new SPIClass(HSPI); spi_hspiSD->begin(15, 32, 33, -1); SD.begin(-1, *spi_hspiSD, 40000000); //integrated SD card
	dht26.begin();

	if (SD.exists(String("/")+String("datalog.csv"))) {
		SD.remove(String("/")+String("datalog.csv"));
	}

	fnc_sd_print_esp32ks(String("datalog.csv"),String(String("CONTADOR")+String("MQ135")+String("MQ2")+String("MQ3")),true);
	contador = 0;

}


void loop()
{
	yield();

  	CalidadAire = analogRead(4);
  	Gases = analogRead(2);
  	alcohol = analogRead(35);
  	alcohol = dht26.readTemperature();
  	alcohol = dht26.readHumidity();
  	Serial.println(String("Paquete:")+String(contador));
  	Serial.println(String("El nivel de gases es de:")+String(CalidadAire));
  	Serial.println(String("La calidad del aire es de:")+String(Gases));
  	Serial.println(String("El lvl de alcohol es:")+String(alcohol));
  	Serial.println(String("La tempt. es de:")+String(temperatura));
  	Serial.println(String("El lvl de alcohol es:")+String(humedad));
  	Serial.print(String("Calidad del Aire")); Serial.print("="); Serial.println(CalidadAire);
  	Serial.print(String("Gases")); Serial.print("="); Serial.println(Gases);
  	Serial.print(String("Alcohol")); Serial.print("="); Serial.println(alcohol);
  	Serial.print(String("Temperatura")); Serial.print("="); Serial.println(temperatura);
  	Serial.print(String("Humedad")); Serial.print("="); Serial.println(humedad);
  	contador = (contador + 1);
  	fnc_sd_print_esp32ks(String("datalog.csv"),String(String(contador)+String(";")+String(CalidadAire)+String(";")+String(Gases)+String(";")+String(alcohol)+String(";")),true);
  	delay(1000);

}