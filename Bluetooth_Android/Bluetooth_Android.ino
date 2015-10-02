#include <TimerOne.h>
int ledState = LOW;
static String inputString = "";         // a string to hold incoming data
static boolean stringComplete = false;  // whether the string is complete



const int PinSensorA=2;            // boton conectado al pin 4
const int PinSensorB=3;
const int PinSensorC=4;
const int PinSensorD=5;
const int PinRelayPuerta=6;
const int PinBluetoothReset=7;

const int tiempoAntirebote =10;


int comandos=0;
int TiempoEnmascarado=20;
int TiempoApertura=5;

static  int CONTADOR=0;
int cuenta =0;          //Guarda el numero de veces que el boton ha sido presionado
static int estadoBotonA=0;
static int memA=0;
static int estadoBotonAnteriorA=0;
static int estadoBotonB=0;
static int memB=0;
static int estadoBotonAnteriorB=0;
static int estadoBotonC=0;
static int memC=0;
static int estadoBotonAnteriorC=0;
static int estadoBotonD=0;
static int memD=0;
static int estadoBotonAnteriorD=0;

/*Función antirebote*/
boolean antirebote  (int pin ) {
int  contador =0;
boolean estado;            // guarda el estado del boton 
boolean estadoAnterior;    // guarda el ultimo estado del boton 

  do {
    estado = digitalRead (pin);
    if (estado != estadoAnterior ){  // comparamos el estado actual 
      contador = 0;                   // reiniciamos el contador 
      estadoAnterior = estado;
    }
    else{
      contador = contador +1;       // aumentamos el contador en 1
    }
    delay(1);
  }
  while (contador < tiempoAntirebote);
  return estado;
}

void serialEvent() {
  while (Serial.available()) {

    // get the new byte:
    char inChar = (char)Serial.read(); 
   //  Serial.println(inChar); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
   
    } 

    
  }
}

void setup (){                      
  Serial.begin(9600);   //Iniciamos la comunicacion serial
  pinMode(PinSensorA,INPUT); // Alarma de Intrusion
  pinMode(PinSensorB,INPUT); // alarma de Intrusion
  pinMode(PinSensorC,INPUT); // alarma de Apertura
  pinMode(PinRelayPuerta,OUTPUT);
  pinMode(PinBluetoothReset,OUTPUT);
  
 digitalWrite(PinBluetoothReset,HIGH);
 delay(100);
 digitalWrite(PinBluetoothReset,LOW);
 delay(100);
 digitalWrite(PinBluetoothReset,HIGH);
 digitalWrite(PinRelayPuerta,LOW);
  
 pinMode(13,OUTPUT);
 digitalWrite(13,HIGH);
 inputString.reserve(100);

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(blinkLED); // blinkLED to run every 0.15 seconds
 
}

void Funcion(char var){
  
  switch(var){


     case 'F':
     Serial.write ("f\r\n");//Fake alarm
    break;
    case 'L':
     Serial.write ("l\r\n");//Loop
    break;
    
    case 'E':
     Serial.write ("e\r\n");//conexion exitosa del bluetooth
    break;
    
    case 'B':
      Serial.write ("b\r\n");  // reset bluetooth
     // delay(100);
      digitalWrite(PinBluetoothReset,LOW);
      delay(100);
      digitalWrite(PinBluetoothReset,HIGH);
    break;

    case 'O':
      Serial.write ("o\r\n"); 
      CONTADOR=0;
      digitalWrite(PinRelayPuerta,HIGH);
   
     // delay(TiempoApertura*1000);
     // digitalWrite(PinRelayPuerta,LOW);//open Door Timer    
       break;
    
    default:
    break;    
    
    }
  
  inputString = "";
  stringComplete = false;
  }

void loop () {
   if (stringComplete) {
      
    Funcion(inputString[0]);}
    
  if (memA){   
      memA=0;
         Serial.write ("A\r\n");         //checamos  si esta preionado y si lo esta
         delay(TiempoEnmascarado*1000);
 
   }
   if (stringComplete) {
      
    Funcion(inputString[0]);}
    
 if (memB){   
      memB=0;
         Serial.write ("B\r\n");         //checamos  si esta preionado y si lo esta
         delay(TiempoEnmascarado*1000);
 
   }
  if (stringComplete) {
      
    Funcion(inputString[0]);}
    
 
    if (memC){   
      memC=0;
         Serial.write ("C\r\n");         //checamos  si esta preionado y si lo esta
         delay(TiempoEnmascarado*1000);
 
   }
  if (stringComplete) {
      
    Funcion(inputString[0]);}
    
  
    if (memD){   
      memD=0;
         Serial.write ("D\r\n");         //checamos  si esta preionado y si lo esta
         delay(TiempoEnmascarado*1000);
 
   }
    if (stringComplete) {
      
    Funcion(inputString[0]);}
    

 
  }


void blinkLED(void)
{
  if (ledState == LOW) {
    ledState = HIGH;
    
  
  estadoBotonA =digitalRead (PinSensorA);              //leemos el estado del boton
 
  if ((estadoBotonA  != estadoBotonAnteriorA)||(estadoBotonA==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorA)){   
      memA=1;
 
    }
  }
  estadoBotonAnteriorA = estadoBotonA;

   
  estadoBotonB =digitalRead (PinSensorA);              //leemos el estado del boton
 
  if ((estadoBotonB  != estadoBotonAnteriorB)||(estadoBotonB==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorB)){   
      memB=1;
 
    }
  }
  estadoBotonAnteriorB = estadoBotonB;

   
  estadoBotonC =digitalRead (PinSensorC);              //leemos el estado del boton
 
  if ((estadoBotonC != estadoBotonAnteriorC)||(estadoBotonC==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorC)){   
      memC=1;
 
    }
  }
  estadoBotonAnteriorC = estadoBotonC;

   
  estadoBotonD =digitalRead (PinSensorD);              //leemos el estado del boton
 
  if ((estadoBotonD  != estadoBotonAnteriorD)||(estadoBotonD==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorD)){   
      memD=1;
 
    }
  }
  estadoBotonAnteriorD = estadoBotonD;

  } else {
  
    ledState = LOW;
    
   CONTADOR++;
  if(CONTADOR==TiempoApertura){
    digitalWrite(PinRelayPuerta,LOW);//open Door Timer  
    }
  }
  digitalWrite(13,ledState);
    
}
