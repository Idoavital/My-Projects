/*
 * tree app !
 * the app show all the file and the directory of the path that get from the user
 * 
 * 
 */

/* 
 * File:   tree.cpp
 * Author: ido
 *
 * Created on February 20, 2018, 3:30 PM
 */

#include <cstdlib>
#include <string.h>  /*strcmp */
#include <stdexcept> /*exep   */
#include <dirent.h> /*opendir */
#include <iostream> /*cout    */
#include <algorithm> 

#include "tree.h"

using  std::string;
using  std::cout;
namespace ilrd
{
/*
 * 
 */
  
 /*******************************************************************************/ 
/***********************static functoin****************************************/
 /* get the last name */
static string GetLast (const std::string& str)
{ 
   std::size_t found = str.find_last_of("/\\");
   return str.substr(found+1);     
}

/*get the first name */
static string GetFirst(const std::string& str)
{ 
   std::size_t found = str.find_first_of("/\\");
   return str.substr(0,found);     
}

/* spilt the first name */
static string LessFirst(const std::string& str)
{ 
   std::size_t found = str.find_first_of("/\\");
   return str.substr(found+1);     
}

/*******************************************************************************/
/*************************private class ***************************************/

class DirHandle
{
public:
	DirHandle(const string dir_name);
	~DirHandle();
        operator DIR*();
private:
	DIR *m_dir;
};

/*******************************************************************************/
/*************************functor class ***************************************/
/*  display*/
class displayName
{
public:
    displayName(int i = 0):m_i(i){};
  void operator() (const std::shared_ptr<File> & file)
  {
    
    if (file!=NULL)
      {
        m_i++; 
        /* print space */
        for (int j = 0; j < m_i;j++)
          {
            cout<<"│   ";
          }     
        file->Display(m_i);      
        m_i--;
      }
    
  }
private:
   int m_i; /* for the indent */
};

class FindName
{
public:
  FindName (string name):m_name(name){}
  bool operator()(const std::shared_ptr<File> & file)
  {
    if (file != NULL)
      {
        if (0 == (m_name.compare (file->GetName() )))
        {   
          return true;
        }
     }
  return false;
  }
  
private:
  string m_name;
};
/*******************************************************************************/
/**************************BuildTree   *****************************************/
std::shared_ptr<Directory> Directory::BuildTree(const string& file_name)
{
  
    DirHandle dir (file_name);
	std::shared_ptr<Directory> dir_ptr(new Directory(GetLast(file_name)));

	if (NULL == dir)
	{
		dir_ptr->m_files.push_back(std::shared_ptr<File>(new File("error open :"+file_name)));
		return dir_ptr;
	}
    struct dirent *entry;
 

    while ((entry = readdir(dir)) != NULL) 
    {
            if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                continue;

            if(entry->d_type == DT_DIR)
            {
                //std::cout<<file_name + '/' + entry->d_name<<(entry->d_name)<<std::endl;              
                dir_ptr->m_files.push_back( BuildTree(file_name + '/' + entry->d_name));
                
            }
            else if(entry->d_type == DT_REG)
            {
               // std::cout<<"file : "<<(entry->d_name)<<std::endl;
                dir_ptr->m_files.push_back(std::shared_ptr<File>(new File(entry->d_name)));
            }     
         
    }
    return dir_ptr;

}
/*******************************************************************************/
/*****************class File   ************************************************/
 File::File(const string& file_name):m_name(file_name)
 {
 }
 File::~File()
 { 
 }
 
 /* display  the name of the file */
 void File::Display(int indent ) const
 {
   std::cout<<"├──"<<m_name<<std::endl;
 }
 
 string  File::GetName()
 {
   return m_name;
 }
 
 std::shared_ptr<File> File::Find(const string& path)
 {
   if (path.compare (m_name)==0)
     {
       return std::shared_ptr<File> (this);
     }
   return NULL;
 }
 /*******************************************************************************/
/*****************class Directory  ********************************************/
 
Directory::Directory(const string& file_name):File(file_name),m_files(2,0)
{
   
}

/* display all the tree sub tree */
void Directory::Display(int indent) const
 { 
    File::Display (indent);
    for_each (m_files.begin (),m_files.end (), displayName(indent));
 }

/* find the  dir name from the base path */
std::shared_ptr<File> Directory::Find(const string& path)
{
  std::vector<std::shared_ptr<File>>::iterator it_find;
  string first = GetFirst (path);
  string last = GetLast (path);
  
  
  it_find =std::find_if (m_files.begin (),m_files.end (),FindName(GetFirst (path)) );
  
  if ( it_find != m_files.end() && last.compare (GetFirst (path)) )
    {
      
      return (*it_find)->Find(LessFirst(path));
    }

      return std::shared_ptr<File>(new File("canot open file "+path));
 
}

/*******************************************************************************/
/****************class DirHandle  ********************************************/
DirHandle::DirHandle(const string dir_name)
{
    m_dir = opendir(dir_name.c_str ());
   /* if (m_dir == NULL)
      {

        //throw std::invalid_argument( "can not open dir" );
      } */ 
}
DirHandle::~DirHandle()
{
    closedir(m_dir);
}

DirHandle::operator DIR*()
{
  return m_dir;
}
	

}//namespace ilrd