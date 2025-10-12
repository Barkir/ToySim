#pragma once

enum toyErrors get_commands(std::vector<uint32_t> *commands, const std::string& filename);
size_t getFileSize(std::ifstream& file);


template<typename T>
void hexDump(const std::vector<T>& buffer);


void init(std::vector<uint32_t> commands);
