#include <iostream>
using namespace std;
#include <stdio.h>
#include <cstdlib>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "includes/funciones.h"

int main(int argc, char **argv){
    iniciarAllegro();
    intro();
    menuPrincipal();
    mostrarTexto("hola", "fonts/DS-DIGI.TTF", 50, 50, 255, 255, "izq", 0, 0, 5);
    cerrarAllegro();

   return 0;
}
