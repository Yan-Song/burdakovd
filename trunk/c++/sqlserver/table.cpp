#ifndef TABLE_CPP
#define TABLE_CPP
#include "macro.hpp"
#include "table.hpp"
#include "exceptions.hpp"
#include <fstream>
#include <cstdio>
#include <cassert>

vector<string> split(const string& s, const char d)
{
    vector<string> ans;
    int prev=-1;
    do
    {
        int cur=s.find_first_of(d, prev+1);
        ans.push_back(s.substr(prev+1,cur-prev-1));
        prev=cur;
    }
    while (prev!=string::npos);
    return ans;
}

string Table::encode(const string& s)
{
	string ans(s.size()*2,'?');
	for(int i=0; i<s.size(); i++)
	{
        //debug((unsigned char)s[i]);
        unsigned char c = s[i];
        if (c<0 || c>256) throw CorruptedData();
		ans[2*i] = 'A' + (c/16);
		ans[2*i+1] = 'A' + (c%16);
	};
	return ans;
}

string Table::decode(const string& s)
{
	string ans(s.size()/2,'?');
	for(int i=0; i<ans.size(); i++)
		ans[i] = 16 * (s[2*i]-'A') + (s[2*i+1]-'A');
	return ans;
}

string Table::vencode(const vector<string>& v)
{
    string ans="";
	vector<string> vans;
	for(int i=0; i<v.size(); i++)
        vans.push_back(encode(v[i]));
    foreach(i,v)
        ans+=(i?";":"")+vans[i];
    return ans;
}

vector<string> Table::vdecode(const string& s)
{
    vector<string> v=split(s,';'),vans;
    for(int i=0; i<v.size(); i++)
        vans.push_back(decode(v[i]));
    return vans;
}

void Table::filenames()
{
    filename=path+"/"+table+".db";
    meta = filename+".meta";
}

Table::Table(string _path, string tablename): path(_path), table(tablename)
// загружаем в память таблицу
{
    filenames();
	
	// read metadata
	ifstream fmeta(meta.c_str(), ios::in);
	if(!fmeta)
		throw TableNotFound();
	string sfields, sfieldtypes;
	fmeta>>sfields>>sfieldtypes;
	fields=vdecode(sfields);
    fieldtypes=vdecode(sfieldtypes);
	fmeta.close();
	
	// read main data
    ifstream fdata(filename.c_str(),ios::in);
    if(!fdata)
        throw TableDataNotFound();
    string encsrow;
    while(fdata>>encsrow)
    {
        vector<string> srow=vdecode(encsrow);
        vector<Field> row;
        foreach(i,srow)
            row.push_back(Field(fieldtypes[i],srow[i]));
        rows.push_back(row);
    }
    fdata.close();
	
}

Table::Table(string _path, string tablename, vector<string> _fields, vector<string> _fieldtypes): path(_path), table(tablename)
{
    fields = _fields;
    fieldtypes = _fieldtypes;
}

void Table::save()
{
    filenames();
    
    // save metadata
    ofstream fmeta(meta.c_str(),ios::out);
    if(!fmeta)
        throw FileError();
    string sfields=vencode(fields), sfieldtypes=vencode(fieldtypes);
    fmeta<<sfields<<endl<<sfieldtypes<<endl;
    fmeta.close();
    
    // save main data
    ofstream fdata(filename.c_str(),ios::out);
    if(!fdata)
        throw FileError();
    foreach(i,rows)
    {
        vector<string> tmp;
        foreach(j,rows[i])
            tmp.push_back(rows[i][j].data);
        fdata<<vencode(tmp)<<endl;
    }
    fdata.close();
}

void Table::removeIt()
{
    filenames();
    remove(filename.c_str());
    remove(meta.c_str());
}

Database::Database(const string& _path): path(_path)
{

}

Table Database::meta()
{
    try
    {
        return Table(path, "meta");
    }
    catch(TableNotFound)
    {
        vector<string> f, tf;
        f.push_back("tablename");
        tf.push_back("STRING");
        return Table(path, "meta", f, tf);
    }
}

Database::~Database()
{
    //
}

vector<string> Database::listTables()
{
    Table m=meta();
    vector<string> ans;
    foreach(i,m.rows)
        ans.push_back(m.rows[i][0].data);
    return ans;
}

Table Database::createTable(string tablename, vector<string> _fields, vector<string> _fieldtypes)
{
    vector<string> lst=listTables();
    foreach(i,lst)
        if(lst[i]==tablename)
            throw TableAlreadyExists();
    if("meta"==tablename) throw TableAlreadyExists();

    Table m=meta();
    vector<Field> row;
    row.push_back(Field("STRING", tablename));
    m.rows.push_back(row);
    m.save();
    Table q(path, tablename,_fields, _fieldtypes);
    q.save();
    return q;
}

void Database::deleteTable(string tablename)
{
    Table m=meta();
    foreach(i,m.rows)
        if(m.rows[i][0].data==tablename)
        {
            m.rows.erase(m.rows.begin()+i,m.rows.begin()+i+1);
            m.save();
            Table(path, tablename).removeIt();
            return;
        }
    throw TableNotFound();
}

#endif
