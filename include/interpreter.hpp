#pragma once

enum toyErrors get_commands(std::vector<uint32_t> *commands, const std::string& filename);
size_t getFileSize(std::ifstream& file);



std::vector<uint32_t>& charToCmd(std::vector<char> buffer);

template<typename T>
void hexDump(const std::vector<T>& buffer);
