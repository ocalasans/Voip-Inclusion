# Voip-Inclusion

Voip-Inclusion - это библиотека для упрощенной интеграции SAMPVOICE в ваш SA-MP Gamemode, предоставляющая максимальную гибкость и контроль над системой голосовой связи.

## Языки

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Содержание

- [Voip-Inclusion](#voip-inclusion)
  - [Языки](#языки)
  - [Содержание](#содержание)
  - [Установка](#установка)
  - [Требования](#требования)
  - [Основные характеристики](#основные-характеристики)
  - [Глобальная vs Индивидуальная система](#глобальная-vs-индивидуальная-система)
    - [GLOBAL\_VOIP](#global_voip)
    - [NOT\_GLOBAL\_VOIP](#not_global_voip)
  - [Базовая настройка](#базовая-настройка)
    - [Инициализация системы](#инициализация-системы)
  - [Функции управления](#функции-управления)
    - [Voip\_Create](#voip_create)
    - [Voip\_Delete](#voip_delete)
    - [Voip\_Distance](#voip_distance)
  - [Функции обратной связи](#функции-обратной-связи)
    - [Voip\_NotFound](#voip_notfound)
    - [Voip\_NoMicrophone](#voip_nomicrophone)
    - [Voip\_Global](#voip_global)
    - [Voip\_Player](#voip_player)
  - [Функции потоков](#функции-потоков)
    - [Voip\_GetGlobalStream](#voip_getglobalstream)
    - [Voip\_GetLocalStream](#voip_getlocalstream)
    - [Voip\_SetGlobalStream](#voip_setglobalstream)
    - [Voip\_SetLocalStream](#voip_setlocalstream)
  - [Примеры использования](#примеры-использования)
    - [Полная настройка](#полная-настройка)
  - [Пользовательские колбэки](#пользовательские-колбэки)
  - [Лицензия](#лицензия)
    - [Условия:](#условия)

## Установка

1. Скачайте файл [Voip-Inclusion.inc](https://github.com/ocalasans/Voip-Inclusion/releases/download/v1.0.1/Voip-Inclusion.inc)
2. Поместите файл в папку `pawno/include` вашего сервера
3. Добавьте следующую строку после ваших других включений:
```pawn
#include <Voip-Inclusion>
```

## Требования

- [SAMPVOICE](https://github.com/CyberMor/sampvoice) версии 3.1 или ниже (совместимой)
- Плагин SAMPVOICE активирован в `server.cfg`

> [!IMPORTANT]
> Этот include совместим только с версией 3.1 или ниже (совместимой) SAMPVOICE.

## Основные характеристики

- **Гибкая система выполнения**
  - Поддержка глобальных и индивидуальных операций
  - Эффективное управление колбэками

- **Управление потоками**
  - Автоматический глобальный поток (инициализируется в OnGameModeInit include)
  - Настраиваемые локальные потоки для каждого игрока
  - Точный контроль дальности голоса

- **Система обратной связи**
  - Полностью настраиваемые сообщения
  - Уведомления о состоянии системы
  - Обратная связь по подключению и микрофону

- **Расширенные возможности**
  - Настраиваемые колбэки
  - Прямой доступ к потокам
  - Точный контроль дальности голоса

## Глобальная vs Индивидуальная система

Система `GLOBAL_VOIP` и `NOT_GLOBAL_VOIP` определяет, как будут выполняться колбэки:

### GLOBAL_VOIP

- Выполняет колбэк для всех подключенных игроков
- Не требует указания `playerid`
- Полезно для действий, затрагивающих всех игроков одновременно

### NOT_GLOBAL_VOIP

- Выполняет колбэк для конкретного игрока
- Требует указания `playerid`
- Полезно для индивидуальных действий игрока

## Базовая настройка

### Инициализация системы

```pawn
public OnGameModeInit()
{
    // Включить стандартные publics
    Voip_EnableDefaultPublics(true);
    
    // Глобальный поток создается автоматически include здесь

    return true;
}

public OnPlayerConnect(playerid)
{
    // Создать локальный Voip для игрока
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Локальный", playerid);

    return true;
}
```

## Функции управления

### Voip_Create

```pawn
Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
Создает новый экземпляр Voip.
- `VII_global`: Определяет, будет ли создание влиять на всех игроков (`GLOBAL_VOIP`) или конкретного игрока (`NOT_GLOBAL_VOIP`)
- `VII_distance`: Максимальная дальность голоса
- `VII_max_players`: Максимальное количество игроков (используйте `SV_INFINITY` для неограниченного)
- `VII_color`: Цвет сообщений
- `VII_name`: Имя экземпляра
- `playerid`: ID игрока (только при `NOT_GLOBAL_VOIP`)

### Voip_Delete

```pawn
Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
Удаляет экземпляр(ы) Voip.

### Voip_Distance

```pawn
Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Регулирует дальность голоса.

## Функции обратной связи

### Voip_NotFound

```pawn
Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Отправляет обратную связь, когда Voip не обнаружен.

### Voip_NoMicrophone

```pawn
Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Отправляет обратную связь, когда микрофон не обнаружен.

### Voip_Global

```pawn
Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Отправляет обратную связь о подключении к глобальному Voip (созданному в OnGameModeInit include).
```pawn
// Индивидуальный пример
Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Глобальный Voip подключен. Нажмите Z для разговора.", playerid);

// Глобальный пример
if(IsAdmin[playerid]) // Предполагая, что это администратор.
    Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "Глобальный Voip подключен для всех. Нажмите Z для разговора.");
```

### Voip_Player

```pawn
Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Отправляет обратную связь о подключении к локальному Voip игрока.
```pawn
// Индивидуальный пример
Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Локальный Voip подключен. Нажмите B для разговора.", playerid);

// Глобальный пример
Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "Локальный Voip подключен для всех. Нажмите B для разговора.");
```

## Функции потоков

### Voip_GetGlobalStream

```pawn
SV_GSTREAM:Voip_GetGlobalStream()
```
Возвращает глобальный поток, созданный в OnGameModeInit include.

### Voip_GetLocalStream

```pawn
SV_DLSTREAM:Voip_GetLocalStream(playerid)
```
Возвращает локальный поток конкретного игрока.

### Voip_SetGlobalStream

```pawn
bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream)
```
Устанавливает новый глобальный поток.

### Voip_SetLocalStream

```pawn
bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream)
```
Устанавливает новый локальный поток для игрока.

## Примеры использования

### Полная настройка

Включение стандартных publics:
```pawn
public OnGameModeInit()
{
    Voip_EnableDefaultPublics(true);

    return true;
}
```

Создание локального Voip для конкретного игрока:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Локальный", playerid);
    
    return true;
}
```

Отправка обратной связи как глобального, так и локального Voip для конкретного игрока:
```pawn
public OnPlayerSpawn(playerid)
{
    if(IsAdmin[playerid]) // Предполагая, что это администратор.
        Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Глобальный Voip доступен. Нажмите Z для разговора.", playerid);
    
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Локальный Voip активирован. Нажмите B для разговора.", playerid);

    return true;
}
```

Пример команды, влияющей на всех игроков:
```pawn
CMD:voipglobaldist(playerid)
{
    if(IsPlayerAdmin(playerid))
        // Изменяет дистанцию Voip для всех игроков
        Voip_Distance(GLOBAL_VOIP, 50.0, 0xFFFFFFFF, "Администратор изменил дистанцию Voip на 50 метров.");
    
    return true;
}
```

## Пользовательские колбэки

Если вы отключили стандартные publics с помощью `Voip_EnableDefaultPublics(false)`, вы можете реализовать свои собственные колбэки:

```pawn
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    // Ваш пользовательский код здесь
    // keyid 0x42 (B) для локального Voip
    // keyid 0x5A (Z) для глобального Voip
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Ваш пользовательский код здесь
}
```

## Лицензия

Этот Include защищен лицензией Apache 2.0, которая разрешает:

- ✔️ Коммерческое и частное использование
- ✔️ Модификацию исходного кода
- ✔️ Распространение кода
- ✔️ Предоставление патентов

### Условия:

- Сохранение уведомления об авторских правах
- Документирование значительных изменений
- Включение копии лицензии Apache 2.0

Для получения более подробной информации о лицензии: http://www.apache.org/licenses/LICENSE-2.0

**Copyright (c) Calasans - Все права защищены**