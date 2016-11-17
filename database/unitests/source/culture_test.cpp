/// @file 
/// @brief ����� ��� ������������� ������ � ��������� �������/���������

#include <unitests/include/precompiled.h>

namespace
{
///< ��� �������� ������ EN
const wchar_t* const W_STRING_TEST_EN = L"test string";
///< ��� �������� ������ EN
const char* const A_STRING_TEST_EN = "test string";
}
//=====================================================================================================================
// ����� ��� ������������� ������ � ��������� �������/���������
TEST(CultureString, w2utf8 ) 
{
	const auto& stringA = culture::w2utf8( boost::filesystem::path( W_STRING_TEST_EN ) );
	EXPECT_STREQ( stringA.c_str(), A_STRING_TEST_EN );

	const auto& stringA1 = culture::w2utf8( std::wstring( W_STRING_TEST_EN ) );
	EXPECT_STREQ( stringA1.c_str(), A_STRING_TEST_EN );
}
//=====================================================================================================================
// ����� ��� ������������� ������ � ��������� �������/���������
TEST(CultureString, utf2w ) 
{
	const auto& stringA1 = culture::utf2w( A_STRING_TEST_EN );
	EXPECT_STREQ( stringA1.c_str(), W_STRING_TEST_EN );
}
//=====================================================================================================================
