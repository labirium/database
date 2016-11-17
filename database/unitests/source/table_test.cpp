/// @file 
/// @brief ����� ��� ������ � �������� ��

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
class TableF: public ::testing::Test 
{ 
public: 
	/// @brief �����������
	///
	TableF( void ) : database_( std::make_shared<sqlite::Database>( PATH_DB, false ) )
	{
		//��������� ���� id � ���������� ��� �������� ���� �������
		fieldDeclarationTable_.AddField( L"id", sqlite::enums::FieldType::Integer, true );
		//��������� ��������� ���� � �������
		fieldDeclarationTable_.AddField( L"value", sqlite::enums::FieldType::Text );
	};
    /// @brief ����������
    ///
	~TableF(){};
	/// @brief ���, ������� ����� �������� ����� ������� ����� 
	///
	void SetUp( void ){};
	/// @brief ���, ������� ����� �������� ����� �� ���������� �����
	///
	void TearDown( void ){};
protected:
	/// @brif ���������� �������� ����� �������
	///
	const sqlite::FieldDeclarationTable& GetFieldDeclarationTable( void ) const
	{
		return fieldDeclarationTable_;
	}
	/// @brief ���������� �������� ����������� � ��
	///
	sqlite::DatabasePtr GetDatabase( void ) const
	{
		return database_;
	}
private:
	///< �������� ����� �������
	sqlite::FieldDeclarationTable fieldDeclarationTable_;
	///< ����������� � ��
	const sqlite::DatabasePtr database_;
};
}

//=====================================================================================================================
// ���� �������� ����������
TEST_F(TableF, Create ) 
{
	//��������� ������� �� ������ ��������
	EXPECT_NO_THROW( sqlite::Table( TEST_NAME_TABLE, GetFieldDeclarationTable() ) );
}
//=====================================================================================================================
// ���� ��������� ������
TEST_F(TableF, GetData ) 
{
	sqlite::Table table( TEST_NAME_TABLE, GetFieldDeclarationTable() );
	EXPECT_STREQ( table.GetName().c_str(), TEST_NAME_TABLE );
	EXPECT_EQ( table.GetFieldDeclarationTable().GetFieldNameList(), GetFieldDeclarationTable().GetFieldNameList() );
	EXPECT_NE( table.GetFieldDeclarationTablePtr(), nullptr );
}
//=====================================================================================================================
// ���� ��������� ������
TEST_F(TableF, GetQueryWhereRecordSet ) 
{
	//������� �������� �������
	sqlite::Table table( TEST_NAME_TABLE, GetFieldDeclarationTable() );
	//������� ����������
	sqlite::Transaction transaktion( GetDatabase() );

	EXPECT_NO_THROW( table.Drop( transaktion ) );
	EXPECT_NO_THROW( table.Create( transaktion ) );
	EXPECT_NE( table.GetQueryWhereRecordSet()( transaktion ), nullptr );
}
//=====================================================================================================================
// ���� �������� �������
TEST_F(TableF, CreateTable ) 
{
	//������� �������� �������
	sqlite::Table table( TEST_NAME_TABLE, GetFieldDeclarationTable() );
	//������� ����������
	sqlite::Transaction transaktion( GetDatabase() );
	//������� ����������
	EXPECT_NO_THROW( table.Drop( transaktion ) );
	EXPECT_NO_THROW( table.Create( transaktion ) );
	EXPECT_THROW( table.Create( transaktion ), sqlite::Exception );
}
//=====================================================================================================================
// ���� �������� �������
TEST_F(TableF, CreateTableAndDrop ) 
{
	//������� �������� �������
	sqlite::Table table( TEST_NAME_TABLE, GetFieldDeclarationTable() );
	//������� ����������
	sqlite::Transaction transaktion( GetDatabase() );
	//������� ����������
	EXPECT_NO_THROW( table.Drop( transaktion ) );
	EXPECT_NO_THROW( table.Create( transaktion ) );
	//��������� ����������
	transaktion.Commit();

	//������� ����������
	sqlite::Transaction transaktion2( GetDatabase() );
	//������� ����������
	EXPECT_NO_THROW( table.Drop( transaktion2 ) );
	EXPECT_NO_THROW( table.Drop( transaktion2 ) );
	//��������� ����������
	EXPECT_NO_THROW( transaktion2.Commit() );
}
//=====================================================================================================================
// ���� ��������� ������
TEST_F(TableF, InsertData ) 
{
	//������� �������� �������
	auto table = std::make_shared<sqlite::Table>( TEST_NAME_TABLE, GetFieldDeclarationTable() );
	//������� ����������
	sqlite::Transaction transaktion( GetDatabase() );

	//������ ������ � ������� (���������� ������)
	sqlite::ValueTable valueTable( table ); 
	//�������� �������� ��� ���� id
	valueTable.GetIntegerValue( L"id" )->SetNull();
	//�������� �������� ��� ���� value
	valueTable.GetStringValue( L"value" )->Set( L"data" );

	EXPECT_NO_THROW( table->Drop( transaktion ) );
	EXPECT_NO_THROW( table->Create( transaktion ) );
	EXPECT_NO_THROW( table->Insert( transaktion, valueTable ) );
	EXPECT_NO_THROW( table->Insert( transaktion, valueTable ) );
	EXPECT_NO_THROW( table->Insert( transaktion, valueTable ) );
}
//=====================================================================================================================
