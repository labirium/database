/// @file 
/// @brief Тесты для получения данных из таблицы

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
class ValueTableF: public ::testing::Test 
{ 
public: 
	/// @brief Конструктор
	///
	ValueTableF( void ) : database_( std::make_shared<sqlite::Database>( PATH_DB, false ) )
	{
		///< Описание полей таблицы
		sqlite::FieldDeclarationTable fieldDeclarationTable;
		//Добавляем поле id и выставляем как основной ключ таблицы
		fieldDeclarationTable.AddField( L"id", sqlite::enums::FieldType::Integer, true );
		//Добавляем строковое поле в таблицу
		fieldDeclarationTable.AddField( L"value", sqlite::enums::FieldType::Text );
		//Добавляем FLOAT
		fieldDeclarationTable.AddField( L"counts", sqlite::enums::FieldType::Float );
		//Добавляем BLOB
		fieldDeclarationTable.AddField( L"data", sqlite::enums::FieldType::BLob );

		//Создаем описание таблицы
		table_ = std::make_shared<sqlite::Table>( TEST_NAME_TABLE, fieldDeclarationTable );
	};
    /// @brief Деструктор
    ///
	~ValueTableF(){};
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
// Тест создания исключения
TEST_F(ValueTableF, Create ) 
{
	//EXPECT_NO_THROW( sqlite::ValueTable valueTable( GetTable() ) );
	//EXPECT_NO_THROW( sqlite::ValueTable valueTable2( GetTable()->GetFieldDeclarationTablePtr() ) );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(ValueTableF, GetIntegerValue ) 
{
	const wchar_t* const NAME = L"id";
	const sqlite::types::SQLITE_TYPE_INTEGER VALUE = 100;

	sqlite::ValueTable valueTable( GetTable() );
	EXPECT_NO_THROW( valueTable.GetIntegerValue( NAME ) );
	EXPECT_NO_THROW( valueTable.GetIntegerValue( NAME )->Set( VALUE ) );
	EXPECT_EQ( valueTable.GetIntegerValue( NAME )->Get(), VALUE );
	EXPECT_NO_THROW( valueTable.GetIntegerValue( NAME )->Set( VALUE ) );
	EXPECT_NO_THROW( valueTable.GetIntegerValue( NAME )->Get() );
	EXPECT_EQ( valueTable.GetIntegerValue( NAME )->Get(), VALUE );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(ValueTableF, GetStringValue ) 
{
	const wchar_t* const NAME = L"value";
	const sqlite::types::SQLITE_TYPE_STRING VALUE = L"test data";

	sqlite::ValueTable valueTable( GetTable() );
	EXPECT_NO_THROW( valueTable.GetStringValue( NAME ) );
	EXPECT_NO_THROW( valueTable.GetStringValue( NAME )->Set( VALUE ) );
	EXPECT_EQ( valueTable.GetStringValue( NAME )->Get(),  VALUE );
	EXPECT_NO_THROW( valueTable.GetStringValue( NAME )->Set(  VALUE ) );
	EXPECT_NO_THROW( valueTable.GetStringValue( NAME )->Get() );
	EXPECT_EQ( valueTable.GetStringValue( NAME )->Get(),  VALUE );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(ValueTableF, GetFloatValue ) 
{
	const wchar_t* const NAME = L"counts";
	const sqlite::types::SQLITE_TYPE_FLOAT VALUE = 10.5;

	sqlite::ValueTable valueTable( GetTable() );
	EXPECT_NO_THROW( valueTable.GetFloatValue( NAME ) );
	EXPECT_NO_THROW( valueTable.GetFloatValue( NAME )->Set( VALUE ) );
	EXPECT_EQ( valueTable.GetFloatValue( NAME )->Get(),  VALUE );
	EXPECT_NO_THROW( valueTable.GetFloatValue( NAME )->Set(  VALUE ) );
	EXPECT_NO_THROW( valueTable.GetFloatValue( NAME )->Get() );
	EXPECT_EQ( valueTable.GetFloatValue( NAME )->Get(),  VALUE );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(ValueTableF, GetBlobValue ) 
{
	const wchar_t* const NAME = L"data";
	const sqlite::types::SQLITE_TYPE_BLOB VALUE( 1024 * 10, 0);

	sqlite::ValueTable valueTable( GetTable() );
	EXPECT_NO_THROW( valueTable.GetBlobValue( NAME ) );
	EXPECT_NO_THROW( valueTable.GetBlobValue( NAME )->Set( VALUE ) );
	EXPECT_EQ( valueTable.GetBlobValue( NAME )->Get(),  VALUE );
	EXPECT_NO_THROW( valueTable.GetBlobValue( NAME )->Set(  VALUE ) );
	EXPECT_NO_THROW( valueTable.GetBlobValue( NAME )->Get() );
	EXPECT_EQ( valueTable.GetBlobValue( NAME )->Get(),  VALUE );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(ValueTableF, GetFailedData ) 
{
	sqlite::ValueTable valueTable( GetTable() );
	EXPECT_THROW( valueTable.GetStringValue( L"id" ), sqlite::Exception );
	EXPECT_THROW( valueTable.GetFloatValue( L"id" ), sqlite::Exception );
	EXPECT_THROW( valueTable.GetBlobValue( L"id" ), sqlite::Exception );
	EXPECT_NO_THROW( valueTable.GetIntegerValue( L"id" ) );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(ValueTableF, GetData ) 
{
	const wchar_t* const NAME = L"data";
	const sqlite::types::SQLITE_TYPE_BLOB VALUE( 1024 * 10, 0);

	sqlite::ValueTable valueTable( GetTable() );
	EXPECT_NO_THROW( valueTable.GetFieldDeclarationTable() );
	EXPECT_EQ( valueTable.GetFieldDeclarationTable().GetFieldNameList().size(), GetTable()->GetFieldDeclarationTable().GetFieldNameList().size() );	
}
//=====================================================================================================================
// Тест на запись в поток
TEST_F(ValueTableF, StreamDefaultData ) 
{
	std::wostringstream stream;
	sqlite::ValueTable valueTable( GetTable() );
	EXPECT_NO_THROW( stream << valueTable );
	EXPECT_STREQ( stream.str().c_str(), L"\"0\", \"\", \"0\", x''" );	
}
//=====================================================================================================================
// Тест на запись в поток
TEST_F(ValueTableF, Stream ) 
{
	const wchar_t* const NAME = L"value";
	sqlite::types::SQLITE_TYPE_BLOB dataValue( 5, 0 );
	dataValue[0] = 0x01;
	dataValue[1] = 0x02;
	dataValue[2] = 0x03;
	dataValue[3] = 0x72;
	dataValue[4] = 0x64;

	sqlite::ValueTable valueTable( GetTable() );
	EXPECT_NO_THROW( valueTable.GetIntegerValue( L"id" )->Set( 1000 ) );
	EXPECT_NO_THROW( valueTable.GetStringValue( L"value" )->Set( L"test data" ) );
	EXPECT_NO_THROW( valueTable.GetFloatValue( L"counts" )->Set( 999.4 ) );
	EXPECT_NO_THROW( valueTable.GetBlobValue( L"data" )->Set( dataValue ) );

	std::wostringstream stream;
	EXPECT_NO_THROW( stream << valueTable );
	EXPECT_STREQ(stream.str().c_str(), L"\"1000\", \"test data\", \"999.4\", x'0102037264'");
}
//=====================================================================================================================
