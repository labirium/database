/// @file 
/// @brief Файл содержит объявление классов для осуществления получения данных из выборки.

#pragma once

namespace sqlite
{

/// @brief Класс осуществляет получения данных из выборки.
///
class Stmt : boost::noncopyable
{
public:
	/// @brief Конструктор
	///
	/// @param[in] transaktion Транизакция в рамках которой осуществляется опеарация
	/// @param[in] fieldDeclarationTable Описание полей таблицы
	/// @param[in] query запрос к БД
	Stmt( const Transaction& transaktion, const FieldDeclarationTablePtr& fieldDeclarationTable, const std::wstring& query );
	/// @brief Деструктор
	///
	~Stmt() throw();
public:
	/// @brief Осуществляет движение по выборки
	///
	/// @return Возвращает запись поля.
	sqlite::ValueTablePtr Step( void );
	/// @brief Возвращает описание подключение к БД
	///
    sqlite::DatabasePtr GetDataBase( void ) const;
private:
	/// @brief Возвращает описание подключение к БД
	///
	sqlite3* GetSqlite( void ) const;
	/// @brief Возвращает хендел на сконструированный запрос к БД
	///
    sqlite3_stmt* Get( void ) const throw();
private:
	///< Описание подключения к БД
	const DatabasePtr dataBase_;
	///< Описание полей таблицы
    const FieldDeclarationTablePtr fieldDeclarationTable_;
	///< Запрос к БД
    sqlite3_stmt* stmt_;
};
} 
