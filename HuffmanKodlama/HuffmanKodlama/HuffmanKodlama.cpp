#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct HuffmanNode {
	char ch;
	size_t freq;
	HuffmanNode* left;
	HuffmanNode* right;

	HuffmanNode(char character, size_t frequency)
		: ch(character), freq(frequency), left(nullptr), right(nullptr) { }
};

struct KucukFrekansOnce {
	bool operator()(HuffmanNode* a, HuffmanNode* b) const {
		return a->freq > b->freq;
	}
};


std::string dosyadanMetinOku(const std::string& dosyaAdi) {
	std::ifstream dosya(dosyaAdi);
	if (!dosya.is_open()) {
		std::cerr << "Hata: '" << dosyaAdi << "' dosyasi acilamadi!" << std::endl;
		return "";
	}

	std::ostringstream tampon;
	tampon << dosya.rdbuf();
	return tampon.str();
}


void kodlariUret(HuffmanNode* dugum, const std::string& mevcutKod, std::unordered_map<char, std::string>& kodTablosu) {
	if (dugum == nullptr) {
		return;
	}

	if (dugum->left == nullptr && dugum->right == nullptr) {
		kodTablosu[dugum->ch] = mevcutKod.empty() ? "0" : mevcutKod;
		return;
	}

	kodlariUret(dugum->left, mevcutKod + "0", kodTablosu);
	kodlariUret(dugum->right, mevcutKod + "1", kodTablosu);
}


std::string metniSikistir(const std::string& metin, const std::unordered_map<char, std::string>& kodTablosu) {
	std::string sikistirilmis;

	for (char c : metin) {
		sikistirilmis += kodTablosu.at(c);
	}
	return sikistirilmis;
}


std::string metniCoz(HuffmanNode* kok, const std::string& sikistirilmis) {
	if (kok == nullptr || sikistirilmis.empty()) {
		return "";
	}

	std::string cozulmus;
	HuffmanNode* mevcut = kok;


	if (kok->left == nullptr && kok->right == nullptr) {
		for (size_t i = 0; i < sikistirilmis.size(); ++i) {
			cozulmus += kok->ch;
		}
		return cozulmus;
	}

	for (char bit : sikistirilmis) {
		if (bit == '0') {
			mevcut = mevcut->left;
		}
		else if (bit == '1') {
			mevcut = mevcut->right;
		}
		if (mevcut == nullptr) {
			mevcut = kok;
			continue;
		}

		if (mevcut->left == nullptr && mevcut->right == nullptr) {
			cozulmus += mevcut->ch;
			mevcut = kok;
		}
	}
	return cozulmus;
}


void agaciTemizle(HuffmanNode* dugum) {
	if (dugum == nullptr) {
		return;
	}

	agaciTemizle(dugum->left);
	agaciTemizle(dugum->right);
	delete dugum;
}


void dosyayaMetinYaz(const std::string& ciktiDosyaAdi, const std::string& icerik) {
	std::ofstream cikis(ciktiDosyaAdi);
	if (!cikis.is_open()) {
		std::cerr << "Hata: '" << ciktiDosyaAdi << "' dosyasi yazmak icin acilamadi!" << std::endl;
		return;
	}

	cikis << icerik;
	cikis.close();
}


int main() {
	std::string dosyaAdi = "girdi.txt";
	std::string metin = dosyadanMetinOku(dosyaAdi);

	if (metin.empty()) {
		std::cout << "Okunacak metin bulunamadi veya dosya bos." << std::endl;
		return 1;
	}

	std::unordered_map<char, size_t> frekanslar;
	for (char c : metin) {
		frekanslar[c]++;
	}

	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, KucukFrekansOnce> kuyruk;


	for (const auto& cift : frekanslar) {
		HuffmanNode* yeniDugum = new HuffmanNode(cift.first, cift.second);
		kuyruk.push(yeniDugum);
	}

	while (kuyruk.size() > 1) {
		HuffmanNode* sol = kuyruk.top();
		kuyruk.pop();

		HuffmanNode* sag = kuyruk.top();
		kuyruk.pop();

		HuffmanNode* ebeveyn = new HuffmanNode('\0', sol->freq + sag->freq);
		ebeveyn->left = sol;
		ebeveyn->right = sag;

		kuyruk.push(ebeveyn);
	}

	HuffmanNode* kok = kuyruk.empty() ? nullptr : kuyruk.top();

	std::unordered_map<char, std::string> kodTablosu;
	kodlariUret(kok, "", kodTablosu);

	std::string sikistirilmis = metniSikistir(metin, kodTablosu);
	std::string cozulmus = metniCoz(kok, sikistirilmis);

	std::string ciktiDosyaAdi = "sikistirilmis_bitler.txt";
	dosyayaMetinYaz(ciktiDosyaAdi, sikistirilmis);
	std::cout << "Sikistirilmis veri '" << ciktiDosyaAdi << "' dosyasina yazildi." << std::endl;

	std::cout << "Orjinal metin: " << metin << std::endl;
	std::cout << "Sikistirilmis bit dizisi: " << sikistirilmis << std::endl;
	std::cout << "Huffman bit uzunlugu: " << sikistirilmis.size() << " bit" << std::endl;

	std::cout << "Cozulen metin: " << cozulmus << std::endl;
	return 0;
}