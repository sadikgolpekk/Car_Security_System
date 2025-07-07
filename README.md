
# 🚗 Car Security & Control System (Arduino + Proteus)

Bu proje, **Kocaeli Üniversitesi Bilgisayar Mühendisliği Programlama Laboratuvarı dersi** kapsamında geliştirilmiş olup, araç içi güvenlik ve kontrol mekanizmalarının **gömülü sistemler** ile **simülasyon ortamında** gerçekleştirilmesini amaçlamaktadır.

![Image](https://github.com/user-attachments/assets/721c7c67-0046-4daa-b635-53ae9665000b)

## 🎯 Proje Amacı

Bu sistem, Arduino Mega 2560 mikrodenetleyici kartı ile tasarlanmış ve Proteus simülasyon ortamında test edilmiştir. Gerçek hayattaki araç kontrol sistemlerinin temel prensipleri, düşük maliyetli ve güvenilir bir yapı ile modellenmiştir. **Simülasyon ortamı**, devreyi fiziksel olarak kurmadan test edebilmek için tercih edilmiştir.

---

## ⚙️ Kullanılan Teknolojiler ve Bileşenler

- **Arduino Mega 2560**
- **Proteus Design Suite 8.0 (Simülasyon)**
- **LM35 Sıcaklık Sensörü**
- **LDR (Ortam ışığı algılayıcı)**
- **Potansiyometre (Yakıt seviyesi simülasyonu)**
- **Butonlar (Emniyet kemeri, kapı ve motor kontrolü)**
- **LCD Ekran (Sistem durumu)**
- **RGB LED'ler, Buzzer, DC Motor**

---

## 🔧 Temel Özellikler

| Özellik                         | Açıklama                                                                 |
|----------------------------------|--------------------------------------------------------------------------|
| 🚪 Kapı güvenlik kontrolü       | Kapı açıkken motor çalışmaz, kullanıcı uyarılır.                         |
| 🎓 Emniyet kemeri kontrolü      | Kemer takılı değilse motor çalışmaz, buzzer uyarısı verilir.            |
| 🌡️ Isı bazlı klima tetiklemesi | 25°C üzeri sıcaklıkta fan motoru çalışır.                               |
| 🔆 Işık kontrolü                | Ortam karanlıksa otomatik olarak far LED’leri açılır.                   |
| ⛽ Yakıt seviyesi kontrolü     | Düşük yakıt durumunda LED yanıp söner, sıfırda motor kilitlenir.        |

---

## 🧠 Yazılım Akışı (Pseudocode)

```pseudo
BAŞLA
  Eğer kapı açık → Motor çalışmasın
  Eğer kemer takılı değil → Motor çalışmasın + buzzer öt
  Eğer tüm şartlar uygunsa → Motor çalışsın
  Sıcaklık ölç → >25°C ise klima çalışsın
  Işık ölç → LDR < 250 ise farları aç
  Yakıt ölç → <5% ise LED yanıp söner, <=0% ise motor kilitlensin
SON
```

---

## 🧪 Simülasyon Ortamı ve Test Senaryoları

Bu proje, Proteus 8.0 yazılımı üzerinde hazırlanmış ve test edilmiştir. Sistem farklı senaryolar altında test edilerek aşağıdaki sonuçlar gözlemlenmiştir:

- Kapı açıkken motor çalışmıyor, buzzer uyarı veriyor.
- Kemer takılı değilse motor çalışmıyor.
- Ortam karardığında farlar otomatik yanıyor.
- Sıcaklık arttıkça klima (motor fanı) devreye giriyor.
- Yakıt bitince motor otomatik kilitleniyor.

Bu senaryolar, **otomotiv elektroniği** mantığının küçük ölçekte nasıl çalışabileceğini göstermektedir.

---

## 📁 Dosya Yapısı

- `proje.ino` → Arduino kodları
- `.pdsprj` → Proteus simülasyon dosyası
- `LaTeX/` → **LaTeX ile hazırlanmış rapor** ve görselleri
- `.pdf` → Final raporlar ve proje sunum dosyaları

> 📌 Not: Rapor dökümantasyonu bilimsel formatta hazırlanmış olup **LaTeX dokümantasyon sistemi** kullanılmıştır.

---

![Image](https://github.com/user-attachments/assets/41c9d1b4-772f-4ffe-ac10-0f63b880c63d)

## 👨‍💻 Geliştirici

> Sadık Gölpek  
> 🏫 Kocaeli Üniversitesi – Bilgisayar Mühendisliği  

> Ali Kılınç  
> 🏫 Kocaeli Üniversitesi – Bilgisayar Mühendisliği  

---

© 2025 – Bu proje eğitim amaçlı geliştirilmiştir.
