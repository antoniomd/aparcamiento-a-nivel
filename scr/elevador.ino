/*
  Aparcamiento a nivel

  Este programa permite el control de un ascensor para un garaje en una casa.
  El programa permitira que un motor de c.c. controle el movimiento un ascensor.
  Mediante un botón en cada planta se llamará al ascensor y con el botón 0 o 1 situado en el ascensor se 
  seleccionará el piso donde ir. Unos finales de carrera permitirán conocer el piso donde se encuentra el 
  ascensor.

  El circuito:
    - botones.
      Se usarán las entradas 3, 4, 5 y 6.

    - finales de carrera.
      Se usarán las entradas 7 y 8.

    - Motor c.c.
      Se usará la salida 9 para el Enable que regulará la velocidad del motor (0-255).
      Se usarán las salidas 10 y 11 para la dirección subida y bajada respectivamente.

  Created 11 de Junio de 2020
  By Antonio Molina Domínguez
  Modified 
  By

  https://github.com/antoniomd/aparcamiento-a-nivel
*/

// Las constantes no cambiarán. Son usadas para configurar los pines:
const int level0Button = 3;     // Entrada del botón de llamada del ascensor del Nivel 0
const int level1Button = 4;     // Entrada del botón de llamada del ascensor del Nivel 1
const int upButton = 5;         // Entrada del botón de subir del ascensor
const int downButton = 6;       // Entrada del botón de bajar del ascensor
const int level0State = 7;      // Final de carrera que indica que está en la planta 0
const int level1State = 8;      // Final de carrera que indica que está en la planta 1
const int EnableMotor = 9;      // Salida para habilitación del motor
const int upMotor = 10;         // Motor en marcha para subida
const int downMotor = 11;       // Motor en marcha para bajada

// Las variables cambiarán.
int elevatorState;            // Variable que indica la posición del ascensor
int speedMotor;               // Fija la velocidad del motor que se configurá con EnableMotor

void setup() {
  // Declaro los botones como entradas:
  pinMode(level0Button, INPUT);
  pinMode(level1Button, INPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  // Declaro los finales de carrera como entradas:
  pinMode(level0State, INPUT);
  pinMode(level1State, INPUT);
  // Declaro las salidas de motor como salidas:
  pinMode(EnableMotor, OUTPUT);
  pinMode(upMotor, OUTPUT);
  pinMode(downMotor, OUTPUT);
}

void loop() {
  // Compruebo el estado en el que se encuentran los botones:
  level0ButtonState = digitalRead(level0Button);
  level1ButtonState = digitalRead(level1Button);
  upButtonState = digitalRead(upButton);
  downButtonState = digitalRead(downButton);
  // Compruebo donde se encuentra el ascensor:
  if (level0State == 1) elevatorState = 0;        // El ascensor se encuentra en la planta 0
  else if (level1State == 1) elevatorState = 1;   // El ascensor se encuentra en la planta 1
  else elevatorState = 2;                         // El ascensor se encuentra en una posición intermedia
  // Si se pulsa algún botón para bajar y el ascensor no está en la planta 0 se mueve
  if ((level0ButtonState == 1 || downButtonState == 1) && elevatorState != 0) elevatorGoDown();
  // Si se pulsa algún botón para subir y el ascensor no está en la planta 1 se mueve
  else if (level1ButtonState == 1 || upButtonState == 1) && elevatorState != 1) elevatorGoUp();
  // Si no se pulsa ningún botón o el ascensor está en la posición requerida se detiene
  else elevatorStop();
}

void elevatorGoDown() {
  analogWrite(ENABLE,speedMotor);   // Paro del upMotor
  digitalWrite(downMotor,LOW);      // Paro de la dirección subir
  digitalWrite(upMotor,HIGH);       // Paro de la dirección bajar
}

void elevatorGoDown() [
  analogWrite(ENABLE,speedMotor);   // Paro del upMotor
  digitalWrite(downMotor,HIGH);     // Paro de la dirección subir
  digitalWrite(upMotor,LOW);        // Paro de la dirección bajar
]

void elevatorStop() {
  analogWrite(ENABLE,LOW);          // Paro del upMotor
  digitalWrite(downMotor,LOW);      // Paro de la dirección subir
  digitalWrite(upMotor,LOW);        // Paro de la dirección bajar
}