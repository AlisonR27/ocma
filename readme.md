## Dupla
Alison Ranier Araujo de Souza (20210050970)
Joel Fernandes de Lima (20210046735)

## Estratégia

usando eXtreme Go Horse =p

O barco é um struct do tipo Ship que é criado na main do projeto, e é passado para as funções em módulos como um ponteiro do struct principal.
O mapa é lido em funções em um arquivo separado, onde é feita a busca por um peixe de mais importância (muito mais perto, ou com mais valor e distancia média) em todo o mapa e as informações sao passadas ao ponteiro do barco.
O barco então verifica o próprio peso, e vai para o destino. 
Ao chegar, o bot pesca até que sobre apenas 1 peixe nas coordenadas-alvo. Então o bot retorna ao porto mais próximo onde irá vender os peixes. Ao vender,o bot busca novamente na leitura do mapa as coordenadas de melhor importância para seguir a pesca.


## O que ficou faltando fazer (se não deu tempo de fazer tudo)
Desviar de outros barcos e usar alocaçao dinâmica para criar um array de barcos (Não achei outro uso para o código feito até então). 
> Também não busca um outro porto quando o que ele vai vender está ocupado (mas isso é um erro do ocma, né?)

## O que faria diferente se fosse começar o projeto do zero novamente.
Usaria menos funções e passaria as variaveis de posições diretamente como propriedades;
Não teria separado a tomada de decisões do scan do mapa, isso dificulta na hora de recalcular a rota.
Usaria código mais legivel e teria mais cuidado com os espaço entre as funções.

## Comentários
Como ele não roda com outros bots, pode testá-lo sozinho.

>Para executar o bot, rodar: 
>```
>gcc potengi*.c  -o potengi; node ocma.js potengi;
>```

[Projeto no Github](https://github.com/AlisonR27/ocma)