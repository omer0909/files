#include <ao/ao.h>

#include <chrono>
#include <cstring>
#include <iostream>

int main() {
	// AO çalma cihazını başlatma
	ao_initialize();

	// Ses formatını ayarlama
	ao_sample_format format;
	memset(&format, 0, sizeof(format));
	format.bits = 16;     // Örneklem büyüklüğü
	format.channels = 2;  // Kanal sayısı (stereo)
	format.rate = 44100;  // Örnekleme hızı
	format.byte_format = AO_FMT_LITTLE;

	// AO çalma cihazını açma
	ao_device* device = ao_open_live(ao_default_driver_id(), &format, nullptr);
	if (!device) {
		std::cerr << "AO cihazını açma hatası" << std::endl;
		return 1;
	}

	// Çalma yapılacak .wav dosyasının adı
	const char* dosyaAdi = "sound_s.wav";

	// .wav dosyasını okuma
	FILE* dosya = std::fopen(dosyaAdi, "rb");

	std::fseek(dosya, 0, SEEK_END);
	size_t boyut = std::ftell(dosya);

	float toplam_uzunluk = (boyut * 8.0) / (format.rate * format.bits * format.channels);
	float start_time = 1.5f;

	std::cout << "dosya toplam uzunluk: " << toplam_uzunluk << std::endl;
	std::cout << "başlangıç zamanı: " << start_time << std::endl;

	if (start_time >= toplam_uzunluk)
		return 0;

	size_t start_byte = (start_time / 8) * (format.rate * format.bits * format.channels);

	std::fseek(dosya, start_byte, SEEK_SET);

	if (!dosya) {
		std::cerr << "Dosya açma hatası: " << dosyaAdi << std::endl;
		return 1;
	}

	// Ses verilerini okuma ve çalma
	const int BUF_BOYUTU = 4096;
	char buffer[BUF_BOYUTU];

	auto start = std::chrono::system_clock::now();

	while (true) {
		// Verileri oku
		std::size_t okunanByte = std::fread(buffer, sizeof(char), BUF_BOYUTU, dosya);

		// Verileri çal
		if (ao_play(device, buffer, static_cast<uint_32>(okunanByte)) == 0) {
			break;
		}
	}

	{
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_seconds = now - start;
		std::cout << elapsed_seconds.count() << std::endl;
	}

	// Dosyayı kapat
	std::fclose(dosya);

	// AO çalma cihazını kapatma
	ao_close(device);

	// AO'yı temizleme
	ao_shutdown();

	return 0;
}
//sudo apt install libao-dev
//g++ main.cpp -lao -ldl
