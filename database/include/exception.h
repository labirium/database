/// @file 
/// @brief Файл содержит объявление классов для формирования исключений.

#pragma once

namespace sqlite
{
/// @brief Исключение бросаемое модулем sqlite
///
class Exception : public std::runtime_error
{
public:
    /// @brief Конструктор
	///
	/// @param[in] message Сообщение об ошибке
    explicit Exception(const std::string& message );
	/// @brief Деструктор
	///
	virtual ~Exception();
};
} 

