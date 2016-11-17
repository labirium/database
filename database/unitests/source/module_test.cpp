/// @file 
/// @brief ��������� ����

#include <unitests/include/precompiled.h>

namespace
{
///< ���� � ��
const boost::filesystem::path& PATH_TEST_DB = boost::filesystem::temp_directory_path() / L"test.db";
}
//=====================================================================================================================
// ��������� ����
TEST(ModuleTest, First) 
{
	try
	{
			//��������� ���� ������
			auto database = std::make_shared<sqlite::Database>( PATH_TEST_DB, false );

			//�������� ����� �������
			sqlite::FieldDeclarationTable fieldDeclarationTable;
			//��������� ���� id � ���������� ��� �������� ���� �������
			fieldDeclarationTable.AddField( L"id", sqlite::enums::FieldType::Integer, true );
			//��������� ��������� ���� � �������
			fieldDeclarationTable.AddField( L"value", sqlite::enums::FieldType::Text );

			//��������� ������� �� ������ ��������
			auto table = std::make_shared<sqlite::Table>( L"testTable", fieldDeclarationTable );

			//��������� ����������
			sqlite::Transaction transaction( database );

			//�������� �������
			table->Drop( transaction );
			//�������� �������
			table->Create( transaction );


			//������ ������ � ������� (���������� ������)
			sqlite::ValueTable valueTable( table ); 
			//�������� �������� ��� ���� id
			valueTable.GetIntegerValue( L"id" )->SetNull();
			//�������� �������� ��� ���� value
			valueTable.GetStringValue( L"value" )->Set( L"data" );

			//������ ������ � �������  (���������� ������)
			sqlite::ValueTable valueTable2( table );
			//�������� �������� ��� ���� id
			valueTable2.GetIntegerValue( L"id" )->SetNull();
			//�������� �������� ��� ���� value
			valueTable2.GetStringValue( L"value" )->Set( L"������ ���" );

			//������� ����� ������ � �������
			table->Insert( transaction, valueTable );

			//������� ������ �������
			sqlite::InsertValue insertValue( table );
			insertValue.Add( valueTable );
			insertValue.Add( valueTable2 );
			//������� ������ � �������
			insertValue.Exec( transaction );
			//��������� ����������
			transaction.Commit();


						
			//�������� ������ ��� ������� �� ������� � ������ ��������� ��� �������
			auto query = table->GetQueryWhereRecordSet();	
			//query.Where( L"id", L"" );

			//��������� ����������
			sqlite::Transaction transaction2( database );
			
			//��������� ������ � ������� ��
			auto stmt = query( transaction2 );
				
			//��������� ����������
			transaction2.Commit();

			//������������ ������ �� �������
			while( const auto value = stmt->Step() )
			{
				//�������� ������ ��� ���� id
				auto id = value->GetIntegerValue( L"id" )->Get();
				//�������� ������ ��� ���� value
				auto data = value->GetStringValue( L"value" )->Get();
				//������� �� �����
				std::cout << "id: " << id << " value: " << culture::w2utf8( data ) << std::endl;
			}		
	}
	catch (const std::exception& exp )
	{
		GTEST_FATAL_FAILURE_( exp.what() );
	}
}
//=====================================================================================================================

