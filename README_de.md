[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver HMC5883L
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/hmc5883l/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Das HMC5883L von Honeywell ist ein oberflächenmontierbares Multi-Chip-Modul, das für die magnetische Niederfeld-Erfassung mit einer digitalen Schnittstelle für Anwendungen wie kostengünstige Kompassmessung und Magnetometrie entwickelt wurde.Das HMC5883L enthält unsere hochmoderne, hochauflösende Magnetoresistive Sensoren der HMC118X-Serie sowie ein ASIC mit Verstärkung, automatischen Entmagnetisierungsbandtreibern, Offset-Unterdrückung und einem 12-Bit-ADC, der eine Kompasskursgenauigkeit von 1° bis 2° ermöglicht.Der serielle I2C-Bus ermöglicht eine einfache Schnittstelle.Der HMC5883L ist ein 3,0 x 3,0 x 0,9 mm oberflächenmontierbarer 16-poliger bleifreier Chipträger (LCC) Zu den Anwendungen für den HMC5883L gehören Mobiltelefone, Netbooks, Unterhaltungselektronik, automatische Navigationssysteme und persönliche Navigationsgeräte.

LibDriver HMC5883L ist der Treiber mit vollem Funktionsumfang von HMC5883L, der von LibDriver eingeführt wurde. Er bietet Magnetfeldstärkemessung im Dauermodus, Magnetfeldmessung im Einzelmodus und andere Funktionen. LibDriver entspricht MISRA.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example write](#example-write)
    - [example shot](#example-shot)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver HMC5883L-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver HMC5883L IIC。

/test enthält den Testcode des LibDriver HMC5883L-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen。

/example enthält LibDriver HMC5883L-Beispielcode.

/doc enthält das LibDriver HMC5883L-Offlinedokument.

/Datenblatt enthält HMC5883L-Datenblatt。

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie /src, /interface und /example zu Ihrem Projekt hinzu.

### Nutzung

#### example write

```C
uint8_t res;
uint8_t i;
float m_gauss[3];

res = hmc5883l_basic_init();
if (res)
{
    return 1;
}

...


for (i = 0; i < 3; i++)
{
    hmc5883l_interface_delay_ms(1000);
    res = hmc5883l_basic_read((float *)m_gauss);
    if (res)
    {
        hmc5883l_basic_deinit();

        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: x is %0.3f.\n", m_gauss[0]);
    hmc5883l_interface_debug_print("hmc5883l: y is %0.3f.\n", m_gauss[1]);
    hmc5883l_interface_debug_print("hmc5883l: z is %0.3f.\n", m_gauss[2]);
    
    ...
    
}

...

hmc5883l_basic_deinit();

return 0;
```

#### example shot

```c
uint8_t res;
uint8_t i;
float m_gauss[3];

res = hmc5883l_shot_init();
if (res)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    hmc5883l_interface_delay_ms(1000);
    res = hmc5883l_shot_read((float *)m_gauss);
    if (res)
    {
        hmc5883l_shot_deinit();

        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: x is %0.3f.\n", m_gauss[0]);
    hmc5883l_interface_debug_print("hmc5883l: y is %0.3f.\n", m_gauss[1]);
    hmc5883l_interface_debug_print("hmc5883l: z is %0.3f.\n", m_gauss[2]);
    
    ...
    
}

...

hmc5883l_shot_deinit();

return 0;
```

### Dokument

Online-Dokumente: https://www.libdriver.com/docs/hmc5883l/index.html

Offline-Dokumente: /doc/html/index.html

### Beitrag

Bitte senden Sie eine E-Mail an lishifenging@outlook.com

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com