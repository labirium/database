/// @file 
/// @brief Тесты для работы со спомогательными классами

#include <unitests/include/precompiled.h>

namespace
{
///< тестовые данные
const wchar_t* const STRING_TEST = L"TEST_DATA";
}
//=====================================================================================================================
// Тест создания исключения
TEST(FirstString, Create ) 
{
	EXPECT_NO_THROW( tools::FirstString( STRING_TEST ) );
}
//=====================================================================================================================
// Тест получения данных
TEST(FirstString, GetData ) 
{
	tools::FirstString firstString( STRING_TEST );
	EXPECT_STREQ( firstString().c_str(), L"" );
	EXPECT_STREQ( firstString().c_str(), STRING_TEST );
	EXPECT_STREQ( firstString().c_str(), STRING_TEST );
	EXPECT_STRNE( firstString().c_str(), L"" );
}
//=====================================================================================================================

