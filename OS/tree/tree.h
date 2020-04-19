
#ifndef TREE_H
#define TREE_H


#include <dirent.h>	// DIR
#include <string>
#include <memory> /*unique_ptr */
#include <vector>

using std::string;
namespace ilrd
{



class File
{
public:
	explicit File(const string& file_name);		
	virtual void Display(int indent =0) const;	
	virtual ~File();
        string GetName();
        virtual std::shared_ptr<File> Find(const string& path);
	
protected:
	string m_name;
private:
	//disabled
	void operator=(const File& other);
	File(const File& other);
};


class Directory: public File
{
public:
	Directory(const string& file_name);
	
	void Display(int indent = 0) const;
	
	std::shared_ptr<File> Find(const string& path);	
	static std::shared_ptr<Directory> BuildTree(const string& file_name);
private:

	std::vector<std::shared_ptr<File>> m_files;
	
};


}//namespace ilrd


#endif /*TREE_H*/