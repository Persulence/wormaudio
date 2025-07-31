// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "serialization.hpp"

#include "cereal/archives/json.hpp"

#include "resource/register_element_poly.hpp"

namespace resource
{
    void writeStructure(const Handle<Project> &project, const std::filesystem::path &filePath)
    {
        // if (!filePath.ends_with(FILE_EXTENSION))
        // {
        //     filePath.append(FILE_EXTENSION);
        // }

        std::fstream ostream{filePath, std::ios::out};
        // std::stringstream ss;
        
        {
            cereal::JSONOutputArchive archive{ostream};
            archive(*project);
        }

        // std::cout << ss.str();
        // ostream << ss.rdbuf();
        ostream.close();
    }

    void readStructure(const Handle<Project> &project, const std::filesystem::path &filePath)
    {
        {
            std::fstream istream{filePath, std::ios::in};

            if (!istream.good())
            {
                throw IOException{std::format("File invalid: {}", filePath.string())};
            }

            {
                cereal::JSONInputArchive archive{istream};
                archive(*project);
            }

            istream.close();
        }
    }
}


