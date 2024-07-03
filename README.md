# Chess PDS
Repositório com o sistema de jogo de xadrez local.

# Membros
* Breno Duarte Teixeira
* Davi Reis Bahia
* Daniel Zanuncio Dias Castro
* Enzo Santana Guimaraes Moreira
* Leônidas José Furtado Braga

# Problema
Xadrez é um jogo que já está estabelecido há muito tempo, porém os jogadores podem cometer alguns erros ao jogar em um tabuleiro por não considerarem todas os opções de movimentos ou simplesmente não terem conhecimento sobre todas as regras. Além disso, é necessário ter o tabuleiro e as peças para jogar de maneira física, e pode-se acontecer de não ter tais objetos.

# Solução
Nossa solução é criar um sistema que simula um jogo local de xadrez. É uma maneira de simular um jogo e garantir que as regras tradicionais sejam obedecidas ao realizar cada jogada. Dessa forma, é possível realizar uma partida mesmo que todas as regras não sejam conhecidas pelos participantes, e jogos podem ser criados ao simplesmente executar o programa, sem a necessidade de montar um tabuleiro.

# Instalação

# Uso

# Estrutura do projeto

# Principais features
* Criar partica local de xadrez com 2 jogadores;
* Identificar os jogadores participantes;
* Visualizar as peças capturadas;
* Encerrar o jogo após desistências ou acordos de empates;
* Identificar fim de jogo por cheque-mate ou afogamento;
* Acessar histórico das partidas jogadas anteriormente;
* Possibilidade de responder uma mensagem recebida (caso vcs achem interessante colocar);
* Visualização do jogo através do terminal.

# Dificuldades

# Backlog do Produto
1. Como usuário, gostaria de escolher criar um novo jogo em um menu para jogar xadrez com 2 jogadores localmente.
2. Como jogador, gostaria de mover uma peça de acordo com regras tradicionais do xadrez.
3. Como jogador, gostaria de capturar as peças do meu adversário.
4. Como jogador, eu tenho que sair de posições de cheque para continuar o jogo.
5. Como jogador, gostaria de fazer um roque.
6. Como jogador, gostaria de fazer um cheque-mate para ganhar o jogo.
7. Como jogo, devo declarar empate caso um jogador não tenha mais jogadas válidas e o rei não esteja em cheque.
8. Como jogador, gostaria de promover um peão ao alcançar o fim do tabuleiro do meu lado.
9. Como jogador, gostaria de desistir para finalizar a partida antes de um cheque-mate.
10. Como jogador, gostaria de propor um empate ao meu oponente para finalizar a partida antes de um cheque-mate.
11. Como jogador, gostaria de fazer um “en passant”.
12. Como jogo, devo identificar os jogadores.
13. Como usuário, gostaria de visualizar as partidas passadas através de um histórico.
14. Como jogador, gostaria de ver quais peças do jogo foram capturadas.

# Requisitos Funcionais
* **História #1**: Como usuário, gostaria de escolher criar um novo jogo em um menu para jogar xadrez com 2 jogadores localmente.
  * **Critérios de aceitação**:
    - Posso criar apenas um jogo por vez.
    - Ao fechar o programa, o jogo em execução é finalizado.
    - Um jogo deve ter dois jogadores.
    - Cada jogador pode controlar 16 peças, sendo 8 peões, 2 torres, 2 cavalos, 2 bispos, uma rainha e um rei.
    - A disposição inicial do tabuleiro deve seguir as definições da regra do xadrez.
  * **Responsável**: [Leônidas]
  <br>
  
* **História #2**: Como jogador, gostaria de mover uma peça de acordo com regras tradicionais do xadrez.
  * **Critérios de aceitação**:
    - Cada tipo de peça possui movimentos específicos que pode realizar de acordo com as regras.
    - Caso seja um movimento válido, a nova posição da peça é a coordenada que foi movimentada.
    - Caso seja um movimento válido, a posição antifa da peça deve ficar vazia.
    - Um jogador pode movimentar apenas suas próprias peças.
    - Um jogador só pode movimentar suas peças em seu turno.
    - Peças que movem várias casas não podem se movimentar para campos nas suas linhas de movimento que estão inacessíveis por estarem atrás de outras peças.
    - O cavalo pode se mover para qualquer uma das casas que tem acesso de acordo com as regras.
  * **Responsável**: []
  <br>
  
* **História #3**: Como jogador, gostaria de capturar as peças do meu adversário.
  * **Critérios de aceitação**:
    - A peça que capturou uma outra peça deve ter como nova posição as coordenadas da peça capturada.
    - Uma captura de peça deve ser precedida de uma movimentação.
    - Um peão não captura como se movimenta, mas captura as peças em suas diagonais frontais.
    - Um jogador não pode capturar suas prórias peças.
  * **Responsável**: []
  <br>
  
* **História #4**: Como jogador, eu tenho que sair de posições de cheque para continuar o jogo.
  * **Critérios de aceitação**:
    - Os únicos movimentos que podem ser realizados são aqueles que tiram o rei de uma possível coordenada de captura de peças adversárias.
    - Movimentos que deixam o rei em risco não são válidos.
  * **Responsável**: []
  <br>
  
* **História 5**: Como jogador, gostaria de fazer um roque.
  * **Critérios de aceitação**:
    - Um roque só pode ocorrer se o rei e a torre alvo não tiverem se movimentado.
    - Um roque só pode ocorrer se não houver peças entre o rei e a torre alvo.
    - Um roque não pode ser feito se o rei estiver em cheque.
    - O rei deve se movimentar 2 casas em direção da torre alvo, e a torre alvo deve se desolcar para a casa que o rei pulou.
  * **Responsável**: []
  <br>
  
* **História 6**: Como jogador, gostaria de fazer um cheque-mate para ganhar o jogo.
  * **Critérios de aceitação**:
    - O cheque-mate deve ser declarado ao iniciar o turno de um jogador.
    - Um cheque-mate deve ser declarado caso o jogador atual não tenha movimentos válidos e o rei esteja em cheque.
    - O jogo deve finalizar após o cheque-mate.
  * **Responsável**: []
  <br>
  
* **História 7**: Como jogo, devo declarar empate caso um jogador não tenha mais jogadas válidas e o rei não esteja em cheque.
  * **Critérios de aceitação**:
    - O empate deve ser declarado no início do turno de um jogador.
    - Um empate por afogamento deve ser declarado caso o jogador atual não tenha movimentos válidos e o rei não esteja em cheque.
    - O jogo deve finalizar após o empate
  * **Responsável**: []
 <br>
 
* **História 8**: Como jogador, gostaria de promover um peão ao alcançar o fim do tabuleiro do meu lado.
  * **Critérios de aceitação**:
    - Um peão só pode promover caso esteja na última linha do lado oposto que iniciou.
    - A promoção deve ocorrer assim que o peão alcançar as casas com o gatilho.
    - Um peão pode promover para qualquer outra peça que não seja o rei, e se comporta como a peça escolhida.
  * **Responsável**: []
  <br>
  
* **História 9**: Como jogador, gostaria de desistir para finalizar a partida antes de um cheque-mate.
  * **Critérios de aceitação**:
    - Um jogador só pode desistir durante seu turno.
    - O jogo acaba com vitória para o adversário após confirmar a desistência.
  * **Responsável**: []
  <br>
  
* **História 10**: Como jogador, gostaria de propor um empate ao meu oponente para finalizar a partida antes de um cheque-mate.
  * **Critérios de aceitação**:
    - Uma proposta de empate pode ser inicializada durante o turno do jogador.
    - Uma proposta de empate não interrompe o turno do jogador.
    - Uma proposta de empate aceita finaliza o jogo como empate.
  * **Responsável**: []
  <br>
  
* **História 11**: Como jogador, gostaria de fazer um “en passant”.
  * **Critérios de aceitação**:
    - Apenas peões podem executar esse tipo de captura.
    - Essa captura só ocorre caso um peão adversário tenha avançado 2 casas como primeiro movimento e está ao lado do peão que irá realizar a captura.
    - A captura é feita ao mover o peão que irá capturar para a casa que foi pulada, e o peão capturado deve ser removido.
  * **Responsável**: []
  <br>
  
* **História 12**: Como jogo, devo identificar os jogadores.
  * **Critérios de aceitação**:
    - Os jogadores devem inserir nomes ao criar um novo jogo.
    - Os jogadores são identificados nos comandos do jogo com os nomes que inseriram.
  * **Responsável**: []
  <br>
  
* **História 13**: Como usuário, gostaria de visualizar as partidas passadas através de um histórico.
  * **Critérios de aceitação**:
    - O histórico de partidas deve enumerar todos os jogos que já ocorreram localmente.
    - Cada jogo deve ter uma sequência de jogadas que foram executadas na partida.
    - Os jogadores da partida devem ser identificados.
    - o resultado da partida deve estar disponível no fim do histórico da partida.
  * **Responsável**: []
