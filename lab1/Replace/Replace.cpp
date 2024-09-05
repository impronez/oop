#include "stdafx.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	 
	std::string result;
	while (pos < subject.length())
	{
		// Находим позицию искомой строки, начиная с pos
		size_t foundPos = subject.find(searchString, pos);

		// Если foundPos не определена (позиция отсутствует),
		// в результируюущую строку добавляем искомую строку, начиная с pos, и выходим из цикла
		if (foundPos == std::string::npos)
		{
			result.append(subject, pos, subject.length() - pos);
			break;
		}

		// В результирующую строку записываем текст из диапазона [pos,foundPos) и добавляем replacementString
		result.append(subject, pos, foundPos - pos);
		result.append(replacementString);

		// Изменяем позицию на длину searchString
		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyWithReplacement(std::istream &input, std::ostream &output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count.\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>.\n";
		return 1;
	}

	std::ifstream inputFile;
	inputFile.open(argv[1]);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open '" << argv[1] << "' for reading.\n";
		return 1;
	}

	std::ofstream outputFile;
	outputFile.open(argv[2]);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open '" << argv[2] << "' for writing.\n";
		return 1;
	}

	std::string searchString = argv[3];
	std::string replacementString = argv[4];

	CopyWithReplacement(inputFile, outputFile, searchString, replacementString);
	
	outputFile.flush();

	return 0;
}
