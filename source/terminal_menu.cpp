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
 * File:   Menu.cpp
 * Author: Maxwell Aguiar Silva <maxwellaguiarsilva@gmail.com>
 *
 * Created on 3 de Fevereiro de 2019, 21:54
 */

#include<terminal_menu.hpp>
#include<iostream>

using std::cout;
using std::string;
using std::function;
using std::vector;
using namespace cpp_utils::terminal;

// Menu.cpp
Menu::Menu(
    const vector<Item*> &list,
    const unsigned short left,
    const unsigned short top,
    const char * const textColor,
    const char * const backColor
    ) : list( list ), left( left ), top( top ), textColor( textColor ), backColor( backColor )
{
    unsigned short textLength;
    width = 0;
    height = 0;
    for( Item* item : list )
    {
        textLength = item->getText( ).length( );
        width = ( width > textLength ) ? width : textLength;
    }
    width += 2;
    std::
        cout << width;
    height = list.size( ) + 2;

};
Menu::~Menu( ){ };

// Inicia o menu no terminal em modo texto.
void Menu::init( )
{

    using cpp_utils::terminal::TerminalUtils;
    using std::cout;
    using std::endl;
    using std::vector;

    TerminalUtils &terminal = TerminalUtils::get( );
    TerminalUtils::Keyboard &keyboard = terminal.keyboard;
    auto iterator = list.begin( );
    Menu::Item *firstItem = iterator[0], *lastItem = iterator[list.size( ) - 1];

    auto renderView = [&]( )
    {
        // Desenha o menu no termianl.
        terminal.setCursorPosition( top, left );
        cout << backColor << textColor;
        terminal.draw.fill( top, left, width, height );
        terminal.setCursorPosition( top + 1, left + 1 );
        unsigned short counter = 1;
        for( Item* item : list )
        {
            terminal.setCursorPosition( top + counter++, left + 1 );
            if( item == *iterator )
                cout << terminal.SWAPCOLOR_ON;
            cout << item->getText( );
            cout << terminal.SWAPCOLOR_OFF;
        }
    };

    renderView( );

    keyboard.loopKeyPress( [&]( unsigned long keyCode )
    {
        switch( keyCode )
        {
            case keyboard.TK_UP:
                if( *iterator == firstItem )
                    iterator += list.size( ) - 1;
                else
                    --iterator;
                break;
            case keyboard.TK_DOWN:
                if( *iterator == lastItem )
                    iterator -= list.size( ) - 1;
                else
                    ++iterator;
                break;
            case keyboard.TK_ENTER:
                ( *iterator )->action( *( *iterator ) );
                keyboard.setKeyMode( true, false );
                break;
            default:
                break;
        };

        renderView( );

        return keyCode != keyboard.TK_ESC;

    } );

};
void Menu::setColors( const char * const textColor, const char * const backColor )
{
    this->textColor = textColor;
    this->backColor = backColor;
};

// Cria um item de menu com um texto e uma ação.
Menu::Item::Item(
    const string text,
    void *identifier,
    function< void(const Item &item ) > action
    ) : text( text ), action( action ), identifier( identifier ){ };
Menu::Item::~Item( ){ };

// Retorna o texto do item do menu.
const string& Menu::Item::getText( )const
{
    return text;
};

// Retorna o objeto definido para identificar o item de menu.
void* cpp_utils::terminal::Menu::Item::getIdentifier( ) const
{
    return identifier;
};
