#include <iostream>
#include <queue>
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



int main() {

	std::string metin = "merhaba";
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

	std::cout << "Karakter Kodlari: " << std::endl;
	for (const auto& cift : kodTablosu) {
		std::cout << "  '" << cift.first << "' -> " << cift.second << std::endl;
	}

	return 0;
}