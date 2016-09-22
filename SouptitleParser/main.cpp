#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>

#include "SouptitleParser.h"

int main(int argc, const char* argv[]) {
    std::ifstream subtutleFile("test.srt");
    std::string subtitleContent;
    
    // alocate memory first (TODO: need to check that file exist and that length is begger than 0)
    subtutleFile.seekg(0, std::ios::end);
    subtitleContent.reserve(subtutleFile.tellg());
    subtutleFile.seekg(0, std::ios::beg);
    
    // get content and put it to variable
    subtitleContent.assign((std::istreambuf_iterator<char>(subtutleFile)), std::istreambuf_iterator<char>());
    subtutleFile.close();
    
    SouptitleParser parser;
    std::vector<TimeBlock> result = parser.getTimeBlocks(subtitleContent);
    std::cout << result.size() << std::endl;
    std::cout << result[1].start << std::endl;
    
    return 0;
}