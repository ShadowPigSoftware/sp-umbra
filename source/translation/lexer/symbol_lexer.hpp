#pragma once

#include "lexer_token.hpp"
#include <map>
namespace ShadowPig::Umbra {
    class SymbolLexer {
    public:
        SymbolLexer(LexerToken::Type type);
        LexerToken process(UTF32String::PositionIterator& iterator);
        static LexerToken::Type preprocessorDeclarationTypeFromCharacter(const UTF32Character& character);
    private:
        LexerToken::Type _type;
        using TypeMap = std::map<UTF32Character, LexerToken::Type>;
        static TypeMap _typeMap;
    };
}