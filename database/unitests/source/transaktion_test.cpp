/// @file 
/// @brief ����� ��� �������� ���������� ��

#include <unitests/include/precompiled.h>

namespace
{
// ���� � ��
const boost::filesystem::path& PATH_DB = boost::filesystem::temp_directory_path() / L"example.db";
}
//=====================================================================================================================
// ���� �������� ����������
TEST(Transaktion, Create ) 
{
	//��������� ���� ������
	auto database = std::make_shared<sqlite::Database>( PATH_DB, false );

	EXPECT_NO_THROW( sqlite::Transaction transaction( database ) );
}
//=====================================================================================================================
// ���� ��������� ������
TEST(Transaktion, GetData ) 
{
	//��������� ���� ������
	auto database = std::make_shared<sqlite::Database>( PATH_DB, false );
	//������� ���������
	sqlite::Transaction transaction( database );
	//�������� �����
	EXPECT_EQ( transaction.GetDataBase(), database );
	EXPECT_EQ( &transaction(), database.get() );
}
//=====================================================================================================================
// ���� �� ����������� �������
TEST(Transaktion, Commit ) 
{
	//��������� ���� ������
	auto database = std::make_shared<sqlite::Database>( PATH_DB, false );
	//������� ���������
	sqlite::Transaction transaction( database );
	//������ �����
	EXPECT_NO_THROW( transaction.Commit() );
	//��������� �����
	EXPECT_THROW( transaction.Commit(), sqlite::Exception );
}
//=====================================================================================================================
