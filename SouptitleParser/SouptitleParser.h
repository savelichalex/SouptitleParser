#pragma once

#include <string>
#include <regex>
#include <vector>

struct TimeBlock {
    std::string start;
    std::string end;
    std::string firstSentence;
    std::string secondSentence;
};

class SouptitleParser {
private:
    std::regex timeBlockRegex;
    std::smatch matchedTimeBlocks;
public:
    SouptitleParser();
    std::vector<TimeBlock> getTimeBlocks(std::string subtitleContent);
};