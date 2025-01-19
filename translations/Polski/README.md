# Voip-Inclusion

Voip-Inclusion to biblioteka do uproszczonej integracji SAMPVOICE z Twoim Gamemodem SA-MP, oferująca maksymalną elastyczność i kontrolę nad systemem komunikacji głosowej.

## Języki

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Spis treści

- [Voip-Inclusion](#voip-inclusion)
  - [Języki](#języki)
  - [Spis treści](#spis-treści)
  - [Instalacja](#instalacja)
  - [Wymagania](#wymagania)
  - [Główne cechy](#główne-cechy)
  - [System Globalny vs Indywidualny](#system-globalny-vs-indywidualny)
    - [GLOBAL\_VOIP](#global_voip)
    - [NOT\_GLOBAL\_VOIP](#not_global_voip)
  - [Podstawowa konfiguracja](#podstawowa-konfiguracja)
    - [Inicjalizacja systemu](#inicjalizacja-systemu)
  - [Funkcje kontrolne](#funkcje-kontrolne)
    - [Voip\_Create](#voip_create)
    - [Voip\_Delete](#voip_delete)
    - [Voip\_Distance](#voip_distance)
  - [Funkcje informacji zwrotnej](#funkcje-informacji-zwrotnej)
    - [Voip\_NotFound](#voip_notfound)
    - [Voip\_NoMicrophone](#voip_nomicrophone)
    - [Voip\_Global](#voip_global)
    - [Voip\_Player](#voip_player)
  - [Funkcje strumienia](#funkcje-strumienia)
    - [Voip\_GetGlobalStream](#voip_getglobalstream)
    - [Voip\_GetLocalStream](#voip_getlocalstream)
    - [Voip\_SetGlobalStream](#voip_setglobalstream)
    - [Voip\_SetLocalStream](#voip_setlocalstream)
  - [Przykłady użycia](#przykłady-użycia)
    - [Pełna konfiguracja](#pełna-konfiguracja)
  - [Niestandardowe callbacki](#niestandardowe-callbacki)
  - [Licencja](#licencja)
    - [Warunki:](#warunki)

## Instalacja

1. Pobierz plik [Voip-Inclusion.inc](https://github.com/ocalasans/Voip-Inclusion/releases/download/v1.0.1/Voip-Inclusion.inc)
2. Umieść plik w folderze `pawno/include` twojego serwera
3. Dodaj następującą linię po innych includach:
```pawn
#include <Voip-Inclusion>
```

## Wymagania

- [SAMPVOICE](https://github.com/CyberMor/sampvoice) wersja 3.1 lub niższa (która jest kompatybilna)
- Plugin SAMPVOICE aktywowany w `server.cfg`

> [!IMPORTANT]
> Ten include jest kompatybilny tylko z wersją 3.1 lub niższą (która jest kompatybilna) SAMPVOICE.

## Główne cechy

- **Elastyczny system wykonawczy**
  - Obsługa operacji globalnych i indywidualnych
  - Efektywne zarządzanie callbackami

- **Zarządzanie strumieniami**
  - Automatyczny strumień globalny (inicjalizowany w OnGameModeInit include'a)
  - Konfigurowalne strumienie lokalne dla graczy
  - Precyzyjna kontrola zasięgu głosu

- **System informacji zwrotnej**
  - W pełni konfigurowalne wiadomości
  - Powiadomienia o stanie systemu
  - Informacja zwrotna o połączeniu i mikrofonie

- **Zaawansowane funkcje**
  - Konfigurowalne callbacki
  - Bezpośredni dostęp do strumieni
  - Precyzyjna kontrola zasięgu głosu

## System Globalny vs Indywidualny

System `GLOBAL_VOIP` i `NOT_GLOBAL_VOIP` określa sposób wykonywania callbacków:

### GLOBAL_VOIP

- Wykonuje callback dla wszystkich połączonych graczy
- Nie wymaga określenia `playerid`
- Przydatny dla akcji wpływających na wszystkich graczy jednocześnie

### NOT_GLOBAL_VOIP

- Wykonuje callback dla określonego gracza
- Wymaga określenia `playerid`
- Przydatny dla indywidualnych akcji dla gracza

## Podstawowa konfiguracja

### Inicjalizacja systemu

```pawn
public OnGameModeInit()
{
    // Aktywuj domyślne publics
    Voip_EnableDefaultPublics(true);
    
    // Strumień globalny jest automatycznie tworzony przez include tutaj

    return true;
}

public OnPlayerConnect(playerid)
{
    // Tworzenie lokalnego Voip dla gracza
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Lokalny", playerid);

    return true;
}
```

## Funkcje kontrolne

### Voip_Create

```pawn
Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
Tworzy nową instancję Voip.
- `VII_global`: Określa czy tworzenie wpłynie na wszystkich graczy (`GLOBAL_VOIP`) czy na określonego gracza (`NOT_GLOBAL_VOIP`)
- `VII_distance`: Maksymalny zasięg głosu
- `VII_max_players`: Maksymalna liczba graczy (użyj `SV_INFINITY` dla nieograniczonej)
- `VII_color`: Kolor wiadomości
- `VII_name`: Nazwa instancji
- `playerid`: ID gracza (tylko gdy `NOT_GLOBAL_VOIP`)

### Voip_Delete

```pawn
Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
Usuwa instancję(e) Voip.

### Voip_Distance

```pawn
Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Dostosowuje zasięg głosu.

## Funkcje informacji zwrotnej

### Voip_NotFound

```pawn
Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Wysyła informację zwrotną, gdy Voip nie zostanie wykryty.

### Voip_NoMicrophone

```pawn
Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Wysyła informację zwrotną, gdy mikrofon nie zostanie wykryty.

### Voip_Global

```pawn
Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Wysyła informację zwrotną o połączeniu z globalnym Voip (utworzonym w OnGameModeInit include'a).
```pawn
// Przykład indywidualny
Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Globalny Voip połączony. Naciśnij Z aby mówić.", playerid);

// Przykład globalny
if(IsAdmin[playerid]) // Zakładając, że jest administratorem
    Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "Globalny Voip połączony dla wszystkich. Naciśnij Z aby mówić.");
```

### Voip_Player

```pawn
Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Wysyła informację zwrotną o połączeniu z lokalnym Voip gracza.
```pawn
// Przykład indywidualny
Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Lokalny Voip połączony. Naciśnij B aby mówić.", playerid);

// Przykład globalny
Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "Lokalny Voip połączony dla wszystkich. Naciśnij B aby mówić.");
```

## Funkcje strumienia

### Voip_GetGlobalStream

```pawn
SV_GSTREAM:Voip_GetGlobalStream()
```
Zwraca strumień globalny utworzony w OnGameModeInit include'a.

### Voip_GetLocalStream

```pawn
SV_DLSTREAM:Voip_GetLocalStream(playerid)
```
Zwraca lokalny strumień określonego gracza.

### Voip_SetGlobalStream

```pawn
bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream)
```
Ustawia nowy strumień globalny.

### Voip_SetLocalStream

```pawn
bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream)
```
Ustawia nowy lokalny strumień dla gracza.

## Przykłady użycia

### Pełna konfiguracja

Aktywacja domyślnych publics:
```pawn
public OnGameModeInit()
{
    Voip_EnableDefaultPublics(true);

    return true;
}
```

Tworzenie lokalnego Voip dla określonego gracza:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Lokalny", playerid);
    
    return true;
}
```

Wysyłanie informacji zwrotnej o Voip zarówno globalnym jak i lokalnym dla określonego gracza:
```pawn
public OnPlayerSpawn(playerid)
{
    if(IsAdmin[playerid]) // Zakładając, że jest administratorem
        Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Globalny Voip dostępny. Naciśnij Z aby mówić.", playerid);
    
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Lokalny Voip aktywowany. Naciśnij B aby mówić.", playerid);

    return true;
}
```

Przykład komendy wpływającej na wszystkich graczy:
```pawn
CMD:voipglobaldist(playerid)
{
    if(IsPlayerAdmin(playerid))
        // Zmienia zasięg Voip dla wszystkich graczy
        Voip_Distance(GLOBAL_VOIP, 50.0, 0xFFFFFFFF, "Administrator zmienił zasięg Voip na 50 metrów.");
    
    return true;
}
```

## Niestandardowe callbacki

Jeśli wyłączyłeś domyślne publics używając `Voip_EnableDefaultPublics(false)`, możesz zaimplementować własne callbacki:

```pawn
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    // Twój własny kod tutaj
    // keyid 0x42 (B) dla lokalnego Voip
    // keyid 0x5A (Z) dla globalnego Voip
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Twój własny kod tutaj
}
```

## Licencja

Ten Include jest chroniony Licencją Apache 2.0, która pozwala na:

- ✔️ Użycie komercyjne i prywatne
- ✔️ Modyfikację kodu źródłowego
- ✔️ Dystrybucję kodu
- ✔️ Udzielanie patentów

### Warunki:

- Zachowanie informacji o prawach autorskich
- Dokumentowanie znaczących zmian
- Dołączenie kopii licencji Apache 2.0

Więcej szczegółów o licencji: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Wszelkie prawa zastrzeżone**