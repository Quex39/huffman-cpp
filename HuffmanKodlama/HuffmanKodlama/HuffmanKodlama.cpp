#include <iostream>
#include <string>
#include <unordered_map>

struct HuffmanNode {
	char ch;
	size_t freq;
	HuffmanNode* left;
	HuffmanNode* right;

	HuffmanNode(char character, size_t frequency)
		: ch(character), freq(frequency), left(nullptr), right(nullptr) { }
};

int main() {

	std::string metin = "SELAM KIZLAR SIKIM SIZLAR";
	std::unordered_map<char, size_t> frekanslar;

	for (char c : metin) {
		frekanslar[c]++;
	}

	for (const auto& cift : frekanslar) {
		std::cout << cift.first << " -> " << cift.second << std::endl;
	}



	return 0;
}