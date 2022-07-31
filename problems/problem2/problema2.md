# Regra dos seis apertos de mão

A regra dos seis apertos de mão originada por Frigyes Karinthy, sugere que qualquer pessoa do mundo está conectada com qualquer outra através de seus contatos. Segundo ele o número máximo de elos que uma pessoa precisa para se conectar com qualquer outra é seis.

Ao se deparar com essa regra, Êda ficou curiosa para saber o número mínimo de elos que duas pessoas precisam para se conectar. Mas seria impossível calcular isso manualmente, já que existem bilhões de pessoas no mundo. Êda foi atrás do(a) melhor programador(a) que ela conhece para ajudá-la nesta tarefa, você.

Ajude Êda escrevendo um programa que permita escolher duas pessoas e determine o número mínimo de apertos de mão necessários para conectá-las.

## Entrada

A entrada é composta por um único caso de teste. A primeira linha de um caso de teste contém 2 inteiros **S** (0 &le; **S** &lt; **1000**), o *ID* da primeira pessoa, e **E** (0 &le; **E** &lt; **1000**), o *ID* da segunda pessoa que queremos verificar a conectividade.

A segunda linha contém 2 inteiros **N** (2 &le; **N** &lt; **1000**), a quantidade de pessoas, e **M** (1 &le; **M** &lt; **N(N-1)/2**), a quantidade de apertos de mão.

Cada uma das **N** linhas seguintes contém um inteiro **I** (1 &le; **I** &lt; **1000**), representando o *ID* da pessoa, seguido do nome da mesma, onde o nome é composto por no máximo **25** letras minúsculas e sem espaços.

As próximas **M** linhas contém 2 inteiros **V** (0 &le; **V** &lt; **N**) e **W** (0 &le; **W** &lt; **N**), informando que a pessoa **V** apertou a mão da pessoa **W**. Quando **V** ou **W** 

## Saída

Caso não exista nenhuma forma de conectar a pessoa **S** com a pessoa **E**, imprima apenas `sem conexao`.

Caso contrário, a primeira linha da saída deve ser composta por um inteiro **T**, onde **T** é igual a quantidade mínima de apertos de mão necessários para conectar as duas pessoas escolhidas. As **T** linhas seguintes devem representar o caminho dos apertos de mão que conectam as duas pessoas, onde cada linha possui o seguinte formato `nome1 apertou a mao de nome2`, onde *nome1* e *nome2* são os nomes das pessoas que apertaram a mão.

Caso exista mais de uma possível solução, imprima qualquer uma.

## Exemplo

### Exemplo de entrada 1

```
4 42
5 7
4 alex
10 barbara
1 carlos
7 duda
42 eda
4 1
10 42
4 7
10 4
42 7
7 10
1 7
```

### *Saída para o exemplo 1*

```
2
alex apertou a mao de duda
duda apertou a mao de eda

```

No exemplo acima existem algumas conexões possíveis com 2 apertos de mão mas nenhuma com menos, segue algumas possibilidades que resultam em 2 apertos de mão:

- alex -> duda -> eda
- alex -> barbara -> eda

### Exemplo de entrada 2

```
4 42
5 8
4 alex
10 barbara
1 carlos
7 duda
42 eda
12 fabricio
4 1
10 12
4 7
10 4
7 10
12 7
1 7
12 1
```

### *Saída para o exemplo 2*

```
sem conexao

```

Neste exemplo não existe conexão entre as duas pessoas selecionadas
