/// @file 
/// @brief Тесты для работы с данными

#include <unitests/include/precompiled.h>

//=====================================================================================================================
// Тест создания исключения
TEST(ValueType, Create ) 
{
	auto field = std::make_shared<sqlite::Field>( L"data", sqlite::enums::FieldType::Text );

	EXPECT_NO_THROW( sqlite::ValueType<std::wstring>(  L"TestData", field ) );
	EXPECT_NO_THROW( sqlite::ValueType<std::wstring> data( field ) );
}
//=====================================================================================================================
// Тест получения данных
TEST(ValueType, GetData ) 
{
	auto field = std::make_shared<sqlite::Field>( L"data", sqlite::enums::FieldType::Text );
	sqlite::ValueType<std::wstring> valueType(  L"TestData", field );

	EXPECT_STREQ( valueType.Get().c_str(), L"TestData" );
	EXPECT_NO_THROW( valueType.Set(  L"TestData_2") );
	EXPECT_STREQ( valueType.Get().c_str(), L"TestData_2" );
}
//=====================================================================================================================
