/// @file 
/// @brief Файл содержит реализацию классов для вставки полей в таблицу

#include <database/include/precompiled.h>

namespace sqlite
{
//=====================================================================================================================
std::wstring DeleteValue::operator()( void ) const
{
	const std::wstring& tablename = tableName_;
	std::wstringstream stream;

	std::for_each
	( 
		std::begin( valueTableList_ ), 
		std::end( valueTableList_ ),
		[&stream, tablename ]( const ValueTable& valueTable )
		{

			FieldPtr fieldFind;
			for (auto field : valueTable.GetFieldDeclarationTable()()){
				if (!field->GetPrimaryKey()){
					continue;
				}

				fieldFind = field;
				break;
			}

			if (nullptr == fieldFind){
				return;
			}

			stream << L"DELETE FROM " << tablename << " WHERE " << fieldFind->GetName() << " = ";
			if (fieldFind->GetFieldType() == enums::FieldType::Integer){
				stream  << valueTable.GetIntegerValue(fieldFind->GetName())->Get() << L"; ";
			}
			else if (fieldFind->GetFieldType() == enums::FieldType::Float){
				stream << valueTable.GetFloatValue(fieldFind->GetName())->Get() << L"; ";
			}
			else if (fieldFind->GetFieldType() == enums::FieldType::Text){
				stream << valueTable.GetStringValue(fieldFind->GetName())->Get() << L"; ";
			}
		}
	);

	return stream.str();
}
//=====================================================================================================================
void DeleteValue::Add(const sqlite::ValueTable& data)
{
	valueTableList_.push_back( data );
}
//=====================================================================================================================
void DeleteValue::Exec(const sqlite::Transaction& transaction) const
{
	const auto& data = this->operator()();
	if( !data.length() ){
		throw sqlite::Exception( "Don't set value." );
	}

	//Выполняем
	transaction().Exec( data );
}
//=====================================================================================================================
DeleteValue::DeleteValue(const sqlite::Table& table) : tableName_(table.GetName())
{
}
//=====================================================================================================================
DeleteValue::DeleteValue(const sqlite::TablePtr& table) : tableName_(table->GetName())
{
	assert( table && "Invalid input data" );
}
//=====================================================================================================================
DeleteValue::~DeleteValue()
{
}
//=====================================================================================================================
}
