#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

using std::string;

struct Engel {
    string isim;
    double x;
    double y;
    int etiket;
};

class IOtonomModel {
public:
    virtual void egit(const std::vector<Engel>& veri) = 0;
    virtual ~IOtonomModel() = default;
};

class GuvenlikModulu : public IOtonomModel {
    double agirlik_x;
    double agirlik_y;
    double sapma;
    double ogrenme_orani;
    int iterasyon_sayisi;
    double ceza_katsayisi;

public:
    GuvenlikModulu(double ogrenme = 0.001, int iterasyon = 10000, double ceza = 0.01)
        : agirlik_x(0.0), agirlik_y(0.0), sapma(0.0),
          ogrenme_orani(ogrenme), iterasyon_sayisi(iterasyon), ceza_katsayisi(ceza) {}

    void egit(const std::vector<Engel>& engeller) override {
        if (engeller.empty()) {
            throw std::invalid_argument("Hata: Egitim verisi bos olamaz!");
        }

        for (int tur = 0; tur < iterasyon_sayisi; ++tur) {
            for (const auto& engelNoktasi : engeller) {
                double koridor_mesafesi = engelNoktasi.etiket * (agirlik_x * engelNoktasi.x + agirlik_y * engelNoktasi.y + sapma);

                if (koridor_mesafesi >= 1.0) {
                    agirlik_x -= ogrenme_orani * (2 * ceza_katsayisi * agirlik_x);
                    agirlik_y -= ogrenme_orani * (2 * ceza_katsayisi * agirlik_y);
                } else {
                    agirlik_x -= ogrenme_orani * (2 * ceza_katsayisi * agirlik_x - engelNoktasi.x * engelNoktasi.etiket);
                    agirlik_y -= ogrenme_orani * (2 * ceza_katsayisi * agirlik_y - engelNoktasi.y * engelNoktasi.etiket);
                    sapma -= ogrenme_orani * (-engelNoktasi.etiket);
                }
            }
        }
    }
    void siniriYazdir() const {
        std::cout << "--- Optimum Guvenlik Siniri Bulundu ---\n";
        std::cout << "Denklem (Ayristirici Koridor Merkezi):\n";
        std::cout << agirlik_x << " * x + " << agirlik_y << " * y + " << sapma << " = 0\n";
        std::cout << "---------------------------------------\n";
    }
};

int main() {
    std::vector<Engel> engeller = {
        {"Sol Kaldirim Kosesi", 2.0, 5.0, 1},
        {"Sol Park Etmis Arac", 2.5, 8.0, 1},
        {"Sol Refuj Bariyeri", 3.0, 12.0, 1},

        {"Sag Yol Kenari Bariyeri", 7.0, 4.0, -1},
        {"Sag Emniyet Seridi Dubasi", 6.5, 9.0, -1},
        {"Sag Trafik Isareti Diregi", 7.5, 14.0, -1},
            {"Çukur",5,10,-1}
    };

    try {
        IOtonomModel* otonomSistem = new GuvenlikModulu(0.001, 10000, 0.01);

        otonomSistem->egit(engeller);

        dynamic_cast<GuvenlikModulu*>(otonomSistem)->siniriYazdir();

        delete otonomSistem;

    } catch (const std::exception& hata) {
        std::cerr << "Sistem Coktu:" << hata.what() << '\n';
    }

    return 0;
}