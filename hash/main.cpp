#include <iostream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>

using namespace CryptoPP;

std::string HashFile(const std::string& filename) {
    SHA256 hash;
    std::string digest;

    try {
        FileSource file(filename.c_str(), true,
            new HashFilter(hash, new HexEncoder(new StringSink(digest))));
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Crypto++ error: " << e.what() << std::endl;
        exit(1);
    }

    return digest;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    
    std::ifstream infile(filename.c_str());
    if (!infile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    try {
        std::string hash = HashFile(filename);
        std::cout << "Hash: " << hash << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
