[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver HMC5883L

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/hmc5883l/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

Honeywell HMC5883L은 저비용 나침반 및 자기 측정과 같은 애플리케이션을 위한 디지털 인터페이스가 있는 저장 자기 감지용으로 설계된 표면 실장 다중 칩 모듈입니다. HMC118X 시리즈 자기 저항 센서와 증폭, 자동 소거 스트랩 드라이버, 오프셋 제거 및 1° ~ 2°의 나침반 방향 정확도를 가능하게 하는 12비트 ADC를 포함하는 ASIC I2C 직렬 버스를 통해 인터페이스가 간편합니다. HMC5883L은 3.0x3.0x0.9mm 표면 실장 16핀 무연 칩 캐리어(LCC) HMC5883L의 애플리케이션에는 휴대전화, 넷북, 가전제품, 자동 내비게이션 시스템 및 개인용 내비게이션 장치가 포함됩니다.

LibDriver HMC5883L은 LibDriver에서 출시한 HMC5883L의 전체 기능 드라이버입니다. 연속 모드 자기장 강도 판독, 단일 모드 자기장 판독 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver HMC5883L의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver HMC5883L용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver HMC5883L드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver HMC5883L프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver HMC5883L오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 HMC5883L데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인IIC 버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

#### example basic

```C
#include "driver_hmc5883l_basic.h"

uint8_t res;
uint8_t i;
float m_gauss[3];

res = hmc5883l_basic_init();
if (res != 0)
{
    return 1;
}

...


for (i = 0; i < 3; i++)
{
    hmc5883l_interface_delay_ms(1000);
    res = hmc5883l_basic_read((float *)m_gauss);
    if (res != 0)
    {
        (void)hmc5883l_basic_deinit();

        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: x is %0.3f.\n", m_gauss[0]);
    hmc5883l_interface_debug_print("hmc5883l: y is %0.3f.\n", m_gauss[1]);
    hmc5883l_interface_debug_print("hmc5883l: z is %0.3f.\n", m_gauss[2]);
    
    ...
    
}

...

(void)hmc5883l_basic_deinit();

return 0;
```

#### example shot

```c
#include "driver_hmc5883l_shot.h"

uint8_t res;
uint8_t i;
float m_gauss[3];

res = hmc5883l_shot_init();
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    hmc5883l_interface_delay_ms(1000);
    res = hmc5883l_shot_read((float *)m_gauss);
    if (res != 0)
    {
        (void)hmc5883l_shot_deinit();

        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: x is %0.3f.\n", m_gauss[0]);
    hmc5883l_interface_debug_print("hmc5883l: y is %0.3f.\n", m_gauss[1]);
    hmc5883l_interface_debug_print("hmc5883l: z is %0.3f.\n", m_gauss[2]);
    
    ...
    
}

...

(void)hmc5883l_shot_deinit();

return 0;
```

### 문서

온라인 문서: [https://www.libdriver.com/docs/hmc5883l/index.html](https://www.libdriver.com/docs/hmc5883l/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.