/// @file 
/// @brief ����� ��� ������� ���������� ������� ��

#include <unitests/include/precompiled.h>

namespace
{
// �������� ��� �������
const wchar_t* const TEST_NAME_TABLE = L"TEST_TABLE";
// ���� � ��
const boost::filesystem::path& PATH_DB = boost::filesystem::temp_directory_path() / L"example.db";
}

namespace
{
class QueryF: public ::testing::Test 
{ 
public: 
	/// @brief �����������
	///
	QueryF( void ) : database_( std::make_shared<sqlite::Database>( PATH_DB, false ) )
	{
		///< �������� ����� �������
		sqlite::FieldDeclarationTable fieldDeclarationTable;
		//��������� ���� id � ���������� ��� �������� ���� �������
		fieldDeclarationTable.AddField( L"id", sqlite::enums::FieldType::Integer, true );
		//��������� ��������� ���� � �������
		fieldDeclarationTable.AddField( L"value", sqlite::enums::FieldType::Text );

		sqlite::Table ff( TEST_NAME_TABLE, fieldDeclarationTable );
		//������� �������� �������
		table_ = std::make_shared<sqlite::Table>( TEST_NAME_TABLE, fieldDeclarationTable );
	};
    /// @brief ����������
    ///
	~QueryF(){};
	/// @brief ���, ������� ����� �������� ����� ������� ����� 
	///
	void SetUp( void ){};
	/// @brief ���, ������� ����� �������� ����� �� ���������� �����
	///
	void TearDown( void ){};
protected:
	/// @brief ���������� �������
	///
	sqlite::TablePtr GetTable( void ) const
	{
		return table_;
	}
	/// @brief ���������� �������� ����������� � ��
	///
	sqlite::DatabasePtr GetDatabase( void ) const
	{
		return database_;
	}

private:
	///< ����������� � ��
	const sqlite::DatabasePtr database_;
	///< �������� �������
	sqlite::TablePtr table_;

};
}

//=====================================================================================================================
// ���� ��������
TEST_F(QueryF, Create ) 
{
	EXPECT_NO_THROW( GetTable()->GetQueryWhereRecordSet() );
}
//=====================================================================================================================
// ���� ��������� ������
TEST_F(QueryF, GetData ) 
{
	auto query = GetTable()->GetQueryWhereRecordSet();

	//������� ����������
	sqlite::Transaction transaktion( GetDatabase() );
	GetTable()->Drop( transaktion );
	GetTable()->Create( transaktion );

	EXPECT_NO_THROW( query( transaktion ) );
	EXPECT_NE( query( transaktion ), nullptr );
	EXPECT_NE( query( transaktion ), query( transaktion ) );
}
//=====================================================================================================================
// ���� ��������� ������
TEST_F(QueryF, GetDataThrow ) 
{
	auto query = GetTable()->GetQueryWhereRecordSet();

	//������� ����������
	sqlite::Transaction transaktion( GetDatabase() );
	GetTable()->Drop( transaktion );

	EXPECT_THROW( query( transaktion ), sqlite::Exception );
}
//=====================================================================================================================
// ���� WHERE
TEST_F(QueryF, Where ) 
{
	auto query = GetTable()->GetQueryWhereRecordSet();
	EXPECT_NO_THROW( query.Where( L"id > 0" ) );
}
//=====================================================================================================================
