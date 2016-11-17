/// @file 
/// @brief ���� �������� �������� ������� ��� ������������� ������ ���������� � ���� ������.

#pragma once

namespace sqlite
{
/// @brief ����� ��������� ������ � ����������� ��
///
class TransactionImp : boost::noncopyable
{
public:
	/// @brief �����������. ������������ �������� ���������� � ��
	///
	/// @param[in] database �������� ��
    explicit TransactionImp( const DatabasePtr& database );
	/// @brief ����������
	///
    ~TransactionImp() throw(); 
public:
    /// @brief ������������ ������ � ��
	///
    void Commit( void );
public:
	/// @brief ���������� �������� �� � ������ ������� ������� ����������
	///
	DatabasePtr GetDataBase( void ) const throw();
private:
	///< �������� ��
    const DatabasePtr database_;
	///< ��������� �������
    bool commited_; 
};

/// @brief ����� ������������� ��������� �� ������ � ����������� ��
///
class Transaction
{
public:
	/// @brief �����������. ������������ �������� ���������� � ��
	///
	/// @param[in] database �������� ��
    explicit Transaction( const DatabasePtr& database );
	/// @brief ����������
	///
    ~Transaction() throw(); 
public:
    /// @brief ������������ ������ � ��
	///
    void Commit( void );
public:
	/// @brief ���������� �������� �� � ������ ������� ������� ����������
	///
	DatabasePtr GetDataBase( void ) const throw();
	/// @brief ���������� �������� �� � ������ ������� ������� ����������
	///
	const Database& operator()()  const;
private:
	///<���������� ��
    const TransactionImpPtr transactionImp_;
};
}
