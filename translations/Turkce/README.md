# Voip-Inclusion

Voip-Inclusion, SA-MP Gamemode'unuzda SAMPVOICE'in basitleştirilmiş entegrasyonu için bir kütüphanedir ve sesli iletişim sistemi üzerinde maksimum esneklik ve kontrol sağlar.

## Diller

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)

## İçindekiler

- [Voip-Inclusion](#voip-inclusion)
  - [Diller](#diller)
  - [İçindekiler](#i̇çindekiler)
  - [Kurulum](#kurulum)
  - [Gereksinimler](#gereksinimler)
  - [Ana Özellikler](#ana-özellikler)
  - [Global ve Bireysel Sistem](#global-ve-bireysel-sistem)
    - [GLOBAL\_VOIP](#global_voip)
    - [NOT\_GLOBAL\_VOIP](#not_global_voip)
  - [Temel Yapılandırma](#temel-yapılandırma)
    - [Sistem Başlatma](#sistem-başlatma)
  - [Kontrol Fonksiyonları](#kontrol-fonksiyonları)
    - [Voip\_Create](#voip_create)
    - [Voip\_Delete](#voip_delete)
    - [Voip\_Distance](#voip_distance)
  - [Geri Bildirim Fonksiyonları](#geri-bildirim-fonksiyonları)
    - [Voip\_NotFound](#voip_notfound)
    - [Voip\_NoMicrophone](#voip_nomicrophone)
    - [Voip\_Global](#voip_global)
    - [Voip\_Player](#voip_player)
  - [Stream Fonksiyonları](#stream-fonksiyonları)
    - [Voip\_GetGlobalStream](#voip_getglobalstream)
    - [Voip\_GetLocalStream](#voip_getlocalstream)
    - [Voip\_SetGlobalStream](#voip_setglobalstream)
    - [Voip\_SetLocalStream](#voip_setlocalstream)
  - [Kullanım Örnekleri](#kullanım-örnekleri)
    - [Tam Yapılandırma](#tam-yapılandırma)
  - [Özel Callbacks](#özel-callbacks)
  - [Lisans](#lisans)
    - [Koşullar:](#koşullar)

## Kurulum

1. [Voip-Inclusion.inc](https://github.com/ocalasans/Voip-Inclusion/releases/download/v1.0.1/Voip-Inclusion.inc) dosyasını indirin
2. Dosyayı sunucunuzun `pawno/include` klasörüne yerleştirin
3. Diğer include'larınızdan sonra aşağıdaki satırı ekleyin:
```pawn
#include <Voip-Inclusion>
```

## Gereksinimler

- [SAMPVOICE](https://github.com/CyberMor/sampvoice) sürüm 3.1 veya daha düşük (uyumlu olan)
- SAMPVOICE eklentisinin `server.cfg`'de etkinleştirilmiş olması

> [!IMPORTANT]
> Bu include yalnızca SAMPVOICE'in 3.1 veya daha düşük (uyumlu olan) sürümü ile uyumludur.

## Ana Özellikler

- **Esnek Yürütme Sistemi**
  - Global ve bireysel işlemleri destekler
  - Verimli callback yönetimi

- **Stream Yönetimi**
  - Otomatik global stream (include'un OnGameModeInit'inde başlatılır)
  - Oyuncu bazlı özelleştirilebilir yerel streamler
  - Hassas ses mesafesi kontrolü

- **Geri Bildirim Sistemi**
  - Tamamen özelleştirilebilir mesajlar
  - Sistem durumu bildirimleri
  - Bağlantı ve mikrofon geri bildirimi

- **Gelişmiş Özellikler**
  - Özelleştirilebilir callbacks
  - Stream'lere doğrudan erişim
  - Hassas ses mesafesi kontrolü

## Global ve Bireysel Sistem

`GLOBAL_VOIP` ve `NOT_GLOBAL_VOIP` sistemi, callback'lerin nasıl yürütüleceğini belirler:

### GLOBAL_VOIP

- Callback'i bağlı tüm oyuncular için yürütür
- `playerid` belirtilmesi gerekmez
- Tüm oyuncuları aynı anda etkileyen eylemler için kullanışlıdır

### NOT_GLOBAL_VOIP

- Callback'i belirli bir oyuncu için yürütür
- `playerid` belirtilmesi gerekir
- Oyuncu bazlı bireysel eylemler için kullanışlıdır

## Temel Yapılandırma

### Sistem Başlatma

```pawn
public OnGameModeInit()
{
    // Varsayılan public'leri etkinleştir
    Voip_EnableDefaultPublics(true);
    
    // Global stream burada include tarafından otomatik olarak oluşturulur

    return true;
}

public OnPlayerConnect(playerid)
{
    // Oyuncu için yerel Voip oluştur
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Yerel", playerid);

    return true;
}
```

## Kontrol Fonksiyonları

### Voip_Create

```pawn
Voip_Create(bool:VII_global, Float:VII_distance, VII_max_players, VII_color, const VII_name[], playerid = INVALID_PLAYER_ID)
```
Yeni bir Voip örneği oluşturur.
- `VII_global`: Oluşturmanın tüm oyuncuları (`GLOBAL_VOIP`) veya belirli bir oyuncuyu (`NOT_GLOBAL_VOIP`) etkileyeceğini belirler
- `VII_distance`: Maksimum ses erişim mesafesi
- `VII_max_players`: Maksimum oyuncu sayısı (sınırsız için `SV_INFINITY` kullanın)
- `VII_color`: Mesajların rengi
- `VII_name`: Örnek adı
- `playerid`: Oyuncu ID'si (yalnızca `NOT_GLOBAL_VOIP` durumunda)

### Voip_Delete

```pawn
Voip_Delete(bool:VII_global, playerid = INVALID_PLAYER_ID)
```
Voip örneğini/örneklerini kaldırır.

### Voip_Distance

```pawn
Voip_Distance(bool:VII_global, Float:VII_distance, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Ses erişim mesafesini ayarlar.

## Geri Bildirim Fonksiyonları

### Voip_NotFound

```pawn
Voip_NotFound(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Voip algılanmadığında geri bildirim gönderir.

### Voip_NoMicrophone

```pawn
Voip_NoMicrophone(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Mikrofon algılanmadığında geri bildirim gönderir.

### Voip_Global

```pawn
Voip_Global(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Global Voip bağlantısı hakkında geri bildirim gönderir (include'un OnGameModeInit'inde oluşturulur).
```pawn
// Bireysel örnek
Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Global Voip bağlandı. Konuşmak için Z tuşuna basın.", playerid);

// Global örnek
if(IsAdmin[playerid]) // Admin olduğunu varsayalım
    Voip_Global(GLOBAL_VOIP, 0xFFFFFFFF, "Global Voip herkes için bağlandı. Konuşmak için Z tuşuna basın.");
```

### Voip_Player

```pawn
Voip_Player(bool:VII_global, VII_color, const VII_message[], playerid = INVALID_PLAYER_ID)
```
Oyuncunun yerel Voip bağlantısı hakkında geri bildirim gönderir.
```pawn
// Bireysel örnek
Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Yerel Voip bağlandı. Konuşmak için B tuşuna basın.", playerid);

// Global örnek
Voip_Player(GLOBAL_VOIP, 0xFFFFFFFF, "Yerel Voip herkes için bağlandı. Konuşmak için B tuşuna basın.");
```

## Stream Fonksiyonları

### Voip_GetGlobalStream

```pawn
SV_GSTREAM:Voip_GetGlobalStream()
```
Include'un OnGameModeInit'inde oluşturulan global stream'i döndürür.

### Voip_GetLocalStream

```pawn
SV_DLSTREAM:Voip_GetLocalStream(playerid)
```
Belirli bir oyuncunun yerel stream'ini döndürür.

### Voip_SetGlobalStream

```pawn
bool:Voip_SetGlobalStream(SV_GSTREAM:VII_new_stream)
```
Yeni bir global stream belirler.

### Voip_SetLocalStream

```pawn
bool:Voip_SetLocalStream(playerid, SV_DLSTREAM:VII_new_stream)
```
Bir oyuncu için yeni bir yerel stream belirler.

## Kullanım Örnekleri

### Tam Yapılandırma

Varsayılan public'leri etkinleştirme:
```pawn
public OnGameModeInit()
{
    Voip_EnableDefaultPublics(true);

    return true;
}
```

Belirli bir oyuncu için yerel Voip oluşturma:
```pawn
public OnPlayerConnect(playerid)
{
    Voip_Create(NOT_GLOBAL_VOIP, 25.0, SV_INFINITY, 0xFFFFFFFF, "Yerel", playerid);
    
    return true;
}
```

Belirli bir oyuncu için hem global hem de yerel Voip geri bildirimi gönderme:
```pawn
public OnPlayerSpawn(playerid)
{
    if(IsAdmin[playerid]) // Admin olduğunu varsayalım
        Voip_Global(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Global Voip kullanılabilir. Konuşmak için Z tuşuna basın.", playerid);
    
    Voip_Player(NOT_GLOBAL_VOIP, 0xFFFFFFFF, "Yerel Voip etkinleştirildi. Konuşmak için B tuşuna basın.", playerid);

    return true;
}
```

Tüm oyuncuları etkileyen komut örneği:
```pawn
CMD:voipglobaldist(playerid)
{
    if(IsPlayerAdmin(playerid))
        // Tüm oyuncular için Voip mesafesini değiştirir
        Voip_Distance(GLOBAL_VOIP, 50.0, 0xFFFFFFFF, "Admin Voip mesafesini 50 metreye değiştirdi.");
    
    return true;
}
```

## Özel Callbacks

`Voip_EnableDefaultPublics(false)` kullanarak varsayılan public'leri devre dışı bıraktıysanız, kendi callback'lerinizi uygulayabilirsiniz:

```pawn
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    // Özel kodunuz buraya
    // keyid 0x42 (B) yerel Voip için
    // keyid 0x5A (Z) global Voip için
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Özel kodunuz buraya
}
```

## Lisans

Bu Include Apache 2.0 Lisansı altında korunmaktadır ve şunlara izin verir:

- ✔️ Ticari ve özel kullanım
- ✔️ Kaynak kodunda değişiklik
- ✔️ Kod dağıtımı
- ✔️ Patent hakları

### Koşullar:

- Telif hakkı bildirimini korumak
- Önemli değişiklikleri belgelemek
- Apache 2.0 lisansının bir kopyasını dahil etmek

Lisans hakkında daha fazla bilgi için: http://www.apache.org/licenses/LICENSE-2.0

**Telif Hakkı (c) Calasans - Tüm hakları saklıdır**