#pragma once

enum toyErrors get_commands(std::vector<uint32_t> *commands, const std::string& filename);
size_t getFileSize(std::ifstream& file);

void hexDump(std::vector<char> buffer);
