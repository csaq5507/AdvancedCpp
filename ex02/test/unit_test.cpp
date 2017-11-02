//
// Created by ivan on 27/10/17.
//
#include <string>
#include "gtest/gtest.h"
#include "../backup_builder.h"

TEST(BackupBuilder, Diff){
    backup_builder b(fs::path(std::string(get_current_dir_name())));
    fs::path file = fs::path(std::string(get_current_dir_name())) / std::string("test.txt");
    std::ofstream os(file);
    os << "Test Line";
    os.close();
    fs::path difffile = fs::path(std::string(get_current_dir_name())) / std::string("difftest.txt");
    std::ofstream os2(file);
    os2 << "Test Line\nTest Line 2";
    os2.close();
}

TEST(BackupBuilder, Patch){
}

TEST(BackupBuilder, initial_copy){
}

TEST(, ){
}


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

