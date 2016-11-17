/// @file 
/// @brief ����� ��� ������� �� ��

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
class StatmentF: public ::testing::Test 
{ 
public: 
	/// @brief �����������
	///
	StatmentF( void ) : database_( std::make_shared<sqlite::Database>( PATH_DB, false ) )
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
	~StatmentF(){};
	/// @brief ���, ������� ����� �������� ����� ������� ����� 
	///
	void SetUp( void )
	{
		sqlite::Transaction transaktion( GetDatabase() );
		GetTable()->Drop( transaktion );
		GetTable()->Create( transaktion );

		//������ ������ � ������� (���������� ������)
		sqlite::ValueTable valueTable( GetTable() ); 
		//�������� �������� ��� ���� id
		valueTable.GetIntegerValue( L"id" )->SetNull();
		//�������� �������� ��� ���� value
		valueTable.GetStringValue( L"value" )->Set( L"data" );

		//������� ����� ������ � �������
		GetTable()->Insert( transaktion, valueTable );

		//��������� ����������
		transaktion.Commit();
	};
	/// @brief ���, ������� ����� �������� ����� �� ���������� �����
	///
	void TearDown( void ){};
protected:
	/// @brief ���������� ������
	sqlite::Query GetQuery( void ) const
	{
		return table_->GetQueryWhereRecordSet();
	}
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
// ���� �������� ����������
TEST_F(StatmentF, Create ) 
{
	sqlite::Transaction transaktion( GetDatabase() );
	EXPECT_NO_THROW( GetQuery()( transaktion ) );
	EXPECT_NE( GetQuery()( transaktion ), nullptr );
}
//=====================================================================================================================
// ���� ��������� ������
TEST_F(StatmentF, GetData ) 
{
	sqlite::Transaction transaktion( GetDatabase() );
	auto query = GetQuery()( transaktion );
	EXPECT_EQ( query->GetDataBase(), GetDatabase() );
}
//=====================================================================================================================
// ���� ��������� ������
TEST_F(StatmentF, Step ) 
{
	//��������� ����������
	sqlite::Transaction transaktion( GetDatabase() );

	//�������� ������ ��� ������� �� ������� � ������ ��������� ��� �������
	auto query = GetTable()->GetQueryWhereRecordSet();	
			
	//��������� ������ � ������� ��
	auto stmt = query( transaktion );
	EXPECT_NE( stmt, nullptr );
				
	//��������� ����������
	transaktion.Commit();

	const auto value = stmt->Step();
	EXPECT_NE( value.get(), nullptr );

	//�������� ������ ��� ���� id
	auto id = value->GetIntegerValue( L"id" )->Get();
	EXPECT_EQ( id, 1 );
	//�������� ������ ��� ���� value
	auto data = value->GetStringValue( L"value" )->Get();
	EXPECT_STREQ( data.c_str(), L"data" );
	
	//��������� ������ � ������� ��
	const auto value2 = stmt->Step();
	EXPECT_EQ( value2.get(), nullptr );
}
//=====================================================================================================================
