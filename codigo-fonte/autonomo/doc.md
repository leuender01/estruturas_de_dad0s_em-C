*Em linguagem C, as "cores ASCII" **são geradas usando Sequências de Escape ANSI** .Elas enviam códigos
de controle em formato de texto para o terminal.O padrão segue o formato \033[código\_da\_cor e afetam
o texto ou fundo impresso logo após a instrução.*



# Tabela Completa de Cores ANSI (Formato de 8 Cores)

*A tabela básica utiliza os códigos de 30 a 37 para texto e de 40 a 47 para fundo.*


---------
| ***Cor***     | ***Código do***    | ***Código do***    | ***Cor***             | ***Cor***             | 
| ***Básica***  | ***Texto***        | ***Fundo***        | ***Clara/Brilhante*** | ***Clara/Brilhante*** |
|               | ***(Foreground)*** | ***(Background)*** | ***(Texto)***         | ***(Fundo)***         |
---------
`Preto`        \033\[30m          | \033\[40m          | \033\[90m             | \033\[100m            |
---------
`Vermelho`     \033\[31m          | \033\[41m          | \033\[91m             | \033\[101m            |
---------
`Verde`        \033\[32m          | \033\[42m          | \033\[92m             | \033\[102m            |
---------
`Amarelo`      \033\[33m          | \033\[43m          | \033\[93m             | \033\[103m            |
---------
`Azul`         \033\[34m          | \033\[44m          | \033\[94m             | \033\[104m            |
---------
`Magenta`      \033\[35m          | \033\[45m          | \033\[95m             | \033\[105m            |    
---------
`Ciano`        \033\[36m          \033\[46m       \033\[96m    \033\[106m 
---------
`Branco`       \033\[37m          \033\[47m       \033\[97m    \033\[107m  
---------
    

*Tabela de Estilos (Efeitos de Texto)Podem sercombinados
com as cores usando o separador de ponto e vírgula ;.*


---------
| ***Estilo do Texto*** | ***Código ANSI*** | ***Descrição***                            
---------
| `Reset`               | \033\[0m          | Limpa todas as configurações (muito importante usar no fim) 
---------
| `Negrito`             | \033\[1m          | Aumenta a intensidade ou deixa o texto negrito              
---------
| `Sublinhado`          | \033\[4m          | Sublinha o texto                                            
---------
| `Invertido`           | \033\[7m          | Inverte as cores do texto e do fundo                        
---------

# Exemplo de Código Prático em C

## c
```bash

#include <stdio.h>

int main() {
    // Texto em vermelho com fundo amarelo
    printf("\033[31;43m Erro! Caracter invalido.\033[0m\n");

    // Texto em verde brilhante
    printf("\033[92m Operacao concluida com sucesso!\033[0m\n");

    return 0;
}

```
