# Voip-Inclusion

Voip-Inclusion è una libreria per l'integrazione semplificata di SAMPVOICE nel tuo Gamemode SA-MP, offrendo massima flessibilità e controllo sul sistema di comunicazione vocale.

## Lingue

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Indice

- [Voip-Inclusion](#voip-inclusion)
  - [Lingue](#lingue)
  - [Indice](#indice)
  - [Installazione](#installazione)
  - [Requisiti](#requisiti)
  - [Caratteristiche Principali](#caratteristiche-principali)
  - [Sistema Globale vs Individuale](#sistema-globale-vs-individuale)
    - [GLOBAL\_VOIP](#global_voip)
    - [NOT\_GLOBAL\_VOIP](#not_global_voip)
  - [Configurazione Base](#configurazione-base)
    - [Inizializzazione del Sistema](#inizializzazione-del-sistema)
  - [Funzioni di Controllo](#funzioni-di-controllo)
    - [Voip\_Create](#voip_create)
    - [Voip\_Delete](#voip_delete)
    - [Voip\_Distance](#voip_distance)
  - [Funzioni di Feedback](#funzioni-di-feedback)
    - [Voip\_NotFound](#voip_notfound)
    - [Voip\_NoMicrophone](#voip_nomicrophone)
    - [Voip\_Global](#voip_global)
    - [Voip\_Player](#voip_player)
  - [Funzioni di Stream](#funzioni-di-stream)
    - [Voip\_GetGlobalStream](#voip_getglobalstream)
    - [Voip\_GetLocalStream](#voip_getlocalstream)
    - [Voip\_SetGlobalStream](#voip_setglobalstream)
    - [Voip\_SetLocalStream](#voip_setlocalstream)
  - [Esempi di Utilizzo](#esempi-di-utilizzo)
    - [Configurazione Completa](#configurazione-completa)
  - [Callback Personalizzate](#callback-personalizzate)
  - [Licenza](#licenza)
    - [Condizioni](#condizioni)

## Installazione

1. Scarica il file [Voip-Inclusion.inc](https://github.com/ocalasans/Voip-Inclusion/releases/download/v1.0.1/Voip-Inclusion.inc)
2. Posiziona il file nella cartella `pawno/include` del tuo server
3. Aggiungi la seguente riga dopo gli altri include:
```pawn
#include <Voip-Inclusion>
```

## Requisiti

- [SAMPVOICE](https://github.com/CyberMor/sampvoice) versione 3.1 o precedente (compatibile)
- Plugin SAMPVOICE attivato nel `server.cfg`

> [!IMPORTANT]
> Questo include è compatibile solo con la versione 3.1 o precedente (compatibile) di SAMPVOICE.

## Caratteristiche Principali

- **Sistema di Esecuzione Flessibile**
  - Supporto per operazioni globali e individuali
  - Gestione efficiente delle callback

- **Gestione degli Stream**
  - Stream globale automatico (inizializzato in OnGameModeInit dell'include)
  - Stream locali personalizzabili per giocatore
  - Controllo granulare della distanza vocale

- **Sistema di Feedback**
  - Messaggi completamente personalizzabili
  - Notifiche sullo stato del sistema
  - Feedback sulla connessione e sul microfono

- **Funzionalità Avanzate**
  - Callback personalizzabili
  - Accesso diretto agli stream
  - Controllo preciso della distanza vocale

## Sistema Globale vs Individuale

Il sistema di `GLOBAL_VOIP` e `NOT_GLOBAL_VOIP` determina come verranno eseguite le callback:

### GLOBAL_VOIP

- Esegue la callback per tutti i giocatori connessi
- Non richiede specificazione del `playerid`
- Utile per azioni che influenzano tutti i giocatori simultaneamente

### NOT_GLOBAL_VOIP

- Esegue la callback per un giocatore specifico
- Richiede specificazione del `playerid`
- Utile per azioni individuali per giocatore

## Configurazione Base

### Inizializzazione del Sistema

```pawn
public OnGameModeInit()
{
    // Attivare public predefinite
    Voip_EnableDefaultPublics(true);
    
    // Lo stream globale viene creato automaticamente dall'include qui

    return true;
}

public OnPlayerConnect(playerid)
{
    // Creare Voip locale per il giocatore
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Locale", playerid);

    return true;
}
```

## Funzioni di Controllo

### Voip_Create

```pawn
Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
Crea una nuova istanza di Voip.
- `VII_global`: Definisce se la creazione influenzerà tutti i giocatori (`GLOBAL_VOIP`) o un giocatore specifico (`NOT_GLOBAL_VOIP`)
- `VII_distance`: Distanza massima di portata della voce
- `VII_max_players`: Numero massimo di giocatori (usa `SV_INFINITY` per illimitato)
- `VII_color`: Colore dei messaggi
- `VII_name`: Nome dell'istanza
- `playerid`: ID del giocatore (solo quando `NOT_GLOBAL_VOIP`)

### Voip_Delete

```pawn
Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
Rimuove istanza/e di Voip.

### Voip_Distance

```pawn
Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Regola la distanza di portata della voce.

## Funzioni di Feedback

### Voip_NotFound

```pawn
Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Invia feedback quando il Voip non viene rilevato.

### Voip_NoMicrophone

```pawn
Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Invia feedback quando il microfono non viene rilevato.

### Voip_Global

```pawn
Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Invia feedback sulla connessione con il Voip globale (creato in OnGameModeInit dell'include).
```pawn
// Esempio individuale
Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip globale connesso. Premi Z per parlare.", playerid);

// Esempio globale
if(IsAdmin[playerid]) // Supponendo che sia amministratore
    Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "Voip globale connesso per tutti. Premi Z per parlare.");
```

### Voip_Player

```pawn
Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Invia feedback sulla connessione con il Voip locale del giocatore.
```pawn
// Esempio individuale
Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip locale connesso. Premi B per parlare.", playerid);

// Esempio globale
Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "Voip locale connesso per tutti. Premi B per parlare.");
```

## Funzioni di Stream

### Voip_GetGlobalStream

```pawn
SV_GSTREAM:Voip_GetGlobalStream()
```
Restituisce lo stream globale creato in OnGameModeInit dell'include.

### Voip_GetLocalStream

```pawn
SV_DLSTREAM:Voip_GetLocalStream(playerid)
```
Restituisce lo stream locale di un giocatore specifico.

### Voip_SetGlobalStream

```pawn
bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream)
```
Imposta un nuovo stream globale.

### Voip_SetLocalStream

```pawn
bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream)
```
Imposta un nuovo stream locale per un giocatore.

## Esempi di Utilizzo

### Configurazione Completa

Attivare public predefinite:
```pawn
public OnGameModeInit()
{
    Voip_EnableDefaultPublics(true);

    return true;
}
```

Creare Voip locale per il giocatore specifico:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Locale", playerid);
    
    return true;
}
```

Inviare feedback del Voip sia globale che locale per il giocatore specifico:
```pawn
public OnPlayerSpawn(playerid)
{
    if(IsAdmin[playerid]) // Supponendo che sia amministratore
        Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip globale disponibile. Premi Z per parlare.", playerid);
    
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip locale attivato. Premi B per parlare.", playerid);

    return true;
}
```

Esempio di comando che influenza tutti i giocatori:
```pawn
CMD:voipglobaldist(playerid)
{
    if(IsPlayerAdmin(playerid))
        // Modifica la distanza del Voip per tutti i giocatori
        Voip_Distance(GLOBAL_VOIP, 50.0, 0xFFFFFFFF, "L'amministratore ha modificato la distanza del Voip a 50 metri.");
    
    return true;
}
```

## Callback Personalizzate

Se hai disattivato le public predefinite usando `Voip_EnableDefaultPublics(false)`, puoi implementare le tue callback:

```pawn
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    // Il tuo codice personalizzato qui
    // keyid 0x42 (B) per Voip locale
    // keyid 0x5A (Z) per Voip globale
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Il tuo codice personalizzato qui
}
```

## Licenza

Questo Include è protetto sotto la Licenza Apache 2.0, che permette:

- ✔️ Uso commerciale e privato
- ✔️ Modifica del codice sorgente
- ✔️ Distribuzione del codice
- ✔️ Concessione di brevetti

### Condizioni

- Mantenere l'avviso di copyright
- Documentare le modifiche significative
- Includere una copia della licenza Apache 2.0

Per maggiori dettagli sulla licenza: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Tutti i diritti riservati**