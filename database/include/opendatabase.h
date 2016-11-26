/// @file 
/// @brief Файл содержит объявление классов для подключения к базе данных.

#pragma once

namespace sqlite
{
/// @brief Описание класса для подключения к БД
///
class Database : boost::noncopyable
{
public:
    /// @brief Осуществляет попытку открыть соединение к указанной БД
	///
	/// @param[in] path Путь к БД
	/// @param[in] readonly Флаг только на чтение
    Database( const boost::filesystem::path& path, const bool readonly );
	/// @brief Деструктор
	///
    ~Database() throw();
public:
	/// @brief Выполняет запрос к БД
	///
	/// @param[in] queries Запрос к БД
	/// @return Возвращает количество записей которы были модифицированы/добавлены.
    int Exec(const std::wstring& queries) const;
public:
	public:
	/// @brief Возвращает Хендел на подключение к БД
	///
	sqlite3* GetSqlite( void ) const throw();	
	/// @brief Возвращает описание ошибки
	///
	std::string GetErrMessage( void ) const throw();
	/// @brief Возвращает путь к БД
	///
    const boost::filesystem::path& GetPath( void ) const throw();
private:
	///< Хендел для подключения к БД
    sqlite3* sqlite_;   
	///< путь к базе данных
    const boost::filesystem::path path_;
};
}  
