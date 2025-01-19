/*
 * Voip-Inclusion - include for SA-MP (San Andreas Multiplayer)
 * Copyright (c) Calasans
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#if defined _voip_inclusion
    #undef _voip_inclusion
#endif

#if defined _voip_inclusion_included
    #endinput
#endif
#define _voip_inclusion_included

#if !defined _INC_open_mp
    #if !defined _samp_included
        #error "The `a_samp` library has not been activated. Please activate it at the beginning of your Gamemode, Ex: `#include <a_samp>`"
    #endif
#endif

#include <sampvoice>

/*
$$$$$$$\             $$$$$$\  $$\           $$\   $$\     $$\                               
$$  __$$\           $$  __$$\ \__|          \__|  $$ |    \__|                              
$$ |  $$ | $$$$$$\  $$ /  \__|$$\ $$$$$$$\  $$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\   $$$$$$$\ 
$$ |  $$ |$$  __$$\ $$$$\     $$ |$$  __$$\ $$ |\_$$  _|  $$ |$$  __$$\ $$  __$$\ $$  _____|
$$ |  $$ |$$$$$$$$ |$$  _|    $$ |$$ |  $$ |$$ |  $$ |    $$ |$$ /  $$ |$$ |  $$ |\$$$$$$\  
$$ |  $$ |$$   ____|$$ |      $$ |$$ |  $$ |$$ |  $$ |$$\ $$ |$$ |  $$ |$$ |  $$ | \____$$\ 
$$$$$$$  |\$$$$$$$\ $$ |      $$ |$$ |  $$ |$$ |  \$$$$  |$$ |\$$$$$$  |$$ |  $$ |$$$$$$$  |
\_______/  \_______|\__|      \__|\__|  \__|\__|   \____/ \__| \______/ \__|  \__|\_______/ 
*/

#define NOT_GLOBAL_VOIP (SV_FALSE)
#define GLOBAL_VOIP (SV_TRUE)

#define VII_loop_0:(%0) foreach(new %0: Player)
#define VII_loop_1:(%0) for(new %0 = 0; %0 < MAX_PLAYERS; %0 ++)

/*
$$\    $$\                    $$\           $$\       $$\                     
$$ |   $$ |                   \__|          $$ |      $$ |                    
$$ |   $$ |$$$$$$\   $$$$$$\  $$\  $$$$$$\  $$$$$$$\  $$ | $$$$$$\   $$$$$$$\ 
\$$\  $$  |\____$$\ $$  __$$\ $$ | \____$$\ $$  __$$\ $$ |$$  __$$\ $$  _____|
 \$$\$$  / $$$$$$$ |$$ |  \__|$$ | $$$$$$$ |$$ |  $$ |$$ |$$$$$$$$ |\$$$$$$\  
  \$$$  / $$  __$$ |$$ |      $$ |$$  __$$ |$$ |  $$ |$$ |$$   ____| \____$$\ 
   \$  /  \$$$$$$$ |$$ |      $$ |\$$$$$$$ |$$$$$$$  |$$ |\$$$$$$$\ $$$$$$$  |
    \_/    \_______|\__|      \__| \_______|\_______/ \__| \_______|\_______/ 
*/

new SV_GSTREAM:gstream = SV_NULL;
new SV_DLSTREAM:lstream[MAX_PLAYERS] = { SV_NULL, ... };

static bool:VII_created[MAX_PLAYERS] = SV_FALSE,
    bool:VII_use_default_publics = false,
    VII_check_foreach[7] = 0,
    VII_max_players_save[MAX_PLAYERS],
    VII_color_save[MAX_PLAYERS],
    VII_name_save[MAX_PLAYERS][20];

/*
$$$$$$$$\                              $$\     $$\                               
$$  _____|                             $$ |    \__|                              
$$ |   $$\   $$\ $$$$$$$\   $$$$$$$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\   $$$$$$$\ 
$$$$$\ $$ |  $$ |$$  __$$\ $$  _____|\_$$  _|  $$ |$$  __$$\ $$  __$$\ $$  _____|
$$  __|$$ |  $$ |$$ |  $$ |$$ /        $$ |    $$ |$$ /  $$ |$$ |  $$ |\$$$$$$\  
$$ |   $$ |  $$ |$$ |  $$ |$$ |        $$ |$$\ $$ |$$ |  $$ |$$ |  $$ | \____$$\ 
$$ |   \$$$$$$  |$$ |  $$ |\$$$$$$$\   \$$$$  |$$ |\$$$$$$  |$$ |  $$ |$$$$$$$  |
\__|    \______/ \__|  \__| \_______|   \____/ \__| \______/ \__|  \__|\_______/ 
*/

stock VII_Compare_String(const VII_string_1[], const VII_string_2[], VII_value) {
    for(new VII_v = 0; VII_v < VII_value; VII_v ++) {
        if(VII_string_1[VII_v] != VII_string_2[VII_v])
            return SV_FALSE;

        if(VII_string_1[VII_v] == 0 || VII_string_1[VII_v] == '\n')
            return SV_TRUE;
    }

    return SV_FALSE;
}

stock VII_Send_Message(playerid, VII_color, const VII_message[]) {
    new temp_message[156];
    format(temp_message, sizeof(temp_message), "%s", VII_message);

    if(!VII_Compare_String(temp_message, "", 2) && !VII_Compare_String(temp_message, " ", 3))
        SendClientMessage(playerid, VII_color, temp_message);

    return SV_TRUE;
}

stock Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID) {
    if(!VII_global) {
        if(!VII_created[playerid]) {
            if(SvGetVersion(playerid) != 0) {
                if(SvHasMicro(playerid)) {
                    if(gstream != SV_NULL) {
                        SvAttachListenerToStream(gstream, playerid);
                        SvAddKey(playerid, 0x5A); // Press > Z
                    }

                    static VII_format_message[20];

                    format(VII_format_message, 20, VII_name);
                    lstream[playerid] = SvCreateDLStreamAtPlayer(VII_distance, VII_max_players, playerid, VII_color, VII_format_message);
                    SvAddKey(playerid, 0x42); // Press > B

                    VII_created[playerid] = SV_TRUE;
                    VII_max_players_save[playerid] = VII_max_players;
                    VII_color_save[playerid] = VII_color;

                    format(VII_name_save[playerid], 20, VII_name);

                    return SV_TRUE;
                }

                return SV_FALSE;
            }

            return SV_FALSE;
        }

        return SV_FALSE;
    }
    else if(VII_global) {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_check_foreach[0]++;

            VII_loop_0:(i) {
                if(!VII_created[i]) {
                    if(SvGetVersion(i) != 0) {
                        if(SvHasMicro(i)) {
                            if(gstream != SV_NULL) {
                                SvAttachListenerToStream(gstream, i);
                                SvAddKey(i, 0x5A); // Press > Z
                            }

                            static VII_format_message[20];

                            format(VII_format_message, 20, VII_name);
                            lstream[i] = SvCreateDLStreamAtPlayer(VII_distance, VII_max_players, i, VII_color, VII_format_message);
                            SvAddKey(i, 0x42); // Press > B

                            VII_created[i] = SV_TRUE;
                            VII_max_players_save[i] = VII_max_players;
                            VII_color_save[i] = VII_color;

                            format(VII_name_save[i], 20, VII_name);
                        }
                        
                        if(i >= VII_check_foreach[0]) {
                            VII_check_foreach[0] = 0;
                            
                            return SV_TRUE;
                        }
                        
                        return SV_FALSE;
                    }
                    
                    return SV_FALSE;
                }
                
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i) {
                if(!VII_created[i]) {
                    if(SvGetVersion(i) != 0) {
                        if(SvHasMicro(i)) {
                            if(gstream != SV_NULL) {
                                SvAttachListenerToStream(gstream, i);
                                SvAddKey(i, 0x5A); // Press > Z
                            }

                            static VII_format_message[20];

                            format(VII_format_message, 20, VII_name);
                            lstream[i] = SvCreateDLStreamAtPlayer(VII_distance, VII_max_players, i, VII_color, VII_format_message);
                            SvAddKey(i, 0x42); // Press > B
                            
                            VII_created[i] = SV_TRUE;
                            VII_max_players_save[i] = VII_max_players;
                            VII_color_save[i] = VII_color;

                            format(VII_name_save[i], 20, VII_name);
                        }
                        
                        if(i >= MAX_PLAYERS)
                            return SV_TRUE;
                        
                        return SV_FALSE;
                    }
                    
                    return SV_FALSE;
                }
                
                return SV_FALSE;
            }
        #endif
        
        return SV_FALSE;
    }
    
    return SV_FALSE;
}

stock Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID) {
    if(!VII_global) {
        if(VII_created[playerid]) {
            if(lstream[playerid]) {
                SvDeleteStream(lstream[playerid]);
                lstream[playerid] = SV_NULL;
            }

            if(gstream != SV_NULL)
                SvDetachListenerFromStream(gstream, playerid);
            
            VII_created[playerid] = SV_FALSE;
            VII_max_players_save[playerid] = SV_INFINITY;
            VII_color_save[playerid] = -1;
            VII_name_save[playerid] = "Undefined";

            return SV_TRUE;
        }

        return SV_FALSE;
    }
    else if(VII_global) {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_check_foreach[1]++;
            
            VII_loop_0:(i) {
                if(VII_created[i]) {
                    if(lstream[i]) {
                        SvDeleteStream(lstream[i]);
                        lstream[i] = SV_NULL;
                    }
                    
                    if(gstream != SV_NULL)
                        SvDetachListenerFromStream(gstream, i);
                    
                    VII_created[i] = SV_FALSE;
                    VII_max_players_save[i] = SV_INFINITY;
                    VII_color_save[i] = -1;
                    VII_name_save[i] = "Undefined";
                }
                
                if(i >= VII_check_foreach[1]) {
                    VII_check_foreach[1] = 0;
                    
                    return SV_TRUE;
                }
                
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i) {
                if(VII_created[i]) {
                    if(lstream[i]) {
                        SvDeleteStream(lstream[i]);
                        lstream[i] = SV_NULL;
                    }
                    
                    if(gstream != SV_NULL)
                        SvDetachListenerFromStream(gstream, i);
                    
                    VII_created[i] = SV_FALSE;
                    VII_max_players_save[i] = SV_INFINITY;
                    VII_color_save[i] = -1;
                    VII_name_save[i] = "Undefined";
                }
                
                if(i >= MAX_PLAYERS)
                    return SV_TRUE;
                
                return SV_FALSE;
            }
        #endif
        
        return SV_FALSE;
    }
    
    return SV_FALSE;
}

stock Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID) {
    if(!VII_global) {
        if(VII_created[playerid]) {
            if(lstream[playerid])
                SvDeleteStream(lstream[playerid]);
            
            lstream[playerid] = SvCreateDLStreamAtPlayer(VII_distance, VII_max_players_save[playerid], playerid, VII_color_save[playerid], VII_name_save[playerid]);
            
            VII_Send_Message(playerid, VII_color, VII_message);
            
            return SV_TRUE;
        }
        
        return SV_FALSE;
    }
    else if(VII_global) {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_check_foreach[6]++;
            
            VII_loop_0:(i) {
                if(VII_created[i]) {
                    if(lstream[i])
                        SvDeleteStream(lstream[i]);
                    
                    lstream[i] = SvCreateDLStreamAtPlayer(VII_distance, VII_max_players_save[i], i, VII_color_save[i], VII_name_save[i]);
                    
                    VII_Send_Message(i, VII_color, VII_message);
                }

                if(i >= VII_check_foreach[6]) {
                    VII_check_foreach[6] = 0;
                    
                    return SV_TRUE;
                }
                
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i) {
                if(VII_created[i]) {
                    if(lstream[i])
                        SvDeleteStream(lstream[i]);
                    
                    lstream[i] = SvCreateDLStreamAtPlayer(VII_distance, VII_max_players_save[i], i, VII_color_save[i], VII_name_save[i]);
                    
                    VII_Send_Message(i, VII_color, VII_message);
                }
                
                if(i >= MAX_PLAYERS)
                    return SV_TRUE;
                
                return SV_FALSE;
            }
        #endif
        
        return SV_FALSE;
    }
    
    return SV_FALSE;
}

stock Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID) {
    if(!VII_global) {
        if(!SvGetVersion(playerid)) {
            VII_Send_Message(playerid, VII_color, VII_message);
            
            return SV_TRUE;
        }
        
        return SV_FALSE;
    }
    else if(VII_global) {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_check_foreach[2]++;
            
            VII_loop_0:(i) {
                if(!SvGetVersion(i))
                    VII_Send_Message(i, VII_color, VII_message);
                
                if(i >= VII_check_foreach[2]) {
                    VII_check_foreach[2] = 0;
                    
                    return SV_TRUE;
                }
                
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i) {
                if(!SvGetVersion(i))
                    VII_Send_Message(i, VII_color, VII_message);
                
                if(i >= MAX_PLAYERS)
                    return SV_TRUE;
                
                return SV_FALSE;
            }
        #endif
        
        return SV_FALSE;
    }
    
    return SV_FALSE;
}

stock Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID) {
    if(!VII_global) {
        if(!SvHasMicro(playerid)) {
            VII_Send_Message(playerid, VII_color, VII_message);
            
            return SV_TRUE;
        }
        
        return SV_FALSE;
    }
    else if(VII_global) {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_check_foreach[3]++;
            
            VII_loop_0:(i) {
                if(!SvGetVersion(i))
                    VII_Send_Message(i, VII_color, VII_message);
                
                if(i >= VII_check_foreach[3]) {
                    VII_check_foreach[3] = 0;
                    
                    return SV_TRUE;
                }
                
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i) {
                if(!SvGetVersion(i))
                    VII_Send_Message(i, VII_color, VII_message);
                
                if(i >= MAX_PLAYERS)
                    return SV_TRUE;
                
                return SV_FALSE;
            }
        #endif
        
        return SV_FALSE;
    }
    
    return SV_FALSE;
}

stock Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID) {
    if(!VII_global) {
        if(SvGetVersion(playerid) != 0) {
            if(SvHasMicro(playerid)) {
                if(gstream != SV_NULL) {
                    VII_Send_Message(playerid, VII_color, VII_message);
                    
                    return SV_TRUE;
                }
                
                return SV_FALSE;
            }
            
            return SV_FALSE;
        }
        
        return SV_FALSE;
    }
    else if(VII_global) {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_check_foreach[4]++;

            VII_loop_0:(i) {
                if(SvGetVersion(i) != 0) {
                    if(SvHasMicro(i)) {
                        if(gstream != SV_NULL)
                            VII_Send_Message(i, VII_color, VII_message);
                        
                        if(i >= VII_check_foreach[4]) {
                            VII_check_foreach[4] = 0;
                            
                            return SV_TRUE;
                        }
                        
                        return SV_FALSE;
                    }
                    
                    return SV_FALSE;
                }
                
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i) {
                if(SvGetVersion(i) != 0) {
                    if(SvHasMicro(i)) {
                        if(gstream != SV_NULL)
                            VII_Send_Message(i, VII_color, VII_message);
                        
                        if(i >= MAX_PLAYERS)
                            return SV_TRUE;
                        
                        return SV_FALSE;
                    }
                    
                    return SV_FALSE;
                }
                
                return SV_FALSE;
            }
        #endif
        
        return SV_FALSE;
    }
    
    return SV_FALSE;
}

stock Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID) {
    if(!VII_global) {
        if(SvGetVersion(playerid) != 0) {
            if(SvHasMicro(playerid)) {
                if(lstream[playerid]) {
                    VII_Send_Message(playerid, VII_color, VII_message);
                    
                    return SV_TRUE;
                }
                
                return SV_FALSE;
            }
            
            return SV_FALSE;
        }
        
        return SV_FALSE;
    }
    else if(VII_global) {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_check_foreach[5]++;
            
            VII_loop_0:(i) {
                if(SvGetVersion(i) != 0) {
                    if(SvHasMicro(i)) {
                        if(lstream[i])
                            VII_Send_Message(i, VII_color, VII_message);
                        
                        if(i >= VII_check_foreach[5]) {
                            VII_check_foreach[5] = 0;
                            
                            return SV_TRUE;
                        }
                        
                        return SV_FALSE;
                    }
                    
                    return SV_FALSE;
                }
                
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i) {
                if(SvGetVersion(i) != 0) {
                    if(SvHasMicro(i)) {
                        if(lstream[i])
                            VII_Send_Message(i, VII_color, VII_message);
                        
                        if(i >= MAX_PLAYERS)
                            return SV_TRUE;
                        
                        return SV_FALSE;
                    }
                    
                    return SV_FALSE;
                }
                
                return SV_FALSE;
            }
        #endif
        
        return SV_FALSE;
    }
    
    return SV_FALSE;
}

stock SV_GSTREAM:Voip_GetGlobalStream() {
    return gstream;
}

stock SV_DLSTREAM:Voip_GetLocalStream(playerid) {
    if(playerid >= 0 && playerid < MAX_PLAYERS)
        return lstream[playerid];

    return SV_NULL;
}

stock bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream) {
    if(VII_new_stream != SV_NULL) {
        SvDeleteStream(gstream);

        gstream = SV_NULL;
        gstream = VII_new_stream;

        return SV_TRUE;
    }
    return SV_FALSE;
}

stock bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream) {
    if(playerid >= 0 && playerid < MAX_PLAYERS && VII_new_stream != SV_NULL) {
        SvDeleteStream(lstream[playerid]);
        
        lstream[playerid] = SV_NULL;
        lstream[playerid] = VII_new_stream;

        return SV_TRUE;
    }

    return SV_FALSE;
}

stock Voip_EnableDefaultPublics(bool:VII_enable = true) {
    VII_use_default_publics = VII_enable;

    return SV_TRUE;
}

stock Voip_Debug(bool:VII_debug = SV_FALSE)
    SvDebug(VII_debug);

public OnGameModeInit() {
    print(" ");
    print("__________________________________________________________________");
    print("||==============================================================||");
    print("||                                                              ||");
    print("||                        Voip Inclusion                        ||");
    print("||                                                              ||");
    print("||                 8b           d8         88                   ||");
    print("||                 `8b         d8'         88                   ||");
    print("||                  `8b       d8'          88                   ||");
    print("||                   `8b     d8'           88                   ||");
    print("||                    `8b   d8'  aaaaaaaa  88                   ||");
    print("||                     `8b d8'   ========  88                   ||");
    print("||                      `888'              88                   ||");
    print("||                       `8'               88                   ||");
    print("||                                                              ||");
    print("||                                                              ||");
    print("||                                                              ||");
    print("|| Developer: Calasans                                          ||");
    print("|| Instagram: ocalasans                                         ||");
    print("|| Discord: ocalasans                                           ||");
    print("||                                                              ||");
    print("|| [Info]: Include version: 1.0.1                               ||");
    print("||                                                              ||");
    print("||==============================================================||");
    print("__________________________________________________________________");
    print(" ");

    gstream = SvCreateGStream(0xDEB887FF, "G");
    
    #if defined VII_OnGameModeInit
        return VII_OnGameModeInit();
    #else
        return SV_TRUE;
    #endif
}

public OnGameModeExit() {
    if(gstream != SV_NULL) {
        SvDeleteStream(gstream);
        gstream = SV_NULL;
    }
    
    #if defined VII_OnGameModeExit
        return VII_OnGameModeExit();
    #else
        return SV_TRUE;
    #endif
}

public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid) {
    if(VII_use_default_publics) {
        if(VII_created[playerid]) {
            if(keyid == 0x42 && lstream[playerid])
                SvAttachSpeakerToStream(lstream[playerid], playerid);
            
            if(keyid == 0x5A && gstream) {
                if(IsPlayerAdmin(playerid))
                    SvAttachSpeakerToStream(gstream, playerid);
            }
        }
    }
    
    #if defined VII_OnPlayerActivationKeyPress
        return VII_OnPlayerActivationKeyPress(playerid, keyid);
    #endif
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid) {
    if(VII_use_default_publics) {
        if(VII_created[playerid]) {
            if(keyid == 0x42 && lstream[playerid])
                SvDetachSpeakerFromStream(lstream[playerid], playerid);
            
            if(keyid == 0x5A && gstream) {
                if(IsPlayerAdmin(playerid))
                    SvDetachSpeakerFromStream(gstream, playerid);
            }
        }
    }
    
    #if defined VII_OnPlayerActKeyRelease
        return VII_OnPlayerActKeyRelease(playerid, keyid);
    #endif
}

/*
 $$$$$$\  $$\       $$$$$$\  
$$  __$$\ $$ |     $$  __$$\ 
$$ /  $$ |$$ |     $$ /  \__|
$$$$$$$$ |$$ |     \$$$$$$\  
$$  __$$ |$$ |      \____$$\ 
$$ |  $$ |$$ |     $$\   $$ |
$$ |  $$ |$$$$$$$$\\$$$$$$  |
\__|  \__|\________|\______/ 
*/

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit VII_OnGameModeInit
#if defined VII_OnGameModeInit
    forward VII_OnGameModeInit();
#endif

#if defined _ALS_OnGameModeExit
    #undef OnGameModeExit
#else
    #define _ALS_OnGameModeExit
#endif
#define OnGameModeExit VII_OnGameModeExit
#if defined VII_OnGameModeExit
    forward VII_OnGameModeExit();
#endif

#if defined ALS_OnPlayerActivationKeyPress
    #undef OnPlayerActivationKeyPress
#else
    #define _ALS_OnPlayerActivationKeyPress
#endif
#if defined VII_OnPlayerActivationKeyPress
    forward VII_OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid);
#endif

#if defined ALS_OnPlayerActKeyRelease
    #undef OnPlayerActivationKeyRelease
#else
    #define _ALS_OnPlayerActKeyRelease
#endif
#if defined VII_OnPlayerActKeyRelease
    forward VII_OnPlayerActKeyRelease(SV_UINT:playerid, SV_UINT:keyid);
#endif