## Include Voip-Inclusion SA:MP

Este include oferece uma integração simplificada do `Voip` em seu Gamemode, proporcionando flexibilidade incomparável. Com a capacidade de utilizar callbacks para alterações personalizadas e enviar mensagens aos jogadores, além de suporte global para todos os jogadores. É recomendável que você leia as categorias abaixo para ficar informado.

English > [README](https://github.com/ocalasans/Voip-Inclusion/blob/main/README.eng.md).

-----------------------
 
### Como instalar?

Você deve fazer o download do include. Depois de tê-lo feito, você deverá colocar o include na pasta (pawno > include). Após ter feito isso, abra o arquivo pwn do seu Gamemode e coloque o seguinte código abaixo dos seus outros includes:
```pawn
#include <Voip-Inclusion>
```

-----------------------

### Includes necessárias

* [SAMPVOICE](https://github.com/CyberMor/sampvoice).

> [!WARNING]
> Este include só é compatível até a versão `3.1` do sampvoice.

-----------------------

### Como funciona?

Este include opera da seguinte maneira: o usuário simplesmente precisa ativá-lo em seu Gamemode. Além disso, é imperativo que o usuário tenha o [SAMPVOICE](https://github.com/CyberMor/sampvoice) incluído em sua biblioteca e tenha ativado o plugin correspondente no `server.cfg`. No que concerne às funcionalidades, este include é altamente flexível, permitindo ao usuário configurar as mensagens conforme desejado e de maneira personalizada. As callbacks não se limitam a uma única utilização; o usuário pode usá-las quando e onde quiser, tantas vezes quanto necessário. No entanto, suas vantagens não param por aí. Nas callbacks das funções, estão disponíveis opções globais, incluindo definições como `NOT_GLOBAL_VOIP`, que não representam a comunicação global, e `GLOBAL_VOIP`, que a representam. Além disso, este **README** também contém mais duas categorias, explicando detalhadamente as callbacks tanto em contexto global quanto não global, e fornecendo orientações claras sobre sua implementação.

-----------------------

### Como utilizar de forma não global?

Nesta categoria, encontra-se a explicação de como utilizar todas as callbacks de forma não global.

-----------------------

```pawn
native Voip_Criar(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a distância.</kbd>    
3 - <kbd>Defina o máximo de jogadores, SV_INFINITY é padrão.</kbd>    
4 - <kbd>Defina a cor.</kbd>    
5 - <kbd>Defina o nome.</kbd>    
6 - <kbd>Defina o playerid (jogador).</kbd>

* Exemplo:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Criar(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local", playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Excluir(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina o playerid (jogador).</kbd>

* Exemplo:
```pawn
public OnPlayerDisconnect(playerid, reason)
{
    Voip_Excluir(NOT_GLOBAL_VOIP, playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Distancia(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a distância.</kbd>    
3 - <kbd>Defina a cor.</kbd>    
4 - <kbd>Defina a mensagem.</kbd>    
5 - <kbd>Defina o playerid (jogador).</kbd>

* Exemplo:
```pawn
CMD:voipdistancia(playerid)
{
    Voip_Distancia(NOT_GLOBAL_VOIP, 30.0, 0xFFFFFFFF, "Você ajustou a distância do seu voip para 30 metros.", playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_NaoEncontrado(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a cor.</kbd>    
3 - <kbd>Defina a mensagem.</kbd>    
4 - <kbd>Defina o playerid (jogador).</kbd>

* Exemplo:
```pawn
public OnPlayerSpawn(playerid)
{
    Voip_NaoEncontrado(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Seu voip não foi encontrado.", playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_NaoMicrofone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a cor.</kbd>    
3 - <kbd>Defina a mensagem.</kbd>    
4 - <kbd>Defina o playerid (jogador).</kbd>

* Exemplo:
```pawn
public OnPlayerSpawn(playerid)
{
    Voip_NaoMicrofone(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Seu microfone não foi detectado.", playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a cor.</kbd>    
3 - <kbd>Defina a mensagem.</kbd>    
4 - <kbd>Defina o playerid (jogador).</kbd>

* Exemplo:
```pawn
public OnPlayerSpawn(playerid)
{
    Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "O seu voip global foi carregado com sucesso. Pressione a tecla Z para falar.", playerid);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Jogador(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a cor.</kbd>    
3 - <kbd>Defina a mensagem.</kbd>    
4 - <kbd>Defina o playerid (jogador).</kbd>

* Exemplo:
```pawn
public OnPlayerSpawn(playerid)
{
    Voip_Jogador(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "O seu voip local foi carregado com sucesso. Pressione a tecla B para falar.", playerid);
    //
    return true;
}
```

-----------------------

### Como utilizar de forma global?

Nesta categoria, encontra-se a explicação de como utilizar todas as callbacks globalmente. Observem que ao definir uma callback com `GLOBAL_VOIP`, não será necessário especificar o último parâmetro, que é o `playerid`.

-----------------------

```pawn
native Voip_Criar(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a distância.</kbd>    
3 - <kbd>Defina o máximo de jogadores, SV_INFINITY é padrão.</kbd>    
4 - <kbd>Defina a cor.</kbd>    
5 - <kbd>Defina o nome.</kbd>    
6 - <kbd>Não defina o playerid, apague-o.</kbd>

* Exemplo:
```pawn
CMD:criarvoip(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Criar(GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Local");
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Excluir(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Não defina o playerid, apague-o.</kbd>

* Exemplo:
```pawn
CMD:excluirvoip(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Excluir(GLOBAL_VOIP);
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Distancia(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a distância.</kbd>    
3 - <kbd>Defina a cor.</kbd>    
4 - <kbd>Defina a mensagem.</kbd>    
5 - <kbd>Não defina o playerid, apague-o.</kbd>

* Exemplo:
```pawn
CMD:voipdistancia(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Distancia(GLOBAL_VOIP, 30.0, 0xFFFFFFFF, "O administrador ajustou a distância do voip para 30 metros.");
    //
    return true;
}
```

-----------------------

```pawn
native Voip_NaoEncontrado(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a cor.</kbd>    
3 - <kbd>Defina a mensagem.</kbd>    
4 - <kbd>Não defina o playerid, apague-o.</kbd>

* Exemplo:
```pawn
CMD:voipencontrado(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_NaoEncontrado(GLOBAL_VOIP, 0xFFFFFFFF, "O administrador fez uma verificação no servidor, mas o seu voip não foi encontrado.");
    //
    return true;
}
```

-----------------------

```pawn
native Voip_NaoMicrofone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a cor.</kbd>    
3 - <kbd>Defina a mensagem.</kbd>    
4 - <kbd>Não defina o playerid, apague-o.</kbd>

* Exemplo:
```pawn
CMD:voipmicrofone(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_NaoMicrofone(GLOBAL_VOIP, 0xFFFFFFFF, "O administrador fez uma verificação no servidor, mas o seu microfone não foi detectado.");
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a cor.</kbd>    
3 - <kbd>Defina a mensagem.</kbd>    
4 - <kbd>Não defina o playerid, apague-o.</kbd>

* Exemplo:
```pawn
CMD:voipglobal(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "O administrador fez uma verificação no servidor, e seu voip global foi encontrado. Pressione a tecla Z para falar.");
    //
    return true;
}
```

-----------------------

```pawn
native Voip_Jogador(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
1 - <kbd>Defina se é global.</kbd>    
2 - <kbd>Defina a cor.</kbd>    
3 - <kbd>Defina a mensagem.</kbd>    
4 - <kbd>Não defina o playerid, apague-o.</kbd>

* Exemplo:
```pawn
CMD:voipjogador(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Jogador(GLOBAL_VOIP, 0xFFFFFFFF, "O administrador fez uma verificação no servidor, e seu voip local foi encontrado. Pressione a tecla B para falar.");
    //
    return true;
}
```

-----------------------

### Outras callbacks

```pawn
Voip_Depurar(bool:VII_debug = SV_FALSE)
```

* Exemplo:
```pawn
CMD:ativarlogsvoip(playerid)
{
    if(IsPlayerAdmin(playerid))
        Voip_Depurar(true); // Para desativar retire o "true" e nao defina nenhum parâmetro.
    //
    return true;
}
```

-----------------------

### Informações de contato

Instagram: [ocalasans](https://instagram.com/ocalasans)   
YouTube: [Calasans](https://www.youtube.com/@ocalasans)   
Discord: ocalasans   
Comunidade: [SA:MP Programming Community©](https://abre.ai/samp-spc)
