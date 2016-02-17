#pragma once
#include <vector>
#include <string>
void load_obj(std::string fileName, std::vector<float>& vertice_pos,
	std::vector<float>& texture_pos,
	std::vector<float>& normal_pos,
	std::vector<unsigned int>& indices);