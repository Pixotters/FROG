#include <iostream>
#include <SFML/Graphics.hpp>
#include "FROG/AssetManager.hpp"
#include "FROG/GameObject.hpp"

static int LOAD_COUNT = 0;

#include "TestFile.hpp"
//typedef sf::Texture Tex;

void loadFromFile(const std::string& path, const std::string& id) 
throw (std::runtime_error)
{
  std::unique_ptr<TestFile> pr(new TestFile() );  
  LOAD_COUNT++;
  if( not pr->loadFromFile(path) )
    {
      std::string err = "Impossible to create asset because a problem ";
      err += "problem occured while loading " + path;
      throw std::runtime_error(err);
          
    }
}



int main(int charc, char ** argv)
{  
  int ceiling = 1000;
  if(charc >= 3)
    {
      ceiling = atoi(argv[2]);
    }
  if(charc >= 2)
    {
      std::cout << "Performing "<<ceiling<<" loadings "<<std::endl;

      if( * argv[1] == '0')
        {
          // no asset manager
          LOAD_COUNT = 0;
          for(int i = 0; i < ceiling; i++)
            loadFromFile("test.png", "a");
          std::cout<< "Without AssetManager -> "<<LOAD_COUNT<<"/"<<ceiling<<std::endl;
        }else{
        // using asset manager
        frog::AssetManager<std::string, TestFile> am;
        for(int i = 0; i < ceiling; i++)
          am.loadFromFile("makelog", "a");
        std::cout<< "With AssetManager -> "<<am.getLoadCount()<<"/"<<ceiling<<std::endl;

      }
    }
  std::cout << "Ending..." <<std::endl;
}
