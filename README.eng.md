## Include Voip-Inclusion SA:MP

This include provides seamless integration of `Voip` into your Gamemode, offering unparalleled flexibility. With the ability to utilize callbacks for custom changes and send messages to players, along with global support for all players. It is recommended that you read the categories below to stay informed.

-----------------------

### How to install?

You should download the include. After doing so, you need to place the include in the folder (pawno > include). Once you have done that, open the pwn file of your Gamemode and insert the following code below your other includes:
```pawn
#include <VeiculoFuncoes>
```

-----------------------

### Necessary includes

* [SAMPVOICE](https://github.com/CyberMor/sampvoice).

> [!WARNING]
> This include is only compatible up to version `3.1` of sampvoice.

-----------------------

### How it works?

This include operates as follows: the user simply needs to activate it in their Gamemode. Additionally, it is imperative that the user has [SAMPVOICE](https://github.com/CyberMor/sampvoice) included in their library and has activated the corresponding plugin in the `server.cfg`. As for functionality, this include is highly flexible, allowing the user to configure messages as desired and in a personalized manner. The callbacks are not limited to a single use; the user can use them whenever and wherever they want, as many times as necessary. However, its advantages do not end there. In the callbacks of the functions, global options are available, including definitions such as `NOT_GLOBAL_VOIP`, which do not represent global communication, and `GLOBAL_VOIP`, which do. Furthermore, this **README** also contains two more categories, explaining the callbacks in both global and non-global contexts in detail, and providing clear guidance on their implementation.

-----------------------

### How to use non-globally?

In this category, you'll find an explanation of how to use all callbacks in a non-global manner.

-----------------------

```pawn
native Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the distance.</kbd>    
3 - <kbd>Define the maximum players, SV_INFINITY is default.</kbd>    
4 - <kbd>Define the color.</kbd>    
5 - <kbd>Define the name.</kbd>    
6 - <kbd>Define the playerid (player).</kbd>

* Example:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local", playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the playerid (player).</kbd>

* Example:
```pawn
public OnPlayerDisconnect(playerid, reason)
{
    Voip_Delete(NOT_GLOBAL_VOIP, playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the distance.</kbd>    
3 - <kbd>Define the color.</kbd>    
4 - <kbd>Define the message.</kbd>    
5 - <kbd>Define the playerid (player).</kbd>

* Example:
```pawn
CMD:voipdistance(playerid)
{
    Voip_Distance(NOT_GLOBAL_VOIP, 30.0, 0xFFFFFFFF, "You adjusted your voip distance to 30 meters.", playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the color.</kbd>    
3 - <kbd>Define the message.</kbd>    
4 - <kbd>Define the playerid (player).</kbd>

* Example:
```pawn
public OnPlayerSpawn(playerid)
{
    Voip_NotFound(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Your voip was not found.", playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the color.</kbd>    
3 - <kbd>Define the message.</kbd>    
4 - <kbd>Define the playerid (player).</kbd>

* Example:
```pawn
public OnPlayerSpawn(playerid)
{
    Voip_NoMicrophone(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Your microphone was not detected.", playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the color.</kbd>    
3 - <kbd>Define the message.</kbd>    
4 - <kbd>Define the playerid (player).</kbd>

* Example:
```pawn
public OnPlayerSpawn(playerid)
{
    Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Your global voip has been successfully loaded. Press the Z key to speak.", playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the color.</kbd>    
3 - <kbd>Define the message.</kbd>    
4 - <kbd>Define the playerid (player).</kbd>

* Example:
```pawn
public OnPlayerSpawn(playerid)
{
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Your local voip has been successfully loaded. Press the B key to speak.", playerid);
    //
    return true;
}
```

-----------------------

### How to use globally?

In this category, you'll find an explanation of how to use all callbacks globally. Note that when defining a callback with `GLOBAL_VOIP`, it's not necessary to specify the last parameter, which is `playerid`.

-----------------------

```pawn
native Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the distance.</kbd>    
3 - <kbd>Define the maximum players, SV_INFINITY is default.</kbd>    
4 - <kbd>Define the color.</kbd>    
5 - <kbd>Define the name.</kbd>    
6 - <kbd>Don't set the playerid, delete it.</kbd>

* Example:
```pawn
CMD:voipcreate(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Create(GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local");
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Don't set the playerid, delete it.</kbd>

* Example:
```pawn
CMD:voipdelete(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Delete(GLOBAL_VOIP);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the distance.</kbd>    
3 - <kbd>Define the color.</kbd>    
4 - <kbd>Define the message.</kbd>    
5 - <kbd>Don't set the playerid, delete it.</kbd>

* Example:
```pawn
CMD:voipdistance(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Distance(GLOBAL_VOIP, 30.0, 0xFFFFFFFF, "The administrator adjusted the voip distance to 30 meters.");
    //
    return true;
}
```

-----------------------

```pawn
native Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the color.</kbd>    
3 - <kbd>Define the message.</kbd>    
4 - <kbd>Don't set the playerid, delete it.</kbd>

* Example:
```pawn
CMD:voipfound(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_NotFound(GLOBAL_VOIP, 0xFFFFFFFF, "The administrator checked the server, but your voip was not found.");
    //
    return true;
}
```

-----------------------

```pawn
native Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the color.</kbd>    
3 - <kbd>Define the message.</kbd>    
4 - <kbd>Don't set the playerid, delete it.</kbd>

* Example:
```pawn
CMD:voipmicrophone(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_NoMicrophone(GLOBAL_VOIP, 0xFFFFFFFF, "The administrator checked the server, but your microphone was not detected.");
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the color.</kbd>    
3 - <kbd>Define the message.</kbd>    
4 - <kbd>Don't set the playerid, delete it.</kbd>

* Example:
```pawn
CMD:voipglobal(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "The administrator checked the server, and your global voip was found. Press the Z key to speak.");
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Define if it's global.</kbd>    
2 - <kbd>Define the color.</kbd>    
3 - <kbd>Define the message.</kbd>    
4 - <kbd>Don't set the playerid, delete it.</kbd>

* Example:
```pawn
CMD:voipplayer(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "The administrator checked the server, and your local voip was found. Press the B key to speak.");
    //
    return true;
}
```

-----------------------

### Other callbacks

```pawn
Voip_Debug(bool:VII_debug = SV_FALSE)
```

* Example:
```pawn
CMD:enablelogsvoip(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Debug(true); // To disable, remove "true" and do not define any parameters.
    //
    return true;
}
```

-----------------------

### Contact Information

Instagram: [ocalasans](https://instagram.com/ocalasans)   
YouTube: [Calasans](https://www.youtube.com/@ocalasans)   
Discord: ocalasans   
Community: [SA:MP Programming Community©](https://abre.ai/samp-spc)
