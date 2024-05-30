# Projeto de Monitoramento de Qualidade da Água com ESP32

Este projeto utiliza um ESP32 em conjunto com sensores DHT22, LDR e um potenciômetro para simular um sensor de pH. O objetivo é monitorar dados ambientais, como temperatura, umidade, luminosidade e pH simulado, e enviar esses dados para um servidor MQTT.

## Requisitos

- ESP32
- Sensor de temperatura e umidade DHT22
- Sensor de luminosidade LDR
- Potenciômetro (simulação de sensor de pH)
- Tela LCD I2C
- Acesso à rede Wi-Fi

## Dependências

- DHT sensor library for ESPx
- PubSubClient
- ArduinoJson
- LiquidCrystal I2C

## Instruções de Uso

1. Clone ou baixe o repositório do projeto.
2. Abra o código-fonte no Arduino IDE.
3. Instale as bibliotecas necessárias: DHT sensor library for ESPx, PubSubClient, ArduinoJson e LiquidCrystal I2C.
4. Conecte o ESP32 à porta USB do seu computador.
5. Compile e envie o código para o ESP32.
6. Os dados serão exibidos no LCD I2C.

Certifique-se de configurar corretamente o acesso à rede Wi-Fi e as credenciais do servidor MQTT no código antes de enviar para o ESP32.

## Funcionamento

O ESP32 realiza a leitura dos sensores DHT22 e LDR, e do potenciômetro (simulando o sensor de pH). Os dados são formatados em um JSON e enviados para um servidor MQTT no tópico "tago/data/post".

## Equipe

Este projeto foi desenvolvido por:

- **Eduardo Brites** - RM 552943
- **Gabriel Leão** - RM 552642
- **Karolina Soares** - RM 554187

## Licença

Este projeto é licenciado sob a Licença MIT. Para mais detalhes, consulte o arquivo LICENSE no repositório.

---
