# Voip-Inclusion

Voip-Inclusion är ett bibliotek för förenklad integration av SAMPVOICE i din SA-MP Gamemode, som erbjuder maximal flexibilitet och kontroll över röstkommunikationssystemet.

## Språk

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Türkçe: [README](../Turkce/README.md)

## Innehållsförteckning

- [Voip-Inclusion](#voip-inclusion)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [Installation](#installation)
  - [Krav](#krav)
  - [Huvudfunktioner](#huvudfunktioner)
  - [Globalt vs Individuellt System](#globalt-vs-individuellt-system)
    - [GLOBAL\_VOIP](#global_voip)
    - [NOT\_GLOBAL\_VOIP](#not_global_voip)
  - [Grundläggande Konfiguration](#grundläggande-konfiguration)
    - [Systeminitiering](#systeminitiering)
  - [Kontrollfunktioner](#kontrollfunktioner)
    - [Voip\_Create](#voip_create)
    - [Voip\_Delete](#voip_delete)
    - [Voip\_Distance](#voip_distance)
  - [Feedbackfunktioner](#feedbackfunktioner)
    - [Voip\_NotFound](#voip_notfound)
    - [Voip\_NoMicrophone](#voip_nomicrophone)
    - [Voip\_Global](#voip_global)
    - [Voip\_Player](#voip_player)
  - [Strömningsfunktioner](#strömningsfunktioner)
    - [Voip\_GetGlobalStream](#voip_getglobalstream)
    - [Voip\_GetLocalStream](#voip_getlocalstream)
    - [Voip\_SetGlobalStream](#voip_setglobalstream)
    - [Voip\_SetLocalStream](#voip_setlocalstream)
  - [Användningsexempel](#användningsexempel)
    - [Fullständig Konfiguration](#fullständig-konfiguration)
  - [Anpassade Callbacks](#anpassade-callbacks)
  - [Licens](#licens)
    - [Villkor:](#villkor)

## Installation

1. Ladda ner filen [Voip-Inclusion.inc](https://github.com/ocalasans/Voip-Inclusion/releases/download/v1.0.1/Voip-Inclusion.inc)
2. Placera filen i mappen `pawno/include` på din server
3. Lägg till följande rad efter dina andra includes:
```pawn
#include <Voip-Inclusion>
```

## Krav

- [SAMPVOICE](https://github.com/CyberMor/sampvoice) version 3.1 eller lägre (som är kompatibel)
- SAMPVOICE-plugin aktiverad i `server.cfg`

> [!IMPORTANT]
> Detta include är endast kompatibelt med version 3.1 eller lägre (som är kompatibel) av SAMPVOICE.

## Huvudfunktioner

- **Flexibelt Exekveringssystem**
  - Stöd för globala och individuella operationer
  - Effektiv hantering av callbacks

- **Strömningshantering**
  - Automatisk global strömning (initieras i OnGameModeInit av include)
  - Anpassningsbara lokala strömmar per spelare
  - Detaljerad kontroll över röstavstånd

- **Feedbacksystem**
  - Helt anpassningsbara meddelanden
  - Systemstatusnotifieringar
  - Anslutnings- och mikrofonfeedback

- **Avancerade Funktioner**
  - Anpassningsbara callbacks
  - Direkt åtkomst till strömmar
  - Precis kontroll över röstavstånd

## Globalt vs Individuellt System

Systemet med `GLOBAL_VOIP` och `NOT_GLOBAL_VOIP` bestämmer hur callbacks ska exekveras:

### GLOBAL_VOIP

- Exekverar callback för alla anslutna spelare
- Kräver ingen specificering av `playerid`
- Användbart för åtgärder som påverkar alla spelare samtidigt

### NOT_GLOBAL_VOIP

- Exekverar callback för en specifik spelare
- Kräver specificering av `playerid`
- Användbart för individuella åtgärder per spelare

## Grundläggande Konfiguration

### Systeminitiering

```pawn
public OnGameModeInit()
{
    // Aktivera standardpublics
    Voip_EnableDefaultPublics(true);
    
    // Den globala strömmen skapas automatiskt av include här

    return true;
}

public OnPlayerConnect(playerid)
{
    // Skapa lokal Voip för spelaren
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Lokal", playerid);

    return true;
}
```

## Kontrollfunktioner

### Voip_Create

```pawn
Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
Skapar en ny Voip-instans.
- `VII_global`: Definierar om skapandet ska påverka alla spelare (`GLOBAL_VOIP`) eller en specifik spelare (`NOT_GLOBAL_VOIP`)
- `VII_distance`: Maximalt röstavstånd
- `VII_max_players`: Maximalt antal spelare (använd `SV_INFINITY` för obegränsat)
- `VII_color`: Färg på meddelanden
- `VII_name`: Instansnamn
- `playerid`: Spelar-ID (endast när `NOT_GLOBAL_VOIP`)

### Voip_Delete

```pawn
Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
Tar bort Voip-instans(er).

### Voip_Distance

```pawn
Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Justerar röstavståndet.

## Feedbackfunktioner

### Voip_NotFound

```pawn
Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Skickar feedback när Voip inte upptäcks.

### Voip_NoMicrophone

```pawn
Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Skickar feedback när mikrofonen inte upptäcks.

### Voip_Global

```pawn
Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Skickar feedback om anslutningen till global Voip (skapad i OnGameModeInit av include).
```pawn
// Individuellt exempel
Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Global Voip ansluten. Tryck Z för att prata.", playerid);

// Globalt exempel
if(IsAdmin[playerid]) // Antar att det är en administratör
    Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "Global Voip ansluten för alla. Tryck Z för att prata.");
```

### Voip_Player

```pawn
Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Skickar feedback om anslutningen till spelarens lokala Voip.
```pawn
// Individuellt exempel
Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Lokal Voip ansluten. Tryck B för att prata.", playerid);

// Globalt exempel
Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "Lokal Voip ansluten för alla. Tryck B för att prata.");
```

## Strömningsfunktioner

### Voip_GetGlobalStream

```pawn
SV_GSTREAM:Voip_GetGlobalStream()
```
Returnerar den globala strömmen skapad i OnGameModeInit av include.

### Voip_GetLocalStream

```pawn
SV_DLSTREAM:Voip_GetLocalStream(playerid)
```
Returnerar den lokala strömmen för en specifik spelare.

### Voip_SetGlobalStream

```pawn
bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream)
```
Sätter en ny global ström.

### Voip_SetLocalStream

```pawn
bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream)
```
Sätter en ny lokal ström för en spelare.

## Användningsexempel

### Fullständig Konfiguration

Aktivera standardpublics:
```pawn
public OnGameModeInit()
{
    Voip_EnableDefaultPublics(true);

    return true;
}
```

Skapa lokal Voip för specifik spelare:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Lokal", playerid);
    
    return true;
}
```

Skicka både global och lokal Voip-feedback till specifik spelare:
```pawn
public OnPlayerSpawn(playerid)
{
    if(IsAdmin[playerid]) // Antar att det är en administratör
        Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Global Voip tillgänglig. Tryck Z för att prata.", playerid);
    
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Lokal Voip aktiverad. Tryck B för att prata.", playerid);

    return true;
}
```

Exempel på kommando som påverkar alla spelare:
```pawn
CMD:voipglobaldist(playerid)
{
    if(IsPlayerAdmin(playerid))
        // Ändrar Voip-avståndet för alla spelare
        Voip_Distance(GLOBAL_VOIP, 50.0, 0xFFFFFFFF, "Administratör ändrade Voip-avståndet till 50 meter.");
    
    return true;
}
```

## Anpassade Callbacks

Om du har inaktiverat standardpublics med `Voip_EnableDefaultPublics(false)` kan du implementera dina egna callbacks:

```pawn
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    // Din anpassade kod här
    // keyid 0x42 (B) för lokal Voip
    // keyid 0x5A (Z) för global Voip
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Din anpassade kod här
}
```

## Licens

Detta Include är skyddat under Apache 2.0-licensen, som tillåter:

- ✔️ Kommersiell och privat användning
- ✔️ Modifiering av källkoden
- ✔️ Distribution av koden
- ✔️ Patentbeviljande

### Villkor:

- Behåll upphovsrättsmeddelandet
- Dokumentera betydande ändringar
- Inkludera en kopia av Apache 2.0-licensen

För mer information om licensen: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Alla rättigheter förbehållna**