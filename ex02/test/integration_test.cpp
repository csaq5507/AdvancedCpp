//
// Created by ivan on 27/10/17.
//
#include "gtest/gtest.h"
#include "../src/vcs_utility.h"
#include <fstream>
#include <sstream>
#include <string>

#include <experimental/filesystem>
#include <vector>

using namespace std;
using namespace std::experimental::filesystem;

TEST(vcs_utility_backup_builder, commit){
    Vcs init = Vcs();
    if(!init.is_vcs_initialized())
        init.init_vcs();
    Vcs test = Vcs();

    path testfile =path("test_file");
    std::ofstream file_to_commit(testfile);
    file_to_commit << "Hallo" <<std::endl;
    file_to_commit.close();
    ASSERT_NO_THROW(test.commit("Test Commit"));
    path committet_file=std::string(".vcs_info_dir") / std::string("user_file_dir") / std::string("test_file");
    std::ifstream committet(committet_file);
    std::ifstream testie(testfile);

    string str(static_cast<stringstream const&>(stringstream() << committet.rdbuf()).str());
    string str1(static_cast<stringstream const&>(stringstream() << testie.rdbuf()).str());
    ASSERT_EQ(str,str1);


}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

