#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <array>
#include <cstring>
#include <SDL.h>
#include <algorithm>
#include "fragment.h"

struct Face {
    std::array<int, 3> vertexIndices;
    std::array<int, 3> normalIndices;
};

bool loadOBJ(const std::string& path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec3>& out_normals, std::vector<Face>& out_faces)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cout << "No se pudo abrir el archivo: " << path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string lineHeader;
        iss >> lineHeader;

        if (lineHeader == "v")
        {
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            out_vertices.push_back(vertex);
        }
        else if (lineHeader == "vn")
        {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            out_normals.push_back(normal);
        }
        else if (lineHeader == "f")
        {
            Face face;
            for (int i = 0; i < 3; ++i)
            {
                std::string faceData;
                iss >> faceData;

                std::replace(faceData.begin(), faceData.end(), '/', ' ');

                std::istringstream faceDataIss(faceData);
                int temp; // for discarding texture indices
                faceDataIss >> face.vertexIndices[i] >> temp >> face.normalIndices[i];

                // obj indices are 1-based, so convert to 0-based
                face.vertexIndices[i]--;
                face.normalIndices[i]--;
            }
            out_faces.push_back(face);
        }
    }

    return true;
}

std::vector<Vertex> setupVertexArray(const std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, const std::vector<Face>& faces)
{
    std::vector<Vertex> vertexArray;
    
    // For each face
    for (const auto& face : faces)
    {
        // For each vertex in the face
        for (int i = 0; i < 3; ++i)
        {
            // Get the vertex position from the input arrays using the indices from the face
            glm::vec3 vertexPosition = vertices[face.vertexIndices[i]];
            glm::vec3 vertexNormal = normals[face.normalIndices[i]];

            // Add the vertex position and normal to the vertex array
            vertexArray.push_back(Vertex{vertexPosition, vertexNormal});
        }

    }

    return vertexArray;
}