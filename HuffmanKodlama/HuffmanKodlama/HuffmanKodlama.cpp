#include <iostream>
#include <string>

struct HuffmanNode {
	char ch;
	size_t freq;
	HuffmanNode* left;
	HuffmanNode* right;

	HuffmanNode(char character, size_t frequency)
		: ch(character), freq(frequency), left(nullptr), right(nullptr) { }
};

int main() {
	HuffmanNode dugum('a', 3);

	std::cout << "Karakter: " << dugum.ch << ", Frekans: " << dugum.freq << std::endl;

	return 0;
}