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
 * File:   CppUtils.cpp
 * Author: Maxwell Aguiar Silva <maxwellaguiarsilva@gmail.com>
 *
 * Created on 29 de Março de 2019, 11:37
 */

#include <cpp_utils.hpp>
#include <chrono>

using namespace cpp_utils::datetime_utils;

//
unsigned long long get_time_in_micro_seconds( )
{
    return std::chrono::time_point_cast< std::chrono::microseconds > (
        std::chrono::high_resolution_clock::now( )
        ).time_since_epoch( ).count( );
}