#pragma once

#include <string>
#include <iostream>
#include <filesystem>

class FileAssistanceSystem
{
public:
	FileAssistanceSystem();
	~FileAssistanceSystem();

	bool GetInputFiles();
	bool GetOutputPaths();

public:
	std::filesystem::path input_dir;
	std::filesystem::path output_dir;

	// All files in the input directory
	std::vector<std::filesystem::path> input_files;
	// The full path of all files in the output directory
	std::vector<std::filesystem::path> output_path;
};

