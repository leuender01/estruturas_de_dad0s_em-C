#include <stdio.h>
#include <stdlib.h>
#include <libnotify/notify.h>

int main(void){
    
    notify_init("MeuAPP"); // inicializa e da um nome para minha aplicação

    NotifyNotification *n = notify_notification_new(
                "Mensagem do leu", //Definimos o titulo da notificação
                "Eu to te vendo lauani", //COrpo da mensagem em sí
                NULL //Icone
           );
    
    if(!notify_notification_show(n, NULL)){

        printf("Falha ao enviar a notificação\n");
    }

    g_object_unref(G_OBJECT(n));
    notify_uninit();

    return 0;
}

