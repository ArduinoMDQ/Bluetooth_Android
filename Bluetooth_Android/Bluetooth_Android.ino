String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

const int PinSensorA=2;            // boton conectado al pin 4
const int PinSensorB=3;
const int PinSensorC=4;
const int PinSensorD=5;
const int PinRelayPuerta=6;
const int PinBluetoothReset=7;

const int tiempoAntirebote =10;


int comandos=0;
int TiempoEnmascarado=20;
int TiempoApertura=10;

int cuenta =0;          //Guarda el numero de veces que el boton ha sido presionado
int estadoBotonA;
int estadoBotonAnteriorA;
int estadoBotonB;
int estadoBotonAnteriorB;
int estadoBotonC;
int estadoBotonAnteriorC;
int estadoBotonD;
int estadoBotonAnteriorD;

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
      digitalWrite(PinRelayPuerta,HIGH);
      digitalWrite(13,LOW);
      delay(TiempoApertura*1000);
      digitalWrite(PinRelayPuerta,LOW);//open Door Timer    
      digitalWrite(13,HIGH);
    break;
    
    default:
    break;    
    
    }
  
  inputString = "";
  stringComplete = false;
  }

void loop () {
  
  estadoBotonA =digitalRead (PinSensorA);              //leemos el estado del boton
 
  if ((estadoBotonA  != estadoBotonAnteriorA)||(estadoBotonA==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorA)){   
         Serial.write ("A\r\n");         //checamos  si esta preionado y si lo esta
          digitalWrite(13,LOW);
          delay(TiempoEnmascarado*1000);
          digitalWrite(13,HIGH);
   }
  }
   estadoBotonAnteriorA = estadoBotonA;      // guardamos el estado del boton

  
  estadoBotonB =digitalRead (PinSensorB);              //leemos el estado del boton
 

   if ((estadoBotonB  != estadoBotonAnteriorB)||(estadoBotonB==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorB)){   
         Serial.write ("B\r\n");         //checamos  si esta preionado y si lo esta
          digitalWrite(13,LOW);
          delay(TiempoEnmascarado*1000);
          digitalWrite(13,HIGH);
   }
  }
   estadoBotonAnteriorB = estadoBotonB;      // guardamos el estado del boton
  
  estadoBotonC =digitalRead (PinSensorC);              //leemos el estado del boton
 
  
   if ((estadoBotonC  != estadoBotonAnteriorC)||(estadoBotonC==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorC)){   
         Serial.write ("C\r\n");         //checamos  si esta preionado y si lo esta
            digitalWrite(13,LOW);
          delay(TiempoEnmascarado*1000);
          digitalWrite(13,HIGH);
   }
  }
 
      estadoBotonAnteriorC = estadoBotonC;      // guardamos el estado del boton
  
  estadoBotonD =digitalRead (PinSensorD);              //leemos el estado del boton
 
  
   if ((estadoBotonD  != estadoBotonAnteriorD)||(estadoBotonD==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (PinSensorD)){   
         Serial.write ("D\r\n");         //checamos  si esta preionado y si lo esta
            digitalWrite(13,LOW);
          delay(TiempoEnmascarado*1000);
          digitalWrite(13,HIGH);
   }
  }
 
      estadoBotonAnteriorD = estadoBotonD;      // guardamos el estado del boton
     if (stringComplete) {
      
    Funcion(inputString[0]);}

   
  }


