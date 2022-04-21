#include "lexer_token.hpp"

namespace ShadowPig::Umbra {
    LexerToken::LexerToken():
        _type(Type::Invalid)
    {}
    
    LexerToken::LexerToken(Type type, const Lexeme& lexeme, Line line, Column column):
        _type(type),
        _lexeme(lexeme),
        _line(line),
        _column(column)
    {}

    LexerToken::Type LexerToken::type() const
    {
        return _type;
    }
        
    const LexerToken::Lexeme& LexerToken::lexeme() const
    {
        return _lexeme;
    }

    LexerToken::Line LexerToken::line() const {
        return _line;
    }

    LexerToken::Column LexerToken::column() const {
        return _column;
    }

    bool LexerToken::operator == (const LexerToken& other) const
    {
        return (_type == other._type) && (_lexeme == other._lexeme);
    }
}

std::ostream& operator << (std::ostream& stream, const ShadowPig::Umbra::LexerToken& token)
{
    return stream << token.type() << "(" << token.lexeme() << ")";
}