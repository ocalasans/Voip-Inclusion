/*
    * Voip-Inclusion v1.0.0

    -

    Português:

    Este include proporciona uma integração de alta qualidade do Voip em seu Gamemode. Além disso, é
    configurável por meio de callbacks, permitindo uma personalização flexível e adaptável às
    necessidades específicas do seu projeto de jogo. Desenvolvido por [Calasans]. 

    © [2024] [Calasans]. Todos os direitos reservados.

    -

    English:

    This include provides excellent Voip integration into your Gamemode, and it's configurable through
    callbacks, allowing for flexible customization tailored to the specific needs of your game project.
    Developed by [Calasans].

    © [2024] [Calasans]. All rights reserved.

    -

    Discord: ocalasans
    Youtube: Calasans
    Instagram: ocalasans

    SA:MP Programming Comunnity©: https://abre.ai/samp-spc
*/

#if defined _voip_inclusion
    #undef _voip_inclusion
#endif
//
#if defined _voip_inclusion_included
    #endinput
#endif
#define _voip_inclusion_included
//
#if !defined _INC_open_mp
    #if !defined _samp_included
        #error "A biblioteca `a_samp` nao foi ativada. Por favor, ative-a no inicio do seu Gamemode. Ex: `#include <a_samp>`"
    #endif
#endif
//
#include <sampvoice>

/*
$$$$$$$\             $$$$$$\  $$\           $$\                                               $$\       $$$$$$$\             $$$$$$\  $$\           $$\   $$\     $$\                               
$$  __$$\           $$  __$$\ \__|          \__|                                              $$ |      $$  __$$\           $$  __$$\ \__|          \__|  $$ |    \__|                              
$$ |  $$ | $$$$$$\  $$ /  \__|$$\ $$$$$$$\  $$\  $$$$$$$\  $$$$$$\   $$$$$$\   $$$$$$$\       $$ |      $$ |  $$ | $$$$$$\  $$ /  \__|$$\ $$$$$$$\  $$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\   $$$$$$$\ 
$$ |  $$ |$$  __$$\ $$$$\     $$ |$$  __$$\ $$ |$$  _____|$$  __$$\ $$  __$$\ $$  _____|      \__|      $$ |  $$ |$$  __$$\ $$$$\     $$ |$$  __$$\ $$ |\_$$  _|  $$ |$$  __$$\ $$  __$$\ $$  _____|
$$ |  $$ |$$$$$$$$ |$$  _|    $$ |$$ |  $$ |$$ |$$ /      $$ /  $$ |$$$$$$$$ |\$$$$$$\        $$\       $$ |  $$ |$$$$$$$$ |$$  _|    $$ |$$ |  $$ |$$ |  $$ |    $$ |$$ /  $$ |$$ |  $$ |\$$$$$$\  
$$ |  $$ |$$   ____|$$ |      $$ |$$ |  $$ |$$ |$$ |      $$ |  $$ |$$   ____| \____$$\       $$ |      $$ |  $$ |$$   ____|$$ |      $$ |$$ |  $$ |$$ |  $$ |$$\ $$ |$$ |  $$ |$$ |  $$ | \____$$\ 
$$$$$$$  |\$$$$$$$\ $$ |      $$ |$$ |  $$ |$$ |\$$$$$$$\ \$$$$$$  |\$$$$$$$\ $$$$$$$  |      $$ |      $$$$$$$  |\$$$$$$$\ $$ |      $$ |$$ |  $$ |$$ |  \$$$$  |$$ |\$$$$$$  |$$ |  $$ |$$$$$$$  |
\_______/  \_______|\__|      \__|\__|  \__|\__| \_______| \______/  \_______|\_______/       \__|      \_______/  \_______|\__|      \__|\__|  \__|\__|   \____/ \__| \______/ \__|  \__|\_______/ 
*/

#define NOT_GLOBAL_VOIP (SV_FALSE)
#define GLOBAL_VOIP (SV_TRUE)
//
#define VII_loop_0:(%0) foreach(new %0: Player)
#define VII_loop_1:(%0) for(new %0 = 0; %0 < MAX_PLAYERS; %0 ++)

/*
$$\    $$\                    $$\                               $$\                 $$\       $$\    $$\                    $$\           $$\       $$\                     
$$ |   $$ |                   \__|                              \__|                $$ |      $$ |   $$ |                   \__|          $$ |      $$ |                    
$$ |   $$ |$$$$$$\   $$$$$$\  $$\  $$$$$$\ $$\    $$\  $$$$$$\  $$\  $$$$$$$\       $$ |      $$ |   $$ |$$$$$$\   $$$$$$\  $$\  $$$$$$\  $$$$$$$\  $$ | $$$$$$\   $$$$$$$\ 
\$$\  $$  |\____$$\ $$  __$$\ $$ | \____$$\\$$\  $$  |$$  __$$\ $$ |$$  _____|      \__|      \$$\  $$  |\____$$\ $$  __$$\ $$ | \____$$\ $$  __$$\ $$ |$$  __$$\ $$  _____|
 \$$\$$  / $$$$$$$ |$$ |  \__|$$ | $$$$$$$ |\$$\$$  / $$$$$$$$ |$$ |\$$$$$$\        $$\        \$$\$$  / $$$$$$$ |$$ |  \__|$$ | $$$$$$$ |$$ |  $$ |$$ |$$$$$$$$ |\$$$$$$\  
  \$$$  / $$  __$$ |$$ |      $$ |$$  __$$ | \$$$  /  $$   ____|$$ | \____$$\       $$ |        \$$$  / $$  __$$ |$$ |      $$ |$$  __$$ |$$ |  $$ |$$ |$$   ____| \____$$\ 
   \$  /  \$$$$$$$ |$$ |      $$ |\$$$$$$$ |  \$  /   \$$$$$$$\ $$ |$$$$$$$  |      $$ |         \$  /  \$$$$$$$ |$$ |      $$ |\$$$$$$$ |$$$$$$$  |$$ |\$$$$$$$\ $$$$$$$  |
    \_/    \_______|\__|      \__| \_______|   \_/     \_______|\__|\_______/       \__|          \_/    \_______|\__|      \__| \_______|\_______/ \__| \_______|\_______/ 
*/

new SV_GSTREAM:gstream = SV_NULL;
new SV_DLSTREAM:lstream[MAX_PLAYERS] = { SV_NULL, ... };
//
static VII_voip_message[156],
    bool:VII_voip_created[MAX_PLAYERS] = SV_FALSE,
    VII_voip_check_foreach[7] = 0,
    VII_voip_max_players[MAX_PLAYERS],
    VII_voip_color[MAX_PLAYERS],
    VII_voip_name[MAX_PLAYERS][20];

/*
 $$$$$$\              $$\                                         $$\        $$$$$$\    $$\     $$\                                     
$$  __$$\             $$ |                                        $$ |      $$  __$$\   $$ |    $$ |                                    
$$ /  $$ |$$\   $$\ $$$$$$\    $$$$$$\   $$$$$$\   $$$$$$$\       $$ |      $$ /  $$ |$$$$$$\   $$$$$$$\   $$$$$$\   $$$$$$\   $$$$$$$\ 
$$ |  $$ |$$ |  $$ |\_$$  _|  $$  __$$\ $$  __$$\ $$  _____|      \__|      $$ |  $$ |\_$$  _|  $$  __$$\ $$  __$$\ $$  __$$\ $$  _____|
$$ |  $$ |$$ |  $$ |  $$ |    $$ |  \__|$$ /  $$ |\$$$$$$\        $$\       $$ |  $$ |  $$ |    $$ |  $$ |$$$$$$$$ |$$ |  \__|\$$$$$$\  
$$ |  $$ |$$ |  $$ |  $$ |$$\ $$ |      $$ |  $$ | \____$$\       $$ |      $$ |  $$ |  $$ |$$\ $$ |  $$ |$$   ____|$$ |       \____$$\ 
 $$$$$$  |\$$$$$$  |  \$$$$  |$$ |      \$$$$$$  |$$$$$$$  |      $$ |       $$$$$$  |  \$$$$  |$$ |  $$ |\$$$$$$$\ $$ |      $$$$$$$  |
 \______/  \______/    \____/ \__|       \______/ \_______/       \__|       \______/    \____/ \__|  \__| \_______|\__|      \_______/ 
*/

stock VII_voip_verification_strcmp(const VII_string_1[], const VII_string_2[], value)
{
    for(new v = 0; v < value; v ++)
    {
        if(VII_string_1[v] != VII_string_2[v])
            return SV_FALSE;
        //
        if(VII_string_1[v] == 0 || VII_string_1[v] == '\n')
            return SV_TRUE;
    }
    //
    return SV_FALSE;
}

stock VII_voip_send_message(playerid, VII_color, const VII_message[])
{
    format(VII_voip_message, sizeof(VII_voip_message), "%s", VII_message);
    //
    if(!VII_voip_verification_strcmp(VII_voip_message, "", 2) && !VII_voip_verification_strcmp(VII_voip_message, " ", 3))
        SendClientMessage(playerid, VII_color, VII_voip_message);
    //
    return SV_TRUE;
}

public OnGameModeInit()
{
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
    print("||                      V-I versao 1.0.0                        ||");
    print("||                        By: Calasans                          ||");
    print("||                  Discord: abre.ai/samp-spc                   ||");
    print("||                                                              ||"); 
    print("||==============================================================||");
    print("__________________________________________________________________");
    print(" ");
    //
    gstream = SvCreateGStream(0xDEB887FF, "G");
    //
    #if defined VII_OnGameModeInit
        return VII_OnGameModeInit();
    #else
        return SV_TRUE;
    #endif
}

public OnGameModeExit()
{
    if(gstream != SV_NULL)
    {
        SvDeleteStream(gstream);
        gstream = SV_NULL;
    }
    //
    #if defined VII_OnGameModeExit
        return VII_OnGameModeExit();
    #else
        return SV_TRUE;
    #endif
}

public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    if(VII_voip_created[playerid])
    {
        if(keyid == 0x42 && lstream[playerid])
            SvAttachSpeakerToStream(lstream[playerid], playerid);
        //
        if(keyid == 0x5A && gstream)
        {
            if(IsPlayerAdmin(playerid))
                SvAttachSpeakerToStream(gstream, playerid);
        }
    }
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    if(VII_voip_created[playerid])
    {
        if(keyid == 0x42 && lstream[playerid])
            SvDetachSpeakerFromStream(lstream[playerid], playerid);
        //
        if(keyid == 0x5A && gstream)
        {
            if(IsPlayerAdmin(playerid))
                SvDetachSpeakerFromStream(gstream, playerid);
        }
    }
}

/*
$$$$$$$$\                                                                $$\       $$$$$$$$\                              $$\     $$\                               
$$  _____|                                                               $$ |      $$  _____|                             $$ |    \__|                              
$$ |   $$\   $$\ $$$$$$$\   $$$$$$$\  $$$$$$\   $$$$$$\   $$$$$$$\       $$ |      $$ |   $$\   $$\ $$$$$$$\   $$$$$$$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\   $$$$$$$\ 
$$$$$\ $$ |  $$ |$$  __$$\ $$  _____|$$  __$$\ $$  __$$\ $$  _____|      \__|      $$$$$\ $$ |  $$ |$$  __$$\ $$  _____|\_$$  _|  $$ |$$  __$$\ $$  __$$\ $$  _____|
$$  __|$$ |  $$ |$$ |  $$ |$$ /      $$ /  $$ |$$$$$$$$ |\$$$$$$\        $$\       $$  __|$$ |  $$ |$$ |  $$ |$$ /        $$ |    $$ |$$ /  $$ |$$ |  $$ |\$$$$$$\  
$$ |   $$ |  $$ |$$ |  $$ |$$ |      $$ |  $$ |$$   ____| \____$$\       $$ |      $$ |   $$ |  $$ |$$ |  $$ |$$ |        $$ |$$\ $$ |$$ |  $$ |$$ |  $$ | \____$$\ 
$$ |   \$$$$$$  |$$ |  $$ |\$$$$$$$\ \$$$$$$  |\$$$$$$$\ $$$$$$$  |      $$ |      $$ |   \$$$$$$  |$$ |  $$ |\$$$$$$$\   \$$$$  |$$ |\$$$$$$  |$$ |  $$ |$$$$$$$  |
\__|    \______/ \__|  \__| \_______| \______/  \_______|\_______/       \__|      \__|    \______/ \__|  \__| \_______|   \____/ \__| \______/ \__|  \__|\_______/ 
*/

stock Voip_Criar(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
{
    if(!VII_global)
    {
        if(!VII_voip_created[playerid])
        {
            if(SvGetVersion(playerid) != 0)
            {
                if(SvHasMicro(playerid))
                {
                    if(gstream != SV_NULL)
                    {
                        SvAttachListenerToStream(gstream, playerid);
                        SvAddKey(playerid, 0x5A); // Pressione | Press > Z
                    }
                    static VII_format_message[20];
                    format(VII_format_message, 20, VII_name);
                    //
                    lstream[playerid] = SvCreateDLStreamAtPlayer(VII_distance, VII_max_players, playerid, VII_color, VII_format_message);
                    SvAddKey(playerid, 0x42); // Pressione | Press > B
                    //
                    VII_voip_created[playerid] = SV_TRUE;
                    //
                    VII_voip_max_players[playerid] = VII_max_players,
                    VII_voip_color[playerid] = VII_color,
                    format(VII_voip_name[playerid], 20, VII_name);
                    //
                    return SV_TRUE;
                }
                //
                return SV_FALSE;
            }
            //
            return SV_FALSE;
        }
        //
        return SV_FALSE;
    }
    else if(VII_global)
    {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_voip_check_foreach[0]++;
            //
            VII_loop_0:(i)
            {
                if(!VII_voip_created[i])
                {
                    if(SvGetVersion(i) != 0)
                    {
                        if(SvHasMicro(i))
                        {
                            if(gstream != SV_NULL)
                            {
                                SvAttachListenerToStream(gstream, i);
                                SvAddKey(i, 0x5A); // Pressione | Press > Z
                            }
                            static VII_format_message[20];
                            format(VII_format_message, 20, VII_name);
                            //
                            lstream[i] = SvCreateDLStreamAtPlayer(VII_distance, VII_max_players, i, VII_color, VII_format_message);
                            SvAddKey(i, 0x42); // Pressione | Press > B
                            //
                            VII_voip_created[i] = SV_TRUE;
                            //
                            VII_voip_max_players[i] = VII_max_players,
                            VII_voip_color[i] = VII_color,
                            format(VII_voip_name[i], 20, VII_name);
                        }
                        //
                        if(i >= VII_voip_check_foreach[0])
                        {
                            VII_voip_check_foreach[0] = 0;
                            //
                            return SV_TRUE;
                        }
                        //
                        return SV_FALSE;
                    }
                    //
                    return SV_FALSE;
                }
                //
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i)
            {
                if(!VII_voip_created[i])
                {
                    if(SvGetVersion(i) != 0)
                    {
                        if(SvHasMicro(i))
                        {
                            if(gstream != SV_NULL)
                            {
                                SvAttachListenerToStream(gstream, i);
                                SvAddKey(i, 0x5A); // Pressione | Press > Z
                            }
                            static VII_format_message[20];
                            format(VII_format_message, 20, VII_name);
                            //
                            lstream[i] = SvCreateDLStreamAtPlayer(VII_distance, VII_max_players, i, VII_color, VII_format_message);
                            SvAddKey(i, 0x42); // Pressione | Press > B
                            //
                            VII_voip_created[i] = SV_TRUE;
                            //
                            VII_voip_max_players[i] = VII_max_players,
                            VII_voip_color[i] = VII_color,
                            format(VII_voip_name[i], 20, VII_name);
                        }
                        //
                        if(i >= MAX_PLAYERS)
                            return SV_TRUE;
                        //
                        return SV_FALSE;
                    }
                    //
                    return SV_FALSE;
                }
                //
                return SV_FALSE;
            }
        #endif
        //
        return SV_FALSE;
    }
    //
    return SV_FALSE;
}

stock Voip_Excluir(bool:VII_global, playerid = INVALID_PLAYER_ID)
{
    if(!VII_global)
    {
        if(VII_voip_created[playerid])
        {
            if(lstream[playerid])
            {
                SvDeleteStream(lstream[playerid]);
                lstream[playerid] = SV_NULL;
            }
            //
            if(gstream != SV_NULL)
                SvDetachListenerFromStream(gstream, playerid);
            //
            VII_voip_created[playerid] = SV_FALSE;
            //
            VII_voip_max_players[playerid] = SV_INFINITY,
            VII_voip_color[playerid] = -1,
            VII_voip_name[playerid] = "Undefined";
            //
            return SV_TRUE;
        }
        //
        return SV_FALSE;
    }
    if(VII_global)
    {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_voip_check_foreach[1]++;
            //
            VII_loop_0:(i)
            {
                if(VII_voip_created[i])
                {
                    if(lstream[i])
                    {
                        SvDeleteStream(lstream[i]);
                        lstream[i] = SV_NULL;
                    }
                    //
                    if(gstream != SV_NULL)
                        SvDetachListenerFromStream(gstream, i);
                    //
                    VII_voip_created[i] = SV_FALSE;
                    //
                    VII_voip_max_players[i] = SV_INFINITY,
                    VII_voip_color[i] = -1,
                    VII_voip_name[i] = "Undefined";
                }
                //
                if(i >= VII_voip_check_foreach[1])
                {
                    VII_voip_check_foreach[1] = 0;
                    //
                    return SV_TRUE;
                }
                //
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i)
            {
                if(VII_voip_created[i])
                {
                    if(lstream[i])
                    {
                        SvDeleteStream(lstream[i]);
                        lstream[i] = SV_NULL;
                    }
                    //
                    if(gstream != SV_NULL)
                        SvDetachListenerFromStream(gstream, i);
                    //
                    VII_voip_created[i] = SV_FALSE;
                    //
                    VII_voip_max_players[i] = SV_INFINITY,
                    VII_voip_color[i] = -1,
                    VII_voip_name[i] = "Undefined";
                }
                //
                if(i >= MAX_PLAYERS)
                    return SV_TRUE;
                //
                return SV_FALSE;
            }
        #endif
        //
        return SV_FALSE;
    }
    //
    return SV_FALSE;
}

stock Voip_Distancia(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
{
    if(!VII_global)
    {
        if(VII_voip_created[playerid])
        {
            if(lstream[playerid])
                SvDeleteStream(lstream[playerid]);
            //
            lstream[playerid] = SvCreateDLStreamAtPlayer(VII_distance, VII_voip_max_players[playerid], playerid, VII_voip_color[playerid], VII_voip_name[playerid]);
            //
            VII_voip_send_message(playerid, VII_color, VII_message);
            //
            return SV_TRUE;
        }
        //
        return SV_FALSE;
    }
    else if(VII_global)
    {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_voip_check_foreach[6]++;
            //
            VII_loop_0:(i)
            {
                if(VII_voip_created[i])
                {
                    if(lstream[i])
                        SvDeleteStream(lstream[i]);
                    //
                    lstream[i] = SvCreateDLStreamAtPlayer(VII_distance, VII_voip_max_players[i], i, VII_voip_color[i], VII_voip_name[i]);
                    //
                    VII_voip_send_message(i, VII_color, VII_message);
                }
                if(i >= VII_voip_check_foreach[6])
                {
                    VII_voip_check_foreach[6] = 0;
                    //
                    return SV_TRUE;
                }
                //
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i)
            {
                if(VII_voip_created[i])
                {
                    if(lstream[i])
                        SvDeleteStream(lstream[i]);
                    //
                    lstream[i] = SvCreateDLStreamAtPlayer(VII_distance, VII_voip_max_players[i], i, VII_voip_color[i], VII_voip_name[i]);
                    //
                    VII_voip_send_message(i, VII_color, VII_message);
                }
                //
                if(i >= MAX_PLAYERS)
                    return SV_TRUE;
                //
                return SV_FALSE;
            }
        #endif
        //
        return SV_FALSE;
    }
    //
    return SV_FALSE;
}

stock Voip_NaoEncontrado(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
{
    if(!VII_global)
    {
        if(!SvGetVersion(playerid))
        {
            VII_voip_send_message(playerid, VII_color, VII_message);
            //
            return SV_TRUE;
        }
        //
        return SV_FALSE;
    }
    else if(VII_global)
    {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_voip_check_foreach[2]++;
            //
            VII_loop_0:(i)
            {
                if(!SvGetVersion(i))
                    VII_voip_send_message(i, VII_color, VII_message);
                //
                if(i >= VII_voip_check_foreach[2])
                {
                    VII_voip_check_foreach[2] = 0;
                    //
                    return SV_TRUE;
                }
                //
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i)
            {
                if(!SvGetVersion(i))
                    VII_voip_send_message(i, VII_color, VII_message);
                //
                if(i >= MAX_PLAYERS)
                    return SV_TRUE;
                //
                return SV_FALSE;
            }
        #endif
        //
        return SV_FALSE;
    }
    //
    return SV_FALSE;
}

stock Voip_NaoMicrofone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
{
    if(!VII_global)
    {
        if(!SvHasMicro(playerid))
        {
            VII_voip_send_message(playerid, VII_color, VII_message);
            //
            return SV_TRUE;
        }
        //
        return SV_FALSE;
    }
    else if(VII_global)
    {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_voip_check_foreach[3]++;
            //
            VII_loop_0:(i)
            {
                if(!SvGetVersion(i))
                    VII_voip_send_message(i, VII_color, VII_message);
                //
                if(i >= VII_voip_check_foreach[3])
                {
                    VII_voip_check_foreach[3] = 0;
                    //
                    return SV_TRUE;
                }
                //
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i)
            {
                if(!SvGetVersion(i))
                    VII_voip_send_message(i, VII_color, VII_message);
                //
                if(i >= MAX_PLAYERS)
                    return SV_TRUE;
                //
                return SV_FALSE;
            }
        #endif
        //
        return SV_FALSE;
    }
    //
    return SV_FALSE;
}

stock Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
{
    if(!VII_global)
    {
        if(SvGetVersion(playerid) != 0)
        {
            if(SvHasMicro(playerid))
            {
                if(gstream != SV_NULL)
                {
                    VII_voip_send_message(playerid, VII_color, VII_message);
                    //
                    return SV_TRUE;
                }
                //
                return SV_FALSE;
            }
            //
            return SV_FALSE;
        }
        //
        return SV_FALSE;
    }
    else if(VII_global)
    {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_voip_check_foreach[4]++;
            //
            VII_loop_0:(i)
            {
                if(SvGetVersion(i) != 0)
                {
                    if(SvHasMicro(i))
                    {
                        if(gstream != SV_NULL)
                            VII_voip_send_message(i, VII_color, VII_message);
                        //
                        if(i >= VII_voip_check_foreach[4])
                        {
                            VII_voip_check_foreach[4] = 0;
                            //
                            return SV_TRUE;
                        }
                        //
                        return SV_FALSE;
                    }
                    //
                    return SV_FALSE;
                }
                //
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i)
            {
                if(SvGetVersion(i) != 0)
                {
                    if(SvHasMicro(i))
                    {
                        if(gstream != SV_NULL)
                            VII_voip_send_message(i, VII_color, VII_message);
                        //
                        if(i >= MAX_PLAYERS)
                            return SV_TRUE;
                        //
                        return SV_FALSE;
                    }
                    //
                    return SV_FALSE;
                }
                //
                return SV_FALSE;
            }
        #endif
        //
        return SV_FALSE;
    }
    //
    return SV_FALSE;
}

stock Voip_Jogador(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
{
    if(!VII_global)
    {
        if(SvGetVersion(playerid) != 0)
        {
            if(SvHasMicro(playerid))
            {
                if(lstream[playerid])
                {
                    VII_voip_send_message(playerid, VII_color, VII_message);
                    //
                    return SV_TRUE;
                }
                //
                return SV_FALSE;
            }
            //
            return SV_FALSE;
        }
        //
        return SV_FALSE;
    }
    else if(VII_global)
    {
        #if defined _INC_y_iterate || defined _FOREACH_LOCAL_VERSION
            VII_loop_0:(i)
                VII_voip_check_foreach[5]++;
            //
            VII_loop_0:(i)
            {
                if(SvGetVersion(i) != 0)
                {
                    if(SvHasMicro(i))
                    {
                        if(lstream[i])
                            VII_voip_send_message(i, VII_color, VII_message);
                        //
                        if(i >= VII_voip_check_foreach[5])
                        {
                            VII_voip_check_foreach[5] = 0;
                            //
                            return SV_TRUE;
                        }
                        //
                        return SV_FALSE;
                    }
                    //
                    return SV_FALSE;
                }
                //
                return SV_FALSE;
            }
        #elseif !defined _INC_y_iterate || !defined _FOREACH_LOCAL_VERSION
            VII_loop_1:(i)
            {
                if(SvGetVersion(i) != 0)
                {
                    if(SvHasMicro(i))
                    {
                        if(lstream[i])
                            VII_voip_send_message(i, VII_color, VII_message);
                        //
                        if(i >= MAX_PLAYERS)
                            return SV_TRUE;
                        //
                        return SV_FALSE;
                    }
                    //
                    return SV_FALSE;
                }
                //
                return SV_FALSE;
            }
        #endif
        //
        return SV_FALSE;
    }
    //
    return SV_FALSE;
}

stock Voip_Depurar(bool:VII_debug = SV_FALSE)
    SvDebug(VII_debug);

/*
$$$$$$$$\                     $$\ $$\           $$\       
$$  _____|                    $$ |\__|          $$ |      
$$ |      $$$$$$$\   $$$$$$\  $$ |$$\  $$$$$$$\ $$$$$$$\  
$$$$$\    $$  __$$\ $$  __$$\ $$ |$$ |$$  _____|$$  __$$\ 
$$  __|   $$ |  $$ |$$ /  $$ |$$ |$$ |\$$$$$$\  $$ |  $$ |
$$ |      $$ |  $$ |$$ |  $$ |$$ |$$ | \____$$\ $$ |  $$ |
$$$$$$$$\ $$ |  $$ |\$$$$$$$ |$$ |$$ |$$$$$$$  |$$ |  $$ |
\________|\__|  \__| \____$$ |\__|\__|\_______/ \__|  \__|
                    $$\   $$ |                            
                    \$$$$$$  |                            
                     \______/                             
*/

stock Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
    return Voip_Criar(VII_global, VII_distance, VII_max_players, VII_color, VII_name, playerid);
//
stock Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
    return Voip_Excluir(VII_global, playerid);
//
stock Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
    return Voip_Distancia(VII_global, VII_distance, VII_color, VII_message, playerid);
//
stock Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
    return Voip_NaoEncontrado(VII_global, VII_color, VII_message, playerid);
//
stock Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
    return Voip_NaoMicrofone(VII_global, VII_color, VII_message, playerid);
//
stock Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
    return Voip_Jogador(VII_global, VII_color, VII_message, playerid);
//
stock Voip_Debug(bool:VII_debug = SV_FALSE)
    SvDebug(VII_debug);

/*
$$$$$$$\             $$$$$$\  $$\           $$\                                               $$\       $$$$$$$\             $$$$$$\  $$\           $$\   $$\     $$\                               
$$  __$$\           $$  __$$\ \__|          \__|                                              $$ |      $$  __$$\           $$  __$$\ \__|          \__|  $$ |    \__|                              
$$ |  $$ | $$$$$$\  $$ /  \__|$$\ $$$$$$$\  $$\  $$$$$$$\  $$$$$$\   $$$$$$\   $$$$$$$\       $$ |      $$ |  $$ | $$$$$$\  $$ /  \__|$$\ $$$$$$$\  $$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\   $$$$$$$\ 
$$ |  $$ |$$  __$$\ $$$$\     $$ |$$  __$$\ $$ |$$  _____|$$  __$$\ $$  __$$\ $$  _____|      \__|      $$ |  $$ |$$  __$$\ $$$$\     $$ |$$  __$$\ $$ |\_$$  _|  $$ |$$  __$$\ $$  __$$\ $$  _____|
$$ |  $$ |$$$$$$$$ |$$  _|    $$ |$$ |  $$ |$$ |$$ /      $$ /  $$ |$$$$$$$$ |\$$$$$$\        $$\       $$ |  $$ |$$$$$$$$ |$$  _|    $$ |$$ |  $$ |$$ |  $$ |    $$ |$$ /  $$ |$$ |  $$ |\$$$$$$\  
$$ |  $$ |$$   ____|$$ |      $$ |$$ |  $$ |$$ |$$ |      $$ |  $$ |$$   ____| \____$$\       $$ |      $$ |  $$ |$$   ____|$$ |      $$ |$$ |  $$ |$$ |  $$ |$$\ $$ |$$ |  $$ |$$ |  $$ | \____$$\ 
$$$$$$$  |\$$$$$$$\ $$ |      $$ |$$ |  $$ |$$ |\$$$$$$$\ \$$$$$$  |\$$$$$$$\ $$$$$$$  |      $$ |      $$$$$$$  |\$$$$$$$\ $$ |      $$ |$$ |  $$ |$$ |  \$$$$  |$$ |\$$$$$$  |$$ |  $$ |$$$$$$$  |
\_______/  \_______|\__|      \__|\__|  \__|\__| \_______| \______/  \_______|\_______/       \__|      \_______/  \_______|\__|      \__|\__|  \__|\__|   \____/ \__| \______/ \__|  \__|\_______/ 
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
//
#if defined _ALS_OnGameModeExit
    #undef OnGameModeExit
#else
    #define _ALS_OnGameModeExit
#endif
#define OnGameModeExit VII_OnGameModeExit
#if defined VII_OnGameModeExit
    forward VII_OnGameModeExit();
#endif
//