/// @file 
/// @brief Файл содержит объявление классов для осуществления операций над таблицей базы данных.

#pragma once

namespace sqlite
{
/// @brief Описание операций над таблицей в БД
///
class Table
{
public:
	/// @brief Конструктор
	///
	/// @param[in] name Имя таблицы
	/// @param[in] fieldDeclarationTable описание полей таблицы
	Table( const std::wstring& name, const sqlite::FieldDeclarationTable& fieldDeclarationTable  );
	/// @brief Деструктор
	///
	virtual ~Table();
public:
	/// @brief Создание таблицы по заданным полям
	///
	/// @param[in] transaktion Описание транзакции
	void Create( const Transaction& transaktion ) const;
	/// @brief Удаление таблицы
	///
	/// @param[in] transaktion Описание транзакции
	void Drop( const Transaction& transaktion ) const;
	/// @brief Осуществляет вставку новой записи
	///
	/// @param[in] transaktion Описание транзакции
	/// @param[in] valueTable Описание переменной
	void Insert( const sqlite::Transaction& transaktion, const sqlite::ValueTable& valueTable ) const;
	/// @brief Осуществляет удаление записи
	///
	/// @param[in] transaktion Описание транзакции
	/// @param[in] valueTable Описание переменной
	void Delete(const sqlite::Transaction& transaktion, const sqlite::ValueTable& valueTable) const;
	/// @brief Возвращает запрос для выборки по таблице
	///
	Query GetQueryWhereRecordSet( void ) const;
public:
	/// @brief Возвращает имя таблицы
	///
	const std::wstring& GetName( void ) const; 
	///@brief Вовращает описание полей
	///
	const FieldDeclarationTable& GetFieldDeclarationTable( void ) const;
	///@brief Вовращает указатель на описание полей таблицы
	///
	const FieldDeclarationTablePtr GetFieldDeclarationTablePtr( void ) const;
private:
	///< Описание полей таблицы
	const sqlite::FieldDeclarationTablePtr fieldDeclarationTable_;	
	///< Имя таблицы
	const std::wstring name_;
};
}

