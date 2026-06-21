#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>

/* Lê todos os eventos inotify disponíveis do descritor de arquivo 'fd'.
   wd é a tabela de descritores de monitoramento para os diretórios em argv.
   argc é o tamanho de wd e argv.
   argv é a lista de diretórios monitorados.
   A entrada 0 de wd e argv não é usada. */

static void
handle_events(int fd, int *wd, int argc, char* argv[])
{
    /* Alguns sistemas não conseguem ler variáveis inteiras se elas não
       estiverem devidamente alinhadas. Em outros sistemas, o alinhamento incorreto
       pode diminuir o desempenho. Portanto, o buffer usado para ler do
       descritor de arquivo inotify deve ter o mesmo alinhamento que
       a struct inotify_event. */

    char buf[4096]
        __attribute__ ((aligned(__alignof__(struct inotify_event))));
    const struct inotify_event *event;
    ssize_t size;

    /* Loop enquanto eventos puderem ser lidos do descritor de arquivo inotify. */

    for (;;) {

        /* Lê alguns eventos. */

        size = read(fd, buf, sizeof(buf));
        if (size == -1 && errno != EAGAIN) {
            perror("erro\n");
            exit(EXIT_FAILURE);
        }

        /* Se a leitura não-bloqueante read() não encontrou eventos para ler, então
           ela retorna -1 com errno definido como EAGAIN. Nesse caso,
           nós saímos do loop. */

        if (size <= 0)
            break;

        /* Loop sobre todos os eventos no buffer. */

        for (char *ptr = buf; ptr < buf + size;
                ptr += sizeof(struct inotify_event) + event->len) {

            event = (const struct inotify_event *) ptr;

            /* Imprime o tipo do evento. */

            if (event->mask & IN_OPEN)
                printf("IN_OPEN: \n");
            if (event->mask & IN_CLOSE_NOWRITE)
                printf("IN_CLOSE_NOWRITE:\n" );
            if (event->mask & IN_CLOSE_WRITE)
                printf("IN_CLOSE_WRITE:\n" );

            /* Imprime o nome do diretório monitorado. */

            for (size_t i = 1; i < argc; ++i) {
                if (wd[i] == event->wd) {
                    printf("%s/", argv[i]);
                    break;
                }
            }

            /* Imprime o nome do arquivo. */

            if (event->len)
                printf("%s", event->name);

            /* Imprime o tipo do objeto do sistema de arquivos. */

            if (event->mask & IN_ISDIR)
                printf("[directory]\n");
            else
                printf("[file]\n");
        }
    }
}

int
main(int argc, char* argv[])
{
    char buf;
    int fd, i, poll_num;
    int *wd;
    nfds_t nfds;
    struct pollfd fds[2];

    if (argc < 2) {
        printf("Uso: %s CAMINHO [CAMINHO ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Pressione a tecla ENTER para terminar\n");

    /* Cria o descritor de arquivo para acessar a API inotify. */

    fd = inotify_init1(IN_NONBLOCK);
    if (fd == -1) {
        perror("error\n");
        exit(EXIT_FAILURE);
    }

    /* Aloca memória para os descritores de monitoramento. */

    wd = calloc(argc, sizeof(int));
    if (wd == NULL) {
        perror("error\n");
        exit(EXIT_FAILURE);
    }

    /* Marca os diretórios para os eventos:
       - arquivo foi aberto
       - arquivo foi fechado */

    for (i = 1; i < argc; i++) {
        wd[i] = inotify_add_watch(fd, argv[i],
                                  IN_OPEN | IN_CLOSE);
        if (wd[i] == -1) {
            fprintf(stderr, "Não é possível monitorar %s: %s\n",
                    argv[i], strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    /* Prepara para o polling (monitoramento multiplexado). */

    nfds = 2;

    fds[0].fd = STDIN_FILENO;       /* Entrada do console */
    fds[0].events = POLLIN;

    fds[1].fd = fd;                 /* Entrada do Inotify */
    fds[1].events = POLLIN;

    /* Aguarda por eventos e/ou entrada do terminal. */

    printf("Escutando eventos.\n");
    for (;;) {
        poll_num = poll(fds, nfds, -1);
        if (poll_num == -1) {
            if (errno == EINTR)
                continue;
            perror("error\n");
            exit(EXIT_FAILURE);
        }

        if (poll_num > 0) {

            if (fds[0].revents & POLLIN) {

                /* Entrada do console disponível. Esvazia o stdin e sai. */

                while (read(STDIN_FILENO, &buf, 1) > 0 && buf != '\n')
                    continue;
                break;
            }

            if (fds[1].revents & POLLIN) {

                /* Eventos do Inotify estão disponíveis. */

                handle_events(fd, wd, argc, argv);
            }
        }
    }

    printf("Escuta de eventos interrompida\n");

    /* Fecha o descritor de arquivo inotify. */

    close(fd);

    free(wd);
    exit(EXIT_SUCCESS);
}
