/// @file 
/// @brief ����� ��� �������� ���� ������

#include <unitests/include/precompiled.h>

namespace
{
///< ���� � ��
const boost::filesystem::path& PATH_TEST_DB = boost::filesystem::temp_directory_path() / L"test.db";
}
//=====================================================================================================================
// ���� �� �������� ��
TEST(DataBase, Open) 
{ 
	EXPECT_THROW( sqlite::Database( std::wstring() , false ), sqlite::Exception );
	EXPECT_THROW( sqlite::Database( std::wstring() , true ), sqlite::Exception );
	EXPECT_THROW( sqlite::Database( PATH_TEST_DB , true ), sqlite::Exception );
	EXPECT_NO_THROW( sqlite::Database( PATH_TEST_DB , false ) );
}
//=====================================================================================================================
// ���� �� ��������� �������
TEST(DataBase, GetData) 
{
	sqlite::Database database( PATH_TEST_DB , false );
	//���� � ��
	EXPECT_EQ( database.GetPath(), PATH_TEST_DB );
	EXPECT_EQ( database.GetPath(), PATH_TEST_DB );
	//�������� ������
	EXPECT_EQ( database.GetErrMessage(), "not an error" );
	//������ �� ����������� � ��
	EXPECT_NE( database.GetSqlite(), nullptr );
	
}
//=====================================================================================================================
int main(int argc, char **argv) 
{
	//�������� ��������� ���������� �� ������� � �����
	::testing::InitGoogleTest(&argc, argv);
	//��������� �����
	return RUN_ALL_TESTS();
}
//=====================================================================================================================
