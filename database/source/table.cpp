/// @file 
/// @brief Файл содержит реализацию классов для осуществления операций над таблицей базы данных.

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
	//Формируем запрос
	stream << L"CREATE TABLE " << name_ << L" ( " << (*fieldDeclarationTable_)() << L" )";
	//Выполняем запрос
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
	//Создаем группу операций для текущей таблицы
	sqlite::InsertValue inserter( *this );
	inserter.Add( valueTable );
	//Выполняем
	inserter.Exec( transaktion );
}
//=====================================================================================================================
void Table::Delete(const sqlite::Transaction& transaktion, const sqlite::ValueTable& valueTable) const
{
	//Создаем группу операций для текущей таблицы
	sqlite::DeleteValue deleter(*this);
	deleter.Add(valueTable);
	//Выполняем
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
