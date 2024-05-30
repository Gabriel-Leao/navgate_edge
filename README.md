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

## Contato

Para mais informações, entre em contato com o desenvolvedor:

- Nome: Gabriel Leão
- E-mail: gabriel.leao2507@gmail.com

---