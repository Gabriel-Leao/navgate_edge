# Projeto de Monitoramento Água com ESP32

Este projeto utiliza um ESP32 em conjunto com sensores DHT22, LDR e um potenciômetro para simular um sensor de pH. O objetivo é monitorar dados ambientais, como temperatura, umidade, luminosidade e pH simulado, e enviar esses dados para um servidor MQTT.

## Requisitos

- ESP32
- Sensor de temperatura e umidade DHT22
- Sensor de luminosidade LDR
- Potenciômetro (simulação de sensor de pH)
- Acesso à rede Wi-Fi

## Dependências

- DHT sensor library for ESPx
- PubSubClient
- ArduinoJson

## Instruções de Uso

1. Clone ou baixe o repositório do projeto.
2. Abra o código-fonte no Arduino IDE.
3. Instale as bibliotecas necessárias: DHT sensor library for ESPx, PubSubClient e ArduinoJson.
4. Conecte o ESP32 à porta USB do seu computador.
5. Compile e envie o código para o ESP32.
6. Abra o monitor serial para visualizar os dados coletados e enviados.

Certifique-se de configurar corretamente o acesso à rede Wi-Fi e as credenciais do servidor MQTT no código antes de enviar para o ESP32.

## Funcionamento

O ESP32 realiza a leitura dos sensores DHT22 e LDR, e do potenciômetro (simulando o sensor de pH). Os dados são formatados em um JSON e enviados para um servidor MQTT no tópico "tago/data/post".

## Equipe

Para mais informações, entre em contato com os desenvolvedores:

<div>
<p>
  <img src="https://github.com/Projeto-Dev-Aula/cp2-front-web-2sem/assets/145347801/900140b6-2724-452a-a822-296d38ace27f" width="75" height="75" alt="Eduardo foto" />  Eduardo Brites - RM 552943 <br>
</p>

<p>
  <img src="https://github.com/Projeto-Dev-Aula/cp2-front-web-2sem/assets/145347801/aa2590ea-10d1-4fbb-82f9-52e05fa5339a" width="75" height="75" alt="Gabriel foto" />  Gabriel Leão - RM 552642 <br>
</p>

<p>
  <img src="https://github.com/Projeto-Dev-Aula/cp2-front-web-2sem/assets/145347801/addf3154-41e5-4227-ba6d-887d3ea737a1" width="75" height="75" alt="Karol foto" /> Karolina Soares - RM 554187 
</p>
</div>

---