/// @file 
/// @brief ���� �������� ���������� ������������� ������ � ��������� �������/���������

#pragma once

/// ��������������� �����
namespace culture
{
/// @brief ����������� ������ � utf8
///
/// @param[in] source ���� � �����
inline std::string w2utf8( const boost::filesystem::path& source )
{
	return boost::locale::conv::utf_to_utf<char>( source.wstring() );
}
/// @brief ����������� ������ � utf8
///
/// @param[in] source ������ �� ��������������
inline std::string w2utf8( const std::wstring& source )
{
	return boost::locale::conv::utf_to_utf<char>( source );
}
/// @brief ����������� utf8 � ������
///
/// @param[in] source ������ �� ��������������
inline std::wstring utf2w( const std::string& source )
{
	return boost::locale::conv::utf_to_utf<wchar_t>( source );
}
}