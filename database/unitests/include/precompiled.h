/// @file 
/// @brief Файл содержит список хедаров для осуществления предварительной сборки заголовков

#pragma once

/// @brief Дружественный класс для unitest сборки
#define FRIENT_UNITEST friend class ::testing::Test;

//WINDOWS
#include <database/include/targetver.h>
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN            

//GTEST
#include <gtest/gtest.h>
//DataBase
#include <database/database.h>
