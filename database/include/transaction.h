/// @file 
/// @brief Файл содержит описание классов для осуществления работы транзакции в базе данных.

#pragma once

namespace sqlite
{
/// @brief Класс реализует работу с транзакцией БД
///
class TransactionImp : boost::noncopyable
{
public:
	/// @brief Конструктор. Осуществляет открытие транзакции в БД
	///
	/// @param[in] database Описание БД
    explicit TransactionImp( const DatabasePtr& database );
	/// @brief Дестурктор
	///
    ~TransactionImp() throw(); 
public:
    /// @brief Осуществляет коммит в БД
	///
    void Commit( void );
public:
	/// @brief Возвращает описание БД в рамках которой открыта транзакция
	///
	DatabasePtr GetDataBase( void ) const throw();
private:
	///< Описание БД
    const DatabasePtr database_;
	///< Состояние коммита
    bool commited_; 
};

/// @brief Класс предоставляет интерфейс по работе с транзакцией БД
///
class Transaction
{
public:
	/// @brief Конструктор. Осуществляет открытие транзакции в БД
	///
	/// @param[in] database Описание БД
    explicit Transaction( const DatabasePtr& database );
	/// @brief Дестурктор
	///
    ~Transaction() throw(); 
public:
    /// @brief Осуществляет коммит в БД
	///
    void Commit( void );
public:
	/// @brief возвращает описание БД в рамках которой открыта транзакция
	///
	DatabasePtr GetDataBase( void ) const throw();
	/// @brief возвращает описание БД в рамках которой открыта транзакция
	///
	const Database& operator()()  const;
private:
	///<Транзакция БД
    const TransactionImpPtr transactionImp_;
};
}
