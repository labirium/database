/// @file 
/// @brief ���� �������� ������ ������� ��� ������������� ��������������� ������ ����������

#pragma once

/// @brief ������������� ����� ��� unitest ������
#define FRIENT_UNITEST friend class ::testing::Test;

//WINDOWS
#include <database/include/targetver.h>
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN            

//GTEST
#include <gtest/gtest.h>
//DataBase
#include <database/database.h>
