#pragma once

#include <fstream>

namespace etb {
	
	class File {
	public:

		File(const std::string& path);
		~File();

		std::string ReadLine();

		inline bool Eof() { return file.eof(); }
		void Close();

		static bool Exists(const std::string& path);
		static std::string ReadAll(const std::string& path);

	private:
		std::ifstream file;
	};

}