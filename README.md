# 🚀 Otonom Navigasyon Güvenlik Modülü (SVM Tabanlı)

Bu proje, 2 boyutlu bir düzlemde tanımlanmış iki farklı engel sınıfı arasında, otonom araçlar için **"Maksimum Güvenlik Koridoru"** oluşturan bir yazılım modülüdür. Standart doğrusal ayırıcıların aksine bu sistem, engelleri sadece birbirinden ayırmakla kalmaz; her iki sınıftaki en yakın engel koordinatlarına olan uzaklığı matematiksel olarak maksimize eder.

## 🎯 Projenin Amacı
Otonom araç navigasyonunda basit bir ayırıcı çizgi sistem güvenliği için yeterli değildir. Bu modülün amacı, aracın geçebileceği en geniş boşluğu (Safety Margin) garanti eden optimum sınırı hesaplamaktır.

## 🛠 Teknik Özellikler & Mimari

### 1. Yazılım Mimarisi (OOP)
Proje, **Nesne Yönelimli Programlama (OOP)** prensipleri doğrultusunda katmanlı bir yapıda tasarlanmıştır:
* **`IOtonomModel` (Arayüz):** Sistemin genişleyebilirliğini sağlayan, `egit` ve `tahminEt` metotlarını barındıran koruyucu katman.
* **`GuvenlikModulu` (Yalıtılmış Modül):** SVM algoritmasını, Gradyan İniş (Gradient Descent) optimizasyonunu ve hata yönetimini içeren çekirdek katman.
* **İzolasyon:** Modüller arasındaki şeffaf katmanlama, sistem bileşenlerinin birbirine müdahale etmesini engelleyerek güvenliği artırır.

### 2. Güvenli Bellek Yönetimi
Otonom sistemler gibi kritik yapılarda bellek sızıntısı sistem çökmesine eşdeğerdir.
* **Sıfır Sızıntı Politikası:** Manuel pointer (`new`/`delete`) yönetimi yerine Modern C++ STL bileşeni olan `std::vector` tercih edilmiştir.
* **Otomatik Yıkım:** Veriler, kapsam dışına çıktığında dinamik ve güvenli bir şekilde bellekten temizlenir.

### 3. Algoritmik Model (SVM)
Modül, **Destek Vektör Makineleri (SVM)** teorisini temel alır.
* **Optimizasyon:** `agirlik_x`, `agirlik_y` ve `sapma (bias)` parametreleri üzerinden Hinge Loss türevi kullanılarak optimum dengeye ulaşılır.
* **Öğrenme Oranı:** `0.001` olarak belirlenen hassas oran, modelin salınım yapmadan kararlı bir şekilde çözüme yerleşmesini sağlar.

## 📈 Zaman Karmaşıklığı Analizi (Big-O)

Algoritmanın performansı asimptotik olarak analiz edilmiştir:
* **Karmaşıklık:** $O(Epoch \times N)$.
* **Analiz:** Eğitim döngüsündeki iterasyon sayısı (10.000 Epoch), çalışma zamanını doğrusal (lineer) olarak katlayan bir çarpan etkisi yaratır. Bu, maksimum güvenlik koridorunu bulmak için ödenen matematiksel bir zaman bedelidir.

## 📊 Örnek Senaryo
Sistem, aşağıdaki gibi farklı engel sınıflarını analiz eder:
* **Sol Engeller (Sınıf 1):** Kaldırım köşeleri, park etmiş araçlar.
* **Sağ Engeller (Sınıf -1):** Bariyerler, trafik direkleri.

Algoritma çalıştırıldığında, bu iki grubu en geniş marjla ayıran `ax + by + c = 0` denklemi elde edilir.
