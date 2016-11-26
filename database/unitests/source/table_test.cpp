/// @file 
/// @brief Тесты для работы с таблицей БД

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
class TableF: public ::testing::Test 
{ 
public: 
	/// @brief Конструктор
	///
	TableF( void ) : database_( std::make_shared<sqlite::Database>( PATH_DB, false ) )
	{
		//Добавляем поле id и выставляем как основной ключ таблицы
		fieldDeclarationTable_.AddField( L"id", sqlite::enums::FieldType::Integer, true );
		//Добавляем строковое поле в таблицу
		fieldDeclarationTable_.AddField( L"value", sqlite::enums::FieldType::Text );
	};
    /// @brief Деструктор
    ///
	~TableF(){};
	/// @brief Код, который будет выполнен перед началом теста 
	///
	void SetUp( void ){};
	/// @brief Код, который будет выполнен сразу по завершении теста
	///
	void TearDown( void ){};
protected:
	/// @brif Возрващает описание полей таблицы
	///
	const sqlite::FieldDeclarationTable& GetFieldDeclarationTable( void ) const
	{
		return fieldDeclarationTable_;
	}
	/// @brief Возвращает описание подулючение к БД
	///
	sqlite::DatabasePtr GetDatabase( void ) const
	{
		return database_;
	}
private:
	///< Описание полей таблицы
	sqlite::FieldDeclarationTable fieldDeclarationTable_;
	///< Подключение к БД
	const sqlite::DatabasePtr database_;
};
}

//=====================================================================================================================
// Тест создания исключения
TEST_F(TableF, Create ) 
{
	//Формируем таблицу на основе описания
	EXPECT_NO_THROW( sqlite::Table( TEST_NAME_TABLE, GetFieldDeclarationTable() ) );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(TableF, GetData ) 
{
	sqlite::Table table( TEST_NAME_TABLE, GetFieldDeclarationTable() );
	EXPECT_STREQ( table.GetName().c_str(), TEST_NAME_TABLE );
	EXPECT_EQ( table.GetFieldDeclarationTable().GetFieldNameList(), GetFieldDeclarationTable().GetFieldNameList() );
	EXPECT_NE( table.GetFieldDeclarationTablePtr(), nullptr );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(TableF, GetQueryWhereRecordSet ) 
{
	//Создаем описание таблицы
	sqlite::Table table( TEST_NAME_TABLE, GetFieldDeclarationTable() );
	//Создаем транзакцию
	sqlite::Transaction transaktion( GetDatabase() );

	EXPECT_NO_THROW( table.Drop( transaktion ) );
	EXPECT_NO_THROW( table.Create( transaktion ) );
	EXPECT_NE( table.GetQueryWhereRecordSet()( transaktion ), nullptr );
}
//=====================================================================================================================
// Тест создание таблицы
TEST_F(TableF, CreateTable ) 
{
	//Создаем описание таблицы
	sqlite::Table table( TEST_NAME_TABLE, GetFieldDeclarationTable() );
	//Создаем транзакцию
	sqlite::Transaction transaktion( GetDatabase() );
	//Создаем транзакцию
	EXPECT_NO_THROW( table.Drop( transaktion ) );
	EXPECT_NO_THROW( table.Create( transaktion ) );
	EXPECT_THROW( table.Create( transaktion ), sqlite::Exception );
}
//=====================================================================================================================
// Тест создание таблицы
TEST_F(TableF, CreateTableAndDrop ) 
{
	//Создаем описание таблицы
	sqlite::Table table( TEST_NAME_TABLE, GetFieldDeclarationTable() );
	//Создаем транзакцию
	sqlite::Transaction transaktion( GetDatabase() );
	//Создаем транзакцию
	EXPECT_NO_THROW( table.Drop( transaktion ) );
	EXPECT_NO_THROW( table.Create( transaktion ) );
	//Закрываем транзакцию
	transaktion.Commit();

	//Создаем транзакцию
	sqlite::Transaction transaktion2( GetDatabase() );
	//Создаем транзакцию
	EXPECT_NO_THROW( table.Drop( transaktion2 ) );
	EXPECT_NO_THROW( table.Drop( transaktion2 ) );
	//Закрываем транзакцию
	EXPECT_NO_THROW( transaktion2.Commit() );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(TableF, InsertData ) 
{
	//Создаем описание таблицы
	auto table = std::make_shared<sqlite::Table>( TEST_NAME_TABLE, GetFieldDeclarationTable() );
	//Создаем транзакцию
	sqlite::Transaction transaktion( GetDatabase() );

	//Запись данных в таблицу (подготовка данных)
	sqlite::ValueTable valueTable( table ); 
	//Выставка значения для поля id
	valueTable.GetIntegerValue( L"id" )->SetNull();
	//Выставка значения для поля value
	valueTable.GetStringValue( L"value" )->Set( L"data" );

	EXPECT_NO_THROW( table->Drop( transaktion ) );
	EXPECT_NO_THROW( table->Create( transaktion ) );
	EXPECT_NO_THROW( table->Insert( transaktion, valueTable ) );
	EXPECT_NO_THROW( table->Insert( transaktion, valueTable ) );
	EXPECT_NO_THROW( table->Insert( transaktion, valueTable ) );
}
//=====================================================================================================================
