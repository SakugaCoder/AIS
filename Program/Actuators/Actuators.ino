#include <LiquidCrystal.h>      //Inclusion de la librerio LiquidCrystal para el control de la LCD
LiquidCrystal pantalla(12,8,7,6,4,2); //Configuarcion de la LCD  Rs = pin 12, Enabled = pin 8, db4 = pin 7, db5 = pin 5, db6= pin 4, db7 = pin 2.
                                      //Nota se utilizarion entradas analogas y pines sin funcion pwm para controlar las valvulas, ya que estas trabajan con dos estados(enendido y apagado).
                                      //Ademas de que la utilizcion de los pines pwm es inecesaria ya que estos se reservan para actividades como el control del tono del zumbador.

#define VALVULAEA1 A5   //A1 = arboles1   //Declaracion de todos los pines que controlaran las valvulas: VALVULA + E(electronica) + numero de valvula.
#define VALVULAEA2 A4   //A2 = arboles2
#define VALVULAEPL A3   //PL = plantas
#define VALVULAEC1 A2   //C1 = cesped 1
#define VALVULAEC2 A1   //C2 = cesped 2 
#define VALVULAETI A0   //TI =Tinaco     //Nota: esta constante es para el control de la valvula que llena el tinaco, actulmente esta en desuso pero se reserva para esta actividad.
#define BOMBA 13    // //pin que controlara el encendido de la bomba.

String instruccion;
String valorInstruccion;

boolean bucle = true;
unsigned long tiempo;

void setup(){
  pinMode(VALVULAEA1, OUTPUT);   //configuarion de los pines que controlaran las valvulas y la bomba como salidas.
  pinMode(VALVULAEA2, OUTPUT);
  pinMode(VALVULAEPL, OUTPUT);
  pinMode(VALVULAEC1, OUTPUT);
  pinMode(VALVULAEC2, OUTPUT);
  pinMode(VALVULAETI, OUTPUT);
  pinMode(BOMBA, OUTPUT);
  Serial.begin(9600);   //Inicializacionde la velocidad del puertos serie en 96600 baudios
  pantalla.begin(20,4);
  //Serial.println("Sistema iniciado");
  pantalla.clear();
  pantalla.setCursor(2,0);   // pantalla.setCursor(valorDeLaColumna(de 0 a 3 en este caso donde 0 es la columna 1),valorDeLaFila(de 0 a 19 donde 0 es la columna 1)
  pantalla.print("Sistema iniciado");
  digitalWrite(VALVULAEA1, LOW);
  digitalWrite(VALVULAEA2, LOW);
  digitalWrite(VALVULAEPL, LOW);
  digitalWrite(VALVULAEC1, LOW);
  digitalWrite(VALVULAEC2, LOW);
  digitalWrite(BOMBA, LOW);
}

void loop(){
  String valor;
  if(Serial.available()){
  while(Serial.available()){
    retardoSerial();
    bucle = true;
    char caracter= Serial.read();
    instruccion = instruccion + caracter;
  }
  String  areaInstruccion= instruccion.substring(0,2);

  if(areaInstruccion == "DI"){
      valorInstruccion = instruccion.substring(2);

      if(valorInstruccion == "LU"){
        Serial.println("Dia lunes");
        pantalla.clear();
        pantalla.setCursor(2,0);
        pantalla.print("Dia Lunes");
      }

      else if(valorInstruccion == "MA"){
        Serial.println("Dia martes");
        pantalla.clear();
        pantalla.setCursor(2,0);
        pantalla.print("Dia Martes");
      }

      else if(valorInstruccion == "MI"){
        Serial.println("Dia Miercoles");
        pantalla.clear();
        pantalla.setCursor(2,0);
        pantalla.print("Dia Miercoles");
      }

      else if(valorInstruccion == "JU"){
        Serial.println("Dia Jueves");
        pantalla.clear();
        pantalla.setCursor(2,0);
        pantalla.print("Dia Jueves");
      }

      else if(valorInstruccion == "VI"){
        Serial.println("Dia Viernes");
        pantalla.clear();
        pantalla.setCursor(2,0);
        pantalla.print("Dia Viernes");
      }

      else if(valorInstruccion == "SA"){
        Serial.println("Dia Sabado");
        pantalla.clear();
        pantalla.setCursor(2,0);
        pantalla.print("Dia Sabado");
      }

      else if(valorInstruccion == "DO"){
        Serial.println("Dia Domingo");
        pantalla.clear();
        pantalla.setCursor(2,0);
        pantalla.print("Dia Domingo");
      }
      

  }

  else if(areaInstruccion == "KE"){
    valorInstruccion = instruccion.substring(3);

    if(valorInstruccion == "1"){
      Serial.println("Caracter: 1");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: 1");
    }

    if(valorInstruccion == "2"){
      Serial.println("Caracter: 2");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: 2");
    }
    
    if(valorInstruccion == "3"){
      Serial.println("Caracter: 3");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: 3");
    }
    
    if(valorInstruccion == "4"){
      Serial.println("Caracter: 4");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: 4");
    }

    if(valorInstruccion == "5"){
      Serial.println("Caracter: 5");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: 5");
    }

    if(valorInstruccion == "6"){
      Serial.println("Caracter: 6");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: 6");
    }

    if(valorInstruccion == "7"){
      Serial.println("Caracter: 7");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: 7");
    }

    if(valorInstruccion == "8"){
      Serial.println("Caracter: 8");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: 8");
    }

    if(valorInstruccion == "9"){
      Serial.println("Caracter: 9");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: 9");
    }

    if(valorInstruccion == "0"){
      Serial.println("Caracter: 0");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: 0");
    }

    if(valorInstruccion == "A"){
      Serial.println("Caracter: A");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: A");
    }

    if(valorInstruccion == "B"){
      Serial.println("Caracter: B");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: B");
    }

    if(valorInstruccion == "C"){
      Serial.println("Caracter: C");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: C");
    }

    if(valorInstruccion == "D"){
      Serial.println("Caracter: D");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: D");
    }

    if(valorInstruccion == "*"){
      Serial.println("Caracter: *");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: *");
    }

    if(valorInstruccion == "#"){
      Serial.println("Caracter: #");
      pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Caracter: #");
    }
  }

  else if(areaInstruccion == "BO"){
    Serial.println("Boton OK Presionado");
    pantalla.clear();
      pantalla.setCursor(2,0);
      pantalla.print("Boton OK Presionado");
  }
  instruccion = "";
  }  
}

void retardoSerial(){
  tiempo = millis();
  while(bucle == true){  
    
    if((millis() - tiempo) >= 10){
      bucle = false;
    }
  } 
}


