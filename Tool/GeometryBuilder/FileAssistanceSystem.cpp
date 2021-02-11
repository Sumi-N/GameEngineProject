#include "FileAssistanceSystem.h"
#include <Logging/DebugLog.h>

FileAssistanceSystem::FileAssistanceSystem(){ }

FileAssistanceSystem::~FileAssistanceSystem(){ }

bool FileAssistanceSystem::GetInputFiles()
{
	input_files.clear();

	for (const auto& entry : std::filesystem::directory_iterator(input_dir))
	{
		input_files.push_back(entry.path().filename());
	}

	if (input_files.size() == 0)
	{
		return false;
	}

	return true;
}

bool FileAssistanceSystem::GetOutputPaths()
{
	output_path.clear();

	for (auto filename : input_files)
	{
		std::filesystem::path stem = filename.stem();
		stem += ".tmd";

		std::filesystem::path fullpath = output_dir.string() + stem.string();

		output_path.push_back(fullpath);
	}

	// Check if there is a duplicate
	std::vector<std::filesystem::path>::iterator it = std::unique(output_path.begin(), output_path.end());
	if (!(it == output_path.end()))
	{
		DEBUG_PRINT("Duplicated file name have found druing geometry building process");
		return false;
	}

	return true;
}