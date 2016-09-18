#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <regex>
#include <vector>

struct TimeBlock {
    std::string start;
    std::string end;
    std::string firstSentence;
    std::string secondSentence;
};

class SubtitleParser {
private:
    std::regex timeBlockRegex;
    std::smatch matchedTimeBlocks;
public:
    SubtitleParser() {
        timeBlockRegex = std::regex("(\\d{2}:\\d{2}:\\d{2},\\d{3})\\s-->\\s(\\d{2}:\\d{2}:\\d{2},\\d{3})\r?\n([^\r\n]+)\r?\n([^\r\n]*)");
    }
    std::vector<TimeBlock> getTimeBlocks(std::string subtitleContent) {
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
    }
};

int main(int argc, const char* argv[]) {
    const std::regex timeBlockRegex("(\\d{2}:\\d{2}:\\d{2},\\d{3})\\s-->\\s(\\d{2}:\\d{2}:\\d{2},\\d{3})\r?\n([^\r\n]+)\r?\n([^\r\n]*)");
    
    std::ifstream subtutleFile("test.srt");
    std::string subtitleContent;
    
    // alocate memory first (TODO: need to check that file exist and that length is begger than 0)
    subtutleFile.seekg(0, std::ios::end);
    subtitleContent.reserve(subtutleFile.tellg());
    subtutleFile.seekg(0, std::ios::beg);
    
    // get content and put it to variable
    subtitleContent.assign((std::istreambuf_iterator<char>(subtutleFile)), std::istreambuf_iterator<char>());
    subtutleFile.close();
    
    SubtitleParser parser;
    std::vector<TimeBlock> result = parser.getTimeBlocks(subtitleContent);
    std::cout << result.size() << std::endl;
    std::cout << result[1].start << std::endl;
    
    return 0;
}