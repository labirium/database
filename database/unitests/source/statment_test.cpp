/// @file 
/// @brief Тесты для выборки из БД

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
class StatmentF: public ::testing::Test 
{ 
public: 
	/// @brief Конструктор
	///
	StatmentF( void ) : database_( std::make_shared<sqlite::Database>( PATH_DB, false ) )
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
	~StatmentF(){};
	/// @brief Код, который будет выполнен перед началом теста 
	///
	void SetUp( void )
	{
		sqlite::Transaction transaktion( GetDatabase() );
		GetTable()->Drop( transaktion );
		GetTable()->Create( transaktion );

		//Запись данных в таблицу (подготовка данных)
		sqlite::ValueTable valueTable( GetTable() ); 
		//Выставка значения для поля id
		valueTable.GetIntegerValue( L"id" )->SetNull();
		//Выставка значения для поля value
		valueTable.GetStringValue( L"value" )->Set( L"data" );

		//Вставка одной записи в теблицу
		GetTable()->Insert( transaktion, valueTable );

		//Закрываем транзакцию
		transaktion.Commit();
	};
	/// @brief Код, который будет выполнен сразу по завершении теста
	///
	void TearDown( void ){};
protected:
	/// @brief Возвращает запрос
	sqlite::Query GetQuery( void ) const
	{
		return table_->GetQueryWhereRecordSet();
	}
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
TEST_F(StatmentF, Create ) 
{
	sqlite::Transaction transaktion( GetDatabase() );
	EXPECT_NO_THROW( GetQuery()( transaktion ) );
	EXPECT_NE( GetQuery()( transaktion ), nullptr );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(StatmentF, GetData ) 
{
	sqlite::Transaction transaktion( GetDatabase() );
	auto query = GetQuery()( transaktion );
	EXPECT_EQ( query->GetDataBase(), GetDatabase() );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(StatmentF, Step ) 
{
	//Открываем транзакцию
	sqlite::Transaction transaktion( GetDatabase() );

	//Получаем запрос для выборки по таблице и задаем параметры для выборки
	auto query = GetTable()->GetQueryWhereRecordSet();	
			
	//Выполняем запрос к таблице БД
	auto stmt = query( transaktion );
	EXPECT_NE( stmt, nullptr );
				
	//Закрываем транзакцию
	transaktion.Commit();

	const auto value = stmt->Step();
	EXPECT_NE( value.get(), nullptr );

	//Получаем данные для поля id
	auto id = value->GetIntegerValue( L"id" )->Get();
	EXPECT_EQ( id, 1 );
	//Получаем данные для поля value
	auto data = value->GetStringValue( L"value" )->Get();
	EXPECT_STREQ( data.c_str(), L"data" );
	
	//Выполняем запрос к таблице БД
	const auto value2 = stmt->Step();
	EXPECT_EQ( value2.get(), nullptr );
}
//=====================================================================================================================
