/// @file 
/// @brief ���� �������� ���������� ������� ��� ������������ �������.

#pragma once

namespace sqlite
{
namespace enums
{
/// ��� ����������
typedef enum tagOrderByType
{
	/// ASC
	ASC,
	/// DESC
	DESC
}OrderByType;
}

/// @brief ����� ������������ ������������ �������
///
class Query
{
	friend Table;
protected:
    /// @brief �����������
	///
	/// @param[in] table ��������� �� �������� �������
	explicit Query( const TablePtr& table );
	/// @brief �����������
	///
	/// @param[in] table �������� �������
	explicit Query( const Table& table );
public:
    /// @brief ����������
	///
    ~Query() throw();
public:
	/// @brief ������������ ������� � ��
	///
	/// @param[in] transaktion ���������� � ������ ������� ���� ��������� � ��
	StmtPtr operator()( const Transaction& transaktion ) const;
public:
	/// @brief ������ ��� ����������
	///
	/// @param[in] name ��� ���������
	/// @param[in] type ��� ����������
	Query& OrderBy( const std::wstring& name, enums::OrderByType type = enums::ASC );
	/// @brief ������������ ������ ����������� ��������� ( LIMIT = N )
	///
	/// @param[in] limit ����� � �������
	Query& Limit( const unsigned int limit );
	/// @brief ��������� ������ ������������ �������
	///
	/// @param[in] whereTable ������
	void Where( const std::wstring& whereTable );
private:
	///< ������ �������
	std::vector<std::wstring> where_;
	///< ����������
	std::wstring orderBy_;
	///< ����������� �������
	std::wstring limit_;
private:
	///< �������� �������
    const FieldDeclarationTablePtr fieldDeclarationTable_;
	///< �������� �������
    const std::wstring tableName_;
};
}
