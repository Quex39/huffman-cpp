# huffman-cpp

C++ ile geliştirilmiş **Huffman Kodlama (Huffman Coding)** uygulaması. Metindeki karakterlerin frekanslarına göre min-heap (`std::priority_queue`) kullanarak Huffman ağacı kurar, `0/1` bit kodları üretir, metni sıkıştırır ve orijinal metne geri çözer.

## Özellikler

- Karakter frekanslarının sayılması (`std::unordered_map`)
- `std::priority_queue` (min-heap) ile Huffman ağacı oluşturma
- Ağaç üzerinden karakterlere `0` ve `1` bit kodlarının atanması
- Metni bit dizisine sıkıştırma (`encode`) ve ağaç üzerinden geri çözme (`decode`)
- Dinamik olarak ayrılan düğümlerin bellek temizliği (`delete`)
- `.txt` dosyasından (`girdi.txt`) metin okuma ve sıkıştırılan sonucu dosyaya yazma

## Kullanılan Araçlar

- **Dil:** C++
- **Geliştirme Ortamı:** Visual Studio
- **Sürüm Kontrolü:** Git & GitHub Desktop

## Çalıştırma

1. Depoyu bilgisayarına klonla ve `HuffmanKodlama` çözüm/proje dosyasını Visual Studio ile aç.
2. Girdi metni için `girdi.txt` dosyasını oluşturup içine metin yaz.
3. Projeyi derleyip çalıştır (`Ctrl + F5`).
