/// @file 
/// @brief ����� ��� ���������� ������ database

#include <unitests/include/precompiled.h>

namespace
{
///< ��� ��������� ���������
const char* const STRING_TEST = "Error input data.";
}
//=====================================================================================================================
// ���� �������� ����������
TEST(Exception, Create ) 
{
	EXPECT_NO_THROW( sqlite::Exception( std::string( STRING_TEST ) ) );
}
//=====================================================================================================================
// ���� ��������� ������
TEST(Exception, GetData ) 
{
	 sqlite::Exception exception( STRING_TEST );
	 EXPECT_NO_THROW( exception.what() );
	 EXPECT_NE(  exception.what(), nullptr );
	 EXPECT_STREQ( exception.what(), STRING_TEST );
}
//=====================================================================================================================

