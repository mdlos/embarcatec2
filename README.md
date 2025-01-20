
<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=02A6F4&height=120&section=header"/>
<h1 align="center">Embarcatec | Segunda Atividade Em Grupo</h1>

<div align="center">  
  <img width=40% src="http://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=02A6F4&style=for-the-badge"/>
</div>

<div align="center">
 <a href="#-objetivo-do-projeto"> Objetivo do Projeto</a> • 
  <a href="#-lista-de-requisitos"> Requisitos</a> • 
 <a href="#-tecnologias"> Tecnologias</a> • 
 <a href="#-desenvolvedores"> Desenvolvedores</a>
</div>

## Objetivo do Projeto

Com o auxílio do simulador de eletrônica Wokwi, utilize um teclado matricial 4x4 (ilustrado na Figura 1) para controlar determinados pinos GPIO do microcontrolador RP2040, presente na placa de desenvolvimento Raspberry Pi Pico W. Para esta atividade, realize o acionamento de 03 LEDs (tipo RGB), juntamente com o controle do sinal sonoro de um buzzer. 
Nesta prática, será necessário simular os seguintes componentes: 
1) Teclado matricial 4x4. 
2) 03 LEDs – tipo RGB. 
3) Componente Buzzer. 
4) Microcontrolador Raspberry Pi Pico W. 

## 🗒️ Lista de requisitos

- Deve-se utilizar o ambiente de desenvolvimento VS Code em todas as duas atividades; 
- Os códigos devem ser escritos na linguagem C, juntamente com os recursos do kit de Desenvolvimento de Software Pico SDK; 
- O simulador Wokwi deve estar integrado ao ambiente de desenvolvimento VS Code; 
- Deve-se criar um repositório do github para o versionamento, registro e submissão dessa atividade.

## 🛠 Tecnologias

1. **Git e Github**;
2. **VScode**;
3. **Linguagem C**;

## 🔧 Funcionalidades Implementadas:

1. Controle dos LEDs RGB via Teclado Matricial:
Botão A: Acende o LED vermelho.
Botão B: Acende o LED azul.
Botão C: Acende o LED verde.
Botão D: Acende todos os LEDs (vermelho, azul e verde).

2. Controle de LEDs e Buzzer com Botões Específicos:
Botões * e #: Emite um bip no buzzer e em seguinda emite um alerta piscando os leds e bips curtos.
Botões numéricos (1 a 9): Apaga o LED que estava aceso.

3. Sequência de LEDs:
Botão 0: Acende os LEDs RGB em sequência, um por vez.

4. Toque de música no buzzer e acendimento de LEDs:
Botão #: Toca a música "Brilha Brilha Estrelinha" no buzzer com acendimento de uma combinação LEDs a cada nota musical.

## 👥 Contribuições:

- Marcio: Responsável pela criação da branch "main.c" e inicialização do código.
- José Vinicius: Programou o arquivo diagram.json para a simulação do acionamento dos LEDs, e ajustou o código "main.c" para os LEDs acenderem de acordo com os botões pressionados no teclado matricial.
- Moises: Adicionou a funcionalidade de bip do buzzer para os botões * e #.
- Sara: Implementou a funcionalidade em que ao clicar em qualquer número de 1 a 9 ele acende o led a quantidade de vezes correspondente ao número.
- Paola e Pedro: Implementaram a funcionalidade de acender os LEDs RGB em sequência ao pressionar o botão 0.
- Alexsami: Implementou a funcionalidade de tocar a música "Brilha Brilha Estrelinha" no buzzer com acendimento de uma combinação LEDs a cada nota musical ao clicar em "#".

## 💻 Desenvolvedores
 
<table>
  <tr>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/72825281?v=4" width="100px;" alt=""/><br /><sub><b> Marcio Fonseca </b></sub></a><br />👨‍💻</a></td>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/191687774?v=4" width="100px;" alt=""/><br /><sub><b> José Vinicius </b></sub></a><br />👨‍💻</a></td>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/164667970?v=4" width="100px;" alt=""/><br /><sub><b> Pedro Barros
    </b></sub></a><br />👨‍💻</a></td>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/124692269?v=4" width="100px;" alt=""/><br /><sub><b> Paola Fagundes </b></sub></a><br />👨‍💻</a></td>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/143294885?v=4" width="100px;" alt=""/><br /><sub><b> Sara Souza </b></sub></a><br />👨‍💻</a></td>
<td align="center"><img style="" src="https://avatars.githubusercontent.com/u/135754687?v=4" width="100px;" alt=""/><br /><sub><b> João Paulo </b></sub></a><br />👨‍💻</a></td>
<td align="center"><img style="" src="https://avatars.githubusercontent.com/u/96251377?v=4" width="100px;" alt=""/><br /><sub><b> Moises Amorim </b></sub></a><br />👨‍💻</a></td>
<td align="center"><img style="" src="https://avatars.githubusercontent.com/u/103523809?v=4" width="100px;" alt=""/><br /><sub><b> Alexsami Lopes </b></sub></a><br />👨‍💻</a></td>
<td align="center"><img style="" src="https://avatars.githubusercontent.com/u/60956248?v=4" width="100px;" alt=""/><br /><sub><b> Ramom Andrade </b></sub></a><br />👨‍💻</a></td>
  </tr>
</table>


## 🎥 Demonstração: 
- Para ver o funcionamento do projeto, acesse o vídeo de demonstração gravado por José Vinicius: https://youtu.be/qXF3vxX_nmM
- Extras - Vídeo demostrando implementações extras: https://youtu.be/94Wgb6CxeaM
