/// @file 
/// @brief ���� �������� ���������� ������� ��� ������������� �������� ��� �������� ���� ������.

#include <database/include/precompiled.h>

namespace sqlite
{
//=====================================================================================================================
const std::wstring& Table::GetName( void ) const
{
	return name_;
}
//=====================================================================================================================
const FieldDeclarationTable& Table::GetFieldDeclarationTable( void ) const
{
	return *fieldDeclarationTable_;
}
//=====================================================================================================================
const FieldDeclarationTablePtr Table::GetFieldDeclarationTablePtr( void ) const
{
	return fieldDeclarationTable_;
}
//=====================================================================================================================
Query Table::GetQueryWhereRecordSet( void ) const
{
	return Query( *this );
}
//=====================================================================================================================
void Table::Create( const Transaction& transaktion ) const
{
	std::wostringstream stream;
	//��������� ������
	stream << L"CREATE TABLE " << name_ << L" ( " << (*fieldDeclarationTable_)() << L" )";
	//��������� ������
	transaktion().Exec( stream.str() );	
}
//=====================================================================================================================
void Table::Drop( const Transaction& transaktion ) const
{
	std::wostringstream stream;
	stream << L"DROP TABLE IF EXISTS " << name_;

	transaktion().Exec( stream.str() );
}
//=====================================================================================================================
void Table::Insert( const sqlite::Transaction& transaktion, const sqlite::ValueTable& valueTable ) const
{
	//������� ������ �������� ��� ������� �������
	sqlite::InsertValue inserter( *this );
	inserter.Add( valueTable );
	//���������
	inserter.Exec( transaktion );
}
//=====================================================================================================================
void Table::Delete(const sqlite::Transaction& transaktion, const sqlite::ValueTable& valueTable) const
{
	//������� ������ �������� ��� ������� �������
	sqlite::DeleteValue deleter(*this);
	deleter.Add(valueTable);
	//���������
	deleter.Exec(transaktion);
}
//=====================================================================================================================
Table::Table( const std::wstring& name, const sqlite::FieldDeclarationTable& fieldDeclarationTable ) 
	: name_( name ), fieldDeclarationTable_( std::make_shared<FieldDeclarationTable>( fieldDeclarationTable ) )
{
}
//=====================================================================================================================
Table::~Table()
{
}
//=====================================================================================================================
}
