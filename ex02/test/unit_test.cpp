//
// Created by ivan on 27/10/17.
//
#include <string>
#include "gtest/gtest.h"
#include "../src/backup_builder.h"
#include <fstream>
#include <sstream>

using namespace std;

TEST(BackupBuilder, Diff){
    system("rm -r .vcs_info_dir");
    system("rm test.txt");
    system("rm difftest.txt");
    system("rm diff.txt");
    backup_builder b=backup_builder(fs::path(std::string(get_current_dir_name())));
    fs::path file = fs::path(std::string(get_current_dir_name())) / std::string("test.txt");
    fs::path file2 = fs::path(std::string("test.txt"));
    std::ofstream os(file);
    os << "Test Line";
    os.close();
    fs::path difffile = fs::path(std::string(get_current_dir_name())) / std::string("difftest.txt");

    std::ofstream os2(difffile);
    os2 << "Test Line\nTest Line 2";
    os2.close();
    system("diff test.txt difftest.txt > diff.txt");
    fs::path diff = fs::path(std::string(get_current_dir_name())) / std::string("diff.txt");
    b.initial_copy(file2);
    std::ofstream os3(file);
    os3 << "Test Line\nTest Line 2";
    os3.close();
    b.diff(file2,{0},1);
    fs::path testdiff = fs::path(std::string(get_current_dir_name())) / std::string(".vcs_info_dir") / std::string("1") / std::string("test.txt");
    std::ifstream in (diff);
    std::ifstream in2 (testdiff);

    string str(static_cast<stringstream const&>(stringstream() << in.rdbuf()).str());
    string str2(static_cast<stringstream const&>(stringstream() << in2.rdbuf()).str());

    ASSERT_EQ(str,str2);

}


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

