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
 * File:   Menu.hpp
 * Author: Maxwell Aguiar Silva <maxwellaguiarsilva@gmail.com>
 *
 * Created on 3 de Fevereiro de 2019, 21:54
 */

#pragma once

#include<vector>
#include<string>
#include<functional>
#include<terminal_utils.hpp>

namespace cpp_utils
{
    namespace terminal
    {

        // Menu.hpp
        using std::string;
        using std::function;
        using std::vector;

        // Menu interativo em modo texto no terminal (usando TK_UP, TK_DOWN, TK_ENTER).
        class Menu
        {
        public:
            // Contém a descrição e a ação de um item do menu.
            class Item
            {
            private:
                Item( const Item& orig ) = delete;
                Item( ) = delete;
                const string text;
                function< void(const Item &item ) > action;
                void *identifier;
                friend Menu;
            public:
                Item( const string text, void *identifier, function< void(const Item &item ) > action );
                virtual ~Item( );
                const string& getText( )const;
                void* getIdentifier( )const;
            } ;
        private:
            Menu( const Menu& orig ) = delete;
            Menu( ) = delete;
            unsigned short left, top, width, height;
            const char *textColor, *backColor;
            vector<Item*> list;
        public:
            Menu(
                const vector<Item*> &list,
                const unsigned short left = 1,
                const unsigned short top = 1,
                const char * const textColor = cpp_utils::terminal::TerminalUtils::get( ).FGCOLOR_BLACK,
                const char * const backColor = cpp_utils::terminal::TerminalUtils::get( ).BGCOLOR_WHITE
                );
            virtual ~Menu( );
            // Inicia o menu.
            void init( );
            void setColors( const char * const textColor, const char * const backColor );

        } ;

    };

};