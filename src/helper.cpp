#include <cstddef>

#include "errors.hpp"
#include "helper.hpp"

size_t getFileSize(std::ifstream& file) {
    if (!file.is_open()) return 0;

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    return size;
}

enum toyErrors get_commands(std::vector<uint32_t> *commands, const std::string& filename, size_t *fsz) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Error reading file: " << filename << "\n";
        return TOY_FILE_READ_ERROR;
    }

    size_t fSize = getFileSize(file);
    *fsz = fSize;
    if (fSize % COMMAND_SIZE || fSize == 0) {
        std::cerr << "WRONG FILE SIZE " << fSize << "\n";
        file.close();
        return TOY_WRONG_FILE_SIZE;
    }

    if (file.is_open()) {
        std::vector<char> buffer(fSize);
        file.read(buffer.data(), fSize);
        ON_DEBUG(hexDump(buffer));

        *commands = std::vector<uint32_t>(
        reinterpret_cast<const uint32_t*>(buffer.data()),
        reinterpret_cast<const uint32_t*>(buffer.data()) + fSize / COMMAND_SIZE
        );

        return TOY_SUCCESS;
    }
    return TOY_FAILED;
}
