# Voip-Inclusion

Voip-Inclusion es una biblioteca para la integración simplificada de SAMPVOICE en tu Gamemode SA-MP, ofreciendo máxima flexibilidad y control sobre el sistema de comunicación por voz.

## Idiomas

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Índice

- [Voip-Inclusion](#voip-inclusion)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Instalación](#instalación)
  - [Requisitos](#requisitos)
  - [Características Principales](#características-principales)
  - [Sistema Global vs Individual](#sistema-global-vs-individual)
    - [GLOBAL\_VOIP](#global_voip)
    - [NOT\_GLOBAL\_VOIP](#not_global_voip)
  - [Configuración Básica](#configuración-básica)
    - [Inicialización del Sistema](#inicialización-del-sistema)
  - [Funciones de Control](#funciones-de-control)
    - [Voip\_Create](#voip_create)
    - [Voip\_Delete](#voip_delete)
    - [Voip\_Distance](#voip_distance)
  - [Funciones de Feedback](#funciones-de-feedback)
    - [Voip\_NotFound](#voip_notfound)
    - [Voip\_NoMicrophone](#voip_nomicrophone)
    - [Voip\_Global](#voip_global)
    - [Voip\_Player](#voip_player)
  - [Funciones de Stream](#funciones-de-stream)
    - [Voip\_GetGlobalStream](#voip_getglobalstream)
    - [Voip\_GetLocalStream](#voip_getlocalstream)
    - [Voip\_SetGlobalStream](#voip_setglobalstream)
    - [Voip\_SetLocalStream](#voip_setlocalstream)
  - [Ejemplos de Uso](#ejemplos-de-uso)
    - [Configuración Completa](#configuración-completa)
  - [Callbacks Personalizados](#callbacks-personalizados)
  - [Licencia](#licencia)
    - [Condiciones:](#condiciones)

## Instalación

1. Descarga el archivo [Voip-Inclusion.inc](https://github.com/ocalasans/Voip-Inclusion/releases/download/v1.0.1/Voip-Inclusion.inc)
2. Coloca el archivo en la carpeta `pawno/include` de tu servidor
3. Añade la siguiente línea después de tus otros includes:
```pawn
#include <Voip-Inclusion>
```

## Requisitos

- [SAMPVOICE](https://github.com/CyberMor/sampvoice) versión 3.1 o inferior (que sea compatible)
- Plugin de SAMPVOICE activado en `server.cfg`

> [!IMPORTANT]
> Este include es compatible solo con la versión 3.1 o inferior (que sea compatible) de SAMPVOICE.

## Características Principales

- **Sistema de Ejecución Flexible**
  - Soporte para operaciones globales e individuales
  - Gestión eficiente de callbacks

- **Gestión de Streams**
  - Stream global automático (inicializado en OnGameModeInit del include)
  - Streams locales personalizables por jugador
  - Control granular de distancia de voz

- **Sistema de Feedback**
  - Mensajes totalmente personalizables
  - Notificaciones de estado del sistema
  - Feedback de conexión y micrófono

- **Recursos Avanzados**
  - Callbacks personalizables
  - Acceso directo a los streams
  - Control preciso de distancia de voz

## Sistema Global vs Individual

El sistema de `GLOBAL_VOIP` y `NOT_GLOBAL_VOIP` determina cómo se ejecutarán los callbacks:

### GLOBAL_VOIP

- Ejecuta el callback para todos los jugadores conectados
- No requiere especificación de `playerid`
- Útil para acciones que afectan a todos los jugadores simultáneamente

### NOT_GLOBAL_VOIP

- Ejecuta el callback para un jugador específico
- Requiere especificación de `playerid`
- Útil para acciones individuales por jugador

## Configuración Básica

### Inicialización del Sistema

```pawn
public OnGameModeInit()
{
    // Activar publics predeterminados
    Voip_EnableDefaultPublics(true);
    
    // El stream global se crea automáticamente por el include aquí

    return true;
}

public OnPlayerConnect(playerid)
{
    // Crear Voip local para el jugador
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local", playerid);

    return true;
}
```

## Funciones de Control

### Voip_Create

```pawn
Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
Crea una nueva instancia de Voip.
- `VII_global`: Define si la creación afectará a todos los jugadores (`GLOBAL_VOIP`) o a un jugador específico (`NOT_GLOBAL_VOIP`)
- `VII_distance`: Distancia máxima de alcance de la voz
- `VII_max_players`: Número máximo de jugadores (usar `SV_INFINITY` para ilimitado)
- `VII_color`: Color de los mensajes
- `VII_name`: Nombre de la instancia
- `playerid`: ID del jugador (solo cuando `NOT_GLOBAL_VOIP`)

### Voip_Delete

```pawn
Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
Elimina instancia(s) de Voip.

### Voip_Distance

```pawn
Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Ajusta la distancia de alcance de la voz.

## Funciones de Feedback

### Voip_NotFound

```pawn
Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envía feedback cuando no se detecta el Voip.

### Voip_NoMicrophone

```pawn
Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envía feedback cuando no se detecta el micrófono.

### Voip_Global

```pawn
Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envía feedback sobre la conexión con el Voip global (creado en OnGameModeInit del include).
```pawn
// Ejemplo individual
Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip global conectado. Presiona Z para hablar.", playerid);

// Ejemplo global
if(IsAdmin[playerid]) // Suponiendo que sea administrador.
    Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "Voip global conectado para todos. Presiona Z para hablar.");
```

### Voip_Player

```pawn
Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envía feedback sobre la conexión con el Voip local del jugador.
```pawn
// Ejemplo individual
Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip local conectado. Presiona B para hablar.", playerid);

// Ejemplo global
Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "Voip local conectado para todos. Presiona B para hablar.");
```

## Funciones de Stream

### Voip_GetGlobalStream

```pawn
SV_GSTREAM:Voip_GetGlobalStream()
```
Retorna el stream global creado en OnGameModeInit del include.

### Voip_GetLocalStream

```pawn
SV_DLSTREAM:Voip_GetLocalStream(playerid)
```
Retorna el stream local de un jugador específico.

### Voip_SetGlobalStream

```pawn
bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream)
```
Define un nuevo stream global.

### Voip_SetLocalStream

```pawn
bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream)
```
Define un nuevo stream local para un jugador.

## Ejemplos de Uso

### Configuración Completa

Activar publics predeterminados:
```pawn
public OnGameModeInit()
{
    Voip_EnableDefaultPublics(true);

    return true;
}
```

Crear Voip local para el jugador específico:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local", playerid);
    
    return true;
}
```

Enviar feedback del Voip tanto global como local para el jugador específico:
```pawn
public OnPlayerSpawn(playerid)
{
    if(IsAdmin[playerid]) // Suponiendo que sea administrador.
        Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip global disponible. Presiona Z para hablar.", playerid);
    
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip local activado. Presiona B para hablar.", playerid);

    return true;
}
```

Ejemplo de comando que afecta a todos los jugadores:
```pawn
CMD:voipglobaldist(playerid)
{
    if(IsPlayerAdmin(playerid))
        // Cambia la distancia del Voip para todos los jugadores
        Voip_Distance(GLOBAL_VOIP, 50.0, 0xFFFFFFFF, "Administrador cambió la distancia del Voip a 50 metros.");
    
    return true;
}
```

## Callbacks Personalizados

Si has desactivado los publics predeterminados usando `Voip_EnableDefaultPublics(false)`, puedes implementar tus propios callbacks:

```pawn
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    // Tu código personalizado aquí
    // keyid 0x42 (B) para Voip local
    // keyid 0x5A (Z) para Voip global
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Tu código personalizado aquí
}
```

## Licencia

Este Include está protegido bajo la Licencia Apache 2.0, que permite:

- ✔️ Uso comercial y privado
- ✔️ Modificación del código fuente
- ✔️ Distribución del código
- ✔️ Concesión de patentes

### Condiciones:

- Mantener el aviso de derechos de autor
- Documentar cambios significativos
- Incluir copia de la licencia Apache 2.0

Para más detalles sobre la licencia: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Todos los derechos reservados**