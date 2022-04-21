#include "lexer_token.hpp"

namespace ShadowPig::Umbra {
    LexerToken::LexerToken():
        _type(Type::Invalid)
    {}
    
    LexerToken::LexerToken(Type type, const Lexeme& lexeme):
        _type(type),
        _lexeme(lexeme)
    {}

    LexerToken::Type LexerToken::type() const
    {
        return _type;
    }
        
    const LexerToken::Lexeme& LexerToken::lexeme() const
    {
        return _lexeme;
    }

    bool LexerToken::operator == (const LexerToken& other) const
    {
        return (_type == other._type) && (_lexeme == other._lexeme);
    }
    
    LexerToken LexerToken::PreprocessorImplementationAlpha(const Lexeme& lexeme) {
        return LexerToken(LexerToken::Type::PreprocessorImplementationAlpha, lexeme);
    }
}

std::ostream& operator << (std::ostream& stream, const ShadowPig::Umbra::LexerToken& token)
{
    return stream << token.type() << "(" << token.lexeme() << ")";
}