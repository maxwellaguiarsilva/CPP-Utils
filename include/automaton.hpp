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
 * File:   automaton.hpp
 * Author: Maxwell Aguiar Silva <maxwellaguiarsilva@gmail.com>
 *
 * Created on 7 de Abril de 2019, 23:36
 */
#include <string>
#include <unordered_map>

#pragma once

namespace cpp_utils
{

    namespace automaton
    {

        using std::string;
        using std::vector;
        using std::unordered_map;

        // Simbolos de cada estado.
        class Simbol
        {
        public:
            Simbol( const string &name, State * const targetState );
            virtual ~Simbol( );
        private:
            Simbol( const Simbol& orig ) = delete;
            const string name;
            State * const targetState;
        } ;


        // Estado de um autômato.
        class State // IAMHERE
        {
        public:
            State( const string &name, bool accepted );
            virtual ~State( );
        private:
            State( const State& orig ) = delete;
            unordered_map<unsigned long, Simbol> simbols;
            bool accepted;
            const string name;
        } ;


        // Classe para controlar estados de acordo com a entrada de símbolos.
        class Automaton
        {
        public:
            Automaton( );
            virtual ~Automaton( );
        private:
            Automaton( const Automaton& orig ) = delete;
            vector<State*> states;
            State* initialState;
        } ;


    }

}