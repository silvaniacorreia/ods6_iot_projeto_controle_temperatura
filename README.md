# Monitoramento de Temperatura Aquática com IoT

Este projeto simula um sistema de monitoramento de temperatura da água com ESP32, sensor DHT22, servo motor e protocolo MQTT, utilizando as plataformas Wokwi e Node-RED.

## Objetivos
- Monitorar a temperatura da água em tempo real
- Enviar dados via protocolo MQTT para um dashboard
- Atuar sobre um servo motor em caso de temperatura acima do limite
- Permitir que o limite de temperatura seja ajustado remotamente via MQTT

## Componentes
- ESP32 DevKit v1
- Sensor de temperatura DHT22
- Servo motor SG90
- Broker público HiveMQ
- Dashboard Node-RED

## Tópicos MQTT utilizados
- `ods6_iot/agua/temperatura`: publica a temperatura lida
- `ods6_iot/agua/status`: publica o status do atuador
- `ods6_iot/agua/alerta`: envia alerta de temperatura
- `ods6_iot/agua/config/limite`: recebe novo limite de temperatura

## Como usar
1. Abra o projeto no Wokwi com o código `ESP32_DHT22_MQTT.ino`.
2. Configure o Node-RED conforme o fluxo incluído na pasta `node-red/`.
3. No dashboard, observe os dados publicados, altere o limite e visualize o comportamento do atuador.

## Autor
Silvania Goularte Correia - Projeto para disciplina Objetos Inteligentes Conectados - 2025
