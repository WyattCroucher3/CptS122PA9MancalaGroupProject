//
//  wraptext.hpp
//  Final Proj
//
//  Solution found on [GitHub](https://gist.github.com/andrew-d-jackson/7858095#file-wraptext-hpp)

#ifndef wraptext_hpp
#define wraptext_hpp

inline sf::String wrapText(sf::String string, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold = false){
    float currentOffset = 0;
    bool firstWord = true;
    std::size_t wordBegining = 0;
    
    for (std::size_t pos(0); pos < string.getSize(); ++pos) {
        auto currentChar = string[pos];
        if (currentChar == '\n'){
            currentOffset = 0;
            firstWord = true;
            continue;
        } else if (currentChar == ' ') {
            wordBegining = pos;
            firstWord = false;
        }
        
        auto glyph = font.getGlyph(currentChar, charicterSize, bold);
        currentOffset += glyph.advance;
        
        if (!firstWord && currentOffset > width) {
            pos = wordBegining;
            string[pos] = '\n';
            firstWord = true;
            currentOffset = 0;
        }
    }
    
    return string;
}

#endif /* wraptext_hpp */
