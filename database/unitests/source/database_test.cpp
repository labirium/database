/// @file 
/// @brief Тесты для открытия базы данных

#include <unitests/include/precompiled.h>

namespace
{
///< путь к БД
const boost::filesystem::path& PATH_TEST_DB = boost::filesystem::temp_directory_path() / L"test.db";
}
//=====================================================================================================================
// Тест на открытие БД
TEST(DataBase, Open) 
{ 
	EXPECT_THROW( sqlite::Database( std::wstring() , false ), sqlite::Exception );
	EXPECT_THROW( sqlite::Database( std::wstring() , true ), sqlite::Exception );
	EXPECT_THROW( sqlite::Database( PATH_TEST_DB , true ), sqlite::Exception );
	EXPECT_NO_THROW( sqlite::Database( PATH_TEST_DB , false ) );
}
//=====================================================================================================================
// Тест на получение гетеров
TEST(DataBase, GetData) 
{
	sqlite::Database database( PATH_TEST_DB , false );
	//путь к БД
	EXPECT_EQ( database.GetPath(), PATH_TEST_DB );
	EXPECT_EQ( database.GetPath(), PATH_TEST_DB );
	//описание ошибки
	EXPECT_EQ( database.GetErrMessage(), "not an error" );
	//Хендел на подключение к БД
	EXPECT_NE( database.GetSqlite(), nullptr );
	
}
//=====================================================================================================================
int main(int argc, char **argv) 
{
	//передаем параметры переданные из консоли в тесты
	::testing::InitGoogleTest(&argc, argv);
	//запускаем тесты
	return RUN_ALL_TESTS();
}
//=====================================================================================================================
