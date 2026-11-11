# Winget Auto-Updater

Script em lote (`.bat`) projetado para atualizar automaticamente todos os softwares gerenciados pelo Windows Package Manager (`winget`) na máquina local.

O script inclui elevação automática de privilégios para Administrador via PowerShell e suprime confirmações manuais durante os upgrades.

---

## Como Funciona

1. **Checagem de Permissão:** O script verifica se a sessão atual possui privilégios de Administrador via `net session`.
2. **Auto-Elevação:** Caso não esteja elevado, invoca uma nova instância solicitando permissões elevadas (`RunAs`) e encerra o processo anterior.
3. **Execução Automatizada:** Executa o comando de atualização silenciosa cobrindo todos os pacotes detectados

---

## Modos de Uso
Modo 1: Execução Manual
Dê dois cliques no arquivo .bat.

Confirme o prompt do Controle de Conta de Usuário (UAC) quando solicitado.

Aguarde a finalização no terminal.

Modo 2: Execução na Inicialização do Sistema
Para manter seus programas atualizados a cada boot do Windows:

Pressione Win + R para abrir a janela Executar.

Digite shell:startup e pressione Enter (abre a pasta de inicialização do usuário).

Cole o arquivo .bat (ou um atalho apontando para ele) dentro dessa pasta.

## Pré-requisitos
Windows 10 (versão 1809+) ou Windows 11.

Windows Package Manager (winget) instalado e acessível nas variáveis de ambiente.

Conexão ativa com a internet.

## Observações
Dependendo do volume de programas desatualizados ou do tamanho dos downloads, o script pode levar alguns minutos na primeira execução.

Instaladores que não suportam flags silenciosas nativas podem abrir janelas temporárias durante o processo.