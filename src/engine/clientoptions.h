/* Conquer Space
* Copyright (C) 2021 Conquer Space
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
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once

#include <hjson.h>
#include <istream>
#include <fstream>
#include <string>

namespace conquerspace {
namespace client {
class ClientOptions {
 public:
     void LoadOptions(std::istream& stream);
     void WriteOptions(std::ostream& stream);

     void LoadDefaultOptions();

     Hjson::Value& GetOptions() { return options; }

     Hjson::Value GetDefaultOptions();

     std::string GetDefaultLocation() { return "settings.hjson"; }

 private:
     Hjson::Value options;
};
}  // namespace client
}  // namespace conquerspace