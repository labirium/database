/// @file 
/// @brief Тесты для подготовки строки для вставки в БД

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
class InsertValueF: public ::testing::Test 
{ 
public: 
	/// @brief Конструктор
	///
	InsertValueF( void ) : database_( std::make_shared<sqlite::Database>( PATH_DB, false ) )
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
	~InsertValueF(){};
	/// @brief Код, который будет выполнен перед началом теста 
	///
	void SetUp( void ){};
	/// @brief Код, который будет выполнен сразу по завершении теста
	///
	void TearDown( void ){};
protected:
	/// @brief Возвращает тестовое значение
	///
	sqlite::ValueTable GetValueTable( void ) const
	{
		//Запись данных в таблицу (подготовка данных)
		sqlite::ValueTable valueTable( GetTable() ); 
		//Выставка значения для поля id
		valueTable.GetIntegerValue( L"id" )->SetNull();
		//Выставка значения для поля value
		valueTable.GetStringValue( L"value" )->Set( L"data" );

		return valueTable;
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
TEST_F(InsertValueF, Create ) 
{
	//EXPECT_NO_THROW( sqlite::InsertValue data( GetTable() ) );
}
//=====================================================================================================================
// Тест получения данных
TEST_F(InsertValueF, Add ) 
{
	//Создаем транзакцию
	sqlite::Transaction transaktion( GetDatabase() );
	//Создаем новую таблицу
	GetTable()->Drop( transaktion  );
	GetTable()->Create( transaktion  );
	
	//Дабавляем запись в БД
	sqlite::InsertValue insertValue( GetTable() );
	EXPECT_THROW( insertValue.Exec( transaktion ), sqlite::Exception );
	EXPECT_NO_THROW( insertValue.Add( GetValueTable() ) );
	EXPECT_NO_THROW( insertValue.Add( GetValueTable() ) );

	EXPECT_NO_THROW( insertValue.Exec( transaktion ) );
}
//=====================================================================================================================
