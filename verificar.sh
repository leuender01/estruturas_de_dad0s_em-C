#!/usr/bin/bash

## Armazena Lista de arquivos objestos se estiverem a mais de 3 dias parados

CMD=($(find ./objects -type f -name "*.o" -mtime +3 -printf "%p\n"))

echo "${CMD[@]}"

if [ -z "$CMD" ]; then

    echo "nada a fazer"
    exit

else

    rm -f ${CMD[@]}
    exit

fi
