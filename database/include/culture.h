/// @file 
/// @brief Файл содержит реализацию преобразоваие строки в различные форматы/кодировки

#pragma once

/// Конвертирование строк
namespace culture
{
/// @brief Преобразует строку в utf8
///
/// @param[in] source путь к файлу
inline std::string w2utf8( const boost::filesystem::path& source )
{
	return boost::locale::conv::utf_to_utf<char>( source.wstring() );
}
/// @brief Преобразует строку в utf8
///
/// @param[in] source строка на преобразование
inline std::string w2utf8( const std::wstring& source )
{
	return boost::locale::conv::utf_to_utf<char>( source );
}
/// @brief Преобразует utf8 в строку
///
/// @param[in] source строка на преобразование
inline std::wstring utf2w( const std::string& source )
{
	return boost::locale::conv::utf_to_utf<wchar_t>( source );
}
}