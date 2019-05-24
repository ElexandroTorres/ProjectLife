Life
====
**Projeto de implementação do jogo da vida de Conway.**
Autoria de **Elexandro Torres Tavares**


A partir da leitura de um arquivo de configuração, varias simulações são executadas e geram o resultado de acordo com a regra de sobrevivência **"B3/S23"** , A célula nasce se tiver exatamente três vizinhos vivos e Sobrevive se tiver dois ou três vizinhos vivos.


Compilação do life:
-------------
Para compilar, devemos acessar o diretório do projeto e em seguida entrar na pasta **build**. iremos executar o cmake com o CMakeLists.txt disponível no projeto.
Exemplo:
```
~/Documentos/ProjectLife/build$ cmake -G "Unix Makefiles" ..
```
Em seguida usamos o comando **make** para gerar o executável.
```
~/Documentos/ProjectLife/build$ make
```
Agora o executável já esta pronto e o life pronto para ser usado.

Arquivo de configuração:
-------------
A simulação pode ser executada através do **./glife**. 
Vários argumentos podem ser passados para personalizar a maneira como os dados serão gerados.
O nome do arquivo de configuração é o único argumento obrigatório. Abaixo um exemplo de como pode ser esse arquivo.
```
17 17
*
.................
.................
....***...***....
.................
..*....*.*....*..
..*....*.*....*..
..*....*.*....*..
....***...***....
.................
....***...***....
..*....*.*....*..
..*....*.*....*..
..*....*.*....*..
.................
....***...***....
.................
.................
```
Na primeira linha são informados as dimensões da tabela de células que será lida. Numero de linhas seguido do numero de colunas. Logo em seguida é lido o caractere que será considerado como um célula viva. E abaixo toda a matriz representando as células.
O arquivo deve apresentar esses dados para que a simulação seja possível.

Executando o life:
---------
Para executar o life utilizaremos o **./glife** seguido dos argumentos para personalizar a simulação. Lembrando que o nome do arquivo de configuração é o único argumento obrigatório.
Para ver a lista de argumentos possíveis basta usar o --help.

Abaixo temos um exemplo de execução informando apenas o arquivo de configuração.
```
~/Documentos/ProjectLife/build$ ./glife ../inputConfig/Exemplo1.dat
```
Se o arquivo for lido com sucesso a simulação será executada e os dados mostrados na tela.

Abaixo um exemplo de uma simulação que irá gerar imagens de cada geração e irá executar 100 vezes. Lembrando que a simulação irá parar antes caso encontre estabilidade ou as células sejam extintas.
```
$ ./glife ../inputConfig/Exemplo1 --imgdir ../imgs --maxgen 100
```
Resultados da simulação:
-------
A simulação irá gerar os resultados de acordo com oque você definiu nos argumentos. A forma padrão é a geração de dados pelo console.
 
Quando for encontrado estabilidade será mostrado na saída padrão com qual geração foi a estabilidade.
Ja quando a população de células for extinta será mostrada a mensagem de extinção.

Em casos de não estabilidade ou extinção a simulação irá continuar até o numero máximo de gerações definidos. Caso esse numero não tenha sido definido, vai rodar por um bom tempo.
 





