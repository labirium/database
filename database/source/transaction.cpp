/// @file 
/// @brief Файл содержит реализацию классов для осуществления работы транзакции в базе данных.

#include <database/include/precompiled.h>

namespace
{
/// Строка BEGIN
const wchar_t* const BEGIN =  L"BEGIN";
/// Строка ROLLBACK
const wchar_t* const ROLLBACK =  L"ROLLBACK";
/// Строка COMMIT
const wchar_t* const COMMIT =  L"COMMIT";
}

namespace sqlite
{
//=====================================================================================================================
TransactionImp::TransactionImp( const DatabasePtr& database ) : database_(database),  commited_( false )
{
	if( !database_ )
	{
		assert( !"Invalid input data" );
		throw sqlite::Exception( "Invalid input data" );
	}

    database_->Exec( BEGIN );
}
//=====================================================================================================================
TransactionImp::~TransactionImp() throw()
{
    if(false == commited_ )
    {
        try
        {
            database_->Exec( ROLLBACK );
        }
        catch (const sqlite::Exception& ex )
        {
			ex.what();
			assert( "Error's commit." && ex.what() );
        }
    }
}
//=====================================================================================================================
DatabasePtr TransactionImp::GetDataBase( void ) const throw()
{
	return database_;
}
//=====================================================================================================================
void TransactionImp::Commit()
{
    if( false == commited_ )
    {
        database_->Exec( COMMIT );
        commited_ = true;
		return;
    }
    
	throw sqlite::Exception( "Transaction already commited" );
}
//=====================================================================================================================
Transaction::Transaction( const DatabasePtr& database ) : transactionImp_( std::make_shared<TransactionImp>( database ) )
{
}
//=====================================================================================================================
Transaction::~Transaction() throw()
{
}
//=====================================================================================================================
DatabasePtr Transaction::GetDataBase( void ) const throw()
{
	return transactionImp_->GetDataBase();
}
//=====================================================================================================================
const Database& Transaction::operator()()  const
{
	return *transactionImp_->GetDataBase();
}
//=====================================================================================================================
void Transaction::Commit()
{
    transactionImp_->Commit();
}
//=====================================================================================================================
}  

