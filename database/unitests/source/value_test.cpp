/// @file 
/// @brief ����� ��� ������ � �������

#include <unitests/include/precompiled.h>

//=====================================================================================================================
// ���� �������� ����������
TEST(ValueType, Create ) 
{
	auto field = std::make_shared<sqlite::Field>( L"data", sqlite::enums::FieldType::Text );

	EXPECT_NO_THROW( sqlite::ValueType<std::wstring>(  L"TestData", field ) );
	EXPECT_NO_THROW( sqlite::ValueType<std::wstring> data( field ) );
}
//=====================================================================================================================
// ���� ��������� ������
TEST(ValueType, GetData ) 
{
	auto field = std::make_shared<sqlite::Field>( L"data", sqlite::enums::FieldType::Text );
	sqlite::ValueType<std::wstring> valueType(  L"TestData", field );

	EXPECT_STREQ( valueType.Get().c_str(), L"TestData" );
	EXPECT_NO_THROW( valueType.Set(  L"TestData_2") );
	EXPECT_STREQ( valueType.Get().c_str(), L"TestData_2" );
}
//=====================================================================================================================
