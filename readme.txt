# Cache Memory Simulation

# Input
It is expected that the parameters are passed in the following format:
`` cache_simulator <nsets> <bsize> <association> <replacement> <flag_out> input_file ``

Where each of these fields has the following meaning:
• cache_simulator - file name of executing main of simulator;
• nsets - number of cache sets;
• bsize - block size in bytes;
• assoc - degree of associativity;
• replacement - replacement policy, which can be Random (R), FIFO (F) or L (LRU);
• flag_out - flag that activates the default data output mode;
• input_file - file with the addresses to access the cache.

# Examples of output:
There are two output formats, when the output_flag is 0, the format is as follows:

Access number: 100
Hit rate: 0.40
Miss rate: 0.60
Compulsive miss rate: 0.87
Capacity miss rate: 0.87
Conflict miss rate: 0.00

while flag_saida is 1, the output format is:

100 0.40 0.60 0.13 0.87 0.00


# replacement policy:
 - Random
 - LRU (Least Recently Used)
 - FIFO (First In, First Out)

# Libraries utilized

- stdio
- stdlib
- math
- time
- stdbool

# cache struct:

- long int tag => to store tag.
- bool is_empty => To check if the address has already been filled in or if it is miss compulsive
- int inserted_at => Used to store the time it was entered
- int access_at = Used to store the last time it was accessed

# Observações

- We assign the current value of the file access counter to inserted_at and access_at.
- We use the srand() function to feed the rand and generate the random values ​​with the least bias.
- Variable pattern used is snake_case
- Default function used is camelCase




# Simulador de Caches

# Entrada
É esperado que sejam passados os parametros no seguinte formato:
`` cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> arquivo_de_entrada ``

Onde cada um destes campos possui o seguinte significado:
• cache_simulator - nome do arquivo de execução principal do simulador (todos devem usar este nome, independente da linguagem escolhida;
• nsets - número de conjuntos na cache;
• bsize - tamanho do bloco em bytes;
• assoc - grau de associatividade;
• substituição - política de substituição, que pode ser Random (R), FIFO (F) ou L (LRU);
• flag_saida - flag que ativa o modo padrão de saída de dados;
• arquivo_de_entrada - arquivo com os endereços para acesso à cache.

# Exemplos de saída:
Existem dois formatos de saída, qunado a flag_saida é 0, o formato é o seguinte:

Access number: 100
Hit rate: 0.40
Miss rate: 0.60
Compulsive miss rate: 0.87
Capacity miss rate: 0.87
Conflict miss rate: 0.00

Quando a flag_saida é 1, o formato de saída é

100 0.40 0.60 0.13 0.87 0.00


# Políticas de substituição:
 - Random
 - LRU (Least Recently Used)
 - FIFO (First In, First Out)

# Bibliotecas utilizadas

- stdio
- stdlib
- math
- time
- stdbool

# Estrutura da cache

- long int tag => Para armazenar a tag
- bool is_empty => Para verificar se o endereço já foi preenchido ou se é miss compulsivo
- int inserted_at => Utilizado para armazenar o momento em que foi inserido
- int access_at = Utilizado para armazenar o último momento em que foi acessado

# Observações

- Atribuimos ao inserted_at e access_at o valor do atual do contador de acesso ao arquivo.
- Utilizamos a função srand() para alimentar o rand e gerar os valores aleátorios com menor vício.
- Padrão de váriavel utilizada é a snake_case
- Padrão de função utilizada é a camelCase
