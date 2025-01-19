# Voip-Inclusion

Voip-Inclusion est une bibliothèque pour l'intégration simplifiée de SAMPVOICE dans votre Gamemode SA-MP, offrant une flexibilité et un contrôle maximal sur le système de communication vocale.

## Langues

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Table des matières

- [Voip-Inclusion](#voip-inclusion)
  - [Langues](#langues)
  - [Table des matières](#table-des-matières)
  - [Installation](#installation)
  - [Prérequis](#prérequis)
  - [Caractéristiques principales](#caractéristiques-principales)
  - [Système Global vs Individuel](#système-global-vs-individuel)
    - [GLOBAL\_VOIP](#global_voip)
    - [NOT\_GLOBAL\_VOIP](#not_global_voip)
  - [Configuration de base](#configuration-de-base)
    - [Initialisation du système](#initialisation-du-système)
  - [Fonctions de contrôle](#fonctions-de-contrôle)
    - [Voip\_Create](#voip_create)
    - [Voip\_Delete](#voip_delete)
    - [Voip\_Distance](#voip_distance)
  - [Fonctions de retour](#fonctions-de-retour)
    - [Voip\_NotFound](#voip_notfound)
    - [Voip\_NoMicrophone](#voip_nomicrophone)
    - [Voip\_Global](#voip_global)
    - [Voip\_Player](#voip_player)
  - [Fonctions de flux](#fonctions-de-flux)
    - [Voip\_GetGlobalStream](#voip_getglobalstream)
    - [Voip\_GetLocalStream](#voip_getlocalstream)
    - [Voip\_SetGlobalStream](#voip_setglobalstream)
    - [Voip\_SetLocalStream](#voip_setlocalstream)
  - [Exemples d'utilisation](#exemples-dutilisation)
    - [Configuration complète](#configuration-complète)
  - [Callbacks personnalisés](#callbacks-personnalisés)
  - [Licence](#licence)
    - [Conditions](#conditions)

## Installation

1. Téléchargez le fichier [Voip-Inclusion.inc](https://github.com/ocalasans/Voip-Inclusion/releases/download/v1.0.1/Voip-Inclusion.inc)
2. Placez le fichier dans le dossier `pawno/include` de votre serveur
3. Ajoutez la ligne suivante après vos autres includes :
```pawn
#include <Voip-Inclusion>
```

## Prérequis

- [SAMPVOICE](https://github.com/CyberMor/sampvoice) version 3.1 ou inférieure (compatible)
- Plugin SAMPVOICE activé dans `server.cfg`

> [!IMPORTANT]
> Cet include est uniquement compatible avec la version 3.1 ou inférieure (compatible) de SAMPVOICE.

## Caractéristiques principales

- **Système d'exécution flexible**
  - Support des opérations globales et individuelles
  - Gestion efficace des callbacks

- **Gestion des flux**
  - Flux global automatique (initialisé dans OnGameModeInit de l'include)
  - Flux locaux personnalisables par joueur
  - Contrôle précis de la distance de la voix

- **Système de retour**
  - Messages entièrement personnalisables
  - Notifications d'état du système
  - Retour sur la connexion et le microphone

- **Fonctionnalités avancées**
  - Callbacks personnalisables
  - Accès direct aux flux
  - Contrôle précis de la distance de la voix

## Système Global vs Individuel

Le système de `GLOBAL_VOIP` et `NOT_GLOBAL_VOIP` détermine comment les callbacks seront exécutés :

### GLOBAL_VOIP

- Exécute le callback pour tous les joueurs connectés
- Ne nécessite pas de spécification de `playerid`
- Utile pour les actions qui affectent tous les joueurs simultanément

### NOT_GLOBAL_VOIP

- Exécute le callback pour un joueur spécifique
- Nécessite la spécification de `playerid`
- Utile pour les actions individuelles par joueur

## Configuration de base

### Initialisation du système

```pawn
public OnGameModeInit()
{
    // Activer les publics par défaut
    Voip_EnableDefaultPublics(true);
    
    // Le flux global est créé automatiquement par l'include ici

    return true;
}

public OnPlayerConnect(playerid)
{
    // Créer un Voip local pour le joueur
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local", playerid);

    return true;
}
```

## Fonctions de contrôle

### Voip_Create

```pawn
Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
Crée une nouvelle instance de Voip.
- `VII_global` : Définit si la création affectera tous les joueurs (`GLOBAL_VOIP`) ou un joueur spécifique (`NOT_GLOBAL_VOIP`)
- `VII_distance` : Distance maximale de portée de la voix
- `VII_max_players` : Nombre maximum de joueurs (utilisez `SV_INFINITY` pour illimité)
- `VII_color` : Couleur des messages
- `VII_name` : Nom de l'instance
- `playerid` : ID du joueur (uniquement avec `NOT_GLOBAL_VOIP`)

### Voip_Delete

```pawn
Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
Supprime une ou des instance(s) de Voip.

### Voip_Distance

```pawn
Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Ajuste la distance de portée de la voix.

## Fonctions de retour

### Voip_NotFound

```pawn
Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envoie un retour lorsque le Voip n'est pas détecté.

### Voip_NoMicrophone

```pawn
Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envoie un retour lorsque le microphone n'est pas détecté.

### Voip_Global

```pawn
Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envoie un retour sur la connexion avec le Voip global (créé dans OnGameModeInit de l'include).
```pawn
// Exemple individuel
Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip global connecté. Appuyez sur Z pour parler.", playerid);

// Exemple global
if(IsAdmin[playerid]) // En supposant que c'est un administrateur
    Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "Voip global connecté pour tous. Appuyez sur Z pour parler.");
```

### Voip_Player

```pawn
Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Envoie un retour sur la connexion avec le Voip local du joueur.
```pawn
// Exemple individuel
Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip local connecté. Appuyez sur B pour parler.", playerid);

// Exemple global
Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "Voip local connecté pour tous. Appuyez sur B pour parler.");
```

## Fonctions de flux

### Voip_GetGlobalStream

```pawn
SV_GSTREAM:Voip_GetGlobalStream()
```
Renvoie le flux global créé dans OnGameModeInit de l'include.

### Voip_GetLocalStream

```pawn
SV_DLSTREAM:Voip_GetLocalStream(playerid)
```
Renvoie le flux local d'un joueur spécifique.

### Voip_SetGlobalStream

```pawn
bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream)
```
Définit un nouveau flux global.

### Voip_SetLocalStream

```pawn
bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream)
```
Définit un nouveau flux local pour un joueur.

## Exemples d'utilisation

### Configuration complète

Activer les publics par défaut :
```pawn
public OnGameModeInit()
{
    Voip_EnableDefaultPublics(true);

    return true;
}
```

Créer un Voip local pour un joueur spécifique :
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local", playerid);
    
    return true;
}
```

Envoyer un retour du Voip global et local pour un joueur spécifique :
```pawn
public OnPlayerSpawn(playerid)
{
    if(IsAdmin[playerid]) // En supposant que c'est un administrateur
        Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip global disponible. Appuyez sur Z pour parler.", playerid);
    
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Voip local activé. Appuyez sur B pour parler.", playerid);

    return true;
}
```

Exemple de commande qui affecte tous les joueurs :
```pawn
CMD:voipglobaldist(playerid)
{
    if(IsPlayerAdmin(playerid))
        // Change la distance du Voip pour tous les joueurs
        Voip_Distance(GLOBAL_VOIP, 50.0, 0xFFFFFFFF, "L'administrateur a changé la distance du Voip à 50 mètres.");
    
    return true;
}
```

## Callbacks personnalisés

Si vous avez désactivé les publics par défaut en utilisant `Voip_EnableDefaultPublics(false)`, vous pouvez implémenter vos propres callbacks :

```pawn
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    // Votre code personnalisé ici
    // keyid 0x42 (B) pour Voip local
    // keyid 0x5A (Z) pour Voip global
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Votre code personnalisé ici
}
```

## Licence

Cet Include est protégé sous la Licence Apache 2.0, qui permet :

- ✔️ Utilisation commerciale et privée
- ✔️ Modification du code source
- ✔️ Distribution du code
- ✔️ Octroi de brevets

### Conditions

- Conserver l'avis de droit d'auteur
- Documenter les modifications significatives
- Inclure une copie de la licence Apache 2.0

Pour plus de détails sur la licence : http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Tous droits réservés**