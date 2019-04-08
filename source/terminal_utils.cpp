/*
 * Copyright (C) 2019 Maxwell Aguiar Silva <maxwellaguiarsilva@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * File:   TerminalUtils.cpp
 * Author: Maxwell Aguiar Silva <maxwellaguiarsilva@gmail.com>
 *
 * Created on 29 de Janeiro de 2019, 17:49
 */

#include <terminal_utils.hpp>
#include <cpp_utils.hpp>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <ctime>

// TerminalUtils

using namespace cpp_utils::terminal;
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::function;

//
TerminalUtils::TerminalUtils( ){ };
TerminalUtils::~TerminalUtils( )
{
    cout << COLOR_RESET << CLRSCR;
};

//
unique_ptr<TerminalUtils> TerminalUtils::instance;
TerminalUtils & TerminalUtils::get( )
{
    if( !( instance.get( ) ) )instance = unique_ptr<TerminalUtils>( new TerminalUtils );
    return *( instance.get( ) );
};

//
void TerminalUtils::moveCursor( const TerminalUtils::DIRECTION &d, const int num )
{
    cout << "\033[" << num << ( char ) d;
}

//
void TerminalUtils::setCursorPosition( const unsigned int line, const unsigned int column )
{
    cout << "\033[" << line << ";" << column << "f";
}

// TerminalUtils::Keyboard
class PrivateKeyboard : public TerminalUtils::Keyboard
{
private:
    bool keyMode, keyEcho, keyWait;
    TerminalUtils &term;
    PrivateKeyboard( const PrivateKeyboard& orig ) = delete;
public:

    //
    PrivateKeyboard( TerminalUtils& term ) : term( term ){ };
    virtual ~PrivateKeyboard( )
    {
        setLineMode( );
    };

    //
    void setLineMode( ) override
    {
        struct termios termConfig;
        tcgetattr( STDIN_FILENO, &termConfig ); // Pega os atributos atuais do terminal.
        termConfig.c_lflag |= ( ICANON | ECHO ); // Ativa o ECHO e o modo canônico do terminal.
        termConfig.c_cc[VTIME] = 0; // Tempo de espera.
        termConfig.c_cc[VMIN] = 1; // Quantos caracteres ficar esperando.
        tcsetattr( STDIN_FILENO, TCSANOW, &termConfig ); // Define no terminal os atributos alterados.
        cout << term.SHOW_CURSOR; // Mostra o cursor de digitação no terminal.
        keyMode = false;
        keyEcho = true;
        keyWait = true;
    }

    //
    void setKeyMode( bool wait, bool echo ) override
    {
        struct termios termConfig;
        tcgetattr( STDIN_FILENO, &termConfig ); // Pega os atributos atuais do terminal.
        termConfig.c_lflag &= ~ICANON; // Destaiva o modo canônico do terminal.
        // Ativa ou Desativa o ECHO do terminal de acor com o parâmetro.
        termConfig.c_lflag = echo ? termConfig.c_lflag | ECHO : termConfig.c_lflag & ~ECHO;
        termConfig.c_cc[VTIME] = 0; // Sem tempo de espera.
        termConfig.c_cc[VMIN] = wait * 1; // Quantos caracteres ficar esperando.
        tcsetattr( STDIN_FILENO, TCSANOW, &termConfig ); // Define no terminal os atributos alterados.
        cout << term.HIDE_CURSOR; // Oculta o cursor de digitação no terminal.
        keyMode = true;
        keyWait = wait;
        keyEcho = echo;
    }

    //
    bool getKeyPress( unsigned long &keyCode ) override
    {
        // Algumas teclas como ( F5 = 0x1B5B31357E ) possuem 2 bytes de leitura.
        // Por isso é necessário usar unsigned long;

        // Permite acessar o unsigned long um byte por vez, através de um array de char.
        char *charCodes = ( char* ) &keyCode,
            counter = sizeof ( unsigned long );

        // Caso definido para esperar a tecla, remove o bloqueio de leitura
        // para pegar todos os bytes das teclas especiais. Depois bloqueia novamente.
        keyCode = 0;
        if( keyWait )
        {
            charCodes[--counter] = getc( stdin );
            struct termios termConfig;
            tcgetattr( STDIN_FILENO, &termConfig );
            termConfig.c_cc[VMIN] = 0;
            tcsetattr( STDIN_FILENO, TCSANOW, &termConfig );
            while( ( charCodes[--counter] = getc( stdin ) ) != -1 );
            termConfig.c_cc[VMIN] = 1;
            tcsetattr( STDIN_FILENO, TCSANOW, &termConfig );
        } else // Senão apenas lê todos os bytes é retornar -1.
            while( ( charCodes[--counter] = getc( stdin ) ) != -1 );

        keyCode >>= 8 * ++counter; // ++counter para retirar o último -1 lido.

        return keyCode != 0;

    }

};

//
TerminalUtils::Keyboard::Keyboard( ){ };
TerminalUtils::Keyboard::~Keyboard( ){ };

//
unique_ptr<TerminalUtils::Keyboard> TerminalUtils::Keyboard::instance;
TerminalUtils::Keyboard & TerminalUtils::Keyboard::get( TerminalUtils * term )
{
    if( !( instance.get( ) ) )instance = unique_ptr<Keyboard>( new PrivateKeyboard( *term ) );
    return *( instance.get( ) );
};

//
void TerminalUtils::Keyboard::loopKeyPress( std::function< bool( const unsigned long ) > loopAction )
{
    unsigned long keyCode;
    this->setKeyMode( );
    while( this->getKeyPress( keyCode ), loopAction( keyCode ) );
};

//
void TerminalUtils::Keyboard::loopKeyPress( function< bool( const unsigned long, const unsigned int ) > loopAction, const unsigned int maxFPS )
{

    using cpp_utils::datetime_utils::get_time_in_micro_seconds;

    unsigned long keyCode;

    this->setKeyMode( false );

    const unsigned int maxFPSTime = 1000000 / maxFPS;
    long long beforeTime, deltaTime, waitTime, currentFPSTime, currentTime;

    currentFPSTime = maxFPSTime;
    beforeTime = get_time_in_micro_seconds( );
    while( this->getKeyPress( keyCode ), loopAction( keyCode, ( 1000000 / currentFPSTime ) ) )
    {
        deltaTime = get_time_in_micro_seconds( ) - beforeTime;
        waitTime = maxFPSTime - deltaTime;
        if( waitTime > 0 ) usleep( waitTime );
        currentTime = get_time_in_micro_seconds( );
        currentFPSTime = currentTime - beforeTime;
        beforeTime = currentTime;
    };


};


// TerminalUtils::Draw
TerminalUtils::Draw::Draw( TerminalUtils& term ) : term( term ){ };
TerminalUtils::Draw::~Draw( ){ };

//
unique_ptr<TerminalUtils::Draw> TerminalUtils::Draw::instance;
TerminalUtils::Draw & TerminalUtils::Draw::get( TerminalUtils *term )
{
    if( !( instance.get( ) ) )instance = unique_ptr<Draw>( new Draw( *term ) );
    return *( instance.get( ) );
};

//
void TerminalUtils::Draw::fill(
    const unsigned short line,
    const unsigned short column,
    const unsigned short width,
    const unsigned short height,
    const char c )
{
    string strLine( width, c );

    for( unsigned short counter = 0; counter < height; ++counter )
    {
        term.setCursorPosition( line + counter, column );
        cout << strLine;
    }

};

//
void TerminalUtils::Draw::box(
    const unsigned short line,
    const unsigned short column,
    const unsigned short width,
    const unsigned short height,
    const bool useLinesChars )
{
    char up_down = '-',
        left_right = '|',
        corner = '+';
    if( !useLinesChars )
        up_down = left_right = corner = ' ';
    if( width < 3 || height < 3 )return;

    string lineUpDown( width - 2, up_down );

    term.setCursorPosition( line, column );
    cout << corner << lineUpDown << corner;
    term.moveCursor( TerminalUtils::DOWN, 1 );
    term.moveCursor( TerminalUtils::LEFT, width );

    for( unsigned short counter = 2; counter < height; ++counter )
    {
        cout << left_right;
        term.moveCursor( TerminalUtils::RIGHT, width - 2 );
        cout << left_right;
        term.moveCursor( TerminalUtils::DOWN, 1 );
        term.moveCursor( TerminalUtils::LEFT, width );
    }

    cout << corner << lineUpDown << corner;

};


// TerminalUtils::Color
TerminalUtils::Color::Color( ){ };
TerminalUtils::Color::~Color( ){ };

//
unique_ptr<TerminalUtils::Color> TerminalUtils::Color::instance;
TerminalUtils::Color & TerminalUtils::Color::get( )
{
    if( !( instance.get( ) ) )instance = unique_ptr<Color>( new Color );
    return *( instance.get( ) );
};

//
void TerminalUtils::Color::setColorFG( const unsigned short color )
{
    cout << "\e[38;5;" << color << "m";
}

//
void TerminalUtils::Color::setColorBG( const unsigned short color )
{
    cout << "\e[48;5;" << color << "m";
}
unsigned short const TerminalUtils::Color::rgb24To8bits(
    const unsigned short red,
    const unsigned short green,
    const unsigned short blue
    )
{
    return (
        ( red * 6 / 256 ) * 36 +
        ( green * 6 / 256 ) * 6 +
        ( blue * 6 / 256 )
        ) + 16;
}

//
unsigned short const TerminalUtils::Color::rgbColor8bits(
    const unsigned short red,
    const unsigned short green,
    const unsigned short blue
    )
{
    return red * 36 + green * 6 + blue + 16;
};

//