# Trabalho para a disciplina de Estruturas de Dados.

### Como Jogar
O jogador tem 7 fileiras de cartas com 7 cartas cada e um monte com 3 cartas inicialmente, o objetivo é montar mãos e as "descartar", no ato do "descarte" são contabilizados pontos para a mão baseando-se no sistema de pontos utilizado no pocker.
O jogador pode adicionar cartas a mão, mandar cartas para o monte, verificar sua mão atual e descartar a mão (contabilizar pontos), o objetivo do jogo é fazer o maior número de pontos, a execução encerra com o comando do usuário, o mesmo deve a encerrar quando tiver menos de 5 cartas, pois assim, não pode formar uma mão!

### Semente
Para fins de teste a semente do rand está em 1, se quiser usar outra sequencia ou deixar o jogo "aleatório" basta troca-lá!

### Descrição do trabalho
* Objetivo:
Consolidar seu conhecimento de estruturas dinâmicas de dados (filas, pilhas), através da programação, em linguagem C, de um jogo de paciência.

* Descrição:
Seu programa deverá implementar um jogo de paciência baseado nas regras do jogo de pôquer.
O jogo deverá funcionar da seguinte maneira:
existem 7 fileiras de cartas, visíveis ao usuário, uma pilha de reserva e uma fileira de montagem de mão;
após o embaralhamento inicial, cada uma das 7 fileiras receberá 7 cartas, e as 3 restantes deverão ser colocadas na pilha;
o usuário deverá escolher 5 cartas dentre as disponíveis nas fileiras e montar sua mão para pontuação;
somente pode ser utilizada uma carta de cada fileira para compor a mão;
cartas podem ser retiradas das fileiras e colocadas na pilha de reserva, sem limites de número de cartas para esta retirada;
além das cartas das fileiras, o usuário também pode utilizar-se da pilha de reserva, porém, somente para a carta no topo da pilha a cada mão;
a pontuação será como se segue: 
os pontos de cada mão devem ser acumulados para formar a pontuação final;
cartas usadas para fazer uma mão serão descartadas após a contagem de pontos;
o jogo termina ao haverem menos de 4 cartas disponíveis nas fileiras (a 5a carta virá obrigatoriamente da pilha no caso de haverem exatamente 4 cartas nas fileiras);
cartas que sobrarem na pilha ao final das cartas das fileiras serão desconsideradas.

* Detalhes relevantes para a implementação em C:
Seu programa deverá utilizar as seguintes estruturas dinâmicas de dados:
7 filas simples para a implementação das fileiras principais;
uma pilha simples para a pilha de reserva;
uma lista ordenada para a mão (ordem numérica ascendente).


