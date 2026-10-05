# Entenda o Projeto 2 em 10 minutos

Este é o resumo para você conseguir **explicar e demonstrar** o trabalho sem decorar o código inteiro. O projeto junta conteúdos da Fase 1 — decisões (`if`), repetição (`loop`), variáveis e dados — com o ESP32 da Fase 2.

## 1. O que entra e o que sai?

- **Entradas digitais:** os três botões N, P e K. Cada um informa somente `0` ou `1`.
- **Entrada analógica:** o LDR, que varia com a luz e é usado apenas para **fingir um número de pH** no exercício.
- **Entrada do DHT22:** umidade relativa do ar, usada apenas para **fingir a umidade do solo** no exercício.
- **Saída:** o relé que representa a bomba; o LED azul mostra quando o contato usado para a bomba está ligado.

Imagine que as entradas sejam perguntas e a saída seja a ação: **“A umidade simulada está baixa o bastante para ligar a bomba?”**

## 2. Por que botão pressionado aparece como `1`, mas o pino lê `LOW`?

O programa configura cada botão com `INPUT_PULLUP`. Assim, solto, o pino fica em `HIGH`; pressionado, ele é ligado ao GND e passa a `LOW`. A expressão `digitalRead(PIN_N) == LOW` transforma isso em um valor lógico fácil de entender: `true`/`1` significa “N pressionado”.

Exemplo: se só o botão P estiver pressionado, o Monitor Serial mostra `N=0 P=1 K=0`.

## 3. Como o LDR vira “pH”?

O ESP32 lê o sinal analógico em um número de **0 a 4095**. O programa aplica `pH_simulado = valor × 14 / 4095`. Por exemplo, se a leitura fosse 2048, mostraria aproximadamente **7,0**. Essa conta apenas troca a escala numérica; **não há relação física real entre luz e pH do solo**.

Ao mudar os botões N/P/K, ajuste também o controle de luminosidade do LDR no Wokwi para criar um novo cenário. Não diga que apertar um botão provoca uma mudança real de pH.

## 4. O que é a histerese de 45%–55%?

É uma regra com dois limites, para a bomba não ligar e desligar sem parar perto de um único número:

| Umidade simulada | Se estava desligada | Se estava ligada |
| --- | --- | --- |
| 40% | Liga | Continua ligada |
| 50% | Continua desligada | Continua ligada |
| 56% | Continua desligada | Desliga |

Em uma frase: **abaixo de 45% liga; a partir de 55% desliga; no meio mantém o estado anterior.** Os percentuais são somente parâmetros de demonstração porque o DHT22 não mede água no solo.

## 5. Por que NPK e pH não controlam a bomba?

O enunciado deixa a lógica de decisão para quem desenvolve. Aqui a água é controlada pela umidade simulada; nutrientes e pH são **diagnósticos exibidos**. Isso evita transformar indicadores binários e um LDR em decisões agronômicas reais. A escolha está documentada no README e deve ser explicada no vídeo.

## 6. O que acontece se houver erro de leitura?

Se a umidade retornada pelo DHT22 for inválida, o programa coloca `bombaLigada = false`. É uma medida preventiva no protótipo. Em um sistema real, ainda seria preciso projetar alarmes, alimentação elétrica, proteção da bomba, calibração e sensores apropriados.

## Treino de apresentação (responda sem olhar)

1. Se a umidade sair de 40% para 50%, a bomba desliga? **Não; continua ligada até 55% ou mais.**
2. Se a umidade sair de 56% para 50%, ela liga? **Não; continua desligada até ficar abaixo de 45%.**
3. O LDR mede pH real? **Não; mede luz. O pH é só uma escala simulada.**
4. O DHT22 mede umidade real do solo? **Não; mede umidade relativa do ar.**
5. O que significa `N=1 P=0 K=0`? **Somente o botão N está pressionado; não informa concentração de nutrientes.**

Se você conseguir responder essas cinco perguntas e reproduzir os cenários de umidade no Wokwi, já tem o núcleo do trabalho dominado.

