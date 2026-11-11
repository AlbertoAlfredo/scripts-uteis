# scripts-uteis

Coleção de scripts utilitários, rotinas de automação e ferramentas de linha de comando para manutenção de ambiente, produtividade e gerenciamento de sistemas (Windows & Linux).

Cada diretório deste repositório contém uma ferramenta isolada acompanhada de sua própria documentação detalhada.

---

##  Estrutura do Repositório

O projeto é organizado no formato modular, onde cada script possui sua própria pasta e documentação dedicada:

```text
.
├── 📁 winget-auto-updater/
│   ├── 📄 winget.bat
│   └── 📄 README.md
│
└── 📄 README.md (este arquivo)

```

---

##  Scripts Disponíveis

| Diretório / Script | Plataforma | Descrição |
| --- | --- | --- |
| [`winget-auto-updater`](https://github.com/AlbertoAlfredo/scripts-uteis/tree/main/winget-auto-updater) | Windows | Atualização silenciosa e automatizada de todos os pacotes via Winget com auto-elevação para Administrador. |

*(Novas ferramentas serão listadas aqui conforme forem adicionadas).*

---

## Convenções do Repositório

Para manter a consistência e facilidade de manutenção:

1. **Uma pasta por script:** Cada ferramenta utilitária reside em seu próprio diretório.
2. **README dedicado:** Cada subpasta contém um arquivo `README.md` explicando:
* Objetivo e funcionamento lógico do script.
* Modos de execução (manual, inicialização automática, agendador de tarefas, cron etc.).
* Dependências e permissões necessárias.


3. **Autonomia:** Os scripts são projetados para rodar de forma autônoma e independente de dependências cruzadas entre pastas.

---

## Cuidados e Permissões

* Scripts que realizam alterações a nível de sistema (como modificação de pacotes, serviços ou registros) costumam exigir privilégios elevados (`RunAs Administrator` no Windows ou `sudo` no Linux).
* Revise o código-fonte antes de executar qualquer script com permissões administrativas na sua máquina.

---

## Licença

Este repositório é distribuído sob a licença [MIT](https://github.com/AlbertoAlfredo/scripts-uteis/blob/main/LICENSE)
```

```