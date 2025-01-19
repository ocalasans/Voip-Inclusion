# Voip-Inclusion

Voip-Inclusion é uma biblioteca para integração simplificada do SAMPVOICE em seu Gamemode SA-MP, oferecendo máxima flexibilidade e controle sobre o sistema de comunicação por voz.

## Idiomas

- Deutsch: [README](translations/Deutsch/README.md)
- English: [README](translations/English/README.md)
- Español: [README](translations/Espanol/README.md)
- Français: [README](translations/Francais/README.md)
- Italiano: [README](translations/Italiano/README.md)
- Polski: [README](translations/Polski/README.md)
- Русский: [README](translations/Русский/README.md)
- Svenska: [README](translations/Svenska/README.md)
- Türkçe: [README](translations/Turkce/README.md)

## Índice

- [Voip-Inclusion](#voip-inclusion)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Instalação](#instalação)
  - [Requisitos](#requisitos)
  - [Características Principais](#características-principais)
  - [Sistema Global x Individual](#sistema-global-x-individual)
    - [GLOBAL\_VOIP](#global_voip)
    - [NOT\_GLOBAL\_VOIP](#not_global_voip)
  - [Configuração Básica](#configuração-básica)
    - [Inicialização do Sistema](#inicialização-do-sistema)
  - [Funções de Controle](#funções-de-controle)
    - [Voip\_Create](#voip_create)
    - [Voip\_Delete](#voip_delete)
    - [Voip\_Distance](#voip_distance)
  - [Funções de Feedback](#funções-de-feedback)
    - [Voip\_NotFound](#voip_notfound)
    - [Voip\_NoMicrophone](#voip_nomicrophone)
    - [Voip\_Global](#voip_global)
    - [Voip\_Player](#voip_player)
  - [Funções de Stream](#funções-de-stream)
    - [Voip\_GetGlobalStream](#voip_getglobalstream)
    - [Voip\_GetLocalStream](#voip_getlocalstream)
    - [Voip\_SetGlobalStream](#voip_setglobalstream)
    - [Voip\_SetLocalStream](#voip_setlocalstream)
  - [Exemplos de Uso](#exemplos-de-uso)
    - [Configuração Completa](#configuração-completa)
  - [Callbacks Personalizados](#callbacks-personalizados)
  - [Licença](#licença)
    - [Condições:](#condições)

## Instalação

1. Faça o download do arquivo [Voip-Inclusion.inc](https://github.com/ocalasans/Voip-Inclusion/releases/download/v1.0.1/Voip-Inclusion.inc)
2. Coloque o arquivo na pasta `pawno/include` do seu servidor
3. Adicione a seguinte linha após seus outros includes:
```pawn
#include <Voip-Inclusion>
```

## Requisitos

- [SAMPVOICE](https://github.com/CyberMor/sampvoice) versão 3.1 ou inferior (que seja compatível)
- Plugin do SAMPVOICE ativado no `server.cfg`

> [!IMPORTANT]
> Este include é compatível apenas com a versão 3.1 ou inferior (que seja compatível) do SAMPVOICE.

## Características Principais

- **Sistema de Execução Flexível**
  - Suporte a operações globais e individuais
  - Gerenciamento eficiente de callbacks

- **Gerenciamento de Streams**
  - Stream global automática (inicializada no OnGameModeInit do include)
  - Streams locais personalizáveis por jogador
  - Controle granular de distância de voz

- **Sistema de Feedback**
  - Mensagens totalmente personalizáveis
  - Notificações de status do sistema
  - Feedback de conexão e microfone

- **Recursos Avançados**
  - Callbacks customizáveis
  - Acesso direto às streams
  - Controle preciso de distância de voz

## Sistema Global x Individual

O sistema de `GLOBAL_VOIP` e `NOT_GLOBAL_VOIP` determina como as callbacks serão executadas:

### GLOBAL_VOIP

- Executa a callback para todos os jogadores conectados
- Não requer especificação de `playerid`
- Útil para ações que afetam todos os jogadores simultaneamente

### NOT_GLOBAL_VOIP

- Executa a callback para um jogador específico
- Requer especificação de `playerid`
- Útil para ações individuais por jogador

## Configuração Básica

### Inicialização do Sistema

```pawn
public OnGameModeInit()
{
    // Ativar publics padrão
    Voip_EnableDefaultPublics(true);
    
    // A stream global é criada automaticamente pelo include aqui

    return true;
}

public OnPlayerConnect(playerid)
{
    // Criar Voip local para o jogador
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local", playerid);

    return true;
}
```

## Funções de Controle

### Voip_Create

```pawn
Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
Cria uma nova instância de Voip.
- `VII_global`: Define se a criação afetará todos os jogadores (`GLOBAL_VOIP`) ou um jogador específico (`NOT_GLOBAL_VOIP`)
- `VII_distance`: Distância máxima de alcance da voz
- `VII_max_players`: Número máximo de jogadores (use `SV_INFINITY` para ilimitado)
- `VII_color`: Cor das mensagens
- `VII_name`: Nome da instância
- `playerid`: ID do jogador (apenas quando `NOT_GLOBAL_VOIP`)

### Voip_Delete

```pawn
Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
Remove instância(s) de Voip.

### Voip_Distance

```pawn
Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Ajusta a distância de alcance da voz.

## Funções de Feedback

### Voip_NotFound

```pawn
Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envia feedback quando o Voip não é detectado.

### Voip_NoMicrophone

```pawn
Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envia feedback quando o microfone não é detectado.

### Voip_Global

```pawn
Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envia feedback sobre a conexão com o Voip global (criado no OnGameModeInit do include).
```pawn
// Exemplo individual
Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip global conectado. Pressione Z para falar.", playerid);

// Exemplo global
if(IsAdmin[playerid]) // Supondo que seja administrador.
    Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "Voip global conectado para todos. Pressione Z para falar.");
```

### Voip_Player

```pawn
Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envia feedback sobre a conexão com o Voip local do jogador.
```pawn
// Exemplo individual
Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip local conectado. Pressione B para falar.", playerid);

// Exemplo global
Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "Voip local conectado para todos. Pressione B para falar.");
```

## Funções de Stream

### Voip_GetGlobalStream

```pawn
SV_GSTREAM:Voip_GetGlobalStream()
```
Retorna a stream global criada no OnGameModeInit do include.

### Voip_GetLocalStream

```pawn
SV_DLSTREAM:Voip_GetLocalStream(playerid)
```
Retorna a stream local de um jogador específico.

### Voip_SetGlobalStream

```pawn
bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream)
```
Define uma nova stream global.

### Voip_SetLocalStream

```pawn
bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream)
```
Define uma nova stream local para um jogador.

## Exemplos de Uso

### Configuração Completa

Ativar publics padrão:
```pawn
public OnGameModeInit()
{
    Voip_EnableDefaultPublics(true);

    return true;
}
```

Criar Voip local para o jogador específico:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local", playerid);
    
    return true;
}
```

Enviar feedback do Voip tanto global quanto local para o jogador específico:
```pawn
public OnPlayerSpawn(playerid)
{
    if(IsAdmin[playerid]) // Supondo que seja administrador.
        Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip global disponível. Pressione Z para falar.", playerid);
    
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip local ativado. Pressione B para falar.", playerid);

    return true;
}
```

Exemplo de comando que afeta todos os jogadores:
```pawn
CMD:voipglobaldist(playerid)
{
    if(IsPlayerAdmin(playerid))
        // Altera a distância do Voip para todos os jogadores
        Voip_Distance(GLOBAL_VOIP, 50.0, 0xFFFFFFFF, "Administrador alterou a distância do Voip para 50 metros.");
    
    return true;
}
```

## Callbacks Personalizados

Se você desativou as publics padrão usando `Voip_EnableDefaultPublics(false)`, pode implementar seus próprios callbacks:

```pawn
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    // Seu código personalizado aqui
    // keyid 0x42 (B) para Voip local
    // keyid 0x5A (Z) para Voip global
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Seu código personalizado aqui
}
```

## Licença

Este Include está protegido sob a Licença Apache 2.0, que permite:

- ✔️ Uso comercial e privado
- ✔️ Modificação do código fonte
- ✔️ Distribuição do código
- ✔️ Concessão de patentes

### Condições:

- Manter o aviso de direitos autorais
- Documentar alterações significativas
- Incluir cópia da licença Apache 2.0

Para mais detalhes sobre a licença: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Todos os direitos reservados**
