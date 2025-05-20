# Tópicos MQTT Utilizados no Projeto

Este documento descreve todos os tópicos MQTT utilizados no projeto de monitoramento de temperatura da água, que utiliza um sensor DHT22, uma placa ESP32, um servo motor e interface gráfica via Node-RED.

---

## 1. `ods6_iot/agua/temperatura`

- **Tipo:** Publicador
- **Publicado por:** ESP32
- **Formato da mensagem:** Número decimal (ex: `27.35`)
- **Descrição:** 
  Publica a temperatura da água lida pelo sensor DHT22 a cada 3 segundos. Essa temperatura é visualizada no painel do Node-RED via gauge e gráfico histórico.

---

## 2. `ods6_iot/agua/status`

- **Tipo:** Publicador
- **Publicado por:** ESP32
- **Formato da mensagem:** Texto (string)
- **Exemplos de mensagem:**
  - `Temperatura abaixo de 28.00 °C, atuador em repouso.`
  - `Temperatura acima de 28.00 °C, atuador acionado.`
- **Descrição:** 
  Informa o status atual do sistema baseado na comparação da temperatura medida com o limite configurado. Essa mensagem é exibida em um campo de texto no painel do Node-RED.

---

## 3. `ods6_iot/agua/alerta`

- **Tipo:** Publicador
- **Publicado por:** ESP32
- **Formato da mensagem:** `true` ou `false`
- **Descrição:**
  Indica se o atuador foi acionado devido à temperatura estar acima do limite. Esse valor aciona o LED virtual no painel do Node-RED:
  - `true` → LED vermelho (alerta)
  - `false` → LED verde (normal)

---

## 4. `ods6_iot/agua/config/limite`

- **Tipo:** Assinante
- **Assinado por:** ESP32
- **Formato da mensagem:** Número decimal (ex: `30.5`)
- **Descrição:**
  Permite ao usuário atualizar dinamicamente o limite de temperatura diretamente pelo painel do Node-RED. O novo valor é armazenado em tempo de execução no ESP32 e afeta imediatamente o comportamento do sistema.

---

## Observações

- O prefixo `ods6_iot/agua/` foi escolhido para representar o contexto do projeto, que simula ações relacionadas ao Objetivo de Desenvolvimento Sustentável 6 (Água potável e saneamento).
- Todos os tópicos são públicos e utilizam o broker gratuito `broker.hivemq.com` na porta `1883`.
- As mensagens são transmitidas no formato padrão UTF-8, com QoS 0 (sem garantias de entrega).

---
