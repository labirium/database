/// @file 
/// @brief ���� �������� ���������� ������� ��� ����������� � ���� ������.

#pragma once

namespace sqlite
{
/// @brief �������� ������ ��� ����������� � ��
///
class Database : boost::noncopyable
{
public:
    /// @brief ������������ ������� ������� ���������� � ��������� ��
	///
	/// @param[in] path ���� � ��
	/// @param[in] readonly ���� ������ �� ������
    Database( const boost::filesystem::path& path, const bool readonly );
	/// @brief ����������
	///
    ~Database() throw();
public:
	/// @brief ��������� ������ � ��
	///
	/// @param[in] queries ������ � ��
	/// @return ���������� ���������� ������� ������ ���� ��������������/���������.
    int Exec(const std::wstring& queries) const;
public:
	public:
	/// @brief ���������� ������ �� ����������� � ��
	///
	sqlite3* GetSqlite( void ) const throw();	
	/// @brief ���������� �������� ������
	///
	std::string GetErrMessage( void ) const throw();
	/// @brief ���������� ���� � ��
	///
    const boost::filesystem::path& GetPath( void ) const throw();
private:
	///< ������ ��� ����������� � ��
    sqlite3* sqlite_;   
	///< ���� � ���� ������
    const boost::filesystem::path path_;
};
}  
