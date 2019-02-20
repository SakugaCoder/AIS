#include <LiquidCrystal.h>      //Inclusion de la librerio LiquidCrystal para el control de la LCD
LiquidCrystal pantalla(12, 8, 7, 6, 4, 2); //Configuarcion de la LCD  Rs = pin 12, Enabled = pin 8, db4 = pin 7, db5 = pin 5, db6= pin 4, db7 = pin 2.
//Nota se utilizarion entradas analogas y pines sin funcion pwm para controlar las valvulas, ya que estas trabajan con dos estados(enendido y apagado).
//Ademas de que la utilizcion de los pines pwm es inecesaria ya que estos se reservan para actividades como el control del tono del zumbador.
byte tiempoLCD;
boolean on = true;
boolean off = false;
boolean estadoLCD = on;

#define VALVULAEA1 A5   //A1 = arboles1   //Declaracion de todos los pines que controlaran las valvulas: VALVULA + E(electronica) + numero de valvula.
#define VALVULAEA2 A4   //A2 = arboles2
#define VALVULAEPL A3   //PL = plantas
#define VALVULAEC1 A2   //C1 = cesped 1
#define VALVULAEC2 A1   //C2 = cesped 2 
#define VALVULAETI A0   //TI =Tinaco     //Nota: esta constante es para el control de la valvula que llena el tinaco, actulmente esta en desuso pero se reserva para esta actividad.
#define BOMBA 13    // //pin que controlara el encendido de la bomba.
#define BOTON 3   //pin para leer el estado del boton
#define LCD 5   //pin para controlar el estado de la lcd
unsigned long tiempo;   //Variable a utilizar para cguardar el tiempo que lleva encendida la placa.
unsigned long tiempoAnterior = 0;   //variable de referencia para almacenar la diferencia del tiempo transcurrido y el anterior.

int segundos;  //Declaración de las variables que almacenaran los valores de los segundos, minutos, horas, dias, meses, años.
int minutos;
int horas;
int dias = 1;
int totalDias;

int segundosRiego;
int minutosRiego;
int duracionRiegoArboles = 1;
int duracionRiegoPlantas = 1;
int duracionRiegoPasto = 1;

int Lunes  = 1;
int Martes = 2;
int Miercoles = 3;
int Jueves = 4;
int Viernes = 5;
int Sabado =  6;
int Domingo = 7;
int diaActual = Lunes;
int horasRiegoManana = 2;    //Hora esbalecida en formato de 24 hrs
int minutosRiegoManana = 0;
int horasRiegoTarde = 9;
int minutosRiegoTarde = 0;
//byte diasRiego[]= {lunes, martes, miercoles, jueves, viernes, sabado, domingo};
int diasRiegoProgramados[] = {Lunes, Jueves, Domingo};

boolean entrar = true;
boolean salir = false;
boolean accion;

boolean estadoRiego;
boolean iniciado = true;
boolean finalizado = false;

//Declaración de las variables del control del estado del boton
int lecturaBoton;
int estadoBoton;
int estadoBotonAnterior = LOW;

//Declaración de la variable del tiempo o retardo para el control del estado del boton
unsigned long tiempoActivacion;

boolean EB;
byte CB;   //Variable para contar las veces que se a presionado el boton

int s;

void setup() {
  pinMode(VALVULAEA1, OUTPUT);   //configuarion de los pines que controlaran las valvulas y la bomba como salidas.
  pinMode(VALVULAEA2, OUTPUT);
  pinMode(VALVULAEPL, OUTPUT);
  pinMode(VALVULAEC1, OUTPUT);
  pinMode(VALVULAEC2, OUTPUT);
  pinMode(VALVULAETI, OUTPUT);
  pinMode(BOMBA, OUTPUT);
  pinMode(BOTON, INPUT);
  pinMode(LCD, OUTPUT);
  Serial.begin(9600);   //Inicializacionde la velocidad del puertos serie en 96600 baudios
  pantalla.begin(20, 4);
  pantalla.clear();
  pantalla.setCursor(5, 1);
  pantalla.print("Bienvenido");
  digitalWrite(VALVULAEA1, LOW);
  digitalWrite(VALVULAEA2, LOW);
  digitalWrite(VALVULAEPL, LOW);
  digitalWrite(VALVULAEC1, LOW);
  digitalWrite(VALVULAEC2, LOW);
  digitalWrite(BOMBA, LOW);
  digitalWrite(LCD, HIGH);
}

void loop() {
  tiempo = millis();    //obtiene el tiempo que lleva encendida la placa y lo almacena en lavariable tiempo.
  LeerEstadoBoton();

  if ((tiempo - tiempoAnterior) == 1000) { //Condicion utilizada para medir el tiempo es decir cada 1000 milisegundos trasncuriidos = 1 segundo y se almacenaran en variables estos valores.
    tiempoAnterior = tiempo;
    segundos++;

    if (estadoLCD == on) {
      tiempoLCD++;
    }

    if (tiempoLCD == 60 && estadoLCD == on) {
      estadoLCD = off;
      CB = 0;
      digitalWrite(LCD, LOW);
      Serial.println("LCD apagada por inactividad");
    }

    if (segundos == 60) {      
      segundos = 0;
      minutos++;
      pantalla.clear();
      pantalla.setCursor(0,0);
      pantalla.print("06/01/2017");
      if(horas > 9){
      pantalla.setCursor(15,0);
      pantalla.print(horas);
      }
      if(horas <= 9){
        pantalla.setCursor(15,0);
        pantalla.print("0");
        pantalla.print(horas);          
      }

      if(minutos < 9){
      pantalla.setCursor(17,0);
      pantalla.print(":0");
      pantalla.print(minutos);
      }

      if(minutos > 10){
      pantalla.setCursor(17,0);
      pantalla.print(":");
      pantalla.print(minutos);  
      }

      pantalla.setCursor(3,1);
      pantalla.print("Proximo riego:");
      //Proximo riego
      if((diaActual == Domingo && minutos > horasRiegoTarde) || (diaActual == Lunes && minutos < horasRiegoTarde)){
        Serial.println("Lunes a las:");
        pantalla.setCursor(2,2);
        pantalla.print("Lunes ");
      }

      if((diaActual == Lunes && minutos > horasRiegoTarde) || (diaActual == Martes || diaActual == Miercoles) || (diaActual == Jueves && minutos < horasRiegoTarde)){
        Serial.println("Jueves a las:");
        pantalla.setCursor(2,2);
        pantalla.print("Jueves ");
      }

      if((diaActual == Jueves && minutos > horasRiegoTarde) || (diaActual == Viernes || diaActual == Sabado) || (diaActual == Domingo && minutos < horasRiegoTarde)){
        Serial.println("Domingo a las :");
        pantalla.setCursor(2,2);
        pantalla.print("Domingo ");
      }
      
      if(minutos > horasRiegoManana && minutos <= horasRiegoTarde){
        Serial.println("21:00 pm");
        pantalla.print("21:00 pm");
      }

      if((minutos > horasRiegoTarde) || (minutos >= 0 && minutos <= horasRiegoManana)){
        Serial.println("07:00 am");
        pantalla.print("07:00 am");
      }
    }

    if (minutos == 60) {
      minutos = 0;
      horas++;
    }

    if (horas == 24) {
      horas = 0;
      dias++;
      diaActual = dias;
      totalDias++;

      if (totalDias == 49) {
        //Reset
      }

      if (dias == 8) {
        dias = 1;
        diaActual = dias;
      }
    }

    if (segundos == 10 && s != 1) {
      pantalla.setCursor(2, 1);
      pantalla.print("Sistema iniciado");
      s++;
    }

    Serial.print("segundos: "); Serial.print(segundos); Serial.print("    Minutos: "); Serial.print(minutos);
    Serial.print("    Horas: "); Serial.print(horas); Serial.print("    Dias: "); Serial.println(dias);

    //********************************************************************************************************************************************************************************************
    if (((diasRiegoProgramados[0] == diaActual || diasRiegoProgramados[1] == diaActual || diasRiegoProgramados[2] == diaActual) && ((horasRiegoManana == minutos && minutosRiegoManana == segundos)|| (horasRiegoTarde == minutos && minutosRiegoTarde == segundos))) || CB == 2) {
      estadoLCD = on;
      digitalWrite(LCD, HIGH);
      CB = 0;
      LeerEstadoBoton();
      estadoRiego = iniciado;
      accion = entrar;
      Serial.println("Riego iniciado");
      Serial.println("Riego Arboles iniciado");
      pantalla.clear();
      pantalla.setCursor(4, 0);
      pantalla.print("Iniciando...");
      pantalla.setCursor(4, 1);
      pantalla.print("Riego arboles");      
      while (estadoRiego == iniciado && CB != 2) {
        LeerEstadoBoton();
        digitalWrite(BOMBA, HIGH);

        //*********************************************************************************************************************************************************************************************
        for (int i = 1; i <= 2; i++) {
          if (i == 1) {
            digitalWrite(VALVULAEA1, HIGH);
          }
          else if (i == 2) {
            digitalWrite(VALVULAEA1, LOW);
            digitalWrite(VALVULAEA2, HIGH);

          }

          while (accion == entrar && CB != 2) {
            LeerEstadoBoton();
            if(CB == 2){
              segundosRiego = 0;
              minutosRiego = 0;
              break;
            }
            tiempo =  millis();
            if ((tiempo - tiempoAnterior) == 1000) {
              tiempoAnterior = tiempo;
              segundos++;
              segundosRiego++;
              Serial.print("Regando: ARBOLES          restante: "); Serial.println((duracionRiegoArboles*60) - segundosRiego);
              pantalla.clear();
              pantalla.setCursor(1, 0);
              if (i == 1) {
                pantalla.print("Riego de arboles(1)");
              }

              else if (i == 2) {
                pantalla.print("Riego de arboles(2)");
              }
              pantalla.setCursor(3, 2);
              pantalla.print("Finaliza en: "); pantalla.print((duracionRiegoArboles * 60) - segundosRiego);

              if (segundosRiego == 60) {
                minutosRiego++;
                segundosRiego = 0;
              }

              if (minutosRiego == duracionRiegoArboles) {
                accion = salir;
                segundosRiego = 0;
                minutosRiego = 0;
                if (i == 1) {
                  Serial.println("Riego de arboles finalizado");
                  pantalla.clear();
                  pantalla.setCursor(2, 1);
                  pantalla.print("Riego de arboles");
                  pantalla.setCursor(5, 2);
                  pantalla.print("Finalizado");
                }
              }
              if (segundos == 60) {
                minutos++;
                segundos = 0;
              }

              if (minutos == 60) {
                horas++;
                minutos = 0;
              }

              if (horas == 24) {
                dias++;
                horas = 0;
              }

              if (dias == 7) {
                dias = 1;
              }

            }
          }

          digitalWrite(VALVULAEA1, LOW);
          digitalWrite(VALVULAEA2, LOW);

          accion = entrar;
        }
        //********************************************************************************************************************************************************************************************
        accion = entrar;
        Serial.println("Riego iniciado");
        Serial.println("Regando: Plantas");
        pantalla.clear();
        pantalla.setCursor(4, 0);
        pantalla.print("Iniciando...");
        pantalla.setCursor(3, 2);
        pantalla.print("Riego plantas.");
        digitalWrite(VALVULAEPL, HIGH);

        while (accion == entrar && CB != 2) {
          LeerEstadoBoton();
          if(CB == 2){
            break;  //Salir del bucle
          }
          tiempo = millis();
          if ((tiempo - tiempoAnterior) == 1000) {
            tiempoAnterior = tiempo;
            segundos++;
            segundosRiego++;
            Serial.print("Regando PLANTAS         restante: "); Serial.println((duracionRiegoPlantas*60) - segundosRiego);
            pantalla.clear();
            pantalla.setCursor(2, 0);
            pantalla.print("Riego de plantas");
            pantalla.setCursor(3, 2);
            pantalla.print("Finaliza en: "); pantalla.print((duracionRiegoPlantas * 60) - segundosRiego);
            if (segundosRiego == 60) {
              minutosRiego++;
            }

            if (minutosRiego == duracionRiegoPlantas) {
              segundosRiego = 0;
              minutosRiego = 0;
              accion = salir;
              Serial.println("Riego de plantas terminado");
              pantalla.clear();
              pantalla.setCursor(2, 0);
              pantalla.print("Riego de plantas");
              pantalla.setCursor(5, 1);
              pantalla.print("Finalizado");
            }


            if (segundos == 60) {
              minutos++;
              segundos = 0;
            }

            if (minutos == 60) {
              horas++;
              minutos = 0;
            }

            if (horas == 24) {
              dias++;
              horas = 0;
            }

            if (dias == 7) {
              dias = 1;
            }

          }

        }        
        digitalWrite(VALVULAEPL, LOW);
        //********************************************************************************************************************************************************************************************
        accion = entrar;
        Serial.println("Riego iniciado");
        Serial.println("Regando PASTO");
        pantalla.clear();
        pantalla.setCursor(4, 0);
        pantalla.print("Iniciando...");
        pantalla.setCursor(4, 1);
        pantalla.print("Riego pasto.");        
        for (int i = 1; i <= 2; i++) {

          if (i == 1) {
            digitalWrite(VALVULAEC1, HIGH);
          }

          else if (i == 2) {
            digitalWrite(VALVULAEC1, LOW);
            digitalWrite(VALVULAEC2, HIGH);

          }
          while (accion == entrar && CB != 2) {
            LeerEstadoBoton();
            if(CB == 2){
              break;  //Salir del bucle
            } 
            tiempo = millis();
            if ((tiempo - tiempoAnterior) == 1000) {
              tiempoAnterior = tiempo;
              segundosRiego++;
              segundos++;
              Serial.print("Regando PASTO         restante: "); Serial.println((duracionRiegoPasto*60) - segundosRiego);
              pantalla.clear();
              pantalla.setCursor(2, 0);
              if (i == 1) {
                pantalla.print("Riego de pasto(1)");
              }

              if (i == 2) {
                pantalla.print("Riego de pasto(2)");
              }

              
              pantalla.setCursor(3, 2);
              pantalla.print("Finaliza en: "); pantalla.print((duracionRiegoPasto * 60) - segundosRiego);
              if (segundosRiego == 60) {
                minutosRiego++;
                segundosRiego = 0;
              }

              if (minutosRiego == duracionRiegoPasto) {
                segundosRiego = 0;
                minutosRiego = 0;
                accion = salir;
                if (i == 2) {
                  Serial.println("Riego de pasto finalizado");
                  pantalla.clear();
                  pantalla.setCursor(3, 0);
                  pantalla.print("Riego de pasto");
                  pantalla.setCursor(5, 1);
                  pantalla.print("Finalizado");
                }
              }

              if (segundos == 60) {
                minutos++;
                segundos = 0;
              }

              if (minutos == 60) {
                horas++;
                minutos = 0;
              }

              if (horas == 24) {
                dias++;
                horas = 0;
              }

              if (dias == 7) {
                dias = 1;
              }
            }
          }
          accion = entrar;
        }
        LeerEstadoBoton();
        if(CB == 2){ 
          break;  //Salir del bucle         
        }
        digitalWrite(VALVULAEC2, LOW);
        digitalWrite(BOMBA, LOW);
        estadoRiego = finalizado;
        Serial.println("Riego total finalizado");
        pantalla.clear();
        pantalla.setCursor(1, 1);
        pantalla.print("!Riego Finalizado");
      }
      if(CB == 2){
        digitalWrite(VALVULAEA1, LOW);
        digitalWrite(VALVULAEA2, LOW);
        digitalWrite(VALVULAEPL, LOW);
        digitalWrite(VALVULAEC1, LOW);
        digitalWrite(VALVULAEC2, LOW);
        digitalWrite(BOMBA, LOW);
        Serial.println("Riego cancelado");
        pantalla.clear();
        pantalla.setCursor(2, 1);
        pantalla.print("!Riego cancelado");
        CB = 0;
      }
      estadoLCD = off;
      digitalWrite(LCD, LOW);
    }
  }
}

void LeerEstadoBoton() {
  //Se realiza la lectura aprueba de rebote del boton
  lecturaBoton = digitalRead(BOTON);
  if (lecturaBoton != estadoBotonAnterior) { //Comprueba si hay un cambio de estado del boton.
    tiempoActivacion = millis();           //Si lo hay simplemente inicia una variable con un valor millis para iniciar el retardo.
  }

  if ((millis() - tiempoActivacion) >= 50) { //Si el tiempo - elTiempoActivacion = retardo(se a cumplido el tiempo especifiacdo.
    if (lecturaBoton != estadoBoton) { //Si la lectura es diferente al estado del boton, es decir varia de estadp LOW a HIGH y viceversa. El estado del boton es diferente.
      estadoBoton = lecturaBoton;     //El estado del boton es igual a la lectura.
      if (estadoBoton == HIGH && estadoLCD == on) {      //Cuando el estado del boton sea igual a HIGH.
        EB = on;                     //Manda señal de activación del boton.
        tiempoLCD = 0;
        CB++;
        Serial.println("Boton presionado");
      }

      if (estadoBoton == LOW) {
        EB = off;
      }

      if (estadoBoton == HIGH && estadoLCD == off) {
        estadoLCD = on;
        digitalWrite(LCD, HIGH);
        tiempoLCD = 0;
        Serial.println("LCD encendida");
      }
    }
  }
  estadoBotonAnterior = lecturaBoton;   //Se guarda el estado anterior del boton con el valor de la lectura.
}

