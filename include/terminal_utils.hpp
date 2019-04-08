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
 * File:   TerminalUtils.hpp
 * Author: Maxwell Aguiar Silva <maxwellaguiarsilva@gmail.com>
 *
 * Created on 29 de Janeiro de 2019, 17:49
 */

#pragma once

#include <bits/unique_ptr.h>
#include <functional>
#include <chrono>

using std::unique_ptr;

namespace cpp_utils
{
    namespace terminal
    {

        // Modifica e controla o terminal (console).
        class TerminalUtils
        {
        private:
            static std::unique_ptr<TerminalUtils> instance;
            TerminalUtils( );
            TerminalUtils( const TerminalUtils& orig ) = delete;
        public:

            virtual ~TerminalUtils( );
            static TerminalUtils& get( );

            // Direção para mover o cursor na tela.
            enum DIRECTION
            {
                UP = 'A', DOWN, RIGHT, LEFT
            } ;

            // Modificadores do terminal.
            const char * const CLRSCR = "\033[2J\033[3J\033[0;0f",
                * const SHOW_CURSOR = "\e[?25h",
                * const HIDE_CURSOR = "\e[?25l",
                * const SAVE_CURSOR_POSITION = "\033[s",
                * const LOAD_CURSOR_POSITION = "\033[u",
                * const ERASE_LINE = "\033[K",

                // Modificadores de texto.
                * const BOLD_ON = "\033[1m", * const BOLD_OFF = "\033[21m",
                * const DARK_ON = "\033[2m", * const DARK_OFF = "\033[22m",
                * const ITALIC_ON = "\033[3m", * const ITALIC_OFF = "\033[23m",
                * const UNDERLINE_ON = "\033[4m", * const UNDERLINE_OFF = "\033[24m",
                * const BLINK_ON = "\033[5m", * const BLINK_OFF = "\033[25m",
                * const SWAPCOLOR_ON = "\033[7m", * const SWAPCOLOR_OFF = "\033[27m",

                // Cores do texto no terminal.
                * const COLOR_RESET = "\033[0m",
                * const FGCOLOR_BLACK = "\033[30m", * const BGCOLOR_BLACK = "\033[40m",
                * const FGCOLOR_RED = "\033[31m", * const BGCOLOR_RED = "\033[41m",
                * const FGCOLOR_GREEN = "\033[32m", * const BGCOLOR_GREEN = "\033[42m",
                * const FGCOLOR_YELLOW = "\033[33m", * const BGCOLOR_YELLOW = "\033[43m",
                * const FGCOLOR_BLUE = "\033[34m", * const BGCOLOR_BLUE = "\033[44m",
                * const FGCOLOR_MAGENTA = "\033[35m", * const BGCOLOR_MAGENTA = "\033[45m",
                * const FGCOLOR_CYAN = "\033[36m", * const BGCOLOR_CYAN = "\033[46m",
                * const FGCOLOR_WHITE = "\033[37m", * const BGCOLOR_WHITE = "\033[47m";

            // Move cursor de digitação do terminal.
            // @param DIRECTION = direção (UP, DOWN, RIGHT, LEFT).
            // @param num = número de posições a mover o cursor.
            void moveCursor( const DIRECTION &d, const int num );
            // Move cursor de digitação do terminal.
            // @param line = Número da linha.
            // @param column = Número da coluna.
            void setCursorPosition( const unsigned int line, const unsigned int column );

            // Controla e faz uso das entradas de dados do teclado no terminal .
            class Keyboard
            {
            private:
                Keyboard( const Keyboard& orig ) = delete;
                static std::unique_ptr<Keyboard> instance;
                // Singleton de uso exclusivo da classe TerminalUtils.
                static Keyboard& get( TerminalUtils* term );
                friend TerminalUtils;
            protected:
                Keyboard( );
            public:
                virtual ~Keyboard( ); // Necessário para rodar os destrutures das classes filhas.

                // Código das teclas especiais no terminal.
                // Precisa ser static para ser usado com "switch case".

                static const unsigned long TK_ESC = 0x1B,
                    TK_UP        = 0x1B5B41,
                    TK_DOWN      = 0x1B5B42,
                    TK_RIGHT     = 0x1B5B43,
                    TK_LEFT      = 0x1B5B44,
                    TK_F1        = 0x1B4F50,
                    TK_F2        = 0x1B4F51,
                    TK_F3        = 0x1B4F52,
                    TK_F4        = 0x1B4F53,
                    TK_F5        = 0x1B5B31357E,
                    TK_F6        = 0x1B5B31377E,
                    TK_F7        = 0x1B5B31387E,
                    TK_F8        = 0x1B5B31397E,
                    TK_F9        = 0x1B5B32307E,
                    TK_F10       = 0x1B5B32317E,
                    TK_F11       = 0x1B5B32337E,
                    TK_F12       = 0x1B5B32347E,
                    TK_BACKSPACE = 0x7F,
                    TK_ENTER     = 0xA,
                    TK_TAB       = 0x9,
                    TK_INSERT    = 0x1B5B327E,
                    TK_DELETE    = 0x1B5B337E,
                    TK_PGUP      = 0x1B5B357E,
                    TK_PGDOWN    = 0x1B5B367E,
                    TK_END       = 0x1B5B46,
                    TK_HOME      = 0x1B5B48;

                // Define o terminal para ler entradas somente depois que usuário apertar o Enter.
                virtual void setLineMode( ) = 0;

                // Define o terminal para ler entradas imediatamente ao pressionadar a tecla.
                virtual void setKeyMode( bool wait = true, bool echo = false ) = 0;

                // Faz a leitura de uma tecla quando no KeyMode.
                virtual bool getKeyPress( unsigned long &keyCode ) = 0;

                // Captura teclas em um loop até que a lambda retorne falso, aguardando que uma tecla seja pressionada.
                void loopKeyPress( std::function< bool( const unsigned long ) > loopAction );

                // Captura teclas em um loop até que a lambda retorne falso, sem aguardar que uma tecla seja pressionada e com um FPS máximo definido.
                void loopKeyPress( std::function< bool( const unsigned long, const unsigned int ) > loopAction, unsigned int maxFPS = 60 );


            } &keyboard = Keyboard::get( this );

            // Formas úteis usando ASCII_ART no terminal.
            class Draw
            {
            private:
                static std::unique_ptr<Draw> instance;
                Draw( TerminalUtils& term );
                Draw( ) = delete;
                Draw( const Draw& orig ) = delete;
                TerminalUtils &term;
                // Singleton de uso exclusivo da classe TerminalUtils.
                static Draw& get( TerminalUtils* term );
                friend TerminalUtils;
            public:
                virtual ~Draw( );

                // Preenche uma área do terminal com a cor de fundo atual.
                void fill(
                    const unsigned short line,
                    const unsigned short column,
                    const unsigned short width,
                    const unsigned short height,
                    const char c = ' '
                    );

                // Desenha um quadro na tela com a cor de fundo atual.
                void box(
                    const unsigned short line,
                    const unsigned short column,
                    const unsigned short width,
                    const unsigned short height,
                    const bool useLinesChars = false
                    );

            } &draw = Draw::get( this );


            // Utilizar as cores disponíveis no terminal.
            class Color
            {
            private:
                Color( );
                Color( const Color& orig ) = delete;
                static std::unique_ptr<Color> instance;
                static Color& get( );
                friend TerminalUtils;
            public:
                virtual ~Color( );
                // Define a cor da fonte no terminal.
                void setColorFG( const unsigned short color );
                // Define a cor de fundo no terminal.
                void setColorBG( const unsigned short color );

                // Converte parâmetros RGB de 0 a 255 para uma cor de 8bits.
                // @param red Vermelho (0..255).
                // @param green Verde (0..255).
                // @param blue Azul (0..255).
                // @return Uma cor de 8bits.
                unsigned short const rgb24To8bits(
                    const unsigned short red,
                    const unsigned short green,
                    const unsigned short blue
                    );

                // Converte parâmetros RGB de 0 a 5 para uma cor de 8bits.
                // @param red Vermelho (0..5).
                // @param green Verde (0..5).
                // @param blue Azul (0..5).
                // @return Uma cor de 8bits.
                unsigned short const rgbColor8bits(
                    const unsigned short red,
                    const unsigned short green,
                    const unsigned short blue
                    );
            } &color = Color::get( );

        } ;

    } ;

};
