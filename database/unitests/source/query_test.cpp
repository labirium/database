/// @file 
/// @brief Тесты для задания параметров выборки БД

#include <unitests/include/precompiled.h>

namespace
{
// Тестовое имя таблицы
const wchar_t* const TEST_NAME_TABLE = L"TEST_TABLE";
// путь к БД
const boost::filesystem::path& PATH_DB = boost::filesystem::temp_directory_path() / L"example.db";
}

namespace
{
class QueryF: public ::testing::Test 
{ 
public: 
	/// @brief Конструктор
	///
	QueryF( void ) : database_( std::make_shared<sqlite::Database>( PATH_DB, false ) )
	{
		///< Описание полей таблицы
		sqlite::FieldDeclarationTable fieldDeclarationTable;
		//Добавляем поле id и выставляем как основной ключ таблицы
		fieldDeclarationTable.AddField( L"id", sqlite::enums::FieldType::Integer, true );
		//Добавляем строковое поле в таблицу
		fieldDeclarationTable.AddField( L"value", sqlite::enums::FieldType::Text );

		sqlite::Table ff( TEST_NAME_TABLE, fieldDeclarationTable );
		//Создаем описание таблицы
		table_ = std::make_shared<sqlite::Table>( TEST_NAME_TABLE, fieldDeclarationTable );
	};
    /// @brief Деструктор
    ///
	~QueryF(){};
	/// @brief Код, который будет выполнен перед началом теста 
	///
	void SetUp( void ){};
	/// @brief Код, который будет выполнен сразу по завершении теста
	///
	void TearDown( void ){};
protected:
	/// @brief Возвращает таблицу
	///
	sqlite::TablePtr GetTable( void ) const
	{
		return table_;
	}
	/// @brief Возвращает описание подулючение к БД
	///
	sqlite::DatabasePtr GetDatabase( void ) const
	{
		return database_;
	}

private:
	///< Подключение к БД
	const sqlite::DatabasePtr database_;
	///< Описание таблицы
	sqlite::TablePtr table_;

};
}

//=====================================================================================================================
// Тест создания
TEST_F(QueryF, Create ) 
{
	EXPECT_NO_THROW( GetTable()->GetQueryWhereRecordSet() );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(QueryF, GetData ) 
{
	auto query = GetTable()->GetQueryWhereRecordSet();

	//Создаем транзакцию
	sqlite::Transaction transaktion( GetDatabase() );
	GetTable()->Drop( transaktion );
	GetTable()->Create( transaktion );

	EXPECT_NO_THROW( query( transaktion ) );
	EXPECT_NE( query( transaktion ), nullptr );
	EXPECT_NE( query( transaktion ), query( transaktion ) );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(QueryF, GetDataThrow ) 
{
	auto query = GetTable()->GetQueryWhereRecordSet();

	//Создаем транзакцию
	sqlite::Transaction transaktion( GetDatabase() );
	GetTable()->Drop( transaktion );

	EXPECT_THROW( query( transaktion ), sqlite::Exception );
}
//=====================================================================================================================
// Тест WHERE
TEST_F(QueryF, Where ) 
{
	auto query = GetTable()->GetQueryWhereRecordSet();
	EXPECT_NO_THROW( query.Where( L"id > 0" ) );
}
//=====================================================================================================================
