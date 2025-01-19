# Voip-Inclusion

Voip-Inclusion ist eine Bibliothek für die vereinfachte Integration von SAMPVOICE in Ihren SA-MP Gamemode, die maximale Flexibilität und Kontrolle über das Sprachkommunikationssystem bietet.

## Sprachen

- Português: [README](../../)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Inhaltsverzeichnis

- [Voip-Inclusion](#voip-inclusion)
  - [Sprachen](#sprachen)
  - [Inhaltsverzeichnis](#inhaltsverzeichnis)
  - [Installation](#installation)
  - [Anforderungen](#anforderungen)
  - [Hauptmerkmale](#hauptmerkmale)
  - [Globales vs. Individuelles System](#globales-vs-individuelles-system)
    - [GLOBAL\_VOIP](#global_voip)
    - [NOT\_GLOBAL\_VOIP](#not_global_voip)
  - [Grundkonfiguration](#grundkonfiguration)
    - [Systeminitialisierung](#systeminitialisierung)
  - [Kontrollfunktionen](#kontrollfunktionen)
    - [Voip\_Create](#voip_create)
    - [Voip\_Delete](#voip_delete)
    - [Voip\_Distance](#voip_distance)
  - [Feedback-Funktionen](#feedback-funktionen)
    - [Voip\_NotFound](#voip_notfound)
    - [Voip\_NoMicrophone](#voip_nomicrophone)
    - [Voip\_Global](#voip_global)
    - [Voip\_Player](#voip_player)
  - [Stream-Funktionen](#stream-funktionen)
    - [Voip\_GetGlobalStream](#voip_getglobalstream)
    - [Voip\_GetLocalStream](#voip_getlocalstream)
    - [Voip\_SetGlobalStream](#voip_setglobalstream)
    - [Voip\_SetLocalStream](#voip_setlocalstream)
  - [Verwendungsbeispiele](#verwendungsbeispiele)
    - [Vollständige Konfiguration](#vollständige-konfiguration)
  - [Benutzerdefinierte Callbacks](#benutzerdefinierte-callbacks)
  - [Lizenz](#lizenz)
    - [Bedingungen:](#bedingungen)

## Installation

1. Laden Sie die Datei [Voip-Inclusion.inc](https://github.com/ocalasans/Voip-Inclusion/releases/download/v1.0.1/Voip-Inclusion.inc) herunter
2. Legen Sie die Datei im Ordner `pawno/include` Ihres Servers ab
3. Fügen Sie die folgende Zeile nach Ihren anderen Includes hinzu:
```pawn
#include <Voip-Inclusion>
```

## Anforderungen

- [SAMPVOICE](https://github.com/CyberMor/sampvoice) Version 3.1 oder niedriger (kompatible Version)
- SAMPVOICE Plugin in `server.cfg` aktiviert

> [!IMPORTANT]
> Dieses Include ist nur mit Version 3.1 oder niedriger (kompatible Version) von SAMPVOICE kompatibel.

## Hauptmerkmale

- **Flexibles Ausführungssystem**
  - Unterstützung für globale und individuelle Operationen
  - Effizientes Callback-Management

- **Stream-Management**
  - Automatischer globaler Stream (initialisiert in OnGameModeInit des Includes)
  - Anpassbare lokale Streams pro Spieler
  - Granulare Kontrolle der Sprachreichweite

- **Feedback-System**
  - Vollständig anpassbare Nachrichten
  - Systemstatus-Benachrichtigungen
  - Verbindungs- und Mikrofon-Feedback

- **Erweiterte Funktionen**
  - Anpassbare Callbacks
  - Direkter Zugriff auf Streams
  - Präzise Kontrolle der Sprachreichweite

## Globales vs. Individuelles System

Das System von `GLOBAL_VOIP` und `NOT_GLOBAL_VOIP` bestimmt, wie die Callbacks ausgeführt werden:

### GLOBAL_VOIP

- Führt den Callback für alle verbundenen Spieler aus
- Benötigt keine `playerid`-Spezifikation
- Nützlich für Aktionen, die alle Spieler gleichzeitig betreffen

### NOT_GLOBAL_VOIP

- Führt den Callback für einen bestimmten Spieler aus
- Benötigt `playerid`-Spezifikation
- Nützlich für individuelle Aktionen pro Spieler

## Grundkonfiguration

### Systeminitialisierung

```pawn
public OnGameModeInit()
{
    // Standard-Publics aktivieren
    Voip_EnableDefaultPublics(true);
    
    // Der globale Stream wird hier automatisch vom Include erstellt

    return true;
}

public OnPlayerConnect(playerid)
{
    // Lokales Voip für den Spieler erstellen
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Lokal", playerid);

    return true;
}
```

## Kontrollfunktionen

### Voip_Create

```pawn
Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
Erstellt eine neue Voip-Instanz.
- `VII_global`: Bestimmt, ob die Erstellung alle Spieler (`GLOBAL_VOIP`) oder einen bestimmten Spieler (`NOT_GLOBAL_VOIP`) betrifft
- `VII_distance`: Maximale Reichweite der Stimme
- `VII_max_players`: Maximale Anzahl der Spieler (verwenden Sie `SV_INFINITY` für unbegrenzt)
- `VII_color`: Farbe der Nachrichten
- `VII_name`: Name der Instanz
- `playerid`: Spieler-ID (nur bei `NOT_GLOBAL_VOIP`)

### Voip_Delete

```pawn
Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
Entfernt Voip-Instanz(en).

### Voip_Distance

```pawn
Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Passt die Reichweite der Stimme an.

## Feedback-Funktionen

### Voip_NotFound

```pawn
Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Sendet Feedback, wenn Voip nicht erkannt wird.

### Voip_NoMicrophone

```pawn
Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Sendet Feedback, wenn kein Mikrofon erkannt wird.

### Voip_Global

```pawn
Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Sendet Feedback über die Verbindung mit globalem Voip (erstellt in OnGameModeInit des Includes).
```pawn
// Individuelles Beispiel
Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Globales Voip verbunden. Drücken Sie Z zum Sprechen.", playerid);

// Globales Beispiel
if(IsAdmin[playerid]) // Angenommen, es ist ein Administrator
    Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "Globales Voip für alle verbunden. Drücken Sie Z zum Sprechen.");
```

### Voip_Player

```pawn
Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Sendet Feedback über die Verbindung mit lokalem Voip des Spielers.
```pawn
// Individuelles Beispiel
Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Lokales Voip verbunden. Drücken Sie B zum Sprechen.", playerid);

// Globales Beispiel
Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "Lokales Voip für alle verbunden. Drücken Sie B zum Sprechen.");
```

## Stream-Funktionen

### Voip_GetGlobalStream

```pawn
SV_GSTREAM:Voip_GetGlobalStream()
```
Gibt den globalen Stream zurück, der in OnGameModeInit des Includes erstellt wurde.

### Voip_GetLocalStream

```pawn
SV_DLSTREAM:Voip_GetLocalStream(playerid)
```
Gibt den lokalen Stream eines bestimmten Spielers zurück.

### Voip_SetGlobalStream

```pawn
bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream)
```
Setzt einen neuen globalen Stream.

### Voip_SetLocalStream

```pawn
bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream)
```
Setzt einen neuen lokalen Stream für einen Spieler.

## Verwendungsbeispiele

### Vollständige Konfiguration

Standard-Publics aktivieren:
```pawn
public OnGameModeInit()
{
    Voip_EnableDefaultPublics(true);

    return true;
}
```

Lokales Voip für einen bestimmten Spieler erstellen:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Lokal", playerid);
    
    return true;
}
```

Feedback für sowohl globales als auch lokales Voip an einen bestimmten Spieler senden:
```pawn
public OnPlayerSpawn(playerid)
{
    if(IsAdmin[playerid]) // Angenommen, es ist ein Administrator
        Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Globales Voip verfügbar. Drücken Sie Z zum Sprechen.", playerid);
    
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Lokales Voip aktiviert. Drücken Sie B zum Sprechen.", playerid);

    return true;
}
```

Beispiel für einen Befehl, der alle Spieler betrifft:
```pawn
CMD:voipglobaldist(playerid)
{
    if(IsPlayerAdmin(playerid))
        // Ändert die Voip-Distanz für alle Spieler
        Voip_Distance(GLOBAL_VOIP, 50.0, 0xFFFFFFFF, "Administrator hat die Voip-Distanz auf 50 Meter geändert.");
    
    return true;
}
```

## Benutzerdefinierte Callbacks

Wenn Sie die Standard-Publics mit `Voip_EnableDefaultPublics(false)` deaktiviert haben, können Sie Ihre eigenen Callbacks implementieren:

```pawn
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    // Ihr benutzerdefinierter Code hier
    // keyid 0x42 (B) für lokales Voip
    // keyid 0x5A (Z) für globales Voip
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Ihr benutzerdefinierter Code hier
}
```

## Lizenz

Dieses Include steht unter der Apache 2.0 Lizenz, die Folgendes erlaubt:

- ✔️ Kommerzielle und private Nutzung
- ✔️ Modifikation des Quellcodes
- ✔️ Verteilung des Codes
- ✔️ Patenterteilung

### Bedingungen:

- Urheberrechtshinweis beibehalten
- Wesentliche Änderungen dokumentieren
- Kopie der Apache 2.0 Lizenz beifügen

Weitere Details zur Lizenz: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Alle Rechte vorbehalten**