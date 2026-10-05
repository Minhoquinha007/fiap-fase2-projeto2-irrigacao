# Roteiro sugerido para vídeo não listado (até 5 minutos)

1. **0:00–0:30 — contexto.** Diga que o sistema simula a irrigação da alface com ESP32. Explique que DHT22 e LDR são substituições didáticas, não sensores de solo e pH.
2. **0:30–1:15 — circuito.** Mostre os três botões verdes de N/P/K, o LDR, o DHT22, o relé azul e o LED que simboliza a bomba. Aponte o Monitor Serial.
3. **1:15–2:10 — nutrientes e pH.** Pressione cada botão; mostre o `0/1`. Ajuste manualmente o LDR e mostre o pH simulado. Não diga que o botão, por si só, muda o pH de verdade.
4. **2:10–3:45 — irrigação.** Comece em 60% (desligada), reduza para 40% (liga), ajuste para 50% (continua ligada) e aumente para 56% (desliga). Mostre LED e texto `BOMBA=ON/OFF` concordando.
5. **3:45–4:30 — lógica.** Explique os limites 45%/55%, a histerese e o desligamento em caso de leitura inválida. Diga que esses percentuais são apenas para simulação.
6. **4:30–5:00 — encerramento.** Mostre o README e o link do projeto/repositório. Confira duração final de até 5 minutos e publique como **não listado**.

Fale com suas próprias palavras e mostre o resultado funcionando; o vídeo é a evidência do seu entendimento, não apenas da existência de arquivos.

