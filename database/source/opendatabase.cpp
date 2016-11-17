/// @file 
/// @brief Файл содержит реализацию классов для подключения к базе данных.

#include <database/include/precompiled.h>

namespace
{
/// @brief Осуществляет проверку выполнение операции
///
/// @param[in] sqlite Описание подклбчения к БД
/// @param[in] sqliteRet Описание кода выполенения операции
/// @throw sqlite::Exception Исключение при обнаружении ошибки
void Check( sqlite3* const sqlite, const int sqliteRet )
{
    if( SQLITE_OK != sqliteRet )
    {
        throw sqlite::Exception( sqlite3_errmsg(sqlite) );
    }
}
}

namespace sqlite
{
//=====================================================================================================================
Database::Database( const boost::filesystem::path& path, const bool readonly ) : sqlite_( nullptr ), path_(path)
{
	//проверка входных данных
	if( path.empty() ){
		throw Exception( "Invalid's path: " + path.string() );
	}

	//Открываем БД
	const int flags = readonly ? SQLITE_OPEN_READONLY : SQLITE_OPEN_READWRITE;
	const auto& ret = sqlite3_open_v2( culture::w2utf8( path ).c_str(), &sqlite_, flags | SQLITE_OPEN_CREATE, nullptr );
    if (SQLITE_OK != ret)
    {
		//запоминаем описание ошибки
        const auto& strerr = GetErrMessage();
		// закрываем подключение
        sqlite3_close( sqlite_ );
		// создаем исключение
		throw Exception( strerr );
    }
}
//=====================================================================================================================
Database::~Database() throw()
{
    const auto ret = sqlite3_close( sqlite_ );
    assert(SQLITE_OK == ret && sqlite3_errmsg( sqlite_ ) );
}
//=====================================================================================================================
const boost::filesystem::path& Database::GetPath( void ) const
{
    return path_;
}
//=====================================================================================================================
int Database::Exec( const std::wstring& queries ) const
{
	const auto ret = sqlite3_exec( sqlite_, culture::w2utf8( queries ).c_str(), NULL, NULL, NULL);
    Check( sqlite_, ret );

    return sqlite3_changes( sqlite_ );
}
//=====================================================================================================================
sqlite3* Database::GetSqlite( void ) const throw()
{
	return sqlite_;
}
//=====================================================================================================================
std::string Database::GetErrMessage( void ) const throw()
{
     return sqlite3_errmsg( sqlite_ );
}
//=====================================================================================================================
}
