#pragma once

#include "Define.h"
#include "Result.h"
#include "Array.h"

namespace Tempest
{
	typedef std::string String;

	class File
	{
	public:

		enum class Format
		{
			BinaryWrite,
			BinaryRead,
			Default,
		};

		File() = delete;
		File(String i_filepath, Format i_format = Format::Default) :filepath(i_filepath), format(i_format) {};

		String GetExtensionName() const {return filepath.extension().string(); }
		String GetPathName()      const {return filepath.parent_path().string(); }
		String GetFileName()      const {return filepath.filename().string(); }

		Result Open();
		void   Close();
		size_t GetFileSize();
		Result Write(void*, size_t);
		Result Read(void*, size_t);

		static Array<String> GetAllFilePathsBelowTheDirectory(String);
		static String ReplaceExtension(String, String);
		static String GetExtensionName(String);
		static String GetPathName     (String);
		static String GetFileName     (String);

	private:
		std::filesystem::path filepath;
		Format format;

		std::ifstream read_stream;
		std::ofstream write_stream;
	};

	inline Result File::Open()
	{
		if (format == Format::BinaryRead)
		{
			read_stream.open(filepath, std::ifstream::in | std::ifstream::binary);

			if (!read_stream.is_open())
			{
				return ResultValue::Failure;
			}

			return ResultValue::Success;
		}
		else if (format == Format::BinaryWrite)
		{
			//Create the file if the directory filepath doesn't exist
			if (!std::filesystem::exists(filepath.parent_path()))
			{
				std::filesystem::create_directories(filepath.parent_path());
			}

			write_stream.open(filepath, std::ifstream::out | std::ifstream::binary);

			if (!write_stream.is_open())
			{
				return ResultValue::Failure;
			}

			return ResultValue::Success;
		}
		else
		{
			return ResultValue::Failure;
		}
	}

	inline void File::Close()
	{
		if (format == Format::BinaryRead)
		{
			read_stream.close();
		}
		else if (format == Format::BinaryWrite)
		{
			write_stream.close();
		}
	}

	inline size_t File::GetFileSize()
	{
		if (format == Format::BinaryRead)
		{
			read_stream.seekg(0, std::ios::end);
			size_t end_pos = read_stream.tellg();
			read_stream.seekg(0, std::ios::beg);
			return end_pos;
		}
		else if (format == Format::BinaryWrite)
		{
			return write_stream.tellp();
		}

		return 0;
	}

	inline Result File::Write(void* i_ptr, size_t i_size)
	{
		if (format == Format::BinaryWrite)
		{
			if (write_stream.is_open())
			{
				write_stream.write(reinterpret_cast<char*>(i_ptr), i_size);

				return ResultValue::Success;
			}
		}

		return ResultValue::Failure;
	}

	inline Result File::Read(void* o_ptr, size_t i_size)
	{
		if (format == Format::BinaryRead)
		{
			if (read_stream.is_open())
			{
				read_stream.read(reinterpret_cast<char*>(o_ptr), i_size);

				return ResultValue::Success;
			}
		}

		return ResultValue::Failure;
	}

	inline Array<String> File::GetAllFilePathsBelowTheDirectory(String i_pathname)
	{
		Array<String> filenames;
		for (const auto& entry : std::filesystem::recursive_directory_iterator(i_pathname))
		{
			if (std::filesystem::is_regular_file(entry))
			{

				String processed_path = entry.path().string().erase(0, i_pathname.length());

				filenames.PushBack(processed_path);
			}
		}

		return filenames;
	}

	inline String File::ReplaceExtension(String i_path, String i_extension)
	{
		return std::filesystem::path(i_path).replace_extension(std::filesystem::path(i_extension)).string();
	}

	inline String File::GetExtensionName(String i_path)
	{
		return std::filesystem::path(i_path).extension().string();
	}

	inline String File::GetPathName(String i_path)
	{
		return std::filesystem::path(i_path).parent_path().string();
	}

	inline String File::GetFileName(String i_path)
	{
		return std::filesystem::path(i_path).filename().string();
	}
}


