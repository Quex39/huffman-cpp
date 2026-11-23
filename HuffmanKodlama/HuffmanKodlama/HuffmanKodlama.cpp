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


	if (!kuyruk.empty()) {
		HuffmanNode* enKucuk = kuyruk.top();
		std::cout << "En kucuk frekansli dugum -> Karakter: '" << enKucuk->ch << "', Frekans: " << enKucuk->freq << std::endl;
	}


	return 0;
}