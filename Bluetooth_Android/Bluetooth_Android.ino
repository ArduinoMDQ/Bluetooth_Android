String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
const int PinSensorA=3;            // boton conectado al pin 4
const int PinSensorB=4;
const int PinSensorC=5;
const int PinRelayPuerta=6;

const int tiempoAntirebote =10;


int comandos=0;
int TiempoEnmascarado=30;
int TiempoApertura=10;

int cuenta =0;          //Guarda el numero de veces que el boton ha sido presionado
int estadoBotonA;
int estadoBotonAnteriorA;
int estadoBotonB;
int estadoBotonAnteriorB;
int estadoBotonC;
int estadoBotonAnteriorC;

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
    delay (1);
  }
  while (contador < tiempoAntirebote);
  return estado;
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
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
  pinMode(PinSensorA,INPUT); //declaramos el boton como entrada
  pinMode(PinSensorB,INPUT); //declaramos el boton como entrada
  pinMode(PinSensorC,INPUT); //declaramos el boton como entrada
  pinMode(PinRelayPuerta,OUTPUT);

   pinMode(13,OUTPUT);
   digitalWrite(13,LOW);
  inputString.reserve(100);
}

void loop () {
  
  estadoBotonA =digitalRead (PinSensorA);              //leemos el estado del boton
  estadoBotonB =digitalRead (PinSensorB);              //leemos el estado del boton
  estadoBotonC =digitalRead (PinSensorC);              //leemos el estado del boton
 
  
  if ((estadoBotonA  != estadoBotonAnteriorA)||(estadoBotonA==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorA)){   
         Serial.write ("A\r\n");         //checamos  si esta preionado y si lo esta
          delay(TiempoEnmascarado*1000);
   }
  }
   estadoBotonAnteriorA = estadoBotonA;      // guardamos el estado del boton
 
/*
   if ((estadoBotonB  != estadoBotonAnteriorB)||(estadoBotonB==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorB)){   
         Serial.write ("B\r\n");         //checamos  si esta preionado y si lo esta
          delay(TiempoEnmascarado*1000);
   }
  }
   estadoBotonAnteriorB = estadoBotonB;      // guardamos el estado del boton
  
 
   if ((estadoBotonC  != estadoBotonAnteriorC)||(estadoBotonC==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorC)){   
         Serial.write ("C\r\n");         //checamos  si esta preionado y si lo esta
          delay(TiempoEnmascarado*1000);
   }
  }
 
      estadoBotonAnteriorC = estadoBotonC;      // guardamos el estado del boton
  
  
  
  
  
  // Aca agrego la parte de datos seriales
   if (stringComplete) {
   // Serial.println(inputString); 
    
    if(inputString=="n\n"){
       digitalWrite(PinRelayPuerta,LOW);
       Serial.write ("n\r\n");         
       }
    if(inputString=="s\n"){
        digitalWrite(PinRelayPuerta,HIGH);
        Serial.write ("s\r\n");         
        }
    if(inputString=="o\n"){
        digitalWrite(PinRelayPuerta,HIGH);
        Serial.write ("s\r\n");         
         delay(TiempoApertura*1000);
         digitalWrite(PinRelayPuerta,LOW);
        Serial.write ("n\r\n");         
        }
   // clear the string:
    inputString = "";
    stringComplete = false;
    */
  }
  
  
  
}



