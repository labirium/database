/// @file 
/// @brief Файл содержит объявление функторов для работы со строками

#pragma once

///Вспомогательные классы/шаблоны
namespace tools
{
/// @brief Функтор возвращает заданную строку каждый раз кроме первого обращения.
///
class FirstString
{
public:
	/// @brief Кнструктор
	/// 
	/// @param[in] data строка для возврата
	explicit FirstString( const std::wstring& data = L" ");
	/// @brief Деструктор
	///
	~FirstString();
public:
	/// @brief Операнд
	///
	std::wstring operator()( void ) const throw();
private:
	///< строка для возврата
	std::wstring data_;
	///< Флаг первой операции
	mutable bool bFirst_;
};
}
