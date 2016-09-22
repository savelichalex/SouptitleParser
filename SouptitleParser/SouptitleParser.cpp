#include "SouptitleParser.h"

SouptitleParser::SouptitleParser() {
    timeBlockRegex = std::regex("(\\d{2}:\\d{2}:\\d{2},\\d{3})\\s-->\\s(\\d{2}:\\d{2}:\\d{2},\\d{3})\r?\n([^\r\n]+)\r?\n([^\r\n]*)");
};

std::vector<TimeBlock> SouptitleParser::getTimeBlocks(std::string subtitleContent) {
    std::vector<TimeBlock> result;
    while(std::regex_search(subtitleContent, matchedTimeBlocks, timeBlockRegex)) {
        TimeBlock tb;
        tb.start = matchedTimeBlocks[1];
        tb.end = matchedTimeBlocks[2];
        tb.firstSentence = matchedTimeBlocks[3];
        tb.secondSentence = matchedTimeBlocks[4];
        
        result.insert(result.end(), tb);
        subtitleContent = matchedTimeBlocks.suffix().str();
    }
    return result;
};