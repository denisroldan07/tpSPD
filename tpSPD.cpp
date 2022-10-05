#define BOTON_INICIO 3
#define BOTON_RESET 2
#define MILISEGUNDOS 1000
#define MAX_SEGUNDOS 1023

//  FIN DEFINES //

int pines[]={13,12,11,10,9,8,7,6,5,4};
int maxLeds = 10;

// HEADER DE FUNCIONES //

// bool pasoUnSegundo
// Verifica si paso el tiempo pasado por parametro.
// @param segundo - tiempo que tiene que pasar
// Retorna true si paso el tiempo pasado por parametro , false en otro caso
bool pasoUnSegundo(unsigned int segundo);

// void setPines
// Setea los pines a utilizar en el proyecto
void setPines();

/// void mostrarContadorDeSegundosEnBinario
/// Muestra en los leds el tiempo que paso en el contador de segundos 
/// @param contadorSegundos - Numero que se va a convertir a binario
/// @param pines - Array donde estan los pines seteados
void mostrarContadorDeSegundosEnBinario(int contadorSegundos, int pines[]);

// FIN HEADER DE FUNCIONES //

void setup(){
    setPines();
    Serial.begin(9600);
}

int contadorSegundos = 0;
int botonStartAntes = 0;
int botonRestartAntes = 0;
int valorGuardadoEnPausa = 0;
unsigned long millisAntes;
bool pausa = true;

void loop(){
    int botonStartAhora = digitalRead(BOTON_INICIO);
    int botonRestartAhora = digitalRead(BOTON_RESET);

    //Si aprieto el boton de inicio y este no estaba ya prendido
    if(botonStartAhora == 1 && botonRestartAntes == 0){
    //cambio el valor de verdad de la variable pausa
    pausa = !pausa;
    // si al cambiar el valor de pausa este efectivamente esta en pausa entonces
    // entonces guardo la cantidad de milisegundos transcurrida
    // que no es mas que la diferencia en los milisegundos transcurridos menos los millis que transcurrieron hasta ese momento
        if(pausa){
            valorGuardadoEnPausa = millis() - millisAntes;   
        }else{
            millisAntes = millis() - valorGuardadoEnPausa;
        }
    }

    if(botonRestartAhora == 1 && botonRestartAntes == 0){
        contadorSegundos = 0;
        millisAntes = millis();
    } 

  //CRONOMETRO
  // si el cronometro esta corriendo y ya paso un segundo , sumo 1 al contador de segundos 
  if (!pausa && pasoUnSegundo(MILISEGUNDOS)){
    contadorSegundos++;
  // si no pasaron 1023 segundos entonces paso a binario el contador de segundos , muestro el numero binario en los leds y lo muestro en consola 
    if (contadorSegundos < MAX_SEGUNDOS + 1) {
	mostrarContadorDeSegundosEnBinario(contadorSegundos,pines);
  // si llega al maximo reinicio el contador
    } else if (contadorSegundos == MAX_SEGUNDOS + 1) {
      contadorSegundos = 0;
    }  
  }

  botonStartAntes = botonStartAhora;
  botonRestartAntes = botonRestartAhora;
  delay(5); 
}


void mostrarContadorDeSegundosEnBinario(int contadorSegundos, int pines[]){
    for(int i = 0; i < maxLeds; i++){
      digitalWrite(pines[i],bitRead(contadorSegundos,i));
    }
}
bool pasoUnSegundo(unsigned int segundo){
  unsigned long millisAhora = millis();
  
  if (millisAhora - millisAntes >= segundo) {
    millisAntes = millisAhora;
  	return true;
  }
  return false;
}
void setPines(){
    pinMode(BOTON_INICIO,INPUT);
    pinMode(BOTON_RESET,INPUT);
    for(int i = 0;i < maxLeds;i++){
        pinMode(pines[i],OUTPUT);
    }
}