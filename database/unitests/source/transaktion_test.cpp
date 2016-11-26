/// @file 
/// @brief Тесты для открытия транзакции БД

#include <unitests/include/precompiled.h>

namespace
{
// путь к БД
const boost::filesystem::path& PATH_DB = boost::filesystem::temp_directory_path() / L"example.db";
}
//=====================================================================================================================
// Тест создания исключения
TEST(Transaktion, Create ) 
{
	//Открываем базу данных
	auto database = std::make_shared<sqlite::Database>( PATH_DB, false );

	EXPECT_NO_THROW( sqlite::Transaction transaction( database ) );
}
//=====================================================================================================================
// Тест получения данных
TEST(Transaktion, GetData ) 
{
	//Открываем базу данных
	auto database = std::make_shared<sqlite::Database>( PATH_DB, false );
	//Создаем транакцию
	sqlite::Transaction transaction( database );
	//Получаем гетер
	EXPECT_EQ( transaction.GetDataBase(), database );
	EXPECT_EQ( &transaction(), database.get() );
}
//=====================================================================================================================
// Тест на копирование объекта
TEST(Transaktion, Commit ) 
{
	//Открываем базу данных
	auto database = std::make_shared<sqlite::Database>( PATH_DB, false );
	//Создаем транакцию
	sqlite::Transaction transaction( database );
	//Первый вызов
	EXPECT_NO_THROW( transaction.Commit() );
	//Повторный вызов
	EXPECT_THROW( transaction.Commit(), sqlite::Exception );
}
//=====================================================================================================================
