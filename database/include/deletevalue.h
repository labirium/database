/// @file 
/// @brief Файл содержит объявление классов для вставки полей в таблицу

#pragma once

namespace sqlite
{
/// @brief Описание класса для удалении записи в таблице
///
class DeleteValue
{
public:
	/// @brief Конструктор
	///
	/// @param[in] table Описание таблицы
	explicit DeleteValue(const sqlite::TablePtr& table);
	/// @brief Конструктор
	///
	/// @param[in] table Описание таблицы
	explicit DeleteValue(const sqlite::Table& table);
	/// @brief Деструктор
	///
	~DeleteValue();
public:
	/// @brief Регистрация записи на добавление в таблицу
	/// 
	/// @param[in] data Данные таблицы
	void Add( const sqlite::ValueTable& data );
	/// @brief Осуществляет втавку данных в таблицу
	///
	/// @param[in] transaction Описание транзакции в рамках которой осуществляется вставка
	void Exec( const sqlite::Transaction& transaction ) const;
protected:
	/// @brief Формирует команду для вставки в таблицу
	///
	std::wstring operator()( void ) const;
private:
	///< Список значений на вставку
	ValueTableList valueTableList_;
	///< Имя таблицы
	const std::wstring tableName_;
};
}
