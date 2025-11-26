##  Projeto IoT: Monitoramento de Potência de Sinal WiFi (dBm)



## 👨‍🎓 Integrantes:

- <a href="https://www.linkedin.com/in/christian-gandra/">Christian Gandra</a>
- <a href="https://www.linkedin.com/in/paulo-henrique0601/">Paulo Henrique</a>
- <a href="https://www.linkedin.com/in/vitor-lopes-91763b34a/">Vitor Lopes</a>

### 1. Introdução

&emsp; A qualidade da conectividade sem fio é um fator crítico em aplicações de Internet das Coisas (IoT), impactando a estabilidade da comunicação e a integridade da transmissão de dados. A intensidade do sinal, medida em decibéis por miliwatt (dBm), fornece uma métrica precisa sobre a força do sinal recebido por um dispositivo.

&emsp; Este projeto propõe a implementação de um sistema de monitoramento contínuo da potência do sinal WiFi, utilizando um microcontrolador ESP32 para coletar dados em tempo real e uma plataforma IoT (Ubidots) para visualização. O experimento culmina na simulação do efeito Gaiola de Faraday, um fenômeno de bloqueio de ondas eletromagnéticas por meio da entrada e saída de um elevador, demonstrando a variação abrupta da conectividade.

### 2. Objetivo

&emsp; O objetivo principal deste projeto é desenvolver uma solução IoT funcional capaz de monitorar, registrar e visualizar a potência do sinal WiFi (dBm) em diferentes cenários ambientais.

**Objetivos específicos:**

- Utilizar um ESP32 para medir a potência do sinal WiFi da rede conectada (Inteli.Iot).

- Implementar o protocolo MQTT para transferir os valores de dBm para uma plataforma online (Ubidots).

- Configurar um dashboard na Ubidots com um gráfico contínuo (tempo x dBm) em tempo real.

### 3. Desenvolvimento

**3.1. Hardware e Bibliotecas**
<img src="assets\esp.jpeg">
**Componente/Software**

- Função

- ESP32

- Microcontrolador, responsável pela medição do sinal (RSSI) e comunicação MQTT.

**Ambiente de desenvolvimento e carregamento do código.**

- UbidotsEsp32Mqtt

- Biblioteca para simplificar a conexão WiFi e a comunicação MQTT com a Ubidots.

**WiFi.h**

- Biblioteca nativa do ESP32, essencial para a função WiFi.RSSI().

### 3.2. Medição da Potência do Sinal (RSSI/dBm)

&emsp; A intensidade do sinal WiFi é medida em RSSI (Received Signal Strength Indicator), que é expresso em dBm (decibéis por miliwatt). Valores mais próximos de zero (ex: -30 dBm) indicam um sinal forte, enquanto valores mais distantes (ex: -90 dBm) indicam um sinal fraco.

**Função de Coleta:**
&emsp; A leitura do dBm é realizada através da função nativa do ESP32, que retorna um valor inteiro:

**int32_t dBm = WiFi.RSSI();**


### 3.3. Comunicação MQTT e Plataforma IoT (Ubidots)

&emsp; A plataforma Ubidots foi escolhida para gerenciar a comunicação e a visualização dos dados. Utilizamos a biblioteca UbidotsEsp32Mqtt que abstrai a complexidade do protocolo MQTT.

&emsp; Credenciais e Configuração:
&emsp; As credenciais de rede e Ubidots foram configuradas no cabeçalho do código:

```
WIFI_SSID: "Inteli.Iot"

WIFI_PASS: "Senha Wifi"

UBIDOTS_TOKEN: [Seu Token]

DEVICE_LABEL: "Nome no ubdotis"

VARIABLE_LABEL: "dbm"
```

Processo de Publicação:

- O valor de dBm é lido.

- O valor é adicionado ao payload da Ubidots: ubidots.add(VARIABLE_LABEL, dBm);

- O payload é enviado para o servidor MQTT da Ubidots: ubidots.publish(DEVICE_LABEL);

### 3.4. Configuração do Dashboard na Ubidots

**Gráfico de Linhas (Widget):** O  gráfico de linhas é contínuo, confirmando o uso de um Line Chart ou Time-Series para rastrear a potência em tempo real.

<img src="assets\grafico.png">

**Eixo Y (Potência do Sinal):** O eixo vertical exibe valores em dBm (de -100 a -30), que é a unidade de medida correta para a potência do sinal, conforme descrito.

**Eixo X (Tempo):** O eixo horizontal mostra a data e o horário (11:01, 11:15, etc.), confirmando que é um gráfico Tempo (Timestamp).

**Análise da Variação:** O padrão do gráfico — com picos altos (sinal forte, perto de -30 dBm) e quedas abruptas (sinal fraco, perto de -80 dBm ou mais) — é exatamente o que se espera de um teste de movimentação e, principalmente, do bloqueio de sinal no elevador.

### 4. Resultados e Análise do Experimento

**4.1. Testes de CenárioTestes de Monitoramento de Potência de Sinal**

&emsp; Foram realizados testes de monitoramento de potência do sinal em quatro localidades distintas para demonstrar a funcionalidade e sensibilidade do sistema, registrando diferenças significativas na intensidade (dBm) em função da distância e dos obstáculos.
| Localização (Cenário)                 | Condição Principal                         | Potência Média (dBm) | Estabilidade | Análise |
|---------------------------------------|---------------------------------------------|------------------------|--------------|---------|
| Ateliê                                | Proximidade e linha de visada boa           | -45 a -55 dBm          | Alta         | O sinal se manteve estável e forte por 10 segundos, estabelecendo a linha de base ideal para o experimento. |
| IT Bar                                | Área de alta cobertura e uso                | -50 a -55 dBm          | Alta         | O sinal se mostrou consistentemente bom e confiável, como esperado em uma área de suporte técnico. |
| Laboratório                           | Uso e obstáculos (paredes/equipamentos)     | -55 a -60 dBm          | Média        | Sinal bom, com leve atenuação, mas adequado para aplicações IoT. |
| Catraca da Entrada                    | Extensão da cobertura e ruído               | -65 a -75 dBm          | Baixa        | O sinal oscilava bastante, refletindo zona de borda da cobertura WiFi, com mais ruído e menor potência. |
| Quadra de Vôlei (Fora do Inteli)      | Longa distância e paredes externas          | -70 a -75 dBm          | Baixa        | A longa distância gerou perda significativa de potência, porém o sinal ainda era detectável, mas com menor qualidade. |

### 4.2. Simulação da Gaiola de Faraday (Elevador)

&emsp; A simulação de bloqueio de sinal foi o ponto central do experimento, utilizando o elevador do Inteli para criar o efeito de Gaiola de Faraday.

&emsp; A Gaiola de Faraday, um invólucro condutor (como a cabine metálica do elevador), bloqueia ondas eletromagnéticas, reduzindo drasticamente a potência do sinal.

**Registro no Dashboard**

- Antes do Elevador: O sinal estava em uma faixa normal.

- Entrada no Elevador: O gráfico registrou uma queda imediata e acentuada na potência, atingindo -80 dBm — valor que indica péssima qualidade, quase no limite da desconexão.

- Período de Bloqueio (mais de 5 segundos): O sinal permaneceu no nível mais baixo (ruído).

- Saída do Elevador: O sinal logo se recuperou, retornando aos níveis normais externos.

&emsp; Essa variação abrupta e reversível registrada no dashboard validou a capacidade do sistema de monitorar em tempo real a perda de conectividade causada por barreiras físicas e demonstrou claramente o impacto da Gaiola de Faraday em comunicações sem fio.


### 5. Conclusão

&emsp; O projeto demonstrou com sucesso a aplicação de conceitos fundamentais de IoT para monitoramento de infraestrutura. Utilizando o ESP32 e o protocolo MQTT (via Ubidots), foi possível:

&emsp; Estabelecer um sistema confiável para medição contínua da qualidade de conectividade (dBm).

&emsp; Comprovar o efeito de bloqueio eletromagnético da Gaiola de Faraday, visualizando a perda de sinal em tempo real no dashboard.

&emsp; A integração do hardware de baixo custo com uma plataforma de nuvem permitiu uma análise de dados poderosa, reforçando a importância do monitoramento de sinais para garantir a resiliência de soluções IoT em ambientes complexos.

🔗 [Link para o Vídeo da Demonstração](https://drive.google.com/file/d/1IYqtS2FIjq2ubKIwzjgX1ruJAWkBNI9r/view?usp=sharing)
