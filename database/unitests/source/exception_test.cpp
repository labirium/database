/// @file 
/// @brief Тесты для исключений модуля database

#include <unitests/include/precompiled.h>

namespace
{
///< имя тестового сообщения
const char* const STRING_TEST = "Error input data.";
}
//=====================================================================================================================
// Тест создания исключения
TEST(Exception, Create ) 
{
	EXPECT_NO_THROW( sqlite::Exception( std::string( STRING_TEST ) ) );
}
//=====================================================================================================================
// Тест получения данных
TEST(Exception, GetData ) 
{
	 sqlite::Exception exception( STRING_TEST );
	 EXPECT_NO_THROW( exception.what() );
	 EXPECT_NE(  exception.what(), nullptr );
	 EXPECT_STREQ( exception.what(), STRING_TEST );
}
//=====================================================================================================================

