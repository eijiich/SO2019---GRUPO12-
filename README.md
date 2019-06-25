# SO2019-GRUPO12
Trabalho da disciplia Sistemas Operacionais

Forma de execução (README)
Assim como já foi mencionado, os algoritmos utilizados foram implementados de maneira sequencial e paralela (utilizando PThreads). Dessa forma, para que ocorra a execução correta dos códigos, segue os modos de execução:
 
Código sequencial:
gcc nome_do_codigo.c -o nome_do_binario -lm -lgmp
./nome_do_binario<arquivo_de_entrada>arquivo_de_saida 
 
Código paralelo:
gcc nome_do_codigo.c -o nome_do_binario -lm -lgmp -lpthread
./nome_do_binario<arquivo_de_entrada>arquivo_de_saida
