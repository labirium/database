/// @file 
/// @brief Файл содержит объявление классов для вставки полей в таблицу

#pragma once

namespace sqlite
{
/// @brief Описание класса для вставки записи в таблицу
///
class InsertValue
{
public:
	/// @brief Конструктор
	///
	/// @param[in] table Описание таблицы
	explicit InsertValue( const sqlite::TablePtr& table );
	/// @brief Конструктор
	///
	/// @param[in] table Описание таблицы
	explicit InsertValue( const sqlite::Table& table );
	/// @brief Деструктор
	///
	~InsertValue();
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
