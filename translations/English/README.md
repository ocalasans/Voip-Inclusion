# Voip-Inclusion

Voip-Inclusion is a library for simplified integration of SAMPVOICE into your SA-MP Gamemode, offering maximum flexibility and control over the voice communication system.

## Languages

- Portuguese: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Table of Contents

- [Voip-Inclusion](#voip-inclusion)
  - [Languages](#languages)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
  - [Requirements](#requirements)
  - [Main Features](#main-features)
  - [Global vs Individual System](#global-vs-individual-system)
    - [GLOBAL\_VOIP](#global_voip)
    - [NOT\_GLOBAL\_VOIP](#not_global_voip)
  - [Basic Configuration](#basic-configuration)
    - [System Initialization](#system-initialization)
  - [Control Functions](#control-functions)
    - [Voip\_Create](#voip_create)
    - [Voip\_Delete](#voip_delete)
    - [Voip\_Distance](#voip_distance)
  - [Feedback Functions](#feedback-functions)
    - [Voip\_NotFound](#voip_notfound)
    - [Voip\_NoMicrophone](#voip_nomicrophone)
    - [Voip\_Global](#voip_global)
    - [Voip\_Player](#voip_player)
  - [Stream Functions](#stream-functions)
    - [Voip\_GetGlobalStream](#voip_getglobalstream)
    - [Voip\_GetLocalStream](#voip_getlocalstream)
    - [Voip\_SetGlobalStream](#voip_setglobalstream)
    - [Voip\_SetLocalStream](#voip_setlocalstream)
  - [Usage Examples](#usage-examples)
    - [Complete Configuration](#complete-configuration)
  - [Custom Callbacks](#custom-callbacks)
  - [License](#license)
    - [Conditions:](#conditions)

## Installation

1. Download the [Voip-Inclusion.inc](https://github.com/ocalasans/Voip-Inclusion/releases/download/v1.0.1/Voip-Inclusion.inc) file
2. Place the file in your server's `pawno/include` folder
3. Add the following line after your other includes:
```pawn
#include <Voip-Inclusion>
```

## Requirements

- [SAMPVOICE](https://github.com/CyberMor/sampvoice) version 3.1 or lower (must be compatible)
- SAMPVOICE plugin enabled in `server.cfg`

> [!IMPORTANT]
> This include is only compatible with SAMPVOICE version 3.1 or lower (must be compatible).

## Main Features

- **Flexible Execution System**
  - Support for global and individual operations
  - Efficient callback management

- **Stream Management**
  - Automatic global stream (initialized in the include's OnGameModeInit)
  - Customizable local streams per player
  - Granular voice distance control

- **Feedback System**
  - Fully customizable messages
  - System status notifications
  - Connection and microphone feedback

- **Advanced Features**
  - Customizable callbacks
  - Direct stream access
  - Precise voice distance control

## Global vs Individual System

The `GLOBAL_VOIP` and `NOT_GLOBAL_VOIP` system determines how callbacks will be executed:

### GLOBAL_VOIP

- Executes the callback for all connected players
- Does not require playerid specification
- Useful for actions that affect all players simultaneously

### NOT_GLOBAL_VOIP

- Executes the callback for a specific player
- Requires playerid specification
- Useful for individual actions per player

## Basic Configuration

### System Initialization

```pawn
public OnGameModeInit()
{
    // Enable default publics
    Voip_EnableDefaultPublics(true);
    
    // The global stream is automatically created by the include here

    return true;
}

public OnPlayerConnect(playerid)
{
    // Create local Voip for the player
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local", playerid);

    return true;
}
```

## Control Functions

### Voip_Create

```pawn
Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
Creates a new Voip instance.
- `VII_global`: Defines if the creation will affect all players (`GLOBAL_VOIP`) or a specific player (`NOT_GLOBAL_VOIP`)
- `VII_distance`: Maximum voice range distance
- `VII_max_players`: Maximum number of players (use `SV_INFINITY` for unlimited)
- `VII_color`: Message color
- `VII_name`: Instance name
- `playerid`: Player ID (only when `NOT_GLOBAL_VOIP`)

### Voip_Delete

```pawn
Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
Removes Voip instance(s).

### Voip_Distance

```pawn
Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Adjusts voice range distance.

## Feedback Functions

### Voip_NotFound

```pawn
Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Sends feedback when Voip is not detected.

### Voip_NoMicrophone

```pawn
Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Sends feedback when microphone is not detected.

### Voip_Global

```pawn
Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Sends feedback about global Voip connection (created in the include's OnGameModeInit).
```pawn
// Individual example
Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Global Voip connected. Press Z to talk.", playerid);

// Global example
if(IsAdmin[playerid]) // Assuming it's an administrator
    Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "Global Voip connected for everyone. Press Z to talk.");
```

### Voip_Player

```pawn
Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Sends feedback about player's local Voip connection.
```pawn
// Individual example
Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Local Voip connected. Press B to talk.", playerid);

// Global example
Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "Local Voip connected for everyone. Press B to talk.");
```

## Stream Functions

### Voip_GetGlobalStream

```pawn
SV_GSTREAM:Voip_GetGlobalStream()
```
Returns the global stream created in the include's OnGameModeInit.

### Voip_GetLocalStream

```pawn
SV_DLSTREAM:Voip_GetLocalStream(playerid)
```
Returns a specific player's local stream.

### Voip_SetGlobalStream

```pawn
bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream)
```
Sets a new global stream.

### Voip_SetLocalStream

```pawn
bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream)
```
Sets a new local stream for a player.

## Usage Examples

### Complete Configuration

Enable default publics:
```pawn
public OnGameModeInit()
{
    Voip_EnableDefaultPublics(true);

    return true;
}
```

Create local Voip for specific player:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local", playerid);
    
    return true;
}
```

Send both global and local Voip feedback for specific player:
```pawn
public OnPlayerSpawn(playerid)
{
    if(IsAdmin[playerid]) // Assuming it's an administrator
        Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Global Voip available. Press Z to talk.", playerid);
    
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Local Voip activated. Press B to talk.", playerid);

    return true;
}
```

Example command that affects all players:
```pawn
CMD:voipglobaldist(playerid)
{
    if(IsPlayerAdmin(playerid))
        // Changes Voip distance for all players
        Voip_Distance(GLOBAL_VOIP, 50.0, 0xFFFFFFFF, "Administrator changed Voip distance to 50 meters.");
    
    return true;
}
```

## Custom Callbacks

If you disabled default publics using `Voip_EnableDefaultPublics(false)`, you can implement your own callbacks:

```pawn
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    // Your custom code here
    // keyid 0x42 (B) for local Voip
    // keyid 0x5A (Z) for global Voip
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Your custom code here
}
```

## License

This Include is protected under the Apache License 2.0, which allows:

- ✔️ Commercial and private use
- ✔️ Source code modification
- ✔️ Code distribution
- ✔️ Patent grant

### Conditions:

- Maintain copyright notice
- Document significant changes
- Include Apache License 2.0 copy

For more details about the license: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - All rights reserved**