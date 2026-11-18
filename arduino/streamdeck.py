
import serial
import ctypes

arduino = serial.Serial('COM3', 9600, timeout=1)

# Códigos virtuais das teclas F13 até F24
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

    # Pressiona a tecla
    ctypes.windll.user32.keybd_event(
        vk, 0, 0, 0
    )

    # Solta a tecla
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
