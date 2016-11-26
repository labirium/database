/// @file 
/// @brief Тесты для формирования описания полей таблицы.

#include <unitests/include/precompiled.h>

namespace
{
///< имя тестовой таблицы 1
const wchar_t* TABLE_NAME = L"test_name";
///< имя тестовой таблицы 2
const wchar_t* TABLE_NAME_2 = L"test_name_2";
///< имя тестовой таблицы 3
const wchar_t* TABLE_NAME_3 = L"test_name_3";
///< имя тестовой таблицы 4	
const wchar_t* TABLE_NAME_4 = L"test_name_4";
}
//=====================================================================================================================
// Тест на получение строк через операторы
TEST(FieldType, GetStringTypeOperator ) 
{
	EXPECT_STREQ( static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Integer ), L"INTEGER" );
	EXPECT_STREQ( static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Integer ).ToString(), L"INTEGER" );
	
	EXPECT_STREQ( static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Float ), L"FLOAT" );
	EXPECT_STREQ( static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Float ).ToString(), L"FLOAT" );

	EXPECT_STREQ( static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Text ), L"TEXT" );
	EXPECT_STREQ( static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Text ).ToString(), L"TEXT" );

	EXPECT_STREQ( static_cast<sqlite::FieldType>( sqlite::enums::FieldType::BLob ), L"BLOB" );
	EXPECT_STREQ( static_cast<sqlite::FieldType>( sqlite::enums::FieldType::BLob ).ToString(), L"BLOB" );
}
//=====================================================================================================================
// Тест на получение константых строк
TEST(FieldType, GetConstStringType )
{
	const std::wstring strFnteger = static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Integer );
	EXPECT_STREQ( strFnteger.c_str(), L"INTEGER" );

	const std::wstring strFloat = static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Float );
	EXPECT_STREQ( strFloat.c_str(), L"FLOAT" );

	const std::wstring strText = static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Text );
	EXPECT_STREQ( strText.c_str(), L"TEXT" );

	const std::wstring strBlob = static_cast<sqlite::FieldType>( sqlite::enums::FieldType::BLob );
	EXPECT_STREQ( strBlob.c_str(), L"BLOB" );
}
//=====================================================================================================================
// Тест на получение строк
TEST(FieldType, GetStringType ) 
{
	std::wstring strFnteger( static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Integer ) );
	EXPECT_STREQ( strFnteger.c_str(), L"INTEGER" );

	std::wstring strFloat = static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Float );
	EXPECT_STREQ( strFloat.c_str(), L"FLOAT" );

	std::wstring strText = static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Text );
	EXPECT_STREQ( strText.c_str(), L"TEXT" );

	std::wstring strBlob = static_cast<sqlite::FieldType>( sqlite::enums::FieldType::BLob );
	EXPECT_STREQ( strBlob.c_str(), L"BLOB" );
}
//=====================================================================================================================
// Тест на получение данных
TEST( Field, GetData ) 
{
	EXPECT_NO_THROW( sqlite::Field( TABLE_NAME, sqlite::enums::FieldType::Integer ) );
	EXPECT_NO_THROW( sqlite::Field( TABLE_NAME, sqlite::enums::FieldType::Integer, true ) );

	sqlite::Field field( TABLE_NAME, sqlite::enums::FieldType::Integer );
	//проверяем генерация строки
	auto dataString = field();
	EXPECT_STREQ( dataString.c_str(), L"test_name INTEGER" );
	//проверяем тип поля
	EXPECT_EQ( field.GetFieldType(), sqlite::enums::FieldType::Integer );
	//проверяем имя поля
	const auto& name =  field.GetName();
	EXPECT_STREQ( name.c_str(), TABLE_NAME );
	//проверяем параметр конструктора
	dataString = sqlite::Field( TABLE_NAME, sqlite::enums::FieldType::Float, true )();
	EXPECT_STREQ( dataString.c_str(), L"test_name FLOAT NOT NULL PRIMARY KEY AUTOINCREMENT" );
}

//=====================================================================================================================
//FieldDeclarationTable
//=====================================================================================================================
// Тест на создание объекта
TEST( FieldDeclarationTable, Create ) 
{
	//Создание объекта
	EXPECT_NO_THROW( sqlite::FieldDeclarationTable() );
}
//=====================================================================================================================
// Тест на регистрацию полей в таблице
TEST( FieldDeclarationTable, AddField ) 
{
	sqlite::FieldDeclarationTable fieldDeclarationTable;
	EXPECT_NO_THROW( fieldDeclarationTable.AddField( TABLE_NAME, sqlite::enums::FieldType::Integer ) );
	EXPECT_NO_THROW( fieldDeclarationTable.AddField( TABLE_NAME, sqlite::enums::FieldType::Integer, true ) );

	auto field = std::make_shared<sqlite::Field>( TABLE_NAME, sqlite::enums::FieldType::Integer, true );
	EXPECT_NO_THROW( fieldDeclarationTable.AddField( field ) );
}
//=====================================================================================================================
// Тест на получения данных из таблицы
TEST( FieldDeclarationTable, GetData ) 
{
	sqlite::FieldDeclarationTable fieldDeclarationTable;
	fieldDeclarationTable.AddField( TABLE_NAME, sqlite::enums::FieldType::Integer, true );
	
	//Тест на получения данных из таблицы
	EXPECT_NE( fieldDeclarationTable( TABLE_NAME ), nullptr );
	EXPECT_EQ( fieldDeclarationTable( (std::wstring(TABLE_NAME) + L"_PREF") ), nullptr );
	EXPECT_EQ( fieldDeclarationTable().size(), 1 );
	EXPECT_EQ( fieldDeclarationTable.GetFieldNameList().size(), 1 );
	EXPECT_EQ( fieldDeclarationTable.GetFieldNameList().at(0), TABLE_NAME );
}
//=====================================================================================================================
//StreamString
//=====================================================================================================================
// Тест на поток данных
TEST( StreamString, FieldType ) 
{
	std::wstringstream straem;
	straem << static_cast<sqlite::FieldType>( sqlite::enums::FieldType::Integer );
	EXPECT_STREQ(  straem.str().c_str(), L"INTEGER" );

	std::wstringstream data;
	data << sqlite::Field( TABLE_NAME, sqlite::enums::FieldType::Integer );
	EXPECT_STREQ( data.str().c_str(), L"test_name INTEGER" );
}
//=====================================================================================================================
// Тест на поток данных
TEST( StreamString, Field ) 
{
	sqlite::Field field( TABLE_NAME, sqlite::enums::FieldType::Integer );

	std::wstringstream straem;
	straem << field;
	EXPECT_STREQ(  straem.str().c_str(), L"test_name INTEGER"  );
}
//=====================================================================================================================
// Тест на поток данных
TEST( StreamString, FieldList ) 
{
	sqlite::FieldDeclarationTable fieldDeclarationTable;
	fieldDeclarationTable.AddField( TABLE_NAME, sqlite::enums::FieldType::Integer, true );
	fieldDeclarationTable.AddField( TABLE_NAME_2, sqlite::enums::FieldType::Float );
	fieldDeclarationTable.AddField( TABLE_NAME_3, sqlite::enums::FieldType::Text );
	fieldDeclarationTable.AddField( TABLE_NAME_4, sqlite::enums::FieldType::BLob );

	std::wstringstream straem;
	straem << fieldDeclarationTable();
	EXPECT_STREQ(  straem.str().c_str(), L"test_name INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, test_name_2 FLOAT, test_name_3 TEXT, test_name_4 BLOB"  );
	
	auto fieldNameList = fieldDeclarationTable.GetFieldNameList();
	EXPECT_EQ( fieldNameList.size(), 4 );
	EXPECT_STREQ( sqlite::StrToStringList( fieldNameList ).c_str(), L"\"test_name\", \"test_name_2\", \"test_name_3\", \"test_name_4\"" );
}
//=====================================================================================================================
