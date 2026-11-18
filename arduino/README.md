# Arduino DIY Stream Deck

**Stream Deck caseiro utilizando Arduino UNO + Python + comunicação Serial USB.**

## 1. Sobre o projeto

Este projeto transforma um Arduino UNO em um controlador de atalhos de teclado (DIY Stream Deck).

O Arduino recebe os comandos dos botões físicos e envia mensagens pela porta serial USB para o computador. Um programa Python interpreta essas mensagens e simula o pressionamento de teclas no sistema operacional.

O projeto funciona em Windows e Linux, com pequenas diferenças na configuração do Python.

### Arquitetura

```text
BOTÕES FÍSICOS
      |
      v
ARDUINO UNO
      |
      | USB / Comunicação Serial
      |
      v
PYTHON NO COMPUTADOR
      |
      v
SIMULAÇÃO DE TECLADO
      |
      v
SISTEMA OPERACIONAL
      |
      v
PROGRAMAS E ATALHOS
```

## 2. Componentes utilizados

- 1 Arduino UNO.
- 3 botões físicos.
- Fios para conexão.
- Cabo USB para conectar o Arduino ao computador.
- Computador com Python instalado.

## 3. Ligações elétricas

Os botões utilizam a configuração `INPUT_PULLUP`, dispensando resistores externos de pull-up.

| Botão | Pino Arduino | Comando serial |
|---|---|---|
| Botão 1 | Digital 2 | F13 |
| Botão 2 | Digital 3 | F14 |
| Botão 3 | Digital 4 | F15 |

Cada botão deve ser conectado entre o respectivo pino digital e o GND.

**Funcionamento do INPUT_PULLUP:**

- HIGH: botão solto.
- LOW: botão pressionado.

## 4. Código do Arduino

Arquivo: `streamdeck.ino`

```cpp
const int pinoLed = LED_BUILTIN;

const int f13 = 2;
const int f14 = 3;
const int f15 = 4;

void setup() {
  pinMode(pinoLed, OUTPUT);

  pinMode(f13, INPUT_PULLUP);
  pinMode(f14, INPUT_PULLUP);
  pinMode(f15, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  pressionarBotao(f13, "F13");
  pressionarBotao(f14, "F14");
  pressionarBotao(f15, "F15");
}

void pressionarBotao(int pino, const char* comando) {

  if (digitalRead(pino) == LOW) {

    digitalWrite(pinoLed, HIGH);

    Serial.println(comando);

    while (digitalRead(pino) == LOW) {
      delay(10);
    }

    digitalWrite(pinoLed, LOW);
    delay(50);
  }
}
```

### Funcionamento do firmware

Quando um botão é pressionado:

1. O Arduino identifica o pino em nível LOW.
2. Acende o LED interno.
3. Envia o comando correspondente pela Serial.
4. Aguarda o botão ser solto.
5. Apaga o LED.

O sistema envia apenas um comando por pressionamento, evitando repetição enquanto o botão permanece apertado.

**Velocidade serial:** 9600 baud.

## 5. Configuração no Windows

### Instalação das dependências

```bash
pip install pyserial
```

### Identificação da porta serial

No exemplo deste projeto, a porta utilizada é:

```text
COM3
```

É possível verificar a porta pelo Gerenciador de Dispositivos do Windows, na seção Portas (COM e LPT).

### Código Python

Arquivo: `streamdeck.py`

```python
import serial
import ctypes

arduino = serial.Serial('COM3', 9600, timeout=1)

TECLAS = {
    "F13": 0x7C,
    "F14": 0x7D,
    "F15": 0x7E,
    "F16": 0x7F,
    "F17": 0x80,
    "F18": 0x81,
    "F19": 0x82,
    "F20": 0x83,
    "F21": 0x84,
    "F22": 0x85,
    "F23": 0x86,
    "F24": 0x87
}

def pressionar_tecla(nome):
    if nome not in TECLAS:
        return

    vk = TECLAS[nome]

    ctypes.windll.user32.keybd_event(
        vk, 0, 0, 0
    )

    ctypes.windll.user32.keybd_event(
        vk, 0, 0x0002, 0
    )

    print(f"Tecla enviada: {nome}")

print("Stream Deck iniciado!")

while True:
    comando = arduino.readline().decode(
        'utf-8', errors='ignore'
    ).strip()

    pressionar_tecla(comando)
```

O programa utiliza os códigos virtuais de teclado do Windows para enviar F13 até F24.

## 6. Configuração no Linux

### Instalação das dependências

```bash
pip install pyserial pynput
```

### Identificação da porta serial

Normalmente, o Arduino UNO aparece como:

```text
/dev/ttyACM0
```

Em alguns casos:

```text
/dev/ttyUSB0
```

Para verificar:

```bash
ls /dev/ttyACM*
```

### Permissão de acesso à porta serial

Em distribuições baseadas em Debian e Ubuntu, incluindo Linux Mint:

```bash
sudo usermod -aG dialout $USER
```

Após executar o comando, encerre a sessão e entre novamente.

### Código Python

Arquivo: `streamdeck.py`

```python
import serial
from pynput.keyboard import Controller, Key

arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

teclado = Controller()

TECLAS = {
    "F13": Key.f13,
    "F14": Key.f14,
    "F15": Key.f15,
    "F16": Key.f16,
    "F17": Key.f17,
    "F18": Key.f18,
    "F19": Key.f19,
    "F20": Key.f20,
    "F21": Key.f21,
    "F22": Key.f22,
    "F23": Key.f23,
    "F24": Key.f24
}

print("Stream Deck Linux iniciado!")

while True:
    comando = arduino.readline().decode(
        'utf-8', errors='ignore'
    ).strip()

    if comando in TECLAS:
        teclado.press(TECLAS[comando])
        teclado.release(TECLAS[comando])

        print(f"Tecla enviada: {comando}")
```

**Observação:** o `pynput` pode apresentar limitações no Wayland. No X11, a injeção de teclas costuma funcionar diretamente. A compatibilidade também depende do ambiente gráfico e das permissões.

## 7. Mapeamento das teclas

O Arduino envia os seguintes comandos:

| Comando | Tecla simulada |
|---|---|
| F13 | F13 |
| F14 | F14 |
| F15 | F15 |
| F16 | F16 |
| F17 | F17 |
| F18 | F18 |
| F19 | F19 |
| F20 | F20 |
| F21 | F21 |
| F22 | F22 |
| F23 | F23 |
| F24 | F24 |

As teclas F13 até F24 podem ser utilizadas em programas que permitam configurar atalhos personalizados.

Exemplos de aplicações:

- OBS Studio.
- Discord.
- Photoshop.
- Editores de código.
- Aplicações de produtividade.
- Sistemas de automação.

## 8. Como executar

1. Conecte o Arduino ao computador.
2. Carregue o firmware `streamdeck.ino`.
3. Feche o Monitor Serial da IDE Arduino.
4. Verifique a porta serial.
5. Execute o programa Python:

```bash
python streamdeck.py
```

6. Pressione os botões físicos.
7. Configure as teclas F13, F14 e F15 nos programas desejados.

**Importante:** não abra simultaneamente o Monitor Serial e o programa Python, pois ambos precisam acessar a mesma porta COM.

## 9. Solução de problemas

| Problema | Possível solução |
|---|---|
| Porta COM ocupada | Fechar o Monitor Serial da IDE Arduino |
| Erro de conexão serial | Conferir a porta e a velocidade de 9600 baud |
| Permission denied no Linux | Adicionar usuário ao grupo dialout |
| Botões não respondem | Conferir ligação entre pino e GND |
| Teclas não são reconhecidas | Verificar se o programa aceita F13 até F24 |
| Python não encontra biblioteca | Instalar as dependências com pip |
| Teclas não funcionam no Wayland | Testar em uma sessão X11 |

## 10. Melhorias futuras

Ideias para evolução do projeto:

- [ ] Suporte para até 24 botões.
- [ ] Configuração dos botões por arquivo JSON.
- [ ] Perfis diferentes para trabalho, jogos e aulas.
- [ ] Combinações de teclas e macros.
- [ ] Inicialização automática com o sistema operacional.
- [ ] Interface gráfica para configurar os botões.
- [ ] Detecção automática da porta serial.
- [ ] Compatibilidade multiplataforma com um único código Python.
- [ ] Adição de LEDs indicadores.
- [ ] Utilização de displays para identificação das funções.

---

## Informações técnicas

| Característica | Configuração |
|---|---|
| Microcontrolador | Arduino UNO |
| Comunicação | USB Serial |
| Velocidade | 9600 baud |
| Linguagem do firmware | C++ (Arduino) |
| Linguagem do computador | Python |
| Windows | pyserial + ctypes |
| Linux | pyserial + pynput |
| Protocolo | Texto simples terminado em newline |
| Comandos iniciais | F13, F14 e F15 |

**Projeto DIY Stream Deck — Arduino UNO + Python**

Desenvolvimento experimental, expansível e multiplataforma.