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

Imprima a quantidade mínima de apertos de mão que separam as duas pessoas.

## Exemplo

### Exemplo de entrada

```
42 4
5 8
4 alex
10 barbara
1 carlos
7 duda
42 eda
4 1
10 42
4 7
10 4
7 10
42 7
7 10
1 7
```

### *Saída do exemplo acima*

```
2
```

No exemplo acima existem algumas conexões possíveis com 2 apertos de mão mas nenhuma com menos, segue algumas possibilidades que resultam em 2 apertos de mão:

- alex -> duda -> eda
- alex -> barbara -> eda
