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
 * File:   FrameLoop.hpp
 * Author: Maxwell Aguiar Silva <maxwellaguiarsilva@gmail.com>
 *
 * Created on 29 de Março de 2019, 00:54
 */

#pragma once

#include<functional>

namespace cpp_utils
{

    using FrameLoopRoutine = std::function<bool(&FrameLoop )>;

    // Monitora e controla o FPS do jogo.
    class FrameLoop
    {
    public:
        FrameLoop( FrameLoopRoutine frameLoopRoutine, unsigned int fps = 60 );
        bool setFPS( unsigned int fps );
        unsigned int getFPS( );
        void setRoutine( FrameLoopRoutine routine );
        void start( );
        virtual ~FrameLoop( );
    private:
        FrameLoop( const FrameLoop& orig ) = delete;
        unsigned int framesPerSecond;
        FrameLoopRoutine routine;
    } ;

}