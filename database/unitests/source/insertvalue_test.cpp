/// @file 
/// @brief ����� ��� ���������� ������ ��� ������� � ��

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
class InsertValueF: public ::testing::Test 
{ 
public: 
	/// @brief �����������
	///
	InsertValueF( void ) : database_( std::make_shared<sqlite::Database>( PATH_DB, false ) )
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
	~InsertValueF(){};
	/// @brief ���, ������� ����� �������� ����� ������� ����� 
	///
	void SetUp( void ){};
	/// @brief ���, ������� ����� �������� ����� �� ���������� �����
	///
	void TearDown( void ){};
protected:
	/// @brief ���������� �������� ��������
	///
	sqlite::ValueTable GetValueTable( void ) const
	{
		//������ ������ � ������� (���������� ������)
		sqlite::ValueTable valueTable( GetTable() ); 
		//�������� �������� ��� ���� id
		valueTable.GetIntegerValue( L"id" )->SetNull();
		//�������� �������� ��� ���� value
		valueTable.GetStringValue( L"value" )->Set( L"data" );

		return valueTable;
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
TEST_F(InsertValueF, Create ) 
{
	//EXPECT_NO_THROW( sqlite::InsertValue data( GetTable() ) );
}
//=====================================================================================================================
// ���� ��������� ������
TEST_F(InsertValueF, Add ) 
{
	//������� ����������
	sqlite::Transaction transaktion( GetDatabase() );
	//������� ����� �������
	GetTable()->Drop( transaktion  );
	GetTable()->Create( transaktion  );
	
	//��������� ������ � ��
	sqlite::InsertValue insertValue( GetTable() );
	EXPECT_THROW( insertValue.Exec( transaktion ), sqlite::Exception );
	EXPECT_NO_THROW( insertValue.Add( GetValueTable() ) );
	EXPECT_NO_THROW( insertValue.Add( GetValueTable() ) );

	EXPECT_NO_THROW( insertValue.Exec( transaktion ) );
}
//=====================================================================================================================
