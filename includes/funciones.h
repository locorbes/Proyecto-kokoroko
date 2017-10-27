#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

const int ANCHO=640;
const int ALTO=480;
const float FPS=60;
ALLEGRO_DISPLAY *pantalla = NULL;
ALLEGRO_BITMAP  *imagen = NULL;
ALLEGRO_FONT *fuente = NULL;
ALLEGRO_EVENT_QUEUE *eventos = NULL;

//FUNCIÓN PARA INICIALIZAR ALLEGRO
int iniciarAllegro(){
    if(!al_init()){
      al_show_native_message_box(pantalla, "Error", "Error", "Fallo al iniciar allegro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
   if(!al_init_image_addon()) {
      al_show_native_message_box(pantalla, "Error", "Error", "Fallo al iniciar al_init_image_addon", NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
   pantalla = al_create_display(ANCHO, ALTO);

   if(!pantalla) {
      al_show_native_message_box(pantalla, "Error", "Error", "Fallo al iniciar pantalla", NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
   al_install_keyboard();
   return 1;
}
//FUNCIÓN PARA CARGA IMAGEN
int mostrarImagen(char *ruta, float tiempo, int fadein){
    imagen = al_load_bitmap(ruta);
    int i;

   if(!imagen) {
      al_show_native_message_box(pantalla, "Error", "Error", "Fallo al cargar imagen", NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(pantalla);
      return 0;
   }
    if (fadein > 0){
        if (fadein > 15){
                fadein = 15;
            }
                for (i = 0; i <= 255; i += fadein){
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_tinted_bitmap(imagen, al_map_rgba(i, i, i, i), 0, 0, 0);
                    al_flip_display();
                    al_rest(0.001*fadein);
                }
        }else{
            al_draw_bitmap(imagen, 0, 0, 0);
            al_flip_display();
        }
   al_rest(tiempo);
   al_destroy_bitmap(imagen);
   return 1;
}
//FUNCIÓN PARA MOSTRAR TEXTO
int mostrarTexto(char texto[], char rutaFuente[], int tamFuente, int r, int g, int b, char alineado[], float posX, float posY, float tiempo){
    al_init_font_addon();

    if (!al_init_ttf_addon()){
        cout << stderr << " Fallo al inicializar add-on allegro_ttf." << endl;
        return -1;
    }
    fuente = al_load_font(rutaFuente, tamFuente, 0);
    if (!fuente){
        al_destroy_display(pantalla);
        cout << stderr << " Fallo al cargar fuente." << endl;
        return -1;
    }
    if(strcmp(alineado, "der")==0){
        al_draw_text(fuente, al_map_rgb(r, g, b), posX, posY, ALLEGRO_ALIGN_RIGHT, texto);
    }
    if(strcmp(alineado, "cen")==0){
        al_draw_text(fuente, al_map_rgb(r, g, b), posX, posY, ALLEGRO_ALIGN_CENTER, texto);
    }
    if(strcmp(alineado, "izq")==0){
        al_draw_text(fuente, al_map_rgb(r, g, b), posX, posY, ALLEGRO_ALIGN_LEFT, texto);
    }
    al_flip_display();
    al_rest(tiempo);
    al_destroy_font(fuente);
}
//PANTALLAS DE PRESENTACIÓN
void intro(){
    mostrarImagen("images/utn.jpg", 2.0, 5);
    mostrarImagen("images/not.jpg", 3.0, 5);
    mostrarImagen("images/allegro.jpg", 3.0, 5);
}
//MENU PRINCIPAL DEL JUEGO
int menuPrincipal(){
    bool salir = false;
    int tecla = 0;
    int opcion = 0;
    eventos = al_create_event_queue();
    al_register_event_source(eventos, al_get_keyboard_event_source());
    al_register_event_source(eventos, al_get_display_event_source(pantalla));

    while (!salir){
        while(!al_is_event_queue_empty(eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(eventos, &evento);
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch(evento.keyboard.keycode){
                    case ALLEGRO_KEY_UP:
                        tecla = -1;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        tecla = 1;
                        break;
                    case ALLEGRO_KEY_ENTER:
                        return opcion;
                }
            }
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                salir = true;
            }
        }
        if(opcion>3){
            opcion=3;
        }
        if(opcion<=0){
            opcion=0;
        }
        opcion=opcion+tecla;
        if (ALLEGRO_EVENT_KEY_DOWN){
            switch(opcion){
                case 0:mostrarImagen("images/menu/01.jpg", 0, 0);
                break;
                case 1:mostrarImagen("images/menu/02.jpg", 0, 0);
                break;
                case 2:mostrarImagen("images/menu/03.jpg", 0, 0);
                break;
                case 3:mostrarImagen("images/menu/04.jpg", 0, 0);
                break;
            }
            tecla = 0;
        }
    }
    return 0;
}
void cerrarAllegro(){
   al_destroy_display(pantalla);
}


#endif // FUNCIONES_H_INCLUDED
