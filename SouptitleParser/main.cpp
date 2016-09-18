#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <regex>

struct timeBlock {
    std::string start;
    std::string end;
    std::string firstSentence;
    std::string secondSentence;
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
    
    std::smatch matchedTimeBlocks;
    
    // search all time blocks in loop
    while(std::regex_search(subtitleContent, matchedTimeBlocks, timeBlockRegex)) {
        timeBlock tb;
        tb.start = matchedTimeBlocks[1];
        tb.end = matchedTimeBlocks[2];
        tb.firstSentence = matchedTimeBlocks[3];
        tb.secondSentence = matchedTimeBlocks[4];
        
        std::cout << tb.start << std::endl;
        subtitleContent = matchedTimeBlocks.suffix().str();
    }
    
    return 0;
}